#include "Hsm_Do.h"
#include "Hsm.h"
#include "Hsm_IsStateActive.h"
#include "Hsm_ProcessEvent.h"
#include "Hsm_ProcessTransit.h"

HsmResult Hsm_Do(Hsm *state_machine, HsmEvent *event)
{
    HsmResult rval = 0;
    HsmTransit initial_transit = { .target = state_machine };

    if (!state_machine)
    {
        rval = HSM_RESULT_DO_ERROR_NULL_STATE_POINTER;
    }
    else if (!event)
    {
        rval = HSM_RESULT_DO_ERROR_NULL_EVENT_POINTER;
    }
    else 
    {
        if (!Hsm_IsStateActive(state_machine))
        {
            rval = Hsm_ProcessTransit(state_machine,&initial_transit);
        }

        if (!rval)
        {
            rval = Hsm_ProcessEvent(state_machine,event);
        }
    }

    return rval;
}

