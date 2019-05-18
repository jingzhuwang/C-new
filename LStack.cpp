#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define True 1
#define False 0

typedef int Status;

typedef struct Lnode
{
    SElemType data; //数据域
    struct Lnode *next; //指向下一个元素
} Lnode, *LStack;

Status Init_Stack(LStack &S){  //初始化栈
    S = NULL;
    return OK;
}

Status Del_Stack(LStack &S){   //销毁栈
    Lnode* p=S;
	while(p){
		S = S->next;
		free(p);
		p = S;
	}
	return OK;
}

Status Push(LStack &S, SElemType e){  //入栈
    Lnode* tmp = (LStack)malloc(sizeof(Lnode)); //开辟节点
    if(tmp == NULL) exit(ERROR); 
    tmp->data = e;  //数据与赋值
    tmp->next = S;
    S = tmp; 
    return OK;
}

Status Pop(LStack &S,SElemType& e){  //返回弹出值
    if (S == NULL)
        return ERROR;
    Lnode* tmp;
    tmp = S->next;
    e = S->data;
    free(S);
    S = tmp;
    return OK;
}

int Empty(LStack S){ //非空返回0，空返回1
    if(S == NULL)
        return OK;
    return ERROR;
}

SElemType GetTop(LStack S){  //取栈顶元素
    if (S == NULL)
        return ERROR;
    return S->data;
}
