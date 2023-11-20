#include "simplificator.h"
#include "../utils/my_utils.h"

namespace Simplificator
{

/*
 * Simplie la fonction (doit être sous forme canonique disjonctive).
 */
QStringList simplifyIt(QStringList terms)
{
    QList<QString> cons_list;
    QString consensus;
    QStringList last_terms;
    bool stop(false);

    doAbsorbation(terms);

    while(!stop)
    {
        stop = true;
        cons_list.clear();

        // Recherche des consensus
        for(int i(0); i < terms.size() - 1; ++i)
        {
            for(int j(i + 1); j < terms.size(); ++j)
            {
                consensus = MyUtils::getConsensus(terms[i], terms[j]);
                if(!consensus.isEmpty())
                {
                    cons_list.append(consensus);
                }
            }
        }

        if(!cons_list.isEmpty())
        {
            terms.append(cons_list);
            doAbsorbation(terms);

            if(terms != last_terms)
            {
                last_terms = terms;
                stop = false;
            }
        }
    }

    removeConsensuses(terms);
    return terms;
}

/*
 * Effectue les absorbations possibles sur terms.
 */
void doAbsorbation(QStringList& terms)
{
    bool absor(false);
    QString facto;

    do
    {
        absor = false;

        for(int i(0); i < terms.size() - 1; ++i)
        {
            for(int j(i + 1); j < terms.size(); )
            {
                facto = MyUtils::isThereAbsorbation(terms[i], terms[j]);
                if(facto.isEmpty())
                {
                    j++;
                }

                else
                {
                    terms[i] = facto;
                    terms.removeAt(j);
                    absor = true;
                }
            }
        }

    } while(absor);
}

/*
 * Supprime les consensus se trouvant dans la fonction.
 */
void removeConsensuses(QStringList& terms)
{
    QString consensus;
    int nb_rem(0);

    // Recherche des consensus
    for(int i(0); i < terms.size() - 1; ++i)
    {
        for(int j(i + 1); j < terms.size(); ++j)
        {
            consensus = MyUtils::getConsensus(terms[i], terms[j]);
            if(!consensus.isEmpty())
            {
                nb_rem = MyUtils::removeTerm(terms, consensus);
                if(nb_rem != 0)
                {
                    i -= nb_rem;
                    break;
                }
            }
        }
    }
}

}
