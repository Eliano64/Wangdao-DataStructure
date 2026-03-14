#include "./huffman.h"
#include "huffman.h"
#include <algorithm>

huffmanTree::huffmanTree(int a[], int len) {
	wpl = 0;
	if(len<2){
		return;
	}
	std::sort(a,a+len);
	int cur = 0;
	while(cur<len-1){
		int node = a[cur]+a[++cur];
		a[cur] = node;
		wpl += a[cur];
		std::sort(a+cur,a+len);
	}
}