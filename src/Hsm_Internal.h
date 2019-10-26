#ifndef HSM_INTERNAL_H
#define HSM_INTERNAL_H

#include "Hsm.h"

static inline Hsm *Hsm_GetParent(Hsm *state) 
{ 
    return state->parent;
}

static inline HsmHandler Hsm_GetHandler(Hsm *state)
{
    return state->handler;
}

static inline HsmMachine *Hsm_GetMachine(Hsm *state) 
{ 
    while (Hsm_GetParent(state)) state = Hsm_GetParent(state);
    return (HsmMachine *)state; 
}

static inline HsmActiveLeaf *Hsm_GetFirstActive(HsmMachine *machine)
{
    return machine->hsm.active;
}

static inline HsmActiveLeaf *Hsm_GetNextActive(HsmActiveLeaf *active)
{
    return (active != active->hsm.active ? active->hsm.active : NULL);
}

#endif

