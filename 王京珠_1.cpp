#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define True 1
#define False 0

typedef char SElemType;
typedef char QElemType;

typedef int Status;

/*
 *队列定义
 */
typedef struct ListNode
{
    QElemType data;
    struct ListNode* next;
}ListNode,*ListLink;

typedef struct ListQueue
{
    ListLink head;  //队头
    ListLink tail;  //队尾
    int len;
}ListQueue;

Status Init_Queue(ListQueue& Q){  //初始化队列
    Q.head=Q.tail=(ListLink)malloc(sizeof(ListNode));
    Q.tail->next=NULL;
    Q.len=0;
    return OK;
}

Status Del_Queue(ListQueue& Q){ //销毁队列
    ListLink tmp=Q.head;
    while(tmp!=NULL){
        Q.head=tmp->next;
        tmp=Q.head;
    }
    Q.head=Q.tail=NULL;
    return OK;
}

Status EnQueue(ListQueue& Q,QElemType item){ //入队
    ListNode* newNode = (ListLink)malloc(sizeof(QElemType));
    newNode->data = item;
    newNode->next = NULL;
    Q.tail->next=newNode;
    Q.tail=newNode;
    Q.len++;
    return OK;
}

Status DeQueue(ListQueue& Q){ //无返回引用值
    ListNode *tmp=Q.head->next;
    Q.head=tmp->next;
    free(tmp);
    Q.len--;
    return OK;
}

Status DeQueue(ListQueue& Q,QElemType& item){ //有返回引用值
    if(Q.head == Q.tail) return ERROR;
    ListNode *tmp=Q.head->next;
    item=tmp->data;
    Q.head->next = tmp->next;
    if(Q.tail == tmp) Q.head = Q.tail;
    Q.len--;
    return OK;
}

QElemType GetQueue(ListQueue Q){
    if(Q.head != Q.tail)
        return Q.head->next->data;
    return ERROR;
}

int Empty(ListQueue Q){ //判断队列是否为空，为空返回1
    return !Q.len;    
}

/*
 *堆栈定义
 */
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

/*
 *判断字符串是否是回文(用堆栈和队列实现)，如果是返回1，否则返回0
 *
 * 参数说明:
 *      c---字符串的首地址
 *      len---字符串长度
 * 
 */
int Judge(char *c,int len){
    if(c == NULL || len == 1) return 1;
    LStack S;
    ListQueue Q;
    char cQ,cS;
    int flag=1;
    Init_Stack(S);
    Init_Queue(Q);
    for(int i=0;i<len;i++){
        EnQueue(Q,c[i]);
        Push(S,c[i]);
    }
    while (!Empty(S)&&flag)
    {
        Pop(S,cS);
        DeQueue(Q,cQ);
        if( cS != cQ )
            flag = 0;
    }
    Del_Queue(Q);
    Del_Stack(S);
    return flag;
}

int main()
{
    char c[100];
    char tmp;
    int len = 0;
    printf("输入要判断的字符串(输入'#'停止输入，字符串最大长度100):\n");
    scanf("%c",&tmp);
    while(tmp!='#'){
        c[len] = tmp;
        len++;
        scanf("%c",&tmp);
    }
    if(Judge(c,len))
        printf("该字符串是回文！\n");
    else printf("该字符串不是回文！\n");
    printf("\n");
    system("pause");
    return 0;
}

/*
输入要判断的字符串(输入'#'停止输入，字符串最大长度100):
abcdefgfedcba#
该字符串是回文！

请按任意键继续. . .
*/