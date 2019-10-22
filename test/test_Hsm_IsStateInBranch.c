#include "unity.h"
#include "Hsm_IsStateInBranch.h"

static Hsm m_hsm1;
static Hsm m_hsm2 = { .parent = &m_hsm1 };
static Hsm m_hsm3 = { .parent = &m_hsm2 };
static Hsm m_hsm4 = { .parent = &m_hsm1 };

void setUp(void)
{
}

void tearDown(void)
{
}

/*
 * \test returns true for state == leaf
 */
void test_Hsm_IsStateInBranch_StateIsLeafPasses(void)
{
    TEST_ASSERT(Hsm_IsStateInBranch(&m_hsm4,&m_hsm4));
}

/*
 * \test returns false if state is null
 */
void test_Hsm_IsStateInBranch_StateIsNullFails(void)
{
    TEST_ASSERT(!Hsm_IsStateInBranch(NULL,&m_hsm4));
}

/*
 * \test returns false if leaf is null
 */
void test_Hsm_IsStateInBranch_LeafIsNullFails(void)
{
    TEST_ASSERT(!Hsm_IsStateInBranch(&m_hsm1,NULL));
}

/*
 * \test returns true if state is under leaf
 */
void test_Hsm_IsStateInBranch_StateUnderLeafPasses(void)
{
    TEST_ASSERT(Hsm_IsStateInBranch(&m_hsm1,&m_hsm3));
}

/*
 * \test returns false if state is not under leaf
 */
void test_Hsm_IsStateInBranch_StateNotUnderLeafFails(void)
{
    TEST_ASSERT(!Hsm_IsStateInBranch(&m_hsm4,&m_hsm3));
}
