#include <iostream>
#include <cassert>
#include "test_core.h"
#include "incompatible_types.hpp"
#include "bind_first.hpp"

static unsigned int void_result = 0;
std::string testclass;

struct test_cref{
    void operator()(const incompatible_6 &a, const incompatible_2 &b){
        void_result = a.m_value * b.m_value;
    }
};

struct test_ptr {
    incompatible_1 operator()(incompatible_6 * a, incompatible_2 * b){
        incompatible_1 tmp(b->m_value);
        tmp.m_value *= a->m_value;
        a->m_value += 2;
        return tmp;
    }
};

struct test_val {
    incompatible_1 operator()(incompatible_6 a, incompatible_2 b){
        return incompatible_1(a.m_value * b.m_value);
    }
};

int testcase_value(){
    testclass = "bind_last_2, trojty test, predani hodnotou";
    const size_t TESTCASE_FAIL_BIT = 1 << 0;

    incompatible_6 testval(2);
    incompatible_2 ta_1(3);

    // compute reference
    test_val ref;
    const incompatible_1 reference_result = ref(testval, ta_1);

    // test value
    bind_first_2<test_val, incompatible_1, incompatible_6, incompatible_2> testcase(test_val(), testval);
    incompatible_1 test_result = testcase(ta_1);
    test_assert(reference_result.m_value == test_result.m_value, "Nesouhlasi vypocet predanim hodnotou!");
    test_assert(testval.m_value == 2, "Doslo k prepsani vazaneho argumentu!");
    return 0;
}

int testcase_cref(){
    testclass = "bind_last_2, trojty test, predani konstantni referenci";
    const size_t TESTCASE_FAIL_BIT = 1 << 1;

    incompatible_6 testval(2);
    incompatible_2 ta_1(3);

    // compute reference
    test_val ref;
    const incompatible_1 reference_result = ref(testval, ta_1);

    // test reference (void)
    bind_first_2<test_cref, void, incompatible_6, incompatible_2> testcase(test_cref(), testval);
    testcase(ta_1);
    test_assert(void_result == reference_result.m_value, "Nesouhlasi vypocet predanim konstantni referenci!");
    test_assert(testval.m_value == 2, "Doslo k prepsani vazaneho argumentu!");

    return 0;
}

int testcase_ptr(){
    testclass = "bind_last_2, trojty test, predani (nekonstantnim) ukazatelem";
    const size_t TESTCASE_FAIL_BIT = 1 << 2;

    incompatible_6 testval(2); incompatible_6 * testval_ptr = &testval;
    incompatible_2 ta_1(3); incompatible_2 * tp_1 = &ta_1;

    // compute reference
    test_val ref;
    const incompatible_1 reference_result = ref(testval, ta_1);

    // test pointer
    bind_first_2<test_ptr, incompatible_1, incompatible_6*, incompatible_2 *> testcase(test_ptr(), testval_ptr);
    incompatible_1 test_result = testcase(tp_1);
    test_assert(reference_result.m_value == test_result.m_value, "Nesouhlasi vypocet predanim konstantnim ukazatelem (nekonstantni data)!");
    test_assert(testval.m_value != 2, "Testu se nepovedlo zmenit vazany agrument!");

    return 0;
}


int main(){
    int retval = 0;
    retval |= testcase_value();
    retval |= testcase_cref();
    retval |= testcase_ptr();
    return retval;
}
