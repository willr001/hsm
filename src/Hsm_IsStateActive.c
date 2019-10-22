#include "Hsm_IsStateActive.h"
#include "Hsm_IsStateInBranch.h"
#include <stdlib.h>

bool Hsm_IsStateActive(Hsm *state)
{
    bool rval = false;
    Hsm *active = state ? state->active : NULL;

    while (!rval && active)
    {
        rval = Hsm_IsStateInBranch(state,active);
        active = active->active;
    }

    return rval;
}


