#ifndef ANALYZER_H
#define ANALYZER_H

#include <QList>
#include "../utils/my_const.h"

namespace Analyzer
{

/*
 * Renvoie un tableau contenant la table de vérité de la fonction arb
 */
QList<QList<QChar>> makeTruthTable(MyBinTree* arb, QStringList const& vars);

/*
 * Renvoie la forme canonique disjonctive de la fonction.
 */
QStringList getDisjForm(QList<QList<QChar>> const& table, QStringList const& vars);

/*
 * Renvoie la forme canonique conjonctive de la fonction.
 */
QStringList getConjForm(QList<QList<QChar>> const& table, QStringList const& vars);

/*
 * Remplace les variables de l'arbre binaire avec leurs valeurs respectives.
 */
void fillTreeWithValues(MyBinTree* arb, QStringList const& vars, QList<QChar> const& values);

/*
 * Analyse l'arbre binaire, supprime tous les noeuds et remplace la racine par le resultat de la fonction.
 */
void getFuncResult(MyBinTree* arb);

}

#endif // ANALYZER_H

