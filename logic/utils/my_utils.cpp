#include "my_utils.h"

namespace MyUtils
{

bool isOperator(QString const& op)
{
    return (op.size() == 1 && THE_OPERATORS.contains(op));
}

bool isOperator(QChar const& op)
{
    return THE_OPERATORS.contains(op);
}

bool isBracket(QString const& op)
{
    return (op == "(" || op == ")");
}

bool isBracket(QChar const& op)
{
    return (op == '(' || op == ')');
}

/*
 * Renvoie true si la variable var est correcte
 */
bool checkVariable(Variable const& var)
{
    int conv(0);
    bool conv_bool(true);

    conv = var.toInt(&conv_bool);
    if(conv_bool && conv != 0 && conv != 1)
    {
        return false;
    }

    for(int i(0); i < var.size(); ++i)
    {
        if(!var[i].isLetterOrNumber())
        {
            return false;
        }
    }

    return true;
}

/*
 * Renvoie les variables de la fonction tokens
 */
QStringList getFuncVars(Tokens const& tokens)
{
    QStringList vars;

    for(int i(0); i < tokens.size(); ++i)
    {
        if(!isOperator(tokens[i]) && !isBracket(tokens[i]) &&
           tokens[i] != "0" && tokens[i] != "1")
        {
            vars << tokens[i];
        }
    }

    vars.removeDuplicates();
    return vars;
}

/*
 * Supprime les parenthèses inutiles des tokens
 */
void removeUselessBrackets(Tokens& tokens)
{
    int brackets(0);

    while(tokens[0] == "(" && tokens.last() == ")")
    {
        brackets = 0;

        for(int i(1); i < tokens.size() - 1; ++i)
        {
            if(tokens[i] == "(")
            {
                brackets++;
            }

            else if(tokens[i] == ")")
            {
                brackets--;
                if(brackets < 0)
                    break;
            }
        }

        if(brackets == 0)
        {
            tokens.removeLast();
            tokens.removeFirst();
        }

        else
        {
            break;
        }
    }
}

/*
 * Supprime les termes égales à a et renvoit le nombre de termes supprimés.
 */
int removeTerm(QStringList& terms, Term const& a)
{
    QStringList a_vars(a.split('.')),
                term_vars;
    int nb_rem(0);

    for(int i(0); i < terms.size(); ++i)
    {
        term_vars = terms[i].split('.');
        for(int j(0); j < a_vars.size(); ++j)
        {
            term_vars.removeAll(a_vars[j]);
        }

        if(term_vars.isEmpty())
        {
            nb_rem += terms.removeAll(terms[i]);
            i -= nb_rem;
        }
    }

    return nb_rem;
}

/*
 * Renvoie true si a et b si a = /b
 */
bool areOpposite(Variable const& a, Variable const& b)
{
    return ((a[0] == '/' && QString(a).remove(0, 1) == b) ||
            (b[0] == '/' && QString(b).remove(0, 1) == a));
}

/*
 * Renvoie une liste contenant les variables des termes a et b
 */
QStringList getAllVars(Term const& a, Term const& b)
{
    QStringList vars = a.split('.') + b.split('.');
    vars.removeDuplicates();

    return vars;
}

/*
 * Renvoie le consensus de a et b.
 * Renvoie "" si il n'y a pas de consensus ou un consensus nul.
 */
QString getConsensus(Term const& a, Term const& b)
{
    QStringList vars = getAllVars(a, b),
                result;
    int nb_opposite = 0;

    for(int i(0); i < vars.size(); ++i)
    {
        if((vars[i][0] != '/' && vars.contains("/" + vars[i])) ||
           (vars[i][0] == '/' && vars.contains(vars[i].right(vars[i].size() - 1))))
        {
            if(nb_opposite > 2)
            {
                return 0;
            }

            nb_opposite += 1;
        }

        else
        {
            result << vars[i];
        }
    }

    if(result.isEmpty() || nb_opposite == 0)
    {
        return "";
    }

    return result.join('.');
}

/*
 * Renvoie le résultat de l'absorption des termes a et b.
 * Si il n'y a pas d'absorption, renvoie une chaine vide.
 */
Term isThereAbsorption(Term const& a, Term const& b)
{
    QStringList result, a_fact, b_fact,
                a_vars = a.split('.'),
                b_vars = b.split('.');

    for(int i(0); i < a_vars.size(); ++i)
    {
        if(!b_vars.contains(a_vars[i]))
        {
            a_fact << a_vars[i];
        }

        else
        {
            result << a_vars[i];
        }
    }

    for(int i(0); i < b_vars.size(); ++i)
    {
        if(!a_vars.contains(b_vars[i]))
        {
            b_fact << b_vars[i];
        }
    }

    if(a_fact.isEmpty() || b_fact.isEmpty() ||
       (a_fact.size() == 1 && b_fact.size() == 1 && areOpposite(a_fact[0], b_fact[0])))
    {
        return result.join(".");
    }

    return QString();
}

/*
 * Construit la ligne n pos d'une table de vérité.
 */
QList<QChar> buildTableRow(int pos, int nb_vars)
{
    QList<QChar> tab_row;
    QString pos_bin = MyUtils::toBinaryStr(pos);

    for(int i(nb_vars - 1); i >= 0; --i)
    {
        if(i < pos_bin.size())
        {
            tab_row.append(pos_bin[i]);
        }

        else
        {
            tab_row.append('0');
        }
    }

    return tab_row;
}

/*
 * Renvoie la forme binaire de nb en chaine de caractères (la chaine est inversée).
 */
QString toBinaryStr(uint64_t nb)
{
    QString result;

    while(nb > 0)
    {
        result.append(QString().setNum(nb % 2));
        nb /= 2;
    }

    return result;
}

}
