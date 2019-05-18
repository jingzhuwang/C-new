#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct BiNode
{
    BElemType data;
    struct BiNode *lchild;
    struct BiNode *rchild;
} BitNode, *BitTree;

typedef BitTree QElemType;
typedef BitTree SElemType;
#include "ListQueue.cpp"
#include "Stack.cpp"

int len = 0;

void Init(BitTree &T)
{ //初始化
    T = new BitNode;
    T->lchild = NULL;
    T->rchild = NULL;
}

void Del(BitTree &T)
{ //删除树
    BitNode *tmp = T;
    if (T)
    {
        Del(T->rchild);
        Del(T->lchild);
        delete tmp;
    }
}

void Create(BitTree &T)
{ //创建树
    BElemType c;
    cin >> c;
    if (c == '#')
        T = NULL;
    else
    {
        T = new BitNode;
        T->data = c;
        Create(T->lchild);
        Create(T->rchild);
    }
}

int Depth(BitTree &T)
{ //求树的深度
    if (T == NULL)
        return 0;
    else
    {
        int m = Depth(T->lchild);
        int n = Depth(T->rchild);
        if (m > n)
            return (m + 1);
        else
            return (n + 1);
    }
}

int End_Point_Count(BitTree &T)
{ //端点个数统计
    if (T == NULL)
        return 0;
    if (T->rchild == NULL && T->lchild == NULL)
        return 1;
    return End_Point_Count(T->lchild) + End_Point_Count(T->rchild);
}

int Node_Count(BitTree &T)
{ //节点个数统计
    if (T == NULL)
        return 0;
    else
        return Node_Count(T->lchild) + Node_Count(T->rchild);
}

void Traver(BitTree &T)
{ //求任意二叉树中第一条最长的路径长度，并输出此路径上的节点值
    if (T == NULL)
        return;
    if (T)
    {
        len++; //全局变量
        cout << T->data << "  ";
        int m = Depth(T->lchild);
        int n = Depth(T->rchild);
        if (m > n)
            Traver(T->lchild);
        else
            Traver(T->rchild);
    }
}

int Compare(BitTree &T1, BitTree &T2)
{ //比较两棵二叉树是否相等，相等返回1，不等返回-1
    if (T1 == NULL && T2 == NULL)
        return 1;
    if (!(T1 && T2))
        return 0;
    if (T1->data != T2->data)
        return 0;
    return Compare(T1->lchild, T2->lchild) && Compare(T1->rchild, T2->rchild);
}

void InOrderTraver(BitTree T)
{ //中序遍历二叉树
    if (T)
    {
        InOrderTraver(T->lchild); //中序遍历左子树
        cout << T->data << "   "; //中序遍历根节点
        InOrderTraver(T->rchild); //中序遍历右节点
    }
}

void PreOrderTraver(BitTree T)
{ //先序遍历二叉树
    if (T)
    {
        cout << T->data << "    "; //先序遍历根节点
        PreOrderTraver(T->lchild); //先序遍历左子树
        PreOrderTraver(T->rchild); //先序遍历右子树
    }
}

void PostOrderTraver(BitTree T)
{ //后序遍历二叉树
    if (T)
    {
        PostOrderTraver(T->lchild); //后序遍历左子树
        PostOrderTraver(T->rchild); //后序遍历右子树
        cout << T->data << "    ";  //后序遍历根节点
    }
}

//中序遍历二叉树，该函数需要包含栈的应用,栈中的数据类行为 BitNode* 类型
void InorderTraver_Stack(BitTree T)
{
    Stack S;
    Init(S);
    BitNode *p = T;
    BitNode *q = new BitNode;
    while (p || !Empty(S))
    {
        if (p)
        {
            Push(S, p);
            p = p->lchild;
        }
        else
        {
            Pop(S, q);
            cout << q->data << "  ";
            p = q->rchild;
        }
    }
    Del(S);
}

//层序遍历二叉树，需要用到队列， 队列中元素类型为 BitNode*
void ChengxuTraver(BitTree T)
{
    ListQueue Q;
    Init(Q);
    BitNode *tmp = T;
    EnQueue(Q, tmp);
    while (!Empty(Q))
    {
        DeQueue(Q, tmp);
        if (tmp)
        { //当tmp不为空时
            EnQueue(Q, tmp->lchild);
            EnQueue(Q, tmp->rchild);
            cout << tmp->data << "  ";
        }
    }
    Del(Q);
}

    