#include<iostream>
#include<stdlib.h> 
using namespace std;

typedef struct node{
	int data;   
	struct node* next; 
}*LinkList,Lnode;

int len=sizeof(Lnode);  //链表的长度 
 
void Init(LinkList &L){ //初始化链表 
	L=(LinkList)malloc(len); 
	if(L==NULL) exit(0); 
	L->data=0;
	L->next=NULL; 
}

void Insert_f(LinkList &L,int item){  //头插法 
	Lnode *p=L->next;
	Lnode *tmp=(Lnode*)malloc(len);
	if(tmp==NULL) exit(0);
	tmp->data=item;
	tmp->next=p;
	L->next=tmp;
	L->data++; 
} 
void Insert_l(LinkList &L,int item){ //尾插法 
	Lnode* p=L;
	while(p->next){
		p=p->next; 
	}
	Lnode *q=(LinkList)malloc(len);
	if(q==NULL) exit(0); 
	q->data=item;
	p->next=q;
	q->next=NULL;
	L->data++;  //头结点数据域表示链表长度 
} 

int Insert_p(LinkList &L,int n,int item){  //按照位置插入,n表示插入的地方，item插入的值 
	int i=0;
	if(i<0||(i>L->data+1)){
		cout<<"位置错误"<<endl;
		return 0; 
	} 
	Lnode *p=L;
	while(p&&(i<n-1)){
		p=p->next;
		i++;
	}
	if(!p||i>n-1) return 0;
	Lnode *tmp=(LinkList)malloc(len);
	tmp->next=p->next;
	p->next=tmp;
	tmp->data=item;
	L->data++; 
	return 1;
} 

void del(LinkList &L){ //销毁链表 
	Lnode* p=L->next;
	Lnode *q; 
	while(p){
		q=p->next;
		free(p);
		p=q; 
	}
	free(L);
	L=NULL; 
} 

void display(LinkList &L){ //输出链表内容 
	Lnode* p=L->next;
	while(p){
		cout<<p->data<<endl;
		p=p->next; 
	} 
} 
int main()
{
	LinkList L;
	Init(L);
	int n;
	int i; 
	int num; 
	cout<<" 输入顺序表元素个数:";
	cin>>n;
	cout<<"输入数据(回车确定):"; 
	for(int i=0;i<n;i++){
		cin>>num;
		Insert_f(L,num); 
	}
	display(L);
	cout<<endl<<endl; 	
	cout<<L->data<<endl; 
	cout<<"请输入在插入的位置和插入的值:";
	cin>>i>>num; 
	Insert_p(L,i,num);
	display(L);
	cout<<endl;
	cout<<L->data<<endl; 
	del(L); 
	return 0; 
} 
