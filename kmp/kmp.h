#ifndef KMP
#define KMP

int* getNextVal(char sub[]);

int findSubStr(char s[],char sub[], int next[]);

int findSubStr(char s[], char sub[]);

bool compare(char s[], int len,int step);

#endif