#ifndef MYTEST_H_
#define MYTEST_H_

#include <functional>
#include <string>
#include <vector>

namespace mytest {
struct test {
    test(std::string name_, std::function<void()> test_case_);
    std::string get_name();
    std::function<void()> &get_test_case();

private:
    std::string name;
    std::function<void()> test_case;
};

int &cnt_tests();
int &total_tests();
std::vector<test> &tests();

// NOLINTNEXTLINE: cppcoreguidelines-macro-usage
#define CHECK(equation) mytest::check(#equation, equation, __FILE__, __LINE__)

// NOLINTNEXTLINE: cppcoreguidelines-macro-usage
#define CHECK_MESSAGE(equation, string) \
    mytest::check_message(#equation, equation, __FILE__, string, __LINE__)

// NOLINTNEXTLINE: cppcoreguidelines-macro-usage
#define MYTEST_INTERNAL_TEST_CASE(class_name, name)                    \
    static void class_name();                                          \
    namespace {                                                        \
                                                                       \
    struct MagicStruct_##class_name {                                  \
        MagicStruct_##class_name() {                                   \
            mytest::test next_case =                                   \
                mytest::test(name, std::function<void()>(class_name)); \
            mytest::tests().push_back(next_case);                      \
        }                                                              \
    } magic_init##class_name;                                          \
    }                                                                  \
    static void class_name()

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define MYTEST_INTERNAL_TEST_CASE2(line, name) \
    MYTEST_INTERNAL_TEST_CASE(mytest_test_class_##line, name)
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define MYTEST_INTERNAL_TEST_CASE1(line, name) \
    MYTEST_INTERNAL_TEST_CASE2(line, name)
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define TEST_CASE(name) MYTEST_INTERNAL_TEST_CASE1(__LINE__, name)

void check(const std::string &equation,
           bool result,
           const std::string &filename,
           int line_number);

void check_message(const std::string &equation,
                   bool result,
                   const std::string &filename,
                   const std::string &message,
                   int line_number);

}  // namespace mytest
#endif  // MYTEST_H_