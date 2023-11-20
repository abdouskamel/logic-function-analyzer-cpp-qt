#ifndef SIMPLIFICATOR_H
#define SIMPLIFICATOR_H

#include "../utils/my_const.h"

namespace Simplificator
{

/*
 * Simplie la fonction (doit être sous forme canonique disjonctive).
 */
QStringList simplifyIt(QStringList terms);

/*
 * Effectue les absorbations possibles sur terms.
 */
void doAbsorbation(QStringList& terms);

/*
 * Supprime les consensus se trouvant dans la fonction.
 */
void removeConsensuses(QStringList& terms);

}

#endif // SIMPLIFICATOR_H

