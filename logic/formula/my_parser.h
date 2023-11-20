#ifndef MY_PARSER_H
#define MY_PARSER_H

#include "../utils/binary_tree.h"
#include "../utils/my_const.h"

namespace MyParser
{

/*
 * Renvoie la liste de token de la fonction.
 * Lance des exceptions si la fonction contient des erreurs.
 */
Tokens tokenizeIt(QString const& function);

/*
 * Vérifie si les tokens ne contiennent pas d'erreurs.
 * Peut lancer des exception.
 */
void checkTokens(Tokens const& tokens);

/*
 * Construit l'arbre binaire
 */
void makeTheTree(MyBinTree* arb, Tokens tokens);

}

#endif // MY_PARSER_H

