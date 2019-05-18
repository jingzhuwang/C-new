#include<stdio.h>

typedef int SElemType;

#include"LStack.cpp"

int size;

void Del_Medium(LStack& S,int n)
{
	SElemType item;
	if(n==(size/2+1))
	{	
		Pop(S,item);
		return;
	}
	Pop(S,item);
	n--;
	Del_Medium(S,n);
	Push(S,item);
}

int main()
{
	LStack S;
	int e;
	Init(S);
	printf("输入栈的大小:");
	scanf("%d",&size);
	printf("输入入栈元素:");
	for(int i=0;i<size;i++){
		scanf("%d",&e);
		Push(S,e);
	}
	Del_Medium(S,size);
	for(int i=0;i<size-1;i++)
	{
		Pop(S,e);
		printf("%d   ",e);
	}
	printf("\n");
	Del(S);
	system("pause");
	return 0;
}
/*
输入栈的大小:5
输入入栈元素:1 2 3 4 5
5   4   2   1
请按任意键继续. . .
*/