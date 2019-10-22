#include "unity.h"
#include "Hsm_Do.h"
#include "mock_Hsm_IsStateActive.h"
#include "mock_Hsm_ProcessTransit.h"
#include "mock_Hsm_ProcessEvent.h"
#include "string.h"

Hsm m_hsm;
HsmEvent m_event;
HsmTransit m_transit;

void setUp(void)
{
    Hsm hsm = {};
    HsmEvent event = HSM_EVENT_FIRST_APPLICATION;
    HsmTransit transit = { .target = &m_hsm };
    memcpy(&m_hsm,&hsm,sizeof(hsm));
    memcpy(&m_event,&event,sizeof(event));
    memcpy(&m_transit,&transit,sizeof(transit));
}

void tearDown(void)
{
}

/*
 *  \test an active state machine is checked for active, processes event, and returns result
 */
void test_Hsm_Do_ActiveStateMachineJustProcessesEvent(void)
{
    unsigned returnVal = 666;
    Hsm_IsStateActive_ExpectAndReturn(&m_hsm,true);
    Hsm_ProcessEvent_ExpectAndReturn(&m_hsm,&m_event,returnVal);
    TEST_ASSERT_EQUAL(returnVal,Hsm_Do(&m_hsm,&m_event));
}

/*
 *  \test an inactive state machine is initialized after check and then passed the event
 */
void test_Hsm_Do_InactiveStateMachineCallsProcessTransit(void)
{
    unsigned returnVal = 1;
    Hsm_IsStateActive_ExpectAndReturn(&m_hsm,false);
    Hsm_ProcessTransit_ExpectAndReturn(&m_hsm,&m_transit,0);
    Hsm_ProcessEvent_ExpectAndReturn(&m_hsm,&m_event,returnVal);
    TEST_ASSERT_EQUAL(returnVal,Hsm_Do(&m_hsm,&m_event));
}

/*
 *  \test a null state_machine returns an error
 */
void test_Hsm_Do_NullStateReturnsError(void)
{
    TEST_ASSERT_EQUAL(HSM_RESULT_DO_ERROR_NULL_STATE_POINTER, Hsm_Do(NULL,&m_event));
}

/*
 *  \test a null event returns an error
 */
void test_Hsm_Do_NullEventReturnsError(void)
{
    TEST_ASSERT_EQUAL(HSM_RESULT_DO_ERROR_NULL_EVENT_POINTER, Hsm_Do(&m_hsm,NULL));
}

/*
 *  \test a ProcessTransit error returns the error and doesn't call ProcessEvent
 */
void test_Hsm_ProcessTransitErrorReturns(void)
{
    unsigned returnVal = 42;
    Hsm_IsStateActive_ExpectAndReturn(&m_hsm,false);
    Hsm_ProcessTransit_ExpectAndReturn(&m_hsm,&m_transit,returnVal);
    TEST_ASSERT_EQUAL(returnVal,Hsm_Do(&m_hsm,&m_event));
}

