#ifndef _HSM_PROCESSTRANSIT_H
#define _HSM_PROCESSTRANSIT_H

#include "Hsm.h"

/**
 * \brief Handles a transition and gets the state machine into a stable state
 *
 * \details 
 *      - do transit
 *      - hit active leaves with init events
 *      - if init caused transit, loop
 *
 * \param state_machine The machine containing the transit
 * \param transit       The object defining the transit
 *
 * \return 0 if transit is successuful, else error encountered
 *
 * \test if do transit is successful, inits leaf, return success
 * \test if leaf returns a transit, repeat process, return success
 * \test if transit fails, return its error
 * \test if state_machine is null, return error
 * \test if transit is null, return error
 **/
HsmResult Hsm_ProcessTransit(Hsm *state_machine, HsmTransit *transit);

#endif // _HSM_PROCESSTRANSIT_H
