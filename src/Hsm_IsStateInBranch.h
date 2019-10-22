#ifndef _HSM_ISSTATEINBRANCH_H
#define _HSM_ISSTATEINBRANCH_H

#include "Hsm.h"
#include <stdbool.h>

/**
 * \brief Returns whether \p state is contained within path from \p leaf to root of tree, inclusive.
 *
 * \param state The state to search for
 * \param leaf The state defining the terminus of the branch to search within
 *
 * \returns \c true if state is or is under \c leaf, else false
 *
 * \test returns true for state == leaf
 * \test returns false if state is null
 * \test returns false if leaf is null
 * \test returns true if state is under leaf
 * \test returns false if state is not under leaf
 **/
bool Hsm_IsStateInBranch(Hsm *state, Hsm *leaf);

#endif // _HSM_ISSTATEINBRANCH_H

