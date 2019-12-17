#include <iostream>
#include "bind_last.hpp"
#include "bind_first.hpp"
#include "filter_view.hpp"
#include <vector>
#include <algorithm>

using namespace std;

struct adder {
    int operator()(int num, int whatToAdd) const
    {
        return num + whatToAdd;
    }
};

template <typename T>
void printVec(std::vector<T> &vec)
{
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
}

struct is_even: public std::unary_function<unsigned char, bool> {
    bool operator()(unsigned char num) const { return !(num%2); }
};

int main_()
{
    typedef vector<unsigned int> NUM_VEC;
    NUM_VEC numbers;
    for (int i = 0; i < 25; i++) numbers.push_back(i);

    printVec<unsigned int>(numbers);

    filter_view<NUM_VEC, is_even> fv(numbers, is_even());
    filter_view<NUM_VEC, is_even>::const_iterator it = fv.begin();
    ++it;
    fv.end();
    fv.empty();
    fv.back();
    fv.front();
    fv.get_predicate();
    fv.size();

    return 0;
}
