#include "Hsm_ProcessTransit.h"
#include <string.h>

HsmResult Hsm_ProcessTransit(Hsm *state_machine, HsmTransit *transit)
{
    HsmResult rval = 0;
    Hsm *leaf;
    HsmEvent event = HSM_EVENT_INIT;

    if (state_machine && transit)
    {
        leaf = state_machine;

        if (((leaf = state_machine->active)) && leaf->handler)
        {
            memset(transit,0,sizeof(*transit));
            leaf->handler(leaf,&event,transit);
        }
    }
    return 0;
}
