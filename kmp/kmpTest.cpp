#include "./kmp.h"
#include "../utils.h"
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <new>
#include <unordered_map>

// static bool g_log_next = false;
static std::unordered_map<void *, int> sizeRecord;

void *operator new[](std::size_t size) {
    void *p = std::malloc(size);
    if (p == nullptr) {
        throw std::bad_alloc();
    }
    sizeRecord[p] = size;
    return p;
}

void operator delete[](void *p) noexcept {
    if (p == nullptr) {
        return;
    }
    int size = sizeRecord[p];
    if (size != 0) {
        sizeRecord.erase(p);
        std::cout << "next: ";
        int *arr = static_cast<int *>(p);
        for (long unsigned int i = 0; i < size / sizeof(arr[0]); ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
    }
    std::free(p);
}

void operator delete[](void *p, std::size_t) noexcept { operator delete[](p); }

void debug(char a[], char b[], int x) {
    std::cout << a << "\n";
    if (x >= 0) {
        for (int i = 0; i < x; ++i) {
            std::cout << ' ';
        }
        std::cout << b << "\n";
        std::cout << "found at index: " << x << "\n";
    } else {
        std::cout << b << "\n";
        std::cout << "not found\n";
    }
}

struct Case {
    const char *a;
    const char *b;
    int expected;
};

void test() {
    Case cases[] = {{"", "", 0},
                    {"abc", "", 0},
                    {"", "a", -1},
                    {"hello, world!", "world", 7},
                    {"a b c d", "b c", 2},
                    {"version2.0.1", "2.0", 7},
                    {"abc123xyz", "123", 3},
                    {"Needle in a haystack.", "hay", 12},
                    {"No-match case", "xyz", -1},
                    {"repeat repeat", "peat", 2},
                    {"!@#$%^&*()", "^&*", 5},
                    {"A quick brown fox", "quick", 2},
                    {"aaaaab", "aaab", 2},
                    {"edge-case: end", "end", 11},
                    {"space  and  tabs?", "  ", 5},
                    {"googoegooglegoogoo", "googoo", 12}};

    int pass = 0;
    int total = static_cast<int>(sizeof(cases) / sizeof(cases[0]));
    for (int i = 0; i < total; ++i) {
        char a[1024];
        char b[1024];
        std::strncpy(a, cases[i].a, sizeof(a) - 1);
        std::strncpy(b, cases[i].b, sizeof(b) - 1);
        a[sizeof(a) - 1] = '\0';
        b[sizeof(b) - 1] = '\0';

        // g_log_next = true;
        int ans = findSubStr(a, b);
        // g_log_next = false;
        bool ok = ans == cases[i].expected;
        std::cout << (ok ? "[PASS] " : "[FAIL] ");
        std::cout << "a=\"" << a << "\", b=\"" << b << "\"";
        std::cout << ", got=" << ans << ", expected=" << cases[i].expected
                  << "\n";
        debug(a, b, ans);
        if (ok) {
            ++pass;
        }
    }
    std::cout << "[SUMMARY] " << pass << "/" << total << " passed\n";
}
