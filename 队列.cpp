#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define OK 1
#define ERROR 0
#define Ture 1
#define False 0

typedef int Status;
typedef int QElemType;

static int MaxQueueSize = 5;
static int Add = 2;

typedef struct DuSeQueue
{ //定义队列结构
	QElemType *data;
	//初始空间 5个元素;
	//每次不够增加2个元素
	int head; //队头
	int tail; //队尾
} DuSeQueue;

Status InitDuSeQueue(DuSeQueue &Q)
{ ////初始化一个队列
	Q.data = (QElemType *)malloc(sizeof(QElemType) * MaxQueueSize);
	if (Q.data == NULL)
		exit(False);
	Q.head = 0;
	Q.tail = 0;
	return OK;
}

Status DestroyDuSeQueue(DuSeQueue &Q)
{ //销毁一个队列
	if (Q.data)
		free(Q.data);
	Q.data = NULL;
	return OK;
}

int DuSeQueueLength(DuSeQueue &Q)
{ //队列的长度
	return (Q.tail - Q.head + MaxQueueSize) % MaxQueueSize;
}

Status EnDuSeQueueFront(DuSeQueue &Q, QElemType item)
{ //将一个元素从前入队列
	int len = MaxQueueSize;
	if ((Q.tail + 1) % MaxQueueSize == Q.head)
	{
		int *tmp = (int *)realloc(Q.data, sizeof(QElemType) * (MaxQueueSize + Add));
		Q.data = tmp;
		MaxQueueSize += Add;
		for (int i = 0; i < Q.tail; i++)
		{
			Q.data[(len + i) % MaxQueueSize] = Q.data[i];
		}
		Q.tail = (Q.tail + len) % MaxQueueSize;
	}
	Q.head = (Q.head - 1 + MaxQueueSize) % MaxQueueSize;
	Q.data[Q.head] = item;
	return OK;
}

Status EnDuSeQueueBack(DuSeQueue &Q, QElemType item)
{ //将一个元素从后入队列
	int len = MaxQueueSize;
	if ((Q.tail + 1) % MaxQueueSize == Q.head)
	{ //队满
		int *tmp = (int *)realloc(Q.data, sizeof(QElemType) * (MaxQueueSize + Add));
		Q.data = tmp;
		MaxQueueSize += Add;
		if ((Q.tail + 3) != MaxQueueSize)
		{ //表尾不是指向数组最后一个
			for (int i = 0; i < Q.tail; i++)
			{
				Q.data[(len + i) % MaxQueueSize] = Q.data[i];
			}
			Q.tail = (Q.tail + len) % MaxQueueSize;
		}
	}

	Q.data[Q.tail] = item;
	Q.tail = (Q.tail + 1) % MaxQueueSize;
	return OK;
}

Status DeDuSeQueueFront(DuSeQueue &Q, QElemType &item)
{ //将一个元素从前出队列
	if (Q.head == Q.tail)
		return ERROR;
	item = Q.data[Q.head];
	Q.head = (Q.head + 1) % MaxQueueSize;
	return OK;
}

Status DeDuSeQueueBack(DuSeQueue &Q, QElemType &item)
{ //将一个元素从后出队列
	if (Q.head == Q.tail)
		return ERROR;
	Q.tail = (Q.tail - 1 + MaxQueueSize) % MaxQueueSize;
	item = Q.data[Q.tail];
	return OK;
}

Status DisplayDuSeQueue(DuSeQueue Q)
{ //显示队列中所有元素
	if (Q.head == Q.tail)
	{
		printf("队列为空\n");
		return ERROR;
	}
	if (Q.tail < Q.head)
	{
		for (int i = 0; i < MaxQueueSize; i++)
		{
			if (i < Q.tail || i >= Q.head)
				printf("[%d:%d]\n", i, Q.data[i]);
		}
	}
	else
	{
		for (int i = Q.head; i < Q.tail; i++)
			printf("[%d:%d]\n", i, Q.data[i]);
	}
	return OK;
}
Status DisplayDuSeQueueInMemory(DuSeQueue Q)
{ //显示队列中所有元素
	if (Q.head == Q.tail)
	{
		printf("队列为空\n");
		return ERROR;
	}
	if (Q.tail < Q.head)
	{
		for (int i = 0; i < MaxQueueSize; i++)
		{
			if (i >= Q.tail && i < Q.head)
				printf("[%d: ]\n", i);
			else
				printf("[%d:%d]\n", i, Q.data[i]);
		}
	}
	else
	{
		for (int i = 0; i < MaxQueueSize; i++)
		{
			if (i < Q.head || i >= Q.tail)
				printf("[%d: ]\n", i);
			else
				printf("[%d:%d]\n", i, Q.data[i]);
		}
	}
	return OK;
}

