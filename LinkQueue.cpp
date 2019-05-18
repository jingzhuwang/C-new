//* * * * * * * * * * * * * * * * * * *
// 章  节 : 第3章 栈和队列            *
// 程序名 : 链式队列                  *
// 功  能 : 初始化,入队列,出队列      *
//* * * * * * * * * * * * * * * * * * *
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#define TRUE       1
#define FALSE      0
#define OK         1
#define ERROR      0
#define INFEASIBLE -1
#define OVERFLOW   -2

//Status 是函数的类型,其值是函数结果状态代码
typedef int Status;
//ElemType 是顺序表数据元素类型,此程序定义为int型
typedef int QElemType;

//-----单链队列--队列的链式存储结构-----
typedef struct QNode{       //定义结点结构
	QElemType     data;     //数据域
	struct QNode *next;     //指针域
}QNode,*QueuePtr;
typedef struct linkqueue{  //定义队列结构
	QueuePtr front;        //队头指针
	QueuePtr rear;         //队尾指针
}LinkQueue;

Status InitLinkQueue(LinkQueue &);          //初始化一个队列
Status DestroyLinkQueue(LinkQueue &);       //销毁一个队列
int LinkQueueLength(LinkQueue &Q);          //队列的长度
Status EnLinkQueue(LinkQueue &,QElemType);  //将一个元素入队列
Status DeLinkQueue(LinkQueue &,QElemType &);//将一个元素出队列
Status DisplayLinkQueue(LinkQueue);         //显示队列中所有元素

void main(){
	LinkQueue LQ;
	QElemType e;
	int flag=1,ch,len;
	Status temp;
	//---------------------程序解说-----------------------
	printf("本程序实现链式结构队列的操作。\n");
	printf("可以进行入队列、出队列等操作。\n");
	//----------------------------------------------------
	InitLinkQueue(LQ);       //初始化队列
	while(flag){
		printf("请选择:\n");
		printf("1.显示队列所有元素\n");
		printf("2.入队列\n");
		printf("3.出队列\n");
		printf("4.求队列的长度\n");
		printf("5.退出程序\n");
		scanf("%d",&ch);
		switch(ch){
		case 1:DisplayLinkQueue(LQ);   //显示队列中所有元素
			break;
		case 2:printf("请输入要人队的元素(一个整数):");
			scanf("%d",&e);   //输入要入队列的字符
			EnLinkQueue(LQ,e);//入队列
			DisplayLinkQueue(LQ);
			break;
		case 3:temp=DeLinkQueue(LQ,e);  //出队列
			if(temp==OK){
				printf("出队一个元素:%d\n",e);
				DisplayLinkQueue(LQ);
			}
			else printf("队列为空!\n");
			break;
		case 4:len=LinkQueueLength(LQ);
			printf("队列的长度为:%d\n",len);
			break;
		default:flag=0;
			printf("程序运行结束，按任意键退出!\n");
			getch();
		}
	}
}

Status InitLinkQueue(LinkQueue &Q){//队列初始化
	Q.front=Q.rear=(QueuePtr) malloc(sizeof(QNode)); //生成一个头结点，并把首尾指针指向头结点
	Q.front->next=NULL;
	return OK;
}
Status DestroyLinkQueue(LinkQueue &Q){//销毁一个队列
	QueuePtr p;
	QElemType e;
	while(Q.front!=Q.rear)
		DeLinkQueue(Q,e);
	free(Q.front);
	Q.front=Q.rear=NULL;
	return OK;
}

int LinkQueueLength(LinkQueue &Q){//队列的长度
	int i=0;
	QueuePtr p=Q.front;
	while(p!=Q.rear){
		++i;
		p=p->next;
	}
	return i;
}

Status EnLinkQueue(LinkQueue &Q,QElemType e){//入队列
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));//生成一个新结点
	p->data=e;                      //赋值
	p->next=NULL;
	Q.rear->next=p;                 //插入至队列尾
	Q.rear=p;                       //修改队尾指针
	return OK;
}

Status DeLinkQueue(LinkQueue &Q,QElemType &e){//出队列
	QueuePtr p;
	if(Q.front==Q.rear) return ERROR;     //判断队列是否已空，已空返回ERROR
	p=Q.front->next;                      //p指向队列中第一个元素
	e=p->data;                            //取得该元素值
	Q.front->next=p->next;                //修改队首指针
	if(Q.rear==p) Q.rear=Q.front;         //若队列已空，把队尾指针指向头结点
	free(p);
	return OK;                            //成功出队列，返回OK
}

Status DisplayLinkQueue(LinkQueue Q){//显示队列中所有元素
	QueuePtr p;
	int i=0;
	p=Q.front->next;
	if(p==NULL) printf("队列为空!\n");//队列为空
	else{
		while(p){       //否则显示队列中所有元素
			printf("[%d:%d]",++i,p->data);
			p=p->next;
		}
		printf("\n");
	}
	return OK;
}
