#ifndef tree_H
#define tree_H

// avl
class avlNode {
	friend int getHeight(avlNode *node);
	friend int getBalance(avlNode *node);
	friend void setHeight(avlNode *node);
  private:
    int _height; // 计算balance用。以该节点为根的二叉树的高度
  public:
    int val;
    avlNode *left;
    avlNode *right;
    avlNode(int v) : _height(1), val(v), left(nullptr), right(nullptr) {};
};

class avlTree {
  private:
    void _postDelete(avlNode *_root);
	avlNode* _insert(int v, avlNode *_root);
	avlNode * _rRotate(avlNode *_root);
	avlNode * _lRotate(avlNode *_root);
	avlNode * _lrRotate(avlNode *_root);
	avlNode * _rlRotate(avlNode *_root);
	avlNode * _erase(int v, avlNode * _root);
	avlNode * _rebalance(avlNode *_root);
  public:
    avlNode *root;
	avlTree():root(nullptr) {};
    ~avlTree(); 
    /// 寻找值对应的节点的位置。若没有则返回nullptr
    // 循环
    avlNode *search(int v); 
	//规定每个节点的值相异
    void insert(int v);
	void erase(int v);
};

#endif
