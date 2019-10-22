#include "unity.h"
#include "Hsm.h"
#include "Hsm_ProcessTransit.h"
#include "mock_Hsm_DoTransit.h"

static HsmEventResult m_handler(Hsm *self, HsmEvent *event, HsmTransit *transit);

static unsigned m_hitcount;
static unsigned m_loop;
static Hsm m_hsm = { .handler = &m_handler };
static Hsm m_hsm2 = { .parent = &m_hsm };
static HsmTransit m_transit = { .target = &m_hsm };
static HsmTransit m_transit2 = { .target = &m_hsm2 };

static HsmEventResult m_handler(Hsm *self, HsmEvent *event, HsmTransit *transit) 
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
}


void setUp(void)
{
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
    Hsm_DoTransit_ExpectAndReturn(&m_hsm,&m_transit,0);
    TEST_ASSERT_EQUAL(0,test_Hsm_ProcessTransit(&m_hsm,*m_transit));
    TEST_ASSERT_EQUAL(1,m_hitcount);
}

/*
 * \test if leaf returns a transit, repeat process, return success
 */
void test_Hsm_ProcessTransit_InitTransits(void)
{
    m_loop = 1;
    Hsm_DoTransit_ExpectAndReturn(&m_hsm,&m_transit,0);
    Hsm_DoTransit_ExpectAndReturn(&m_hsm,&m_transit,0);
    TEST_ASSERT_EQUAL(0,test_Hsm_ProcessTransit(&m_hsm,&m_transit));
    TEST_ASSERT_EQUAL(2,m_hitcount);
}

/*
 * \test if transit fails, return its error
 */
void test_Hsm_ProcessTransit_TransitFailReturned(void)
{
    Hsm_DoTransit_ExpectAndReturn(&m_hsm,&m_transit,73);
    TEST_ASSERT_EQUAL(73,test_Hsm_ProcessTransit(&m_hsm,&m_transit));
    TEST_ASSERT_EQUAL(0,m_hitcount);
}

/*
 * \test if state_machine is null, return error
 */
void test_Hsm_ProcessTransit_NullStateFails(void)
{
    TEST_ASSERT_EQUAL(HSM_RESULT_PROCESS_TRANSIT_ERROR_NULL_STATE,test_Hsm_ProcessTransit(NULL,&m_transit));
}

/*
 * \test if transit is null, return error
 */
void test_Hsm_ProcessTransit_NullTransitFails(void)
{
    TEST_ASSERT_EQUAL(HSM_RESULT_PROCESS_TRANSIT_ERROR_NULL_TRANSIT,test_Hsm_ProcessTransit(&m_hsm,NULL));
}

