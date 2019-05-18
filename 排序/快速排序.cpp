/*
快速排序(Quick Sort)使用分治法策略。
它的基本思想是：选择一个基准数，通过一趟排序将要排序的数据分割成独立的两部分；
其中一部分的所有数据都比另外一部分的所有数据都要小。
然后，再按此方法对这两部分数据分别进行快速排序，整个排序过程可以递归进行，以此达到整个数据变成有序序列。

快速排序流程：
(1) 从数列中挑出一个基准值。
(2) 将所有比基准值小的摆放在基准前面，所有比基准值大的摆在基准的后面(相同的数可以到任一边)；在这个分区退出之后，该基准就处于数列的中间位置。
(3) 递归地把"基准值前面的子数列"和"基准值后面的子数列"进行排序。
*/

#include <stdio.h>
#include <stdlib.h>

/*int partition(int *num, int left, int right)
{
    int min = num[right];
    int tmp;
    int i = left;
    for (int j = left; j < right; j++)
    {
        if (num[j] < min)
        {
            tmp = min;
            min = num[j];
            num[j] = min;
            i = i + 1;
        }
    }
    tmp = num[i];
    num[i] = num[right];
    num[right] = tmp;
    return i;
}
/*
 *快速排序
 * 
 * 参数说明:
 *      num---要排序的数组
 *      left---数组的左边界
 *      right---数组的右边界
 * 
 */
void quick_sort(int *num, int left, int right)
{
    if (left >= right)
        return;

    //int mid = partition(num,left,right);
    int min = num[left];
    int j = left;
    int tmp;
    for (int i = left + 1; i <= right;)
    {
        if (num[i] < min)
        {
            tmp = num[j];
            num[j] = num[i];
            num[i] = tmp;
            j++;
        }
        else i++;
    }
    quick_sort(num, left, j );
    quick_sort(num, j + 1 , right);
}

/*void swap(int a[], int m, int n)
{
	int temp = a[m];
	a[m] = a[n];
	a[n] = temp;
}
 
void sort_one(int a[], int m, int n)
{
	int p=m;
	int t = a[m];
	if (m > n)
		return;
	for (int i = m+1; i <= n; i++)
	{
		if (a[i] < t)
		{
			swap(a, ++p, i);
		}
	}
	swap(a, m, p);
	sort_one(a,m,p-1);
	sort_one(a, p + 1, n);
}*/

int main()
{
    int nums[] = {10, 2, 5, 7, 4, 1, 11, 15, 14, 7, 8};
    int len = sizeof(nums) / sizeof(int);
    quick_sort(nums, 0, 9);
    for (int i = 0; i < len; i++)
        printf("%d  ", nums[i]);
    printf("\n");
    system("pause");
    return 0;
}