#include <functional>
#include "test_core.h"
#include <ctime>
#include <iomanip>

struct is_even: public std::unary_function<unsigned char, bool> {
    bool operator()(unsigned char num) const { return !(num%2); }
};

template <typename FILTER_TYPE, typename SEQUENCE>
int check_filter_result(const FILTER_TYPE & filter_test, const SEQUENCE & numbers){
    SEQUENCE reference_filter;
    std::remove_copy_if(numbers.begin(), numbers.end(), std::back_inserter(reference_filter), std::unary_negate<typename FILTER_TYPE::predicate_type>(filter_test.get_predicate()));

    test_assert(filter_test.empty() == reference_filter.empty(), "Filtr je prazdny!");
    test_assert(filter_test.size() == reference_filter.size(), "Delka filtru neodpovida ocekavane delce!");

    // sequencial traversing
    size_t steps = 0;
    typename SEQUENCE::const_iterator original_iterator = reference_filter.begin();
    typename FILTER_TYPE::const_iterator filter_iterator = filter_test.begin();

    time_t elapsed = -clock();
    while ((original_iterator != reference_filter.end()) && (filter_iterator != filter_test.end())){
        test_assert(*original_iterator == *filter_iterator, "Polozka filtru neodpovida ocekavane polozce!");
        ++filter_iterator;
        ++original_iterator;
        ++steps;
    }
    elapsed += clock();
    test_assert(steps == filter_test.size(), "Delka filtru v sekvencnim prochazeni neodpovida ocekavane delce!");

    // begin & end
    if (!filter_test.empty()){
        test_assert(filter_test.front() == reference_filter.front(), "Primy pristup k prvni polozce filtru vraci nespravnou hodnotu!");
        test_assert(filter_test.back() == reference_filter.back(), "Primy pristup k posledni polozce filtru vraci nespravnou hodnotu!");
    }

    std::cout << std::setprecision(5) << "OK! time: " << elapsed / (double)CLOCKS_PER_SEC << std::endl;

    return 0;
}

