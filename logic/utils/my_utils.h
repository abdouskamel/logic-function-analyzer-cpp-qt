#ifndef MY_UTILS_H
#define MY_UTILS_H

#include <QString>
#include <QStringList>
#include "binary_tree.h"
#include "my_const.h"

namespace MyUtils
{

bool isOperator(QString const& op);
bool isOperator(QChar const& op);

bool isBracket(QString const& op);
bool isBracket(QChar const& op);

/*
 * Renvoit true si la variable var est correcte
 */
bool checkVariable(Variable const& var);

/*
 * Renvoit les variables de la fonction tokens
 */
QStringList getFuncVars(Tokens const& tokens);

/*
 * Supprime les parenthèses inutiles des tokens
 */
void removeUselessBrackets(Tokens& tokens);

/*
 * Supprime les termes égales à a et renvoit le nombre de termes
 * supprimés.
 */
int removeTerm(QStringList& terms, Term const& a);

/*
 * Renvoit true si a et b si a = /b
 */
bool areOpposite(Variable const& a, Variable const& b);

/*
 * Renvoit une liste contenant les variables des termes a et b
 */
QStringList getAllVars(Term const& a, Term const& b);

/*
 * Renvoit le consensus de a et b.
 * Renvoit "" si il n'y a pas de consensus ou un consensus nul.
 */
QString getConsensus(Term const& a, Term const& b);

/*
 * Renvoit le résultat de l'absorbation des termes a et b.
 * Si il n'y a pas d'absorbation, renvoit une chaine vide.
 */
Term isThereAbsorbation(Term const& a, Term const& b);

/*
 * Construit la ligne n pos d'une table de vérité.
 */
QList<QChar> buildTableRow(int pos, int nb_vars);

/*
 * Renvoit la forme binaire de nb en chaine de caractères (la chaine est inversée).
 */
QString toBinaryStr(uint64_t nb);

}

#endif // MY_UTILS_
