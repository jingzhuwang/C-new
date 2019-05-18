#include<stdlib.h>
#include<stdio.h>

int delete_elem(int arr[],int len_arr,int new_arr[])
{
   int len=0,n;
	for(int i=0;i<len_arr;i++)
	{
		n=1;
		for(int j=0;j<len;j++)
		{
			if(arr[i]==new_arr[j])
				{ n=0;break; }
		}
		if(n==1) { new_arr[len]=arr[i];len++; continue; }
	}
	return len;
    /*int i = 0, new_arr_len = 0;
    int flag[N] = { 0 };//对每个元素做一个初始标记
    for ( i = 0; i < 9; i++)
    {
        if (flag[arr[i]] == 0)
        {
            new_arr[new_arr_len++] = arr[i];
            flag[arr[i]] = 1;//出现过则标记属性设为1
        }
    }*/
}

int main()
{
	int a[9],new_a[9];
	int new_arr_length;
	for(int i=0;i<9;i++)
		scanf("%d",&a[i]);
    
	int len_a=sizeof(a)/sizeof(a[0]);
	new_arr_length=delete_elem(a,len_a,new_a);
	
	for(int i=0;i<new_arr_length;i++)
		printf("%d   ",new_a[i]);
		
	printf("\n");
    system("pause");
	return 0;
}