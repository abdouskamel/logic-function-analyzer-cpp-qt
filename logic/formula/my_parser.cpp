#include "my_parser.h"
#include "../utils/tokens_exception.h"
#include "../utils/my_utils.h"

namespace MyParser
{

/*
 * Renvoit la liste de token de la fonction.
 * Lance des exceptions si la fonction contient des erreurs.
 */
Tokens tokenizeIt(QString const& function)
{
    Tokens tokens;
    QString var;

    for(int i(0); i < function.size(); ++i)
    {
        if(MyUtils::isOperator(function[i]) || MyUtils::isBracket(function[i]))
        {
            if(!var.isEmpty())
            {
                tokens << var;
                var.clear();
            }

            tokens << QString(function[i]);
        }

        else if(!function[i].isSpace())
        {
            var += function[i];
        }
    }

    if(!var.isEmpty())
    {
        tokens << var;
    }

    checkTokens(tokens);
    return tokens;
}

/*
 * Vérifie si les tokens ne contiennent pas d'erreurs.
 * Peut lancer des exception.
 */
void checkTokens(Tokens const& tokens)
{
    int nb_brackets(0);

    if(tokens.size() == 0)
    {
        throw TokensException("Aucune expression...", tokens, -1);
    }

    if(MyUtils::isOperator(tokens.back()))
    {
        throw TokensException("Opérateur à la fin de l'expression.", tokens, tokens.size() - 1);
    }

    for(int i(0); i < tokens.size(); ++i)
    {
        if(MyUtils::isOperator(tokens[i]))
        {
            if(i < tokens.size() - 1 && MyUtils::isOperator(tokens[i + 1]) && tokens[i + 1] != "/")
            {
                throw TokensException("Deux opérateurs successifs.", tokens, i);
            }
        }

        else if(tokens[i] == "(")
        {
            nb_brackets++;
        }

        else if(tokens[i] == ")")
        {
            if(nb_brackets <= 0)
            {
                throw TokensException("Parenthèse fermante indépendante.", tokens, i);
            }

            nb_brackets--;
        }

        else if(!MyUtils::checkVariable(tokens[i]))
        {
            throw TokensException("Vos variables ne doivent contenir que des caractères alphanumériques.",
                                  tokens, i);
        }

        else if(i < tokens.size() - 1 &&
                (tokens[i + 1] == "/" || !(MyUtils::isOperator(tokens[i + 1]) || tokens[i + 1] == ")")))
        {
            throw TokensException("Deux variables qui se suivent sans opérateur.", tokens, i + 1);
        }
    }

    if(nb_brackets != 0)
    {
        throw TokensException("Veuillez vérifier vos parenthèses.", tokens, -1);
    }
}

/*
 * Construit l'arbre binaire
 */
void makeTheTree(MyBinTree* arb, Tokens tokens)
{
    int brackets(0), the_op(0);
    Tokens left_tok, right_tok;

    if(!tokens.isEmpty())
    {
        if(tokens.size() == 1)
        {
            arb->setValue(tokens[0]);
        }

        else
        {
            MyUtils::removeUselessBrackets(tokens);

            // Récupération de l'opérateur avec la plus basse priorité
            for(int i(0); i < tokens.size(); ++i)
            {
                if(tokens[i] == "(")
                {
                    brackets++;
                }

                else if(tokens[i] == ")")
                {
                    brackets--;
                }

                else if(brackets == 0)
                {
                    if(tokens[i] == "/" && !MyUtils::isOperator(tokens[the_op]))
                    {
                        the_op = i;
                    }

                    else if(tokens[i] == "@" && tokens[the_op] != "." && tokens[the_op] != "+")
                    {
                        the_op = i;
                    }

                    else if(tokens[i] == "." && tokens[the_op] != "+")
                    {
                        the_op = i;
                    }

                    else if(tokens[i] == "+")
                    {
                        the_op = i;
                    }
                }
            }

            left_tok = right_tok = tokens;

            left_tok.erase(left_tok.begin() + the_op, left_tok.end());
            right_tok.erase(right_tok.begin(), right_tok.begin() + the_op + 1);

            arb->setValue(tokens[the_op]);
            if(tokens[the_op] != "/")
            {
                arb->setLeft("");
            }

            arb->setRight("");

            makeTheTree(arb->getLeft(), left_tok);
            makeTheTree(arb->getRight(), right_tok);
        }
    }
}

}
