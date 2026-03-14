#include "./disjointSet.h"
#include "../utils.h"

static bool expectEq(const char *name, int got, int expected) {
	bool ok = got == expected;
	std::cout << (ok ? "[PASS] " : "[FAIL] ") << name << " got=" << got
			  << " expected=" << expected << "\n";
	return ok;
}

void test() {
	int pass = 0;
	int total = 0;

	disjointSet ds(7);

	pass += expectEq("find(0)", ds.find(0), 0);
	++total;

	int r01 = ds.unionSet(0, 1);
	pass += expectEq("unionSet(0,1) root", r01, ds.find(0));
	++total;
	pass += expectEq("find(1)==find(0)", ds.find(1), ds.find(0));
	++total;

	ds.unionSet(2, 3);
	ds.unionSet(3, 4);
	pass += expectEq("find(2)==find(4)", ds.find(2), ds.find(4));
	++total;
	pass += expectEq("find(0)!=find(2)", ds.find(0) == ds.find(2), 0);
	++total;

	ds.unionSet(1, 4);
	pass += expectEq("find(4)==find(0)", ds.find(4), ds.find(0));
	++total;

	//std::cout << "parent[4] before=" << parentBefore << " after=" << parentAfter << "\n";
	std::cout << "[parent]: ";
	for(int i = 0; i < 7; ++i){
		std::cout <<  ds.parent[i] << " ";
	}
	std::cout << "\n";
	std::cout << "[unionSet(3, 6)]\n";
	ds.unionSet(3, 6);
	std::cout << "[parent]: ";
	for(int i = 0; i < 7; ++i){
		std::cout <<  ds.parent[i] << " ";
	}
	std::cout << "\n";
	int setCnt = ds.countSet();
	pass += expectEq("countSet", setCnt, 2);
	++total;

	std::cout << "[SUMMARY] " << pass << "/" << total << " passed\n";
}
