#include<stdio.h>
#include<stdlib.h>

typedef int SElemType;
#include"LStack.cpp"

void Stack_Max(int *nums,int len){  //从大到小排序
    LStack S1,S2;
    SElemType item;
    Init(S1);
    Init(S2);
    int i=0;
    for(;i<len;i++){
        if(Empty(S1) || GetTop(S1) >= nums[i]){   //当栈为空或栈顶元素大于等于nums[i]时，进栈
            Push(S1,nums[i]);
            continue;
        }
        while(!Empty(S1) && GetTop(S1) < nums[i]){ //当栈部位空且栈顶元素值小于nums[i]
            Pop(S1,item);   //从S1弹出元素
            Push(S2,item);  //将S1弹出元素压进S2栈
        }
        Push(S1,nums[i]);   //将nums[i]压入S1栈
        while(!Empty(S2)){  //当S2不为空时将S2中的内压入S1栈
            Pop(S2,item);
            Push(S1,item);
        }
    }
    while (!Empty(S1))
    {
        Pop(S1,item);
        nums[--i] = item;
    }
    Del(S1);
    Del(S2);
}

int main()
{
    int len;
    int i=0;
    printf("输入要排序的数组大小:");
    scanf("%d",&len);
    int *num = (int *)malloc(sizeof(int)*len);
    printf("输入数组元素值:");
    for(i=0;i<len;i++)
        scanf("%d",&num[i]);
    Stack_Max(num,len);
    for(i=0;i<len;i++)
        printf("%d   ",num[i]);
    printf("\n");
    system("pause");
    return 0;
}

/*
输入要排序的数组大小:5
输入数组元素值:5 7 9 10 4
10   9   7   5   4
请按任意键继续. . .
*/