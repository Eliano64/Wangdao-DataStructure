#include "suffix.h"
#include "iostream"

static std::unordered_map<char, std::function<int(int, int)>> operatorMap = {
    {'+', [](int a, int b) { return a + b; }},
    {'-', [](int a, int b) { return a - b; }},
    {'*', [](int a, int b) { return a * b; }},
    {'/', [](int a, int b) { return a / b; }}};

static std::unordered_map<char, int> priorMap = {
    {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'(', -1}};

template <typename T> T lStack<T>::_deleteTop() {
    sNode<T> *next = head->next;
    T val = next->val;
    // std::cout<<"popval"<<val<<'\n';
    head->next = next->next;
    delete next;
    return val;
}

template <typename T> void lStack<T>::push(T val) {
    sNode<T> *node = new sNode<T>(val);
    node->next = head->next;
    head->next = node;
    // std::cout<<node->val<<'\n';
}

template <typename T> lStack<T>::~lStack() {
    for (sNode<T> *cur = head; cur != nullptr;) {
        sNode<T> *tmp = cur;
        cur = cur->next;
        delete tmp;
    }
}

int suffix::_calculate(char opt) {
    auto [ok1, num2] = num->pop();
    auto [ok2, num1] = num->pop();
    if (!(ok1 && ok2)) {
        // std::cout<<ok1<<ok2<<' ';
        return -1;
    }
    // 顺序！！！右操作数先出栈！
    return operatorMap[opt](num1, num2);
    // std::cout << num1 << num2 << top << num3 << ' ';
}

suffix::suffix(std::string expr) {
    num = new numbers;
    opt = new operators;

    out = 0;
    if (expr == "") {
        return;
    }
    for (const char &r : expr) {
        if (r == ')') {
            auto [valid, top] = opt->pop();
            do {
                int num3 = _calculate(top);
                if (num3 == -1) {
                    return;
                }
                num->push(num3);
                if (top != '(') {
                    auto [okTop, nextTop] = opt->pop();
                    if (!okTop) {
                        return;
                    }
                    top = nextTop;
                }
            } while (top != '(');

        } else if (operatorMap.find(r) == operatorMap.end() && r != '(') {
            num->push((int)(r - '0'));
        } else {
            // 符号入栈：先将所有优先级不小于他的出栈
            if (!opt->isEmpty()) {
                // std::cout<<priorMap[r]<<priorMap[opt->getTop().second]<<' ';
                while (priorMap[opt->getTop().second] >= priorMap[r]) {
                    auto [valid, top] = opt->pop();
                    int num3 = _calculate(top);
                    if (num3 == -1) {
                        return;
                    }
                    std::cout << num3 << ' ';
                    num->push(num3);
                }
            }
            opt->push(r);
        }
    }
    while (!opt->isEmpty()) {
        auto [valid, top] = opt->pop();
        if (top == '(') {
            return;
        }
        int num3 = _calculate(top);
        if (num3 == -1) {
            return;
        }
        num->push(num3);
    }

    out = num->pop().second;
    // if(!_){
    // 	std::cout<<"!!!!\n";
    // }
}

suffix::~suffix() {
    delete num;
    delete opt;
}