/*堆排序+直接插入排序*/
#include<stdio.h>
#include<stdlib.h>

void ShortInsert(int *nums,int len){ //直接插入排序
    int tmp,j;
    for(int i = 1;i < len;i++){
        if(nums[i-1] > nums[i]){
            tmp = nums[i];
            nums[i] = nums[i-1];
            for(j = i-1;j >= 0 && tmp < nums[j];j--)
                nums[j+1] = nums[j];
            nums[j+1] = tmp; 
        }
    }
}

void HeapAdjust(int *nums,int start,int end){ //调整堆
    int data = nums[start];
    for(int i = 2*start + 1;i < end;i= i*2){
        if(i < end && nums[i] < nums[i+1]) ++i;
        if(data >= nums[i]) break;
        nums[start] = nums[i];
        start = i;
    }
    nums[start] = data;
}

void CreateHeap(int* nums,int len){ //创建初始堆
    for(int i = len/2 - 1;i>=0;i--)
        HeapAdjust(nums,i,len);
}

void ShortHeap(int *nums,int len){ //堆排序
    int data;
    CreateHeap(nums,len);
    for(int i = len -1;i>=0;i--){
        data = nums[0];
        nums[0] = nums[i];
        nums[i] = data;
        HeapAdjust(nums,0,i-1);
    }
}

int main()
{
    int len;
    int data;
    printf("输入待排序数组长度:");
    scanf("%d",&len);
    int *nums1 = (int*)malloc(sizeof(int)*len);
    int *nums2 = (int*)malloc(sizeof(int)*len);
    printf("输入数组数据元素:");
    for(int i = 0;i < len;i++){
        scanf("%d",&data);
        nums1[i] = data;
        nums2[i] = data;
    }
    ShortInsert(nums1,len);
    printf("直接插入排序结果为：");
    for (int i = 0; i < len; i++)
        printf("%d  ",nums1[i]);
    printf("\n");
    ShortHeap(nums2,len);
    printf("堆排序结果为：");
    for (int i = 0; i < len; i++)
        printf("%d  ",nums2[i]);
    printf("\n");
    free(nums1);
    free(nums2);
    return 0;
}
/*
示例输入：
8
49 38 65 97 49 13 27 76
示例输出：
直接插入排序结果为：13  27  38  49  49  65  76  97
堆排序结果为：13  27  38  49  49  65  76  97
 */