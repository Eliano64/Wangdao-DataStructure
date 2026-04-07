#include "./search.h"

/// @brief
/// 为了简便,idxs有序且每一个元素必然在原数组的每一段里且为该段最大值；原数组段内无序但段内元素的最大值单增有序。
/// @param idxs 索引数组
/// @param iNum 索引数组长度
/// @param arr 原数组
/// @param regionLen 每段长度
/// @example {10, 20, 30}, 3, {1, 10, 8, 20, 13, 15, 11, 28, 27, 30}, {3,
/// 4, 3}
database::database(int *idxs, int iNum, int *arr, int *regionLen) {
    indexs = new index[iNum];
    idxLen = iNum;
    for (int i = 0; i < iNum; ++i) {
        indexs[i] = index(idxs[i]);
    }
    int t = 0; // 辅组变量，计算位置
    for (int i = 0; i < iNum; ++i) {
        if (i > 0) {
            t += regionLen[i - 1];
        }
        number *last = nullptr;
        for (int j = 0; j < regionLen[i]; ++j) {
            number *n = new number(arr[t + j]);
            if (indexs[i].first == nullptr) {
                indexs[i].first = n;
                indexs[i].firstLoc = t + j;
            } else {
				last->next= n;
            }
			last = n;
        }
    }
    arrLen = t + regionLen[iNum - 1];
}

database::~database() {
	for(int i = 0;i<idxLen;++i){
		for(number* cur = indexs[i].first;cur!=nullptr;){
			number * nxt = cur->next;
			delete cur;
			cur = nxt;
		}
	}
	delete[] indexs;
}

/// @brief
/// @param num target number
/// @return index of the first non-less one
int database::_binarySearch(int num) {
    int lo = 0, hi = idxLen, ans = idxLen;
    while (lo < hi) {
        int mi = lo + (hi - lo) / 2;
        if (indexs[mi].max >= num) {
            ans = mi;
            hi = mi;
        } else {
            lo = mi + 1;
        }
    }
    return ans;
}

/// @brief block search
/// @param tar
/// @return (tar应该在“原数据”里的位置)乘以(标志(找到:1,未找到：-1)) 段内未找到返回段内(最后一个元素位置+1)*(-1)
int database::blockSearch(int tar) {
    int loc0 = _binarySearch(tar);
    if (loc0 == idxLen) {
        return -arrLen;
    }
	int ans = indexs[loc0].firstLoc;
	for(number * cur = indexs[loc0].first;cur != nullptr; cur = cur->next){
		if(cur->num==tar){
			return ans;
		}
		ans ++;
	}
	return -ans;
}