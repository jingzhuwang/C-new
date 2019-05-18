#include<stdio.h>
typedef int SElemType;
#include"LStack.cpp"
typedef struct Queue{
	LStack In;
	LStack Out;
}Queue;

Status InitQueue(Queue& Q)
{
	Init(Q.In);
	Init(Q.Out);
	return OK;
}

Status DelQueue(Queue& Q)
{
	Del(Q.In);
	Del(Q.Out);
	return OK;
}

Status EnQueue(Queue& Q,SElemType item)
{
	if(Push(Q.In,item))
		return OK;
	return ERROR;
}

Status OutQueue(Queue& Q,SElemType& item)
{
	SElemType e;
	if(Empty(Q.Out))
	{
		while(!Empty(Q.In))
		{
			Pop(Q.In,e);
			Push(Q.Out,e);
		}
	}
	if(Pop(Q.Out,item))
		return OK;
	else
		printf("栈为空\n");
	return ERROR;
}

int main()
{
	Queue Q;
	int e;
	int flag=1;
	int ch;
	InitQueue(Q);
	while(flag){
		printf("请选择:\n");
		printf("1.插入一个元素\n");  //插入链表元素
		printf("2.删除一个元素\n");  //删除链表元素
		printf("3.退出\n");
		scanf("%d",&ch);
		switch(ch){
		case 1:
			printf("输入要插入的元素:");
			scanf("%d",&e);
			EnQueue(Q,e);
			printf("插入成功\n");
			break;
		case 2:
			OutQueue(Q,e);
			printf("删除了元素:%d\n",e);
			break;
		case 3:
			flag=0;
			break;
		}
	}
	DelQueue(Q);
	system("pause");
	return 0;
}

/*
请选择:
1.插入一个元素
2.删除一个元素
3.退出
1
输入要插入的元素:1
插入成功
请选择:
1.插入一个元素
2.删除一个元素
3.退出
1
输入要插入的元素:2
插入成功
请选择:
1.插入一个元素
2.删除一个元素
3.退出
1
输入要插入的元素:3
插入成功
请选择:
1.插入一个元素
2.删除一个元素
3.退出
2
删除了元素:1
请选择:
1.插入一个元素
2.删除一个元素
3.退出
2
删除了元素:2
请选择:
1.插入一个元素
2.删除一个元素
3.退出
2
删除了元素:3
请选择:
1.插入一个元素
2.删除一个元素
3.退出
3
请按任意键继续. . .*/
