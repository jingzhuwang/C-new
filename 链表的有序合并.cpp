#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct Lnode
{
    int data;
    struct Lnode *next;
} * LinkList, Lnode;

void Init(LinkList &L)
{
    L = (LinkList)malloc(sizeof(Lnode));
    L->data = 0;
    L->next = NULL;
}

void Insert(LinkList &L, int num)
{
    Lnode *p;
    p = (LinkList)malloc(sizeof(Lnode));
    p->next = L->next;
    p->data = num;
    L->next = p;
}

void FreeList_L(LinkList &L)
{
    //销毁带表头结点的单链线性表L
    LinkList p;
    while (L->next)
    {
        p = L->next;       //p指向第一个结点
        L->next = p->next; //表头结点的指针域指向第二个结点
        free(p);
    }
    free(L); //释放表头结点所占的空间
} //FreeList_L

void merge(LinkList &LA, LinkList &LB)
{
    Lnode *pa = LA->next;
    Lnode *pb = LB->next;
    Lnode *pre = LA;
    Lnode *tmp;
    while (pa->next && pb->next)
    {
        if (pa->data < pb->data)
        {
            pa = pa->next;
        }
        if (pa->data > pb->data)
        {
            tmp = pb->next;
            pb->next = pre->next;
            pre->next = pb;
            pb = tmp;
        }
        if (pa->data == pb->data)
        {
            tmp = pb->next;
            free(pb);
            pb = tmp;
            pa = pa->next;
        }
        pre = pre->next;
    }
    if (pb->next != NULL)
        pa->next = pb;
    free(LB);
}
int main()
{
    LinkList p;
    Init(p);
    LinkList q;
    Init(q);
    int a;
    cout << "输入第一个链表值(输入0结束输入)";
    cin >> a;
    while (a != 0)
    {
        Insert(p, a);
        cin >> a;
    }
    cout << "输入第二个链表值(输入0结束输入)";
    cin >> a;
    while (a != 0)
    {
        Insert(q, a);
        cin >> a;
    }
    merge(p, q);
    LinkList t = p->next;
    while (t)
    {
        cout << t->data << "   ";
        t = t->next;
    }
    cout << endl;
    FreeList_L(p);
    system("pause");
    return 0;
}
