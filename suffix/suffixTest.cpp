#include "../utils.h"
#include "./suffix.h"
#include <vector>

struct Case {
    std::string expr;
    int expected;
};

static bool runCase(const Case &c) {
    suffix s(c.expr);
    bool ok = (s.out == c.expected);
    std::cout << (ok ? "[PASS] " : "[FAIL] ") << "\"" << c.expr << "\""
              << " => got: " << s.out << ", expected: " << c.expected << "\n";
    return ok;
}

static std::string repeatPlusOnes(int n) {
    std::string expr = "1";
    for (int i = 1; i < n; ++i) {
        expr += "+1";
    }
    return expr;
}

void test() {
    Case cases[] = {
        {"", 0},
        {"+", 0},
        {"1+", 0},
        {"(1+2", 0},
        {"1++2", 0},
        {"1+2-3*4/5",1+2-3*4/5},
        {"(1+2)-3*4/5",(1+2)-3*4/5},
        {"(1+2-1)*4/5",(1+2-1)*4/5}
    };

    int pass = 0;
    for (const auto &c : cases) {
        if (runCase(c)) {
            ++pass;
        }
    }

    std::string longExpr = repeatPlusOnes(200);
    Case longCase{longExpr, 200};
    if (runCase(longCase)) {
        ++pass;
    }

    std::cout << "[SUMMARY] " << pass << "/" << (sizeof(cases)/sizeof(cases[0]) + 1)
              << " passed\n";
}