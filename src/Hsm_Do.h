#ifndef _HSM_DO_H
#define _HSM_DO_H

#include "Hsm.h"

/***********************************************************************************************//**
 *  \brief Will handle processing of an \p event through the \p state_machine.
 *
 *  \details This function will activate \p state_machine if not already active, process the event, 
 *  and return the result of event processing. Any transitions or generated events due to the passed 
 *  event will be processed as well, until a stable state configuration is reached before returning.
 *
 *  \param state_machine  A pointer to the root (or other) state of a state machine.
 *  \param event          A pointer to the event to be processed.
 *
 *  \returns enum indicating status of event
 *
 *  \post \p event and any triggered internal events/transitions/recalling of deferred events were 
 *  processed to completion.
 *
 *  \test an active state machine is checked for active, processes event, and returns result
 *  \test an inactive state machine is initialized after check and then passed the event
 *  \test a null state_machine returns an error
 *  \test a null event returns an error
 *  \test a PerformTransit error returns the error and doesn't call ProcessEvent
 **************************************************************************************************/
HsmResult Hsm_Do(Hsm *state_machine, HsmEvent *event);

#endif // _HSM_DO_H
