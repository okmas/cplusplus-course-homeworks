#include <iostream>
#include <cassert>
#include <vector>
#include <functional>
#include <algorithm>
#include "test_core.h"
#include "filter_view.hpp"

std::string testclass;
size_t TESTCASE_FAIL_BIT = 0;

#include "filter_test_core.hpp"

typedef std::vector<unsigned char> uvec;
typedef filter_view<uvec, is_even> even_filter;

int testcase(){
    testclass = "Kontejner, sekvencni prochazeni obsahu (zakladni test)";
    TESTCASE_FAIL_BIT = 1 << 0;

    const size_t CAPACITY = 2*10;

    uvec numbers;
    numbers.resize(CAPACITY);

    for (size_t i = 0; i < CAPACITY; ++i){ numbers[i] = i; }

    const uvec & numbers_ref = numbers;

    even_filter filtr(numbers_ref, even_filter::predicate_type());

    return check_filter_result<filter_view<even_filter::container_type, even_filter::predicate_type>, uvec>(filtr, numbers);
}

int main2(){
    return testcase();
}
