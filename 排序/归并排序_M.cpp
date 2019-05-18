#include<iostream>
#include<stdlib.h>
using namespace std;

void merge(int *a,int start,int end,int mid){ //start,end数组的两个端点，mid数组中间位置
    int i=start;
    int j=mid+1;
    int k=0;
    int *tmp=(int *)malloc(sizeof(int) *(end-start+1));
    while(i<=mid && j<=end){
        if (a[i] <= a[j])
            tmp[k++]=a[i++];
        else
            tmp[k++]=a[j++];
    }

    while (i<= mid)
    {
        tmp[k++] = a[i++];
    }
    
    while(j <= end){
        tmp[k++]=a[j++];
    }

    for(i=0;i<end-start+1;i++)
        a[start+i]=tmp[i];

    free(tmp);
}

void merge_sort_c(int *A,int start,int end){

    if(start>=end) return;

    //取start,end中间位置
    int mid=(end+start)/2;
    merge_sort_c(A,start,mid);
    merge_sort_c(A,mid+1,end);
    merge(A,start,end,mid); //合并
}

int main()
{
    int a[10]={3,6,9,10,15,4,6,7,1,12};
    merge_sort_c(a,0,9);
    for(int i=0;i<10;i++)
        cout<<a[i]<<"  ";

    cout<<endl;
    system("pause");
    return 0;
}