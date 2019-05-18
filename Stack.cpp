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
} Lnode, *Linklist;

typedef struct Stack
{
    Lnode* top;  //指向栈顶
    Lnode* base; //指向栈底
}Stack;

Status Init(Stack &S){  //初始化栈
    S.top = NULL;
    S.top = S.base;
    return OK;
}

Status Del(Stack &S){   //销毁栈
    Linklist p;
	while(S.top){
		p=S.top;
		S.top=S.top->next;
		free(p);
	}
	return OK;
}

Status Push(Stack &S, SElemType item){  //入栈
    Linklist tmp = (Linklist)malloc(sizeof(Lnode));
    if(tmp == NULL) exit(ERROR);
    tmp->data = item;
    tmp->next = S.top;
    S.top = tmp;
    if(S.top == NULL) S.base = S.top;
    return OK;
}

Status Pop(Stack &S){  //出栈，不返回弹出值
    if (S.top == NULL)
        return ERROR;
    Linklist tmp = S.top;
    S.top = tmp->next;
    free(tmp);
    return OK;
}

Status Pop(Stack &S,SElemType &item){  //返回弹出值
    if (S.top == NULL)
        return ERROR;
    Linklist tmp = S.top;
    item = S.top->data;
    S.top = S.top->next;
    free(tmp);
    return OK;
}

int Empty(Stack S){ //非空返回0，空返回1
    if(S.top == NULL)
        return OK;
    return ERROR;
}

SElemType GetTop(Stack S){  //取栈顶元素
    if (S.top == NULL)
        return ERROR;
    return S.top->data;
}

/*int main()
{
    Stack S;
    Init(S);
    for (int i = 0; i < 10; i++)
    {
        Push(S,i);
    }   
    Diaplay(S);
    Del(S);
    cout<<endl;
    system("pause");
    return 0;
}*/
