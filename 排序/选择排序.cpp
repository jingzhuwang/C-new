#include<iostream>
#include<stdlib.h>
using namespace std;

/*
 *选择排序
 *
 * 参数说明:
 *      a---要排序的数组
 *      size---数组长度
 * 
 */
void select_sort(int *a,int size){
    void swap(int *a,int m,int n);
    int end=0;
    int min,j;
    for(int i=0;i<size;i++){
        min=i;
        for(j=i+1;j<size;j++){
            if(a[min]>a[j]) min=j;
        }
        swap(a,end,min);
        end++;
    }
}

/*
 *交换函数
 *
 * 参数说明:
 *      a---要交换元素的数组首地址
 *      m---交换的第一个位置
 *      n---交换的第二个位置
 * 
 */
void swap(int *a,int m,int n){ //交换元素，第一个参数为数组，后两个参数为要交换的位置
    int tmp=a[m];
    a[m]=a[n];
    a[n]=tmp;
}

int main()
{
    int A[10]={3,6,9,10,15,4,6,7,1,12};
    select_sort(A,10);
    for(int i = 0; i < 10; i++)
    {
        cout<<A[i]<<"  ";
    }
    cout<<endl;
    system("pause");
    return 0;
}
