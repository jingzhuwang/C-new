/*创建下三角矩阵的压缩存储矩阵，输出该矩阵，并查找其中元素值*/
#include<stdio.h>
#include<stdlib.h>

int* CreateArray(int &n){ //返回矩阵阶数
    int *nums;
    int size;
    printf("输入矩阵阶数:");
    scanf("%d",&n);
    size = n * (n + 1) / 2;
    nums = (int*)malloc(sizeof(int)*size);
    printf("输入矩阵非零元素的值(按行输入):");
    for(int i = 0;i < size;i++){
    	scanf("%d",&nums[i]);
    }
    return nums;
}

int SearchPos(int row,int col){ //row行，col列,寻找下标
    if(col < 0 || row < 0)  return -2;
    if(col > row) return -1;
	return row*(row+1)/2+col; 
}

void Search(int *nums){ //寻找该值在数组中的位置,并输出该值
    int row,col;
    int pos;
    printf("输入要查找元素的行号和列号:");
    scanf("%d %d",&row,&col);
    pos = SearchPos(row,col);
    if(pos == -2) printf("行号和列号输入有误！\n");
    if(pos == -1) printf("该元素值为：0. 未在数组中存放！\n");
    else printf("数组下标为:%d,值为:%d\n",pos,nums[pos]);
}

void DisplayArray(int *nums, int n){
    int pos;
    for(int i = 0;i< n;i++){
        for(int j = 0;j < n;j++){
            pos = SearchPos(i,j);
            if(pos == -1) printf("%3d",0);
            else printf("%3d",nums[pos]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int *nums;
    int row,col,n;
    int pos;
    nums = CreateArray(n);
    printf("\n");
    DisplayArray(nums, n);
    Search(nums);
    free(nums);
    nums = NULL;
    return 0;
}

/*
示例输入:
    3
    1 2 3 4 5 6
示例输出:

    1  0  0
    2  3  0
    4  5  6

    输入要查找元素的行号和列号:0 0
    数组下标为:0,值为:1
 */