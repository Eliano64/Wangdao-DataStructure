#ifndef SQLIST_H
#define SQLIST_H

class sqList{
  protected:
    int MAXLEN;
    int len;
    int *data;

  public:
    sqList(int n = 10); 
    ~sqList(){ delete[] data; }
    inline int getLen() { return this->len; }

    bool insertElem(int n, int index);

    int deleteElem(int index);

    int getItemByIndex(int index);

    int lfindItem(int val);

    bool setItem(int index,int val);
};

class sqListDynamic : public sqList {
  protected:
    void _increaseMax(); 
  public:
    sqListDynamic(int n = 10) : sqList(n) {}

    bool insertElem(int n, int index);
};

#endif
