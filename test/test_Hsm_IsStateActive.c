#include "unity.h"
#include "Hsm_IsStateActive.h"
#include "mock_Hsm_IsStateInBranch.h"

static Hsm m_hsm4 = { .active = NULL};
static Hsm m_hsm3 = { .active = &m_hsm4};
static Hsm m_hsm2 = { .active = &m_hsm3};
static Hsm m_hsm1 = { .active = &m_hsm2};

void setUp(void)
{
}

void tearDown(void)
{
}

/*
 *   \test if within first leaf, don't check any more and return true
 */
void test_Hsm_IsStateActive_FirstLeafPass(void)
{
    Hsm_IsStateInBranch_ExpectAndReturn(&m_hsm1,&m_hsm2,true);
    TEST_ASSERT(Hsm_IsStateActive(&m_hsm1));
}

/*
 *   \test if within third leaf, don't check any more and return true
 */
void test_Hsm_IsStateActive_ThirdLeafPass(void)
{
    Hsm_IsStateInBranch_ExpectAndReturn(&m_hsm1,&m_hsm2,false);
    Hsm_IsStateInBranch_ExpectAndReturn(&m_hsm1,&m_hsm3,false);
    Hsm_IsStateInBranch_ExpectAndReturn(&m_hsm1,&m_hsm4,true);
    TEST_ASSERT(Hsm_IsStateActive(&m_hsm1));
}

/*
 *   \test if no leaves, return false
 */
void test_Hsm_IsStateActive_NoLeavesFail(void)
{
    TEST_ASSERT(!Hsm_IsStateActive(&m_hsm4));
}

/*
 *   \test if state is null, return false
 */
void test_Hsm_IsStateActive_NullStateFail(void)
{
    TEST_ASSERT(!Hsm_IsStateActive(NULL));
}

/*
 *   \test if not within any leaves return false
 */
void test_Hsm_IsStateActive_NotInAnyLeavesFail(void)
{
    Hsm_IsStateInBranch_ExpectAndReturn(&m_hsm1,&m_hsm2,false);
    Hsm_IsStateInBranch_ExpectAndReturn(&m_hsm1,&m_hsm3,false);
    Hsm_IsStateInBranch_ExpectAndReturn(&m_hsm1,&m_hsm4,false);
    TEST_ASSERT(!Hsm_IsStateActive(&m_hsm1));
}

