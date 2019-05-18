//* * * * * * * * * * * * * * * * * * * * *
// 章  节 : 第2章 线性表                  *
// 程序名 : 单链表  (最终版式 2002.9.28)  *
// 功  能 : 插入,删除,查找,显示           *
//* * * * * * * * * * * * * * * * * * * * *

#include <stdio.h>
#include <stdlib.h>
//#include <dos.h>
#include <conio.h>

#define TRUE       1
#define FALSE      0
#define OK         1
#define ERROR      0
#define INFEASIBLE -1
#define OVERFLOW   -2

//Status 是函数的类型,其值是函数结果状态代码
typedef int Status;
//ElemType 是单链表数据元素类型,此程序定义为int型
typedef int ElemType;

//---线性表的单链表存储结构---
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList; 

void CreateList_L(LinkList &L){
	//建立带表头结点的单链表L,并逆位序输入各元素的值
	int i,n;
	LinkList p;
	L=(LinkList) malloc (sizeof (LNode));
	L->next=NULL; //先建立一个带头结点的单链表
	
	
	printf("请输入初始时链表长度:"); //输入生成单链表时的元素个数
	scanf("%d",&n);
	printf("请输入位序从%d到1的各元素(整数)，例如:2 4 5 6 7 ...\n",n);
	for (i=n; i>0; --i){
		p=(LinkList) malloc (sizeof (LNode)); //生成新结点
		scanf("%d",&p->data);
		p->next=L->next; L->next=p; //插入到表头
	}
}//CreateList_L 

void FreeList_L(LinkList &L){
	//销毁带表头结点的单链线性表L
	LinkList p;
	while(L->next){
		p=L->next; //p指向第一个结点
		L->next=p->next;//表头结点的指针域指向第二个结点
		free(p);
	}
	free(L);  //释放表头结点所占的空间
}//FreeList_L

Status ListInsert_L(LinkList &L, int i, ElemType e){
	//在带头结点的单链线性表L中第i个位置之前插入元素e
	LinkList p=L , s;
	int j=0;
	while (p && j<i-1) {p=p->next; ++j;} //寻找第i-1个结点
	if (!p || j>i-1) return ERROR; //i小于1或者大于表长
	s=(LinkList) malloc (sizeof (LNode)); //生成新结点
	s->data=e; s->next=p->next; //插入L中
	p->next=s;
	return OK;
}//ListInsert_L

Status ListDelete_L(LinkList &L, int i, ElemType &e){
	//在带头结点的单链线性表L中,删除第i个元素，并由e返回其值
	LinkList p=L , q;
	int j=0;
	while (p->next && j<i-1){ //寻找第i个结点，并令p指向其前趋
		p=p->next; ++j;
	}
	if (!(p->next) || j>i-1) return ERROR; //删除位置不合理
	q=p->next; p->next=q->next; //删除并释放结点
	e=q->data; free(q);
	return OK;
}//ListDelete_L

void ListDisplay_L(LinkList L){
	//显示链表所有元素
	LinkList p=L->next;
	int i=1;
	printf("链表所有元素:");
	while(p)
    {printf("[%d:%d]",i,p->data);++i;p=p->next;}
	printf("\n");
}//ListDisplay_L

int ListFind_Keyword_L(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType)){
	//在单链表中查找关键字为e的元素，成功返回该元素的位序，
	//失败返回0
	int i;
	LinkList p;
	p=L->next; i=1;
	while(!(*compare)(p->data,e)&&(p->next!=NULL))
    {p=p->next;  i++;}//p指针指向下一个，直到找到或到链表尾为止
	if(!(*compare)(p->data,e)) return 0;//该元素在链表中不存在
	return i;
}//ListFind_Keyword_L

Status ListFind_Order_L(LinkList L,int i,ElemType &e){
	//在单链表中查找第i个元素，成功返回True，并用e返回该元素值，
	//失败返回False
	LinkList p;
	int j;
	p=L->next; j=1;
	while(p->next&&j<i)  //移动指针，直到找到第i个元素
    {p=p->next;++j;}
	if(!p||j>i) return ERROR; //第i个元素不存在
	e=p->data;       //查找成功，用e取得该元素值
	return OK;
}//ListFind_Order_L

Status equal(ElemType x,ElemType y){
	return x==y;
}//equal

int main(){
	LinkList L;
	Status temp;
	int i,num,ch,e,flag=1;
	//clrscr();
	//---------------------程序说明-----------------------
	printf("本程序实现链式结构的线性表的操作。\n");
	printf("可以进行插入，删除，定位，查找等操作。\n");
	//----------------------------------------------------
	
	CreateList_L(L);//生成单链表
	ListDisplay_L(L);
	while(flag){
		printf("请选择:\n");
		printf("1.显示所有元素\n");  //显示链表元素
		printf("2.插入一个元素\n");  //插入链表元素
		printf("3.删除一个元素\n");  //删除链表元素
		printf("4.按关键字查找元素\n");  //按关键字查找
		printf("5.按序号查找元素\n"); //按序号查找
		printf("6.退出程序      \n");  //退出
		scanf("%d",&ch);
		switch(ch){
		case 1:
			ListDisplay_L(L); //显示所有元素
			break;
		case 2:
			printf("请输入要插入元素的位置和数值:\n");
			printf("格式：位置,数值；例如:2,68\n");
			scanf("%d,%d",&i,&e);  //输入要插入的元素和插入的位置
			temp=ListInsert_L(L,i,e);     //插入
			if(temp==ERROR) printf("插入失败!\n");  //插入失败
			else {printf("插入成功!\n");ListDisplay_L(L);} //插入成功
			break;
		case 3:
			printf("请输入要删除元素的位置:");
			scanf("%d",&i);    //输入要删除的元素的位置
			temp=ListDelete_L(L,i,e);  //删除
			if(temp==OK) printf("删除了一个元素:%d\n",e); //删除成功
			else printf("该元素不存在!\n");  //删除失败
			ListDisplay_L(L);
			break;
		case 4:
			printf("请输入要查找的元素的值:");
			scanf("%d",&e);      //输入要查找的元素
			i=ListFind_Keyword_L(L,e,equal);      //定位
			if(i) printf("该元素所在位置:%d\n",i); //显示该元素位置
			else printf("%d不存在!\n",e);//当前元素不存在
			break;
		case 5:
			printf("请输入要查找的元素的位置:");
			scanf("%d",&i);      //输入要查找的元素
			temp=ListFind_Order_L(L,i,e);      //定位
			if(temp==OK) printf("第%d个元素:%d\n",i,e); //显示该元素数值
			else printf("第%d个元素不存在!\n",i);//当前元素不存在
			break;
		case 6:
			flag=0;
			printf("程序结束，按任意键退出!\n");
			getch();
			
		}
    }
	FreeList_L(L);//销毁单链表
	return 0;
}
