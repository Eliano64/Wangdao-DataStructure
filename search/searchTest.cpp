#include "./search.h"
#include "../utils.h"

static bool runCase(const char *name, database &db, int target, int expected) {
	int got = db.blockSearch(target);
	bool ok = got == expected;
	std::cout << (ok ? "[PASS] " : "[FAIL] ") << name << " target=" << target
			  << " got=" << got << " expected=" << expected << "\n";
	return ok;
}

void test() {
	int pass = 0;
	int total = 0;

	int idxs1[] = {10, 20, 30};
	int arr1[] = {1, 10, 8, 20, 13, 15, 11, 28, 27, 30};
	int regionLen1[] = {3, 4, 3};
	database db1(idxs1, 3, arr1, regionLen1);

	pass += runCase("db1 hit first block first", db1, 1, 0); ++total;
	pass += runCase("db1 hit first block non-first", db1, 8, 2); ++total;
	pass += runCase("db1 hit second block first", db1, 20, 3); ++total;
	pass += runCase("db1 hit second block non-first", db1, 15, 5); ++total;
	pass += runCase("db1 hit second block tail", db1, 11, 6); ++total;
	pass += runCase("db1 hit third block first", db1, 28, 7); ++total;
	pass += runCase("db1 hit third block non-first", db1, 27, 8); ++total;
	pass += runCase("db1 hit third block tail", db1, 30, 9); ++total;
	pass += runCase("db1 miss in first block", db1, 9, -3); ++total;
	pass += runCase("db1 miss in second block", db1, 12, -7); ++total;
	pass += runCase("db1 miss over max", db1, 31, -10); ++total;

	int idxs2[] = {4, 9};
	int arr2[] = {4, 1, 9, 8, 7};
	int regionLen2[] = {2, 3};
	database db2(idxs2, 2, arr2, regionLen2);

	pass += runCase("db2 hit first block tail", db2, 1, 1); ++total;
	pass += runCase("db2 hit second block non-first", db2, 8, 3); ++total;
	pass += runCase("db2 miss in first block", db2, 3, -2); ++total;
	pass += runCase("db2 miss over max", db2, 10, -5); ++total;

	std::cout << "[SUMMARY] " << pass << "/" << total << " passed\n";
}
