#ifndef _HSM_DOTRANSIT_H
#define _HSM_DOTRANSIT_H

#include "Hsm.h"

/**
 * \brief Executes a single transit (exits/actions/entries), making the target state[s] active and ready to recieve their initial event.
 **/
HsmResult Hsm_DoTransit(Hsm *state_machine, HsmTransit *transit);

#endif // _HSM_DOTRANSIT_H
