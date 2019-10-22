#include "Hsm_ProcessTransit.h"
#include "Hsm_DoTransit.h"
#include <string.h>

HsmResult Hsm_ProcessTransit(Hsm *state_machine, HsmTransit *transit)
{
    HsmResult rval = 0;
    HsmEvent event;
    HsmTransit init_transit;
    
    if (!state_machine)
    {
        rval = HSM_RESULT_PROCESS_TRANSIT_ERROR_NULL_STATE;
    }
    else if (!transit)
    {
        rval = HSM_RESULT_PROCESS_TRANSIT_ERROR_NULL_TRANSIT;
    }
    else
    {
        while (!rval && transit->target)
        {
            rval = Hsm_DoTransit( state_machine, transit );
            memset(&init_transit, 0, sizeof(init_transit));

            if (!rval && (transit->target->handler))
            {
                event = HSM_EVENT_INIT;
                (void)transit->target->handler(transit->target, &event, &init_transit); // init event transit is always honored
            }

            memcpy(transit, &init_transit, sizeof(*transit));
        }
    }

    return rval;
}