int main()
{
	DuSeQueue Q;
	QElemType e;
	int flag = 1, ch, len;
	int n;
	Status temp;
	InitDuSeQueue(Q); //初始化队列

	while (flag)
	{
		printf("请选择:\n");
		printf("1.显示队列所有元素\n");
		printf("2.显示队列元素在内存中的存储\n");
		printf("3.队头入队列\n");
		printf("4.队尾入队列\n");
		printf("5.队头出队列\n");
		printf("6.队尾出队列\n");
		printf("7.求队列的长度\n");
		printf("8.退出程序\n");
		scanf("%d", &ch);
		switch (ch)
		{
		case 1:
			DisplayDuSeQueue(Q); //显示队列中所有元素
			break;
		case 2:
			DisplayDuSeQueueInMemory(Q); //显示队列中元素在内存中的显示
			break;
		case 3:
			printf("请输入要入队的元素(一个整数):");
			scanf("%d", &e);		//输入要入队列的字符
			EnDuSeQueueFront(Q, e); //入队列
			DisplayDuSeQueueInMemory(Q);
			break;
		case 4:
			printf("请输入要入队的元素(一个整数):");
			scanf("%d", &e);	   //输入要入队列的字符
			EnDuSeQueueBack(Q, e); //入队列
			DisplayDuSeQueueInMemory(Q);
			break;
		case 5:
			temp = DeDuSeQueueFront(Q, e); //出队列
			if (temp == OK)
			{
				printf("出队一个元素:%d\n", e); //若队列不空，显示出队列的元素
				DisplayDuSeQueue(Q);
			}
			else
				printf("队列为空!\n"); //否则队列为空
			break;
		case 6:
			temp = DeDuSeQueueBack(Q, e);
			if (temp == OK)
			{
				printf("出队一个元素:%d\n", e); //若队列不空，显示出队列的元素
				DisplayDuSeQueue(Q);
			}
			else
				printf("队列为空!\n"); //否则队列为空
			break;
		case 7:
			len = DuSeQueueLength(Q);
			printf("队列的长度为:%d\n", len);
			break;
		default:
			flag = 0;
			printf("程序运行结束，按任意键退出!\n");
			getch();
		}
		printf("\n");
	}
	DestroyDuSeQueue(Q);
	return 0;
}

/*
请选择:
1.显示队列所有元素
2.显示队列元素在内存中的存储
3.队头入队列
4.队尾入队列
5.队头出队列
6.队尾出队列
7.求队列的长度
8.退出程序
3
请输入要入队的元素(一个整数):1
[0:1]
[1: ]
[2: ]
[3: ]
[4: ]

请选择:
1.显示队列所有元素
2.显示队列元素在内存中的存储
3.队头入队列
4.队尾入队列
5.队头出队列
6.队尾出队列
7.求队列的长度
8.退出程序
4
请输入要入队的元素(一个整数):2
[0:1]
[1:2]
[2: ]
[3: ]
[4: ]

请选择:
1.显示队列所有元素
2.显示队列元素在内存中的存储
3.队头入队列
4.队尾入队列
5.队头出队列
6.队尾出队列
7.求队列的长度
8.退出程序
3
请输入要入队的元素(一个整数):2
[0:1]
[1:2]
[2: ]
[3: ]
[4:2]

请选择:
1.显示队列所有元素
2.显示队列元素在内存中的存储
3.队头入队列
4.队尾入队列
5.队头出队列
6.队尾出队列
7.求队列的长度
8.退出程序
4
请输入要入队的元素(一个整数):5
[0:1]
[1:2]
[2:5]
[3: ]
[4:2]

请选择:
1.显示队列所有元素
2.显示队列元素在内存中的存储
3.队头入队列
4.队尾入队列
5.队头出队列
6.队尾出队列
7.求队列的长度
8.退出程序
4
请输入要入队的元素(一个整数):6
[0:5]
[1:6]
[2: ]
[3: ]
[4:2]
[5:1]
[6:2]

请选择:
1.显示队列所有元素
2.显示队列元素在内存中的存储
3.队头入队列
4.队尾入队列
5.队头出队列
6.队尾出队列
7.求队列的长度
8.退出程序
1
[4:2]
[5:1]
[6:2]
[0:5]
[1:6]

请选择:
1.显示队列所有元素
2.显示队列元素在内存中的存储
3.队头入队列
4.队尾入队列
5.队头出队列
6.队尾出队列
7.求队列的长度
8.退出程序
2
[0:5]
[1:6]
[2: ]
[3: ]
[4:2]
[5:1]
[6:2]

请选择:
1.显示队列所有元素
2.显示队列元素在内存中的存储
3.队头入队列
4.队尾入队列
5.队头出队列
6.队尾出队列
7.求队列的长度
8.退出程序
4
请输入要入队的元素(一个整数):8
[0:5]
[1:6]
[2:8]
[3: ]
[4:2]
[5:1]
[6:2]

请选择:
1.显示队列所有元素
2.显示队列元素在内存中的存储
3.队头入队列
4.队尾入队列
5.队头出队列
6.队尾出队列
7.求队列的长度
8.退出程序
5
出队一个元素:2
[5:1]
[6:2]
[0:5]
[1:6]
[2:8]

请选择:
1.显示队列所有元素
2.显示队列元素在内存中的存储
3.队头入队列
4.队尾入队列
5.队头出队列
6.队尾出队列
7.求队列的长度
8.退出程序
6
出队一个元素:8
[5:1]
[6:2]
[0:5]
[1:6]

请选择:
1.显示队列所有元素
2.显示队列元素在内存中的存储
3.队头入队列
4.队尾入队列
5.队头出队列
6.队尾出队列
7.求队列的长度
8.退出程序
2
[0:5]
[1:6]
[2: ]
[3: ]
[4: ]
[5:1]
[6:2]

请选择:
1.显示队列所有元素
2.显示队列元素在内存中的存储
3.队头入队列
4.队尾入队列
5.队头出队列
6.队尾出队列
7.求队列的长度
8.退出程序
7
队列的长度为:4

请选择:
1.显示队列所有元素
2.显示队列元素在内存中的存储
3.队头入队列
4.队尾入队列
5.队头出队列
6.队尾出队列
7.求队列的长度
8.退出程序
8

*/