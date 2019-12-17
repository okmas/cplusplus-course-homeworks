#include <iostream>
#include <cassert>
#include <list>
#include <functional>
#include <algorithm>
#include "test_core.h"
#include "filter_view.hpp"

std::string testclass;
size_t TESTCASE_FAIL_BIT = 0;

#include "filter_test_core.hpp"

typedef std::list<unsigned char> ulist;
typedef filter_view<ulist, is_even> even_filter;

void init(ulist & numbers){
    const size_t CAPACITY = 2*10;
    for (size_t i = 0; i < CAPACITY; ++i){ numbers.push_back(i); }
}

int testcase_append(const even_filter & filter, ulist & numbers){
    testclass = "Dynamicky kontejner, pridani prvku na konec";
    TESTCASE_FAIL_BIT = 1 << 0;

    numbers.push_back(2);
    numbers.push_back(3);

    return check_filter_result(filter, numbers);
}
int testcase_insert(const even_filter & filter, ulist & numbers){
    testclass = "Dynamicky kontejner, vlozeni prvku";
    TESTCASE_FAIL_BIT = 1 << 1;

    ulist::iterator pos = numbers.begin();
    std::advance(pos, std::distance(numbers.begin(), numbers.end())/2);

    numbers.insert(pos, 2);
    numbers.insert(pos, 3);

    return check_filter_result(filter, numbers);
}
int testcase_prepend(const even_filter & filter, ulist & numbers){
    testclass = "Dynamicky kontejner, pridani prvku na zacatek";
    TESTCASE_FAIL_BIT = 1 << 2;

    numbers.push_front(2);
    numbers.push_front(3);

    return check_filter_result(filter, numbers);
}
int testcase_remove_back(const even_filter & filter, ulist & numbers){
    testclass = "Dynamicky kontejner, smazani prvku z konce";
    TESTCASE_FAIL_BIT = 1 << 3;

    numbers.pop_back();
    numbers.pop_back();

    return check_filter_result(filter, numbers);
}
int testcase_remove_front(const even_filter & filter, ulist & numbers){
    testclass = "Dynamicky kontejner, smazani prvku ze zacatku";
    TESTCASE_FAIL_BIT = 1 << 4;

    numbers.pop_front();
    numbers.pop_front();

    return check_filter_result(filter, numbers);
}
int testcase_remove_middle(const even_filter & filter, ulist & numbers){
    testclass = "Dynamicky kontejner, smazani prvku";
    TESTCASE_FAIL_BIT = 1 << 5;

    ulist::iterator pos = numbers.begin();
    std::advance(pos, std::distance(numbers.begin(), numbers.end())/2);
    numbers.erase(pos);

    pos = numbers.begin();
    std::advance(pos, std::distance(numbers.begin(), numbers.end())/2);
    numbers.erase(pos);

    return check_filter_result(filter, numbers);
}

int main0(){

    // prepare test environment
    ulist numbers;
    init(numbers);
    even_filter filtr(numbers, is_even());

    int retval = 0;
    retval |= testcase_append(filtr, numbers);
    retval |= testcase_insert(filtr, numbers);
    retval |= testcase_prepend(filtr, numbers);
    retval |= testcase_remove_back(filtr, numbers);
    retval |= testcase_remove_front(filtr, numbers);
    retval |= testcase_remove_middle(filtr, numbers);
    return retval;
}
