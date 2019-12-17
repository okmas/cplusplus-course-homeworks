#ifndef TEST_CORE_H
#define TEST_CORE_H

#include <cassert>
#include <cstdlib>
#include <string>
#include <iostream>

extern std::string testclass;

#if defined (__unix__) || defined (__APPLE__) || defined (__unix) || defined (__GNUG__)
#ifndef __STRING
#define	__STRING(x)	#x
#endif

#define test_assert(result, report) if (!(result)){ \
        std::cerr << testclass << ": " << (report) << std::endl; \
        std::cerr.flush(); \
        std::cerr << __STRING(result) << " (" \
            << __FILE__ << ", " <<  __LINE__ << ", " \
            << __PRETTY_FUNCTION__ << ")" << std::endl; \
        return TESTCASE_FAIL_BIT; \
    }
#else 
#define test_assert(result, report) if (!(result)){ \
        std::cerr << testclass << ": " << (report) << std::endl; \
        std::cerr.flush(); \
        assert(result); \
    }
#endif
/*
void handle_sigabrt(int x __attribute__((unused)) ){
    exit(-1);
}

sighandler_t unused_signal = signal(SIGABRT, handle_sigabrt);
*/

#endif // TEST_CORE_H
