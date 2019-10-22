#ifndef _HSM_ISSTATEACTIVE_H
#define _HSM_ISSTATEACTIVE_H

#include "Hsm.h"
#include <stdbool.h>

/**
*            \brief Returns whether \p state is in the current tree of active states.
*
*            \details Will step through list of active leaves, checking if \p state is contained within any
*            of the active branches.
*
*            \param state The state to be checked.
*
*            \returns \c true if \p state exists and is active, else \c false
*
*            \test if within first leaf, don't check any more and return true
*            \test if within third leaf, don't check any more and return true
*            \test if no leaves, return false
*            \test if state is null, return false
*            \test if not within any leaves return false
**/
bool Hsm_IsStateActive(Hsm *state);

#endif // _HSM_ISSTATEACTIVE_H
