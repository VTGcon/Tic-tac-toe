#include "mytest.h"
#include <iostream>

namespace mytest {
namespace {
// File-local declarations and definitions.
}  // namespace
test::test(std::string name_, std::function<void()> test_case_)
    : name(std::move(name_)), test_case(std::move(test_case_)) {
}
std::string test::get_name() {
    return name;
}
std::function<void()> &test::get_test_case() {
    return test_case;
}

std::vector<test> &tests() {
    static std::vector<test> all_tests = {};
    return all_tests;
}
int &cnt_tests() {
    static int cnt_tests = 0;
    return cnt_tests;
}
int &total_tests() {
    static int total_tests = 0;
    return total_tests;
}

void check(const std::string &equation,
           bool result,
           const std::string &filename,
           int line_number) {
    total_tests()++;
    if (result) {
        cnt_tests()++;
    } else {
        std::cerr << "CHECK(" << equation << ") at " << filename << ":"
                  << line_number << " failed!" << '\n';
    }
}

void check_message(const std::string &equation,
                   bool result,
                   const std::string &filename,
                   const std::string &message,
                   int line_number) {
    total_tests()++;
    if (result) {
        cnt_tests()++;
    } else {
        std::cerr << "CHECK(" << equation << ") at " << filename << ":"
                  << line_number << " failed!" << '\n'
                  << "    message: " << message << '\n';
    }
}

// Externally visible declarations and definitions.
}  // namespace mytest
