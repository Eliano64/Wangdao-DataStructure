#include "../utils.h"
#include "./sqList.h"

void debug(sqList *l){
    std::cout << "[len:] " << l->getLen() << "\n[data:] ";
    for (int i = 0; i < l->getLen(); ++i) {
        std::cout << l->getItemByIndex(i) << " ";
    }
    std::cout << "\n";
}

void testSqList() {
    sqList *l1 = new sqList;
    sqListDynamic *l2 = new sqListDynamic;
    // test init
    std::cout << l1->getLen() << " " << l2->getLen() << '\n';
    debug(l1);
    debug(l2);

    // test insertElem
    for (int i = 0; i < 5; ++i) {
        l1->insertElem(i, i);
        l2->insertElem(i, i);
    }
    // 0 1 2 3 4 ...
    debug(l1);
    debug(l2);
    for (int i = 5; i < 10; ++i) {
        l1->insertElem(i, i - 5);
        l2->insertElem(i, i - 5);
    }
    // 5 6 7 8 9 0 1 2 3 4
    debug(l1);
    debug(l2);
    std::cout << l1->insertElem(10, 10) << '\n';
    std::cout << l2->insertElem(10, 10) << '\n';
    //...
    // 5 6 7 8 9 0 1 2 3 4 10 ...
    debug(l1);
    debug(l2);

    // test deleteElem
    std::cout << l1->deleteElem(-1) << '\n';
    std::cout << l2->deleteElem(11) << '\n';
    //...
    debug(l1);
    debug(l2);
    // 0
    std::cout << l1->deleteElem(5) << '\n';
    // 5 6 7 8 9 1 2 3 4 .
    debug(l1);

    //test get/find
    // -1
    std::cout<<l1->lfindItem(0)<<'\n';
    // 8
    std::cout<<l1->lfindItem(4)<<'\n';
    // 9
    std::cout<<l1->getItemByIndex(4)<<'\n';
    // -1 
    std::cout<<l1->getItemByIndex(9)<<'\n';

    delete l1;
    delete l2;

    sqList *l3 = new sqList;
    for(int i = 0; i < 5; ++i){
        l3->insertElem(i%2,i);
    }
    int idx;
    while( (idx = l3->lfindItem(0)) != -1){
        l3->setItem(idx,2);
    }
    //2 1 2 1 2 ...
    debug(l3);

    delete l3;
}

void test() {
    testSqList();
}