#include "sqList.h"
#include <string.h>

sqList::sqList(int n) {
    this->MAXLEN = n >= 10 ? n : 10;
    this->data = new int[this->MAXLEN];
    ::memset(data, -1, MAXLEN * sizeof(int));
    this->len = 0;
}

void sqListDynamic::_increaseMax() {
    this->MAXLEN *= 2;
    int *tmp = new int[MAXLEN];
    ::memset(tmp, -1, MAXLEN * sizeof(int));
    memcpy(tmp, data, this->len * sizeof(int));
    delete[] data;
    this->data = tmp;
}

// 增
bool sqList::insertElem(int n, int index) {
    if (len == MAXLEN) {
        return false;
    }
    if (index < 0) {
        return false;
    }
    if (index >= len) {
        data[len++] = n;
    } else {
        for (int i = len; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = n;
        len++;
    }
    return true;
}

bool sqListDynamic::insertElem(int n, int index) {
    if (len == MAXLEN) {
        _increaseMax();
    }
    if (index < 0) {
        return false;
    }
    if (index >= len) {
        data[len++] = n;
    } else {
        for (int i = len; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = n;
        len++;
    }
    return true;
}

// 删
int sqList::deleteElem(int index) {
    if (index < 0 || index >= this->len) {
        return -1;
    } else {
        int tmp = this->data[index];
        for (int i = index + 1; i < this->len; ++i) {
            this->data[i - 1] = this->data[i];
        }
        --this->len;
        return tmp;
    }
}

// 查
int sqList::getItemByIndex(int index) {
    if (index < 0 || index >= this->len) {
        return -1;
    } else {
        return data[index];
    }
}

int sqList::lfindItem(int val) {
    for (int i = 0; i < len; ++i) {
        if (data[i] == val) {
            return i;
        }
    }
    return -1;
}

// 改
bool sqList::setItem(int index, int val) {
    if (index < 0 || index >= this->len) {
        return false;
    } else {
        data[index] = val;
        return true;
    }
}