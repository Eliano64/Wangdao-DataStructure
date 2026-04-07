#include "./sort.h"
#include "../utils.h"

struct Case {
	const char *name;
	int input[16];
	int expected[16];
	int len;
};

static bool checkSorted(const char *algo, const Case &c, int data[]) {
	bool ok = true;
	for (int i = 0; i < c.len; ++i) {
		if (data[i] != c.expected[i]) {
			ok = false;
			break;
		}
	}
	std::cout << (ok ? "[PASS] " : "[FAIL] ") << algo << " " << c.name << " got=";
	for (int i = 0; i < c.len; ++i) {
		std::cout << data[i] << (i + 1 == c.len ? ' ' : ',');
	}
	std::cout << "expected=";
	for (int i = 0; i < c.len; ++i) {
		std::cout << c.expected[i] << (i + 1 == c.len ? '\n' : ',');
	}
	if (c.len == 0) {
		std::cout << "expected=empty\n";
	}
	return ok;
}

static bool runQuickCase(const Case &c) {
	int data[16] = {};
	for (int i = 0; i < c.len; ++i) data[i] = c.input[i];
	quickSort(data, 0, c.len);
	return checkSorted("quick", c, data);
}

static bool runHeapCase(const Case &c) {
	int data[16] = {};
	for (int i = 0; i < c.len; ++i) data[i] = c.input[i];
	heapSort(data, c.len);
	return checkSorted("heap", c, data);
}

static bool runMergeCase(const Case &c) {
	int data[16] = {};
	for (int i = 0; i < c.len; ++i) data[i] = c.input[i];
	mergeSort(data, c.len);
	return checkSorted("merge", c, data);
}

void test() {
	Case cases[] = {
		{"empty", {}, {}, 0},
		{"single", {5}, {5}, 1},
		{"sorted", {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, 5},
		{"reverse", {5, 4, 3, 2, 1}, {1, 2, 3, 4, 5}, 5},
		{"duplicate pivot-like", {4, 1, 3, 4, 2, 4}, {1, 2, 3, 4, 4, 4}, 6},
		{"negative mixed", {-3, 7, 0, -1, 5, -3}, {-3, -3, -1, 0, 5, 7}, 6},
		{"general", {9, 2, 8, 2, 7, 3, 6, 4, 5}, {2, 2, 3, 4, 5, 6, 7, 8, 9}, 9}
	};

	int pass = 0;
	int total = 0;
	for (const auto &c : cases) {
		pass += runQuickCase(c); ++total;
		pass += runHeapCase(c); ++total;
		pass += runMergeCase(c); ++total;
	}
	std::cout << "[SUMMARY] " << pass << "/" << total << " passed\n";
}
