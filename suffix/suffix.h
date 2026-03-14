#ifndef SUFFIX
#define SUFFIX

#include <string>
#include <utility>
#include <map>
#include <functional>


template<typename T>
class lStack;

template<typename T>
class sNode {
    friend class lStack<T>;
    T val;
    sNode<T> *next;
    sNode(T val = T()) : val(val), next(nullptr) {}
};

template<typename T>
class lStack {
private:
	sNode<T> *head;
	T _deleteTop();
  public:
    lStack() { head = new sNode<T>; }
    ~lStack(); 
	inline bool isEmpty(){
		return head->next==nullptr;
	}
	inline std::pair<bool,T> getTop(){
		return isEmpty() ? std::pair<bool, T>{false, T{}} : std::pair<bool, T>{true, head->next->val};
	}
	inline std::pair<bool,T> pop(){
		 return isEmpty() ? std::pair<bool, T>{false, T{}} : std::pair<bool, T>{true, _deleteTop()};
	}
	void push(T val);
};

using numbers = lStack<int>;
using operators = lStack<char>;

class suffix {
	numbers* num;
	operators* opt;
	int _calculate(char opt);
public:
	int out;
	suffix(std::string expr="");
	~suffix();
};

#endif