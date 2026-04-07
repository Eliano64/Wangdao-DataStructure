#include "./sort.h"

inline void _swap(int &a, int &b) {
    if ((void *)&a == (void *)&b) {
        return;
    }
    int t = a;
    a = b;
    b = t;
}

// inline int _partition(int *A, int lo, int hi) {
// 	int pivot = A[hi-1];
// 	// x \in [lo, i], A[x] < pivot
// 	int i = lo - 1;
// 	// x \in [i+1, j), A[x] >= pivot
// 	for(int j = lo; j<hi-1; ++j){
// 		if(A[j]<pivot){ // then region gets bigger as i increased, and
// A[j] should be in A[lo..i] 			_swap(A[j],A[++i]);
// 		}
// 	}
// 	_swap(A[i+1],A[hi-1]);
//     return i+1;
// }

inline int _partition(int *A, int lo, int hi) {
    int pivot = A[lo];
    int i = lo;
    int j = hi - 1;
    // [lo, i] [i+1, j] [j+1,hi-1]
    while (i < j) {
        while (i < j && A[i + 1] <= pivot)
            ++i;
		while (i < j && A[j] > pivot)
			--j;
        if (i < j) {
            _swap(A[i + 1], A[j]);
        }
    }
    _swap(A[i], A[lo]);
    return i;
}

void quickSort(int *A, int lo, int hi) {
    if (lo + 1 >= hi) {
        return;
    }
    int mi = _partition(A, lo, hi);
    quickSort(A, lo, mi);
    quickSort(A, mi + 1, hi);
}

void _shiftDown(int *A, int i, int len) {
    while (i * 2 + 1 < len) {
        int more = A[i] > A[2 * i + 1] ? i : 2 * i + 1;
        if (i * 2 + 2 < len) {
            more = A[more] > A[2 * i + 2] ? more : 2 * i + 2;
        }
        if (more == i) {
            return;
        }
        _swap(A[more], A[i]);
        i = more;
    }
}

void _maxHeapInit(int *A, int len) {
    for (int i = len / 2 - 1; i >= 0; --i) {
        _shiftDown(A, i, len);
    }
};

// 大根堆
void heapSort(int *A, int len) {
    _maxHeapInit(A, len);
    for (int i = len - 1; i > 0; --i) {
        _swap(A[0], A[i]);
        _shiftDown(A, 0, i);
    }
}

void _merge(int *A, int lo, int mi, int hi, int *B) {
    int cur = lo;
    int i = lo, j = mi;
    while(i < mi && j < hi) {
        B[cur++] = A[i] < A[j] ? A[i++] : A[j++];
    }
    while (i<mi){
		B[cur++]=A[i++];
	}
	while(j<hi){
		B[cur++]=A[j++];
	}
	for(int k=lo;k<cur;++k){
		A[k] = B[k];
	}
}

//[lo, hi-1]
void _mergeSort(int *A, int lo, int hi, int *B) {
    if (lo >= hi-1) {
        return;
    }
    int mi = lo + (hi - lo) / 2;
    _mergeSort(A, lo, mi, B);
    _mergeSort(A, mi, hi, B);
    _merge(A, lo, mi, hi, B);
}

void mergeSort(int *A, int len) {
    int *B = new int[len]();
    _mergeSort(A, 0, len, B);
    delete[] B;
}
