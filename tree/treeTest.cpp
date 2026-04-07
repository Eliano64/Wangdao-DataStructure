#include "./tree.h"
#include "../utils.h"
#include <climits>
#include <cmath>
#include <string>
#include <vector>
#include <queue>

static int h(avlNode *n) {
	return n == nullptr ? 0 : 1 + std::max(h(n->left), h(n->right));
}

static bool bst(avlNode *n, long long lo, long long hi, std::string &msg) {
	if (n == nullptr) return true;
	if (!(lo < n->val && n->val < hi)) {
		msg = "BST violated at node=" + std::to_string(n->val);
		return false;
	}
	return bst(n->left, lo, n->val, msg) && bst(n->right, n->val, hi, msg);
}

static bool avl(avlNode *n, std::string &msg) {
	if (n == nullptr) return true;
	int lh = h(n->left), rh = h(n->right);
	if (std::abs(lh - rh) > 1) {
		msg = "AVL violated at node=" + std::to_string(n->val) + ", lh=" + std::to_string(lh) + ", rh=" + std::to_string(rh);
		return false;
	}
	return avl(n->left, msg) && avl(n->right, msg);
}

static void levelOrder(avlNode *n, std::vector<int> &out) {
	if (n == nullptr) return;
	std::queue<avlNode *> q;
	q.push(n);
	while (!q.empty()) {
		avlNode *cur = q.front();
		q.pop();
		out.push_back(cur->val);
		if (cur->left != nullptr) q.push(cur->left);
		if (cur->right != nullptr) q.push(cur->right);
	}
}

static bool expectTree(const char *name, avlTree &t, const std::vector<int> &exp) {
	std::string msg;
	bool ok1 = bst(t.root, LLONG_MIN, LLONG_MAX, msg);
	if (!ok1) std::cout << "[FAIL] " << name << " " << msg << "\n";
	msg.clear();
	bool ok2 = avl(t.root, msg);
	if (!ok2) std::cout << "[FAIL] " << name << " " << msg << "\n";
	std::vector<int> got;
	levelOrder(t.root, got);
	bool ok3 = got == exp;
	std::cout << ((ok1 && ok2 && ok3) ? "[PASS] " : "[FAIL] ") << name << " level=";
	for (int i = 0; i < (int)got.size(); ++i) std::cout << got[i] << (i + 1 == (int)got.size() ? ' ' : ',');
	std::cout << "expected=";
	for (int i = 0; i < (int)exp.size(); ++i) std::cout << exp[i] << (i + 1 == (int)exp.size() ? '\n' : ',');
	if (exp.empty()) std::cout << "empty\n";
	return ok1 && ok2 && ok3;
}

static bool testEmptyAndBoundaryOps() {
	avlTree t;
	bool ok = t.root == nullptr && t.search(1) == nullptr;
	t.erase(1);
	ok = expectTree("empty erase", t, {}) && ok;
	t.insert(INT_MIN);
	t.insert(INT_MAX);
	ok = expectTree("boundary insert", t, {INT_MIN, INT_MAX}) && ok;
	ok = (t.search(INT_MIN) != nullptr && t.search(INT_MAX) != nullptr && t.search(0) == nullptr) && ok;
	std::cout << (ok ? "[PASS] " : "[FAIL] ") << "boundary search\n";
	return ok;
}

static bool testDuplicateAndSearch() {
	avlTree t;
	t.insert(5); t.insert(3); t.insert(7); t.insert(3); t.insert(5); t.insert(7);
	bool ok = expectTree("duplicate insert", t, {5, 3, 7});
	ok = (t.search(3) != nullptr && t.search(4) == nullptr) && ok;
	std::cout << (ok ? "[PASS] " : "[FAIL] ") << "duplicate search\n";
	return ok;
}

static bool testRotationShapes() {
	bool ok = true;
	avlTree ll; ll.insert(3); ll.insert(2); ll.insert(1);
	ok = (ll.root && ll.root->val == 2 && ll.root->left && ll.root->left->val == 1 && ll.root->right && ll.root->right->val == 3) && expectTree("LL", ll, {2, 1, 3}) && ok;
	avlTree rr; rr.insert(1); rr.insert(2); rr.insert(3);
	ok = (rr.root && rr.root->val == 2 && rr.root->left && rr.root->left->val == 1 && rr.root->right && rr.root->right->val == 3) && expectTree("RR", rr, {2, 1, 3}) && ok;
	avlTree lr; lr.insert(3); lr.insert(1); lr.insert(2);
	ok = (lr.root && lr.root->val == 2 && lr.root->left && lr.root->left->val == 1 && lr.root->right && lr.root->right->val == 3) && expectTree("LR", lr, {2, 1, 3}) && ok;
	avlTree rl; rl.insert(1); rl.insert(3); rl.insert(2);
	ok = (rl.root && rl.root->val == 2 && rl.root->left && rl.root->left->val == 1 && rl.root->right && rl.root->right->val == 3) && expectTree("RL", rl, {2, 1, 3}) && ok;
	return ok;
}

static bool testEraseCases() {
	avlTree t;
	int a[] = {20, 10, 30, 5, 15, 25, 40, 13, 17};
	for (int x : a) t.insert(x);
	bool ok = true;
	t.erase(13); ok = expectTree("erase leaf", t, {20, 10, 30, 5, 15, 25, 40, 17}) && ok;
	t.erase(15); ok = expectTree("erase one child", t, {20, 10, 30, 5, 17, 25, 40}) && ok;
	t.erase(20); ok = expectTree("erase two children", t, {17, 10, 30, 5, 25, 40}) && ok;
	t.erase(999); ok = expectTree("erase missing", t, {17, 10, 30, 5, 25, 40}) && ok;
	return ok;
}

static bool testInsertStress() {
	avlTree t;
	for (int i = 1; i <= 1000; ++i) {
		t.insert(i);
		std::string msg;
		if (!bst(t.root, LLONG_MIN, LLONG_MAX, msg) || !avl(t.root, msg)) {
			std::cout << "[FAIL] insert stress at i=" << i << " " << msg << "\n";
			return false;
		}
	}
	for (int i = 1; i <= 1000; ++i) if (t.search(i) == nullptr) return false;
	bool ok = h(t.root) <= 2 * (int)std::log2(1000) + 3;
	std::cout << (ok ? "[PASS] " : "[FAIL] ") << "insert stress height=" << h(t.root) << "\n";
	return ok;
}

static bool testEraseStress() {
	avlTree t;
	for (int i = 1; i <= 512; ++i) t.insert(i);
	for (int i = 1; i <= 512; i += 2) {
		t.erase(i);
		std::string msg;
		if (!bst(t.root, LLONG_MIN, LLONG_MAX, msg) || !avl(t.root, msg)) {
			std::cout << "[FAIL] erase stress at i=" << i << " " << msg << "\n";
			return false;
		}
	}
	for (int i = 1; i <= 512; ++i) {
		if ((t.search(i) != nullptr) != (i % 2 == 0)) return false;
	}
	std::cout << "[PASS] erase stress\n";
	return true;
}

void test() {
	int pass = 0;
	int total = 6;
	pass += testEmptyAndBoundaryOps();
	pass += testDuplicateAndSearch();
	pass += testRotationShapes();
	pass += testEraseCases();
	pass += testInsertStress();
	pass += testEraseStress();
	std::cout << "[SUMMARY] " << pass << "/" << total << " passed\n";
}
