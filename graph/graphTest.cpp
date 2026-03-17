#include "./graph.h"
#include "../utils.h"

static bool runCase(const char *name, int **relation, int total, int *rowLens, int amount, int expected) {
	graph g(relation, total, rowLens, amount);
	int got = g.bfsEntrance();
	bool ok = got == expected;
	std::cout << (ok ? "[PASS] " : "[FAIL] ") << name << " got=" << got << " expected=" << expected << "\n";
	return ok;
}

void test() {
	int pass = 0;
	int total = 0;

	int e1_0[] = {0, 1};
	int e1_1[] = {1, 2};
	int e1_2[] = {2, 0};
	int e1_3[] = {2, 3};
	int e1_4[] = {4, 5};
	int e1_5[] = {5, 6};
	int e1_6[] = {6, 4};
	int *r1[] = {e1_0, e1_1, e1_2, e1_3, e1_4, e1_5, e1_6};
	int l1[] = {2, 2, 2, 2, 2, 2, 2};
	pass += runCase("case1: two components with cycles", r1, 7, l1, 7, 2);
	++total;

	int e2_0[] = {0, 1};
	int e2_1[] = {1, 2};
	int e2_2[] = {2, 0};
	int e2_3[] = {3, 4};
	int e2_4[] = {4, 5};
	int e2_5[] = {5, 3};
	int e2_6[] = {6};
	int *r2[] = {e2_0, e2_1, e2_2, e2_3, e2_4, e2_5, e2_6};
	int l2[] = {2, 2, 2, 2, 2, 2, 1};
	pass += runCase("case2: two cycles + one isolated", r2, 7, l2, 7, 3);
	++total;

	int e3_0[] = {0, 1};
	int e3_1[] = {1, 2};
	int e3_2[] = {2, 3};
	int e3_3[] = {3, 1};
	int e3_4[] = {4, 5};
	int e3_5[] = {5, 4};
	int e3_6[] = {6};
	int e3_7[] = {7};
	int *r3[] = {e3_0, e3_1, e3_2, e3_3, e3_4, e3_5, e3_6, e3_7};
	int l3[] = {2, 2, 2, 2, 2, 2, 1, 1};
	pass += runCase("case3: two cyclic components + two isolated", r3, 8, l3, 8, 4);
	++total;

	std::cout << "[SUMMARY] " << pass << "/" << total << " passed\n";
}
