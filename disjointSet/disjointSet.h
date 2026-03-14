#ifndef disjointSet_H
#define disjointSet_H

class disjointSet{
	public:
	int *parent; //为正表示父节点编号，为负（根）表示树中节点数，初始为-1
	int len;
	int find(int n); //路径压缩 O(a(n))
	int unionSet(int p, int n); //按秩压缩 O(log n)
	int countSet();
	disjointSet(int l);
	~disjointSet();
};

#endif
