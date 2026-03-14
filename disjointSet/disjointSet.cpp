#include "./disjointSet.h"
#include "disjointSet.h"
#include <string.h>

int disjointSet::find(int n) {
    int root = n;
    while (parent[root] >= 0) {
        root = parent[root];
    }
    while (n != root) {
        int tmp = n;
        n = parent[n];
        parent[tmp] = root;
    }
    return root;
}

int disjointSet::unionSet(int p, int n) {
    int p0 = find(p);
    int n0 = find(n);
    if (-p0 >= -n0) {
        parent[p0] += parent[n0];
        parent[n0] = p0;
        return p0;
    }
    parent[n0] += parent[p0];
    parent[p0] = n0;
    return n0;
}

int disjointSet::countSet() {
	int cnt = 0;
    for (int i = 0; i < len; ++i) {
        cnt += parent[i] < 0;
    }
	return cnt;
}

disjointSet::disjointSet(int l) {
    len = l;
    parent = new int[len];
    ::memset(parent, -1, len * sizeof(int));
}

disjointSet::~disjointSet() { delete[] parent; }
