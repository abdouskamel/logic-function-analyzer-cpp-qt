#include "analyzer.h"
#include "../utils/operations.h"
#include "../utils/my_utils.h"

#include <cmath>

namespace Analyzer
{
/*
 * Renvoie un tableau contenant la table de vérité de la fonction arb
 */
QList<QList<QChar>> makeTruthTable(MyBinTree* arb, QStringList const& vars)
{
    QList<QList<QChar>> result;
    QList<QChar> table_row;
    MyBinTree* arb_copy(nullptr);

    for(int cpt(0); cpt < pow(2, vars.size()); ++cpt)
    {
        table_row = MyUtils::buildTableRow(cpt, vars.size());

        delete arb_copy;
        arb_copy = new MyBinTree(*arb);

        fillTreeWithValues(arb_copy, vars, table_row);
        getFuncResult(arb_copy);

        table_row.append(arb_copy->getValue()[0]);
        result.append(table_row);
    }


    delete arb_copy;
    arb_copy = nullptr;

    return result;
}

/*
 * Renvoie la forme canonique disjonctive de la fonction.
 */
QStringList getDisjForm(QList<QList<QChar>> const& table, QStringList const& vars)
{
    QStringList result, term;

    for(int i(0); i < table.size(); ++i)
    {
        if(table[i].last() == '1')
        {
            term.clear();

            for(int j(0); j < table[i].size() - 1; ++j)
            {
                if(table[i][j] == '0')
                {
                    term << "/" + vars[j];
                }

                else if(table[i][j] == '1')
                {
                    term << vars[j];
                }
            }

            result.append(term.join('.'));
        }
    }

    return result;
}

/*
 * Renvoie la forme canonique conjonctive de la fonction.
 */
QStringList getConjForm(QList<QList<QChar>> const& table, QStringList const& vars)
{
    QStringList result, term;

    for(int i(0); i < table.size(); ++i)
    {
        if(table[i].last() == '0')
        {
            term.clear();

            for(int j(0); j < table[i].size() - 1; ++j)
            {
                if(table[i][j] == '1')
                {
                    term << "/" + vars[j];
                }

                else if(table[i][j] == '0')
                {
                    term << vars[j];
                }
            }

            result.append(term.join(" + "));
        }
    }

    return result;
}

/*
 * Remplace les variables de l'arbre binaire avec leurs valeurs respectives.
 */
void fillTreeWithValues(MyBinTree* arb, QStringList const& vars, QList<QChar> const& values)
{
    if(!MyUtils::isOperator(arb->getValue()) && arb->getValue() != "1" && arb->getValue() != "0")
    {
        arb->setValue(values[vars.indexOf(arb->getValue())]);
    }

    if(arb->getLeft() != nullptr)
    {
        fillTreeWithValues(arb->getLeft(), vars, values);
    }

    if(arb->getRight() != nullptr)
    {
        fillTreeWithValues(arb->getRight(), vars, values);
    }
}

/*
 * Analyse l'arbre binaire, supprime tout les noeuds et remplace la racine par le resultat de la fonction.
 */
void getFuncResult(MyBinTree* arb)
{
    if(arb->getValue() != "/" && arb->getLeft() != nullptr &&
       MyUtils::isOperator(arb->getLeft()->getValue()))
    {
        getFuncResult(arb->getLeft());
    }

    if(arb->getRight() != nullptr &&
       MyUtils::isOperator(arb->getRight()->getValue()))
    {
        getFuncResult(arb->getRight());
    }

    QString result(arb->getValue());

    if(arb->getValue() == "+")
        result = mor(arb->getLeft()->getValue(), arb->getRight()->getValue());

    else if(arb->getValue() == ".")
        result = mand(arb->getLeft()->getValue(), arb->getRight()->getValue());

    else if(arb->getValue() == "@")
        result = mxor(arb->getLeft()->getValue(), arb->getRight()->getValue());

    else if(arb->getValue() == "/")
        result = mno(arb->getRight()->getValue());

    arb->setValue(result);
    arb->setLeft(nullptr);
    arb->setRight(nullptr);
}

}
