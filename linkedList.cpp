#include "./linkedList.h"

sNode *singleLinkedList::getNodeByIndex(int index) {
    if (index < -1 || index >= len) {
        return nullptr;
    }
    sNode *cur = head;
    for (int i = -1; i < index; ++i) {
        cur = cur->next;
    }
    return cur;
}

sNode *singleLinkedList::_insertNextNode(sNode *prev, int val) {
    sNode *next = prev->next;
    sNode *node = new sNode(val);
    prev->next = node;
    node->next = next;
    len++;
    return node;
}

sNode *singleLinkedList::insertNode(int index, int val) {
    sNode *prev = getNodeByIndex(index - 1);
    if (prev == nullptr) {
        return nullptr;
    }
    return _insertNextNode(prev, val);
}

// 单链表只能知道自己的后继，于是通过交换两节点的值将前插转化为后插
sNode *singleLinkedList::_insertPrevNode(sNode *next, int val) {
    int nextVal = next->val;
    next->val = val;
    return _insertNextNode(next, nextVal);
}

singleLinkedList::singleLinkedList(int data[], int n) {
    head = new sNode();
    len = 0;
    sNode *cur = head;
    for (int i = 0; i < n; ++i) {
        cur = _insertNextNode(cur, data[i]);
    }
}

// 单链表只能知道自己的后继，于是通过交换两节点的值转化为删后继
int singleLinkedList::_deleteNode(sNode *node) {
    sNode *next = node->next;
    int val = node->val;
    // 这里需要读取后一个节点的值，必须判断nullptr
    if (next != nullptr) {
        int nextVal = next->val;
        node->val = nextVal;
        node->next = next->next;
        node = next;
    }
    delete node;
    len--;
    return val;
}

int singleLinkedList::deleteNode(int index) {
    sNode *node = getNodeByIndex(index);
    if (node != nullptr) {
        return _deleteNode(node);
    }
    return -1;
}

sNode *singleLinkedList::lfindNode(int val) {
    for (sNode *cur = head->next; cur != nullptr; cur = cur->next) {
        if (cur->val == val) {
            return cur;
        }
    }
    return nullptr;
}

// 需要在next断之前找到next, 以及当前节点的“上一个”节点（head指出）。
void singleLinkedList::reverse() {
    if (len < 2) {
        return;
    }
    sNode *cur = head->next;
    head->next = nullptr;
    while (cur != nullptr) {
        sNode *next = cur->next;
        cur->next = head->next;
        head->next = cur;
        cur = next;
    }
}

// dlinkedlist
int dLinkedList::_deleteNode(dNode *node) {
    dNode *prev = node->prev;
    dNode *next = node->next;
	prev->next = next;
	if(next!=nullptr){
		next->prev=prev;
	}
	int val = node->val;
	delete node;
	len--;
	return val;
}

dNode* dLinkedList::_insertNextNode(dNode* node, int nextVal){
	dNode * next = node->next;
	dNode * ins=new dNode(nextVal);
	ins->prev = node;
	ins->next = next;
	node->next = ins;
	if(next!=nullptr){
		next->prev = ins;
	}
	len++;
	return ins;
}

dNode * dLinkedList::getNodeByIndex(int index){
	if(index<-1||index>=len){
		return nullptr;
	}
	dNode * cur = head;
	for(int i=-1;i<index;++i){
		cur=cur->next;
	}
	return cur;
}

dNode *dLinkedList::insertNode(int index,int val){
	dNode * prev=getNodeByIndex(index-1);
	if(prev==nullptr){
		return nullptr;
	}
	return _insertNextNode(prev,val);
}

int dLinkedList::deleteNode(int index){
	dNode *node = getNodeByIndex(index);
	if(node==nullptr){
		return -1;
	}
	return _deleteNode(node);
}