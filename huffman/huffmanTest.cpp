#include "./huffman.h"
#include "../utils.h"

static bool runCase(int data[], int len, int expected) {
	std::cout<<"[before data]: ";
	for(int i=0;i<len;++i){
		std::cout<<data[i]<<" ";
	}
	huffmanTree t(data, len);
	bool ok = t.wpl == expected;
	std::cout<<"\n[after data]: ";
	for(int i=0;i<len;++i){
		std::cout<<data[i]<<" ";
	}
	std::cout <<"\n" <<(ok ? "[PASS] " : "[FAIL] ") << "len=" << len << " got=" << t.wpl
			  << " expected=" << expected << "\n";
	return ok;
}

void test() {
	int pass = 0;
	int total = 0;

	int a1[] = {5};
	pass += runCase(a1, 1, 0);
	++total;

	int a2[] = {1, 2, 3, 4};
	pass += runCase(a2, 4, 19);
	++total;

	int a3[] = {1, 1, 1, 1};
	pass += runCase(a3, 4, 8);
	++total;

	int a4[] = {2, 3, 7};
	pass += runCase(a4, 3, 17);
	++total;

	int a5[] = {0, 0, 5};
	pass += runCase(a5, 3, 5);
	++total;

	int a6[] = {5, 29, 7, 8, 14, 23, 3, 11};
	pass += runCase(a6, 8, 271);
	++total;

	std::cout << "[SUMMARY] " << pass << "/" << total << " passed\n";
}

