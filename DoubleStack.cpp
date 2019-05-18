#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define True 1
#define False 0

typedef int Status;

typedef struct DoubleStack
{
    int top[2];
    int bot[2];
    DSElemType *v;
}DblStack;

Status Init(DblStack &S,int m){
    S.v = (DSElemType*)malloc(sizeof(DSElemType)*m);
    if(S.v == NULL) exit(ERROR);
    S.top[0] = -1;
    S.top[1] = m-1;
    S.bot[0] = 0;
    S.bot[1] = m-1;
    return OK;
}

Status Del(DblStack &S){
    free(S.v);
    S.v = NULL;
    return OK;
}

int Empty(DblStack S){
    if(S.top[0]==-1 && S.top[1] == S.bot[1])
        return 1;
    return 0;
}

