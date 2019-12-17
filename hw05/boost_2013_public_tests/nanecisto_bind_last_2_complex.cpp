#include <iostream>
#include <cassert>
#include "test_core.h"
#include "incompatible_types.hpp"
#include "bind_last.hpp"

static unsigned int void_result = 0;
std::string testclass;

struct test_cref{
    void operator()(const incompatible_3 &a, const incompatible_2 &b){
        void_result = a.m_value * b.m_value;
    }
};

struct test_ptr {
    incompatible_1 operator()(incompatible_3 * a, incompatible_2 * b){
        incompatible_1 tmp(a->m_value);
        tmp.m_value *= b->m_value;
        b->m_value += 2;
        return tmp;
    }
};

struct test_val {
    incompatible_1 operator()(incompatible_3 a, incompatible_2 b){
        return incompatible_1(a.m_value * b.m_value);
    }
    incompatible_1 operator()(incompatible_3 a, incompatible_2 b) const {
        return incompatible_1(a.m_value * b.m_value);
    }
};

int testcase_value(){
    testclass = "bind_last_2 v kombinaci s bind_last_1, trojty test, predani hodnotou";
    const size_t TESTCASE_FAIL_BIT = 1 << 0;


    incompatible_3 testval(11);
    incompatible_2 binded_testval(2);

    // compute reference
    test_val ref;
    const incompatible_1 reference_result = ref(testval, binded_testval);

    // test value
    typedef bind_last_2<test_val, incompatible_1, incompatible_3, incompatible_2> binding_envelope;
    binding_envelope testcase_envelope(test_val(), binded_testval);
    bind_last_1<binding_envelope, incompatible_1, incompatible_3> testcase(testcase_envelope, testval);

    incompatible_1 test_result = testcase();
    test_assert(reference_result.m_value == test_result.m_value, "Nesouhlasi vypocet predanim hodnotou!");
    test_assert(testval.m_value == 11, "Doslo k prepsani jednoho z vazanych argumentu!");
    test_assert(binded_testval.m_value == 2, "Doslo k prepsani jednoho z vazanych argumentu!");


    const bind_last_1<binding_envelope, incompatible_1, incompatible_3> & const_testcase = testcase;
    test_result = const_testcase();
    test_assert(reference_result.m_value == test_result.m_value, "Nesouhlasi vypocet predanim hodnotou! (const operator())");
    test_assert(testval.m_value == 11, "Doslo k prepsani jineho z vazanych argumentu! (const operator())");
    test_assert(testval.m_value != 2, "Testu se nepovedlo zmenit vazany agrument! (const operator())");

    return 0;
}

int testcase_cref(){
    testclass = "bind_last_2 v kombinaci s bind_last_1, trojty test, predani konstantni referenci";
    const size_t TESTCASE_FAIL_BIT = 1 << 1;

    incompatible_3 testval(11);
    incompatible_2 binded_testval(2);

    // compute reference
    test_val ref;
    const incompatible_1 reference_result = ref(testval, binded_testval);

    // test reference (void)
    typedef bind_last_2<test_cref, void, incompatible_3, incompatible_2> binding_envelope;
    binding_envelope testcase_envelope(test_cref(), binded_testval);
    bind_last_1<binding_envelope, void, incompatible_3> testcase(testcase_envelope, testval);

    testcase();
    test_assert(void_result == reference_result.m_value, "Nesouhlasi vypocet predanim hodnotou!");
    test_assert(testval.m_value == 11, "Doslo k prepsani jednoho z vazanych argumentu!");
    test_assert(binded_testval.m_value == 2, "Doslo k prepsani jednoho z vazanych argumentu!");

    return 0;
}

int testcase_ptr(){
    testclass = "bind_last_2 v kombinaci s bind_last_1, trojty test, predani (nekonstantnim) ukazatelem";
    const size_t TESTCASE_FAIL_BIT = 1 << 2;

    incompatible_3 testval(11); incompatible_3 * testval_ptr = &testval;
    incompatible_2 binded_testval(2); incompatible_2 * binded_testval_ptr = &binded_testval;

    // compute reference
    test_val ref;
    const incompatible_1 reference_result = ref(testval, binded_testval);

    // test pointer
    typedef bind_last_2<test_ptr, incompatible_1, incompatible_3 *, incompatible_2 *> binding_envelope;
    binding_envelope testcase_envelope(test_ptr(), binded_testval_ptr);
    bind_last_1<binding_envelope, incompatible_1, incompatible_3 *> testcase(testcase_envelope, testval_ptr);

    incompatible_1 test_result = testcase();
    test_assert(reference_result.m_value == test_result.m_value, "Nesouhlasi vypocet predanim hodnotou!");
    test_assert(testval.m_value == 11, "Doslo k prepsani jineho z vazanych argumentu!");
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
