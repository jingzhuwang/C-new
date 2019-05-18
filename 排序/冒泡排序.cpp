#include <stdio.h>
#include <stdlib.h>

/*
 *冒泡排序(Bubble Sort)，又被称为气泡排序或泡沫排序。
 *
 *它是一种较简单的排序算法。它会遍历若干次要排序的数列，每次遍历时，它都会从前往后依次的比较相邻两个数的大小；
 *如果前者比后者大，则交换它们的位置。这样，一次遍历之后，最大的元素就在数列的末尾！ 
 *采用相同的方法再次遍历时，第二大的元素就被排列在最大元素之前。重复此操作，直到整个数列都有序为止！
 */

/*
 *冒泡排序
 *
 * 参数说明:
 *      num---要排序的数组
 *      len---数组的长度
 */
void Bubble_sort_1(int *num, int len)
{

    if (num == NULL || len < 2)
        return;

    int tmp;
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (num[j] > num[j+1])
            {
                tmp = num[j+1];
                num[j+1] = num[j];
                num[j] = tmp;
            }
        }
    }
}

void Bubble_sort_2(int *num, int len)
{

    if (num == NULL || len < 2)
        return;

    int tmp;
    int flag;  //标记位，标记在循环过程重视否有数据交换
    for (int i = 0; i < len; i++)
    {
        flag =1;  //初始置1，表示无数据交换
        for (int j = 0; j < len - i - 1; j++)
        {
            if (num[j] > num[j+1])
            {
                tmp = num[j+1];
                num[j+1] = num[j];
                num[j] = tmp;
                flag = 0; //有数据交换，置0
            }
        }
        if(flag) break;  //如果没有数据交换，退出
    }
}

int main()
{
    int nums[] = {10, 2, 5, 7, 4, 1, 11, 15, 14, 7, 8};
    int len = sizeof(nums) / sizeof(int);
    Bubble_sort_2(nums, len);
    for (int i = 0; i < len; i++)
        printf("%d  ", nums[i]);
    printf("\n");
    system("pause");
    return 0;
}