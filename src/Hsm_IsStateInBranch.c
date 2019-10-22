#include "Hsm_IsStateInBranch.h"

bool Hsm_IsStateInBranch(Hsm *state, Hsm *leaf)
{
    bool rval = false;

    if (state)
    {
        while (!rval && leaf)
        {
            rval = state == leaf;
            leaf = leaf->parent;
        }
    }

    return rval;
}

