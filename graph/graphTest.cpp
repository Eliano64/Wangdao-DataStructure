#include "./graph.h"
#include "../utils.h"

static bool runCase(const char *name, int **relation, int total, int *rowLens, int amount, int expectedBfs, int expectedDfs) {
	graph g(relation, total, rowLens, amount);
	int gotBfs = g.bfsEntrance();
	int gotDfs = g.dfsEntrance();
	bool okBfs = gotBfs == expectedBfs;
	bool okDfs = gotDfs == expectedDfs;
	bool ok = okBfs && okDfs;
	std::cout << (okBfs ? "[PASS] " : "[FAIL] ") << name << " bfs got=" << gotBfs << " expected=" << expectedBfs << "\n";
	std::cout << (okDfs ? "[PASS] " : "[FAIL] ") << name << " dfs got=" << gotDfs << " expected=" << expectedDfs << "\n";
	return ok;
}

static void applyWeights(AOE &aoe, const int weights[][3], int weightCount) {
	for (int i = 0; i < weightCount; ++i) {
		int from = weights[i][0];
		int to = weights[i][1];
		int w = weights[i][2];
		for (edge *cur = aoe.vertices[from].first; cur != nullptr; cur = cur->next) {
			if (cur->to == to) {
				cur->weight = w;
				break;
			}
		}
	}
}

static bool runCriticalCase(const char *name, int **relation, int total, int *rowLens, int amount, const int weights[][3], int weightCount, const int expected[][2], int expectedCount) {
	AOE aoe(relation, total, rowLens, amount);
	applyWeights(aoe, weights, weightCount);
	int **path = aoe.criticalPath();
	bool ok = true;
	int *used = new int[expectedCount];
	for (int i = 0; i < expectedCount; ++i) used[i] = 0;
	for (int i = 0; i < expectedCount; ++i) {
		bool found = false;
		for (int j = 0; j < expectedCount; ++j) {
			if (!used[j] && path[j][0] == expected[i][0] && path[j][1] == expected[i][1]) {
				used[j] = 1;
				found = true;
				break;
			}
		}
		if (!found) ok = false;
	}
	std::cout << (ok ? "[PASS] " : "[FAIL] ") << name << " critical got=";
	for (int i = 0; i < expectedCount; ++i) std::cout << "(" << path[i][0] << "," << path[i][1] << ")";
	std::cout << " expected=";
	for (int i = 0; i < expectedCount; ++i) std::cout << "(" << expected[i][0] << "," << expected[i][1] << ")";
	std::cout << "\n";
	delete[] used;
	for (int i = 0; i < aoe.eNum; ++i) delete[] path[i];
	delete[] path;
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
	pass += runCase("case1: two components with cycles", r1, 7, l1, 7, 2, 2);
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
	pass += runCase("case2: two cycles + one isolated", r2, 7, l2, 7, 3, 3);
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
	pass += runCase("case3: two cyclic components + two isolated", r3, 8, l3, 8, 4, 4);
	++total;

	// AOE case1 (single critical path)
	// 0 --4--> 1 --3--> 4 --4--> 6 --2--> 7
	//  \--2--> 2 --3--> 4
	//  \--1--> 3 --1--> 4
	//            \--3--> 5 --4--> 6
	// 1 --1--> 5, 2 --2--> 5
	// 期望关键活动: (0,1),(1,4),(4,6),(6,7)
	int c1_0[] = {0, 1};
	int c1_1[] = {0, 2};
	int c1_2[] = {0, 3};
	int c1_3[] = {1, 4};
	int c1_4[] = {2, 4};
	int c1_5[] = {3, 5};
	int c1_6[] = {4, 6};
	int c1_7[] = {5, 6};
	int c1_8[] = {2, 5};
	int c1_9[] = {1, 5};
	int c1_10[] = {3, 4};
	int c1_11[] = {6, 7};
	int *cr1[] = {c1_0, c1_1, c1_2, c1_3, c1_4, c1_5, c1_6, c1_7, c1_8, c1_9, c1_10, c1_11};
	int cl1[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
	const int cw1[][3] = {{0,1,4},{0,2,2},{0,3,1},{1,4,3},{2,4,3},{3,5,3},{4,6,4},{5,6,4},{2,5,2},{1,5,1},{3,4,1},{6,7,2}};
	const int ce1[][2] = {{0, 1}, {1, 4}, {4, 6}, {6, 7}};
	pass += runCriticalCase("critical1: weighted single critical path", cr1, 12, cl1, 8, cw1, 12, ce1, 4);
	++total;

	// AOE case2 (multi critical paths)
	// 0 --3--> 1 --4--> 4 --3--> 6 --2--> 7
	//  \--4--> 2 --2--> 4
	//  \--2--> 3 --3--> 4
	// 1 --2--> 5 --3--> 6
	// 2 --3--> 5
	// 3 --3--> 5
	// 存在多条从源点到汇点的路径，关键活动覆盖两条主干并在 6 汇合。
	// 期望关键活动: (0,1),(0,2),(1,4),(2,5),(4,6),(5,6),(6,7)
	int c2_0[] = {0, 1};
	int c2_1[] = {0, 2};
	int c2_2[] = {0, 3};
	int c2_3[] = {1, 4};
	int c2_4[] = {2, 4};
	int c2_5[] = {3, 4};
	int c2_6[] = {1, 5};
	int c2_7[] = {2, 5};
	int c2_8[] = {3, 5};
	int c2_9[] = {4, 6};
	int c2_10[] = {5, 6};
	int c2_11[] = {6, 7};
	int *cr2[] = {c2_0, c2_1, c2_2, c2_3, c2_4, c2_5, c2_6, c2_7, c2_8, c2_9, c2_10, c2_11};
	int cl2[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
	const int cw2[][3] = {{0,1,3},{0,2,4},{0,3,2},{1,4,4},{2,4,2},{3,4,3},{1,5,2},{2,5,3},{3,5,3},{4,6,3},{5,6,3},{6,7,2}};
	const int ce2[][2] = {{0, 1}, {0, 2}, {1, 4}, {2, 5}, {4, 6}, {5, 6}, {6, 7}};
	pass += runCriticalCase("critical2: weighted multi critical paths", cr2, 12, cl2, 8, cw2, 12, ce2, 7);
	++total;

	std::cout << "[SUMMARY] " << pass << "/" << total << " passed\n";
}
