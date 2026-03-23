#ifndef sort_H
#define sort_H

class number {
  public:
    int num;
    number *next;
    number(int t) : num(t), next(nullptr){};
};

class index {
  public:
    int max;
	int firstLoc;
    number *first;
    index(int t = 0, int l=0) : max(t),  firstLoc(l), first(nullptr){};
};


class database{
	int _binarySearch(int num);
	index * indexs;
	int idxLen;
	int arrLen;
	public:
		database(int * idxs, int iNum, int* arr, int * regionLen);
		~database();
		int blockSearch(int tar);
};

#endif
