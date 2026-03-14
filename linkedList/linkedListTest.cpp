#include "../utils.h"
#include "./linkedList.h"


void debug(singleLinkedList *l) {
	std::cout << "[s-data:] ";
	sNode *node = l->head;
	while (node != nullptr) {
		std::cout << "{val:" << node->val << ", next:" << node->next << "} ";
		node = node->next;
	}
	std::cout << '\n';
	std::cout << "[s-len:] " << l->getLen() << "\n";
}

void debug(dLinkedList *l) {
	std::cout << "[d-data:] ";
	dNode *node = l->head;
	while (node != nullptr) {
		std::cout << "{val:" << node->val << ", prev:" << node->prev << ", next:" << node->next << "} ";
		node = node->next;
	}
	std::cout << '\n';
	std::cout << "[d-len:] " << l->getLen() << "\n";
}

void testSingleLinkedList() {
	singleLinkedList *l1 = new singleLinkedList;
	debug(l1);
	for (int i = 0; i < 7; ++i) {
		l1->insertNode(i, i + 1);
	}
	debug(l1);
	sNode *n2 = l1->getNodeByIndex(2);
	std::cout << (n2 == nullptr ? -1 : n2->val) << '\n';
	int d0 = l1->deleteNode(0);
	std::cout << d0 << '\n';
	debug(l1);
	int d1 = l1->deleteNode(3);
	std::cout << d1 << '\n';
	debug(l1);
	int d2 = l1->deleteNode(l1->getLen()-1);
	std::cout << d2 << '\n';
	debug(l1);
	sNode *f = l1->lfindNode(4);
	std::cout << (f == nullptr ? -1 : f->val) << '\n';
	int data[] = {7, 8, 9, -1};
	singleLinkedList *l2 = new singleLinkedList(data, 4);
	debug(l2);
	l2->reverse();
	debug(l2);
	delete l1;
	delete l2;
}

void testDLinkedList() {
	dLinkedList *l = new dLinkedList;
	debug(l);
	for (int i = 0; i < 5; ++i) {
		l->insertNode(i, i + 10);
	}
	debug(l);
	dNode *n2 = l->getNodeByIndex(2);
	std::cout << (n2 == nullptr ? -1 : n2->val) << '\n';
	l->insertNode(2, 99);
	debug(l);
	std::cout << l->deleteNode(0) << '\n';
	debug(l);
	std::cout << l->deleteNode(2) << '\n';
	debug(l);
	std::cout << l->deleteNode(l->getLen() - 1) << '\n';
	debug(l);
	delete l;
}

void test() {
	testSingleLinkedList();
	testDLinkedList();
}

