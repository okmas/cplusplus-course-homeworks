#include <iostream>
#include <cassert>
#include <vector>
#include <functional>
#include <algorithm>
#include "test_core.h"
#include "filter_view.hpp"

#include <iomanip>
#include <ctime>
#include <vector>

std::string testclass;
size_t TESTCASE_FAIL_BIT = 0;

#include "filter_test_core.hpp"

typedef std::vector<unsigned char> uvec;
typedef filter_view<uvec, is_even> even_filter;

void init(uvec ** numbers, const size_t CAPACITY){
    srand(0);
    *numbers = new uvec(CAPACITY);
    assert(*numbers != NULL);

    uvec::iterator i = (*numbers)->begin();
    while (i != (*numbers)->end()){
        *i = rand();
        ++i;
    }
}

int testcase(const size_t CAPACITY){
    testclass = "Opravdu veliky kontejner";
    TESTCASE_FAIL_BIT = 1 << 0;

    uvec * numbers;
    init(&numbers, CAPACITY);
    even_filter filtr(*numbers, is_even());

    int retval = check_filter_result<even_filter, uvec>(filtr, *numbers);
    delete numbers;
    return retval;
}

int main(int argc, char ** argv){
    std::vector<int> vec;
    vec.end();
    time_t total_elapsed = -clock();

    if (argc < 2){
        std::cerr << "Test je potreba poustet s argumentem, udavajicim velikost datove sady. A mimo aisu je jeho vysledek stejne nicnerikajici." << std::endl;
        return 1;
    }

    char * endptr = NULL;
    int capacity = strtol(argv[1], &endptr, 10);
    if ((*endptr != 0) || (capacity <= 0)) {
        std::cerr << "Prijaty argument neni platne kladne cele cislo." << std::endl;
        return 1;
    }

    int retval = testcase(capacity);
    total_elapsed += clock();
    std::cout << std::setprecision(5) << "total time: " << (double)total_elapsed / CLOCKS_PER_SEC << std::endl;
    return retval;
}

