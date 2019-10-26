#include "unity.h"
#include "Hsm.h"
#include "Hsm_ProcessTransit.h"
#include "mock_Hsm_DoTransit.h"
#include <string.h>

static HsmHandlerReturn m_handler(Hsm *self, HsmEvent *event, HsmTransit *transit);

static unsigned m_hitcount;
static unsigned m_loop;
static Hsm m_hsm;
static Hsm m_hsm2;
static HsmTransit m_transit;
static HsmTransit m_transit2;

static HsmHandlerReturn m_handler(Hsm *self, HsmEvent *event, HsmTransit *transit) 
{
    if (event && *event == HSM_EVENT_INIT) 
    {
        m_hitcount++;

        if (m_loop)
        {
            *transit = m_transit2;
            m_loop--;
        }
    }

    return HSM_HANDLER_RETURN_IGNORED;
}


void setUp(void)
{
    Hsm hsm = { .handler = &m_handler };
    Hsm hsm2 = { .handler = &m_handler, .active = &m_hsm };
    HsmTransit transit = { .target = &m_hsm };
    HsmTransit transit2 = { .target = &m_hsm2 };

    memcpy( &m_hsm, &hsm, sizeof(hsm));
    memcpy( &m_hsm2, &hsm2, sizeof(hsm2));
    memcpy( &m_transit, &transit, sizeof(transit));
    memcpy( &m_transit2, &transit2, sizeof(transit2));
    m_hitcount = 0;
    m_loop = 0;
}

void tearDown(void)
{
}

/*
 * \test if do transit is successful, inits leaf, return success
 */
void test_Hsm_ProcessTransit_HappyPath(void)
{
    Hsm_DoTransit_ExpectAndReturn(&m_hsm2,&m_transit,0);
    TEST_ASSERT_EQUAL(0,Hsm_ProcessTransit(&m_hsm2,&m_transit));
    TEST_ASSERT_EQUAL(1,m_hitcount);
}

/*
 * \test if leaf returns a transit, repeat process, return success
 */
void test_Hsm_ProcessTransit_InitTransits(void)
{
    m_loop = 1;
    Hsm_DoTransit_ExpectAndReturn(&m_hsm2,&m_transit,0);
    Hsm_DoTransit_ExpectAndReturn(&m_hsm2,&m_transit2,0);
    TEST_ASSERT_EQUAL(0,Hsm_ProcessTransit(&m_hsm2,&m_transit));
    TEST_ASSERT_EQUAL(2,m_hitcount);
}

/*
 * \test if transit fails, return its error
 */
void test_Hsm_ProcessTransit_TransitFailReturned(void)
{
    Hsm_DoTransit_ExpectAndReturn(&m_hsm,&m_transit,73);
    TEST_ASSERT_EQUAL(73,Hsm_ProcessTransit(&m_hsm,&m_transit));
    TEST_ASSERT_EQUAL(0,m_hitcount);
}

/*
 * \test if state_machine is null, return error
 */
void test_Hsm_ProcessTransit_NullStateFails(void)
{
    TEST_ASSERT_EQUAL(HSM_RESULT_PROCESS_TRANSIT_ERROR_NULL_STATE,Hsm_ProcessTransit(NULL,&m_transit));
}

/*
 * \test if transit is null, return error
 */
void test_Hsm_ProcessTransit_NullTransitFails(void)
{
    TEST_ASSERT_EQUAL(HSM_RESULT_PROCESS_TRANSIT_ERROR_NULL_TRANSIT,Hsm_ProcessTransit(&m_hsm,NULL));
}

