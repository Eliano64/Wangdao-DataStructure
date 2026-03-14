#ifndef LINKEDLIST
#define LINKEDLIST

class sNode {
  public:
    int val;
    sNode *next;
    sNode(int v = -1) : val(v), next(nullptr) {}
};

class singleLinkedList {
  private:
    int len;
    sNode *_insertNextNode(sNode *prev, int val);
    sNode *_insertPrevNode(sNode *next, int val); // O(1)
    int _deleteNextNode(sNode *node);                 

  public:
    sNode *head;
    inline int getLen() { return len; }
    singleLinkedList() {
        head = new sNode();
        len = 0;
    }
    ~singleLinkedList() {
        while (head != nullptr) {
            sNode *tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    singleLinkedList(int data[], int n); // O(n)

    sNode *getNodeByIndex(int index);

    sNode *insertNode(int index, int val);

    int deleteNode(int index);

    sNode *lfindNode(int val);

    void reverse(); // O(n)
};

class dNode {
  public:
    int val;
    dNode *next, *prev;
    dNode(int v = -1) : val(v), next(nullptr), prev(nullptr) {}
};

class dLinkedList{
	private:
    int len;
    int _deleteNode(dNode *node);                
	dNode* _insertNextNode(dNode *node,int nextVal);
  public:
    dNode *head;
    inline int getLen() { return len; }
    dLinkedList() {
        head = new dNode();
        len = 0;
    }
    ~dLinkedList() {
        while (head != nullptr) {
            dNode *tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    dNode *getNodeByIndex(int index);

    dNode *insertNode(int index, int val);

    int deleteNode(int index);
};

#endif