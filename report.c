#ifndef REPORT_H_
#define REPORT_H_

#include <stdio.h>

#include "replace.c"
//#include "traversal.c"

struct fileUpdates {
    int updates;
    char *pathname;
};

//struct fileUpdates arrayOfStruct[20];
/*
void reportUpdates(int update, char *path, int countFiles){
    for(int i = countFiles; i < 20; i++){
        arrayOfStruct[i].updates = update;
        printf("\nupdates in report: %d\n", arrayOfStruct[i].updates);
        arrayOfStruct[i].pathname = path;
        printf("\npath in report: %s\n", arrayOfStruct[i].pathname);
    }
}
*/

int compareUpdates(const void *a, const void *b){
    const struct fileUpdates *x = a;
    const struct fileUpdates *y = b;
    return (x->updates - y->updates);
}

#endif //REPORT