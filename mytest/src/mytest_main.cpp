#include <iostream>
#include "mytest.h"

int main() {
    int cnt = 0;
    int cnt_passed = 0;
    for (auto &i : mytest::tests()) {
        std::cerr << "Running \"" << i.get_name() << "\"..." << '\n';
        cnt++;
        mytest::total_tests() = 0;
        mytest::cnt_tests() = 0;
        i.get_test_case()();
        if (mytest::total_tests() == mytest::cnt_tests()) {
            cnt_passed++;
        }
    }
    std::cerr << "===== Tests passed: " << cnt_passed << "/" << cnt
              << " =====" << '\n';
    return int(cnt_passed != cnt);
}