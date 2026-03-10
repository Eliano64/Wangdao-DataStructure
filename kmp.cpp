#include "kmp.h"
#include <string.h>

bool compare(char s[], int len, int step){
	for(int i=0;i+step<len;++i){
		if(s[i]!=s[i+step]){
			return false;
		}
	}
	return true;
}

int * getNextVal(char sub[]){
	int len = strlen(sub);
	int * next = new int[len];
	// if(len<2){
	// 	return nullptr;
	// }
	next[0]=-1;
	next[1]=0;
	if(sub[1]==sub[next[1]]){
		next[1]=next[next[1]];
	}
	for(int i=2;i<len;++i){
		for(int j=1;j<=i;++j){
			if(compare(sub,i,j)){
				next[i]=i-j;
				if(sub[i]==sub[next[i]]){
					next[i]=next[next[i]];
				}
				break;
			}
		}
	}
	return next;
}

int findSubStr(char s[], char sub[], int next[]) {
    int i = 0;
    int j = 0;
	int len1 =strlen(s);
	int len2 = strlen(sub);
    while (i < len1 && j < len2) {
        if (j == -1 || s[i] == sub[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
	delete [] next;
    if (sub[j] == '\0') {
        return i - j;
    }
    return -1;
}

int findSubStr(char s[], char sub[]){
	if(strlen(sub)==0){
		return 0;
	}
	if(strlen(sub)==1){
		char a = sub[0];
		for(int i=0;s[i]!='\0';++i){
			if(s[i]==a){
				return i;
			}
		}
		return -1;
	}
	if(strlen(s)<strlen(sub)){
		return -1;
	}
	int * next = getNextVal(sub);
	return findSubStr(s,sub,next);
}