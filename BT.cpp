#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef char BElemType;

typedef struct Parent{
	BElemType data;
	int parent;
}Parents;  //双亲节点 

void Create(Parents *p,int len){
	char ch;
	int i,j;
	char first,after;
	for(i=0;i<len;i++)
		p[i].parent = -1;
	printf("请输入各个节点值:");
	for(i=0;i<len;i++){
		scanf("%c",&p[i].data);
	}
	printf("\n");
	printf("请输入每个节点的父子关系(父在前子在后，用逗号隔开):\n");
	printf("输入 #,# 结束输入:\n");
	scanf("%c,%c",&first,&after);
	while((first != '#') && (after != '#')){
		for(i=0;i<len;i++){
			if(p[i].data == first)
				break;  //找出父节点下标 
		}
		for(j=1;j<len;j++){
			if(p[j].data == after)
				break;  //找出子节点下标 
		}
		p[j].parent = i;
		scanf("%c,%c ",&first,&after);
	}
}

int main()
{
	Parents* p;
	int len;
	printf("请输入共有多少个节点:");
	scanf("%d",&len);
	p = (Parents *)malloc(sizeof(Parents)*len);
	getchar();
	Create(p,len);
	for(int i=0;i<len;i++){
		printf("%d %c  %d\n",i,p[i].data,p[i].parent);
	}
	//free(p);
	p = NULL;
	system("pause");
	return 0;
}






