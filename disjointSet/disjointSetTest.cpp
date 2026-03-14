#include "./disjointSet.h"
#include "../utils.h"



static bool expectEq(const char *name, int got, int expected) {
	bool ok = got == expected;
	std::cout << (ok ? "[PASS] " : "[FAIL] ") << name << " got=" << got
			  << " expected=" << expected << "\n";
	return ok;
}

static bool expectParent(const char *name, disjointSet &ds, const int expected[], int len) {
	bool ok = true;
	for (int i = 0; i < len; ++i) {
		if (ds.parent[i] != expected[i]) {
			ok = false;
			break;
		}
	}
	std::cout << (ok ? "[PASS] " : "[FAIL] ") << name << "\n";
	std::cout << "  expected: ";
	for (int i = 0; i < len; ++i) {
		std::cout << expected[i] << (i + 1 == len ? '\n' : ' ');
	}
	std::cout << "  actual:   ";
	for (int i = 0; i < len; ++i) {
		std::cout << ds.parent[i] << (i + 1 == len ? '\n' : ' ');
	}
	return ok;
}

void test() {
	int pass = 0;
	int total = 0;
	disjointSet ds(7);

	int s0[] = {-1, -1, -1, -1, -1, -1, -1};
	pass += expectParent("before find(0)", ds, s0, 7); ++total;
	pass += expectEq("find(0)", ds.find(0), 0); ++total;
	pass += expectParent("after find(0)", ds, s0, 7); ++total;

	pass += expectParent("before union(0,1)", ds, s0, 7); ++total;
	pass += expectEq("union(0,1) root", ds.unionSet(0, 1), 0); ++total;
	int s1[] = {-2, 0, -1, -1, -1, -1, -1};
	pass += expectParent("after union(0,1)", ds, s1, 7); ++total;

	pass += expectParent("before union(2,3)", ds, s1, 7); ++total;
	pass += expectEq("union(2,3) root", ds.unionSet(2, 3), 2); ++total;
	int s2[] = {-2, 0, -2, 2, -1, -1, -1};
	pass += expectParent("after union(2,3)", ds, s2, 7); ++total;

	pass += expectParent("before union(3,4)", ds, s2, 7); ++total;
	pass += expectEq("union(3,4) root", ds.unionSet(3, 4), 2); ++total;
	int s3[] = {-2, 0, -3, 2, 2, -1, -1};
	pass += expectParent("after union(3,4)", ds, s3, 7); ++total;

	pass += expectParent("before union(1,4)", ds, s3, 7); ++total;
	pass += expectEq("union(1,4) root", ds.unionSet(1, 4), 2); ++total;
	int s4[] = {2, 0, -5, 2, 2, -1, -1};
	pass += expectParent("after union(1,4)", ds, s4, 7); ++total;

	pass += expectParent("before find(4)", ds, s4, 7); ++total;
	pass += expectEq("find(4)", ds.find(4), 2); ++total;
	int s5[] = {2, 0, -5, 2, 2, -1, -1};
	pass += expectParent("after find(4)", ds, s5, 7); ++total;

	pass += expectParent("before union(3,6)", ds, s5, 7); ++total;
	pass += expectEq("union(3,6) root", ds.unionSet(3, 6), 2); ++total;
	int s6[] = {2, 0, -6, 2, 2, -1, 2};
	pass += expectParent("after union(3,6)", ds, s6, 7); ++total;

	std::cout << "[SUMMARY] " << pass << "/" << total << " passed\n";
}
