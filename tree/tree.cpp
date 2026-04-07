#include "./tree.h"

avlTree::~avlTree() { _postDelete(this->root); }

avlNode *avlTree::search(int v) {
    // cur: 备选解
    avlNode *cur = root;
    while (cur != nullptr) {
        if (v == cur->val) {
            break;
        }
        if (v < cur->val) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return cur;
}

int getHeight(avlNode *node) {
    if (node != nullptr) {
        return node->_height;
    }
    return 0;
}

int getBalance(avlNode *node) {
    return getHeight(node->left) - getHeight(node->right);
}

void setHeight(avlNode *node) {
    if (node == nullptr) {
        return;
    }
    int a = getHeight(node->left);
    int b = getHeight(node->right);
    node->_height = 1 + (a > b ? a : b);
}

// i: 以i为根的子树是不平衡的原因

//   _root             left
//   /    \     =>     / \
// left               i  _root
// /  \lR               lR/ \
// i
avlNode *avlTree::_rRotate(avlNode *_root) {
    avlNode *left = _root->left;
    avlNode *lR = left->right;
    _root->left = lR;
    left->right = _root;
    setHeight(_root);
    setHeight(left);
    return left;
}

//   _root               right
//    / \                 /\
//       right  =>    _root  i
//      rL/ \          / \rL
//           i
avlNode *avlTree::_lRotate(avlNode *_root) {
    avlNode *right = _root->right;
    avlNode *rL = right->left;
    right->left = _root;
    _root->right = rL;
    setHeight(_root);
    setHeight(right);
    return right;
}
//   _root             _root        i
//   /    \     =>     / \    =>    /\
// left               i         left  _root
// /  \              /\iR       /\      iR/\
//     i          left
//   iL/\         /\iL

avlNode *avlTree::_lrRotate(avlNode *_root) {
    _root->left = _lRotate(_root->left);
    return _rRotate(_root);
}

//   _root               _root           i
//   /    \     =>       / \      =>     /\
//       right              i        _root  right
//      /  \             iL/ \       / \iL  / \
//     i                    right
//    /\iR                  iR/\

avlNode *avlTree::_rlRotate(avlNode *_root) {
    _root->right = _rRotate(_root->right);
    return _lRotate(_root);
}

avlNode *avlTree::_rebalance(avlNode *_root) {
    int balance = getBalance(_root);
    if (balance * balance > 2) {
        // 如果当前层需要调整，那他至少是插入点的爷爷
        int lh = getHeight(_root->left);
        int rh = getHeight(_root->right);
        if (lh > rh) {
			int llh = getHeight(_root->left->left);
			int lrh = getHeight(_root->left->right);
			if(llh >= lrh){ //出现取等情况：另一侧由于删除导致失衡
				// LL : R
				_root = _rRotate(_root);
			}else{
				// LR : LR
				_root = _lrRotate(_root);
			}
        }
        if (lh < rh) {
			int rlh = getHeight(_root->right->left);
			int rrh = getHeight(_root->right->right);
			if(rlh <= rrh){
				// RR : L
				_root = _lRotate(_root);
			}else{
				// RL : RL
				_root = _rlRotate(_root);
			}
        }
    }
    return _root;
}

// _root当前子树的根
//返回；子树的根
avlNode *avlTree::_insert(int v, avlNode *_root) {
    if (_root == nullptr) {
        return new avlNode(v);
    }
    if (v < _root->val) {
        _root->left = _insert(v, _root->left);
    }
    if (v > _root->val) {
        _root->right = _insert(v, _root->right);
    }
    setHeight(_root);
    // 在当层递归中调整
    return _rebalance(_root);
}

void avlTree::insert(int v) { root = _insert(v, root); }

avlNode *avlTree::_erase(int v, avlNode *_root) {
    if (_root == nullptr) {
        return _root;
    }
    if (v < _root->val) {
        _root->left = _erase(v, _root->left);
    }
    if (v > _root->val) {
        _root->right = _erase(v, _root->right);
    }
	//被删点的父节点开始可能会失衡
    if (v == _root->val) {
        // 1. 叶子=>直接删
        if (_root->left == nullptr && _root->right == nullptr) {
            delete _root;
            return nullptr;
        }
        // 2. 有一个孩子 =>孩子代替
        else if (_root->left == nullptr || _root->right == nullptr) {
            avlNode *newRoot = _root->left != nullptr ? _root->left : _root->right;
			delete _root;
            return newRoot;
        }
		// 3. 有2孩子 => 不删此点，此点val改为直接前驱val,删直接前驱，情况变为1 2
		//注意此时被删点为直接前驱
		else{
			avlNode * prev = _root->left;
			while(prev->right!=nullptr){
				prev = prev->right;
			}
			int newVal = prev->val;
			_root->left = _erase(newVal,_root->left);
			_root->val = newVal;
		}
    }
    setHeight(_root);
    // 在当层递归中调整
    return _rebalance(_root);
}


void avlTree::erase(int v) { root = _erase(v, root); }

void avlTree::_postDelete(avlNode *_root) {
	if(_root==nullptr){
		return;
	}
    if (_root->left != nullptr) {
        _postDelete(_root->left);
    }
    if (_root->right != nullptr) {
        _postDelete(_root->right);
    }
    delete _root;
}
