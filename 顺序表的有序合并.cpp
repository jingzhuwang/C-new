#include<iostream>
#include<stdlib.h>
using namespace std;

void merge(int a[],int b[],int c[]){
    int lenA=10;
    int lenB=10;
    int i=0,j=0,k=0;
    while(i<lenA && j<lenB){
        if(a[i] < b[j]){
            c[k++]=a[i++];
        }
        if(a[i] > b[j]){
            c[k++]=b[j++];
        }
        if(a[i]==b[j]){
            c[k++]=a[i++];
            j++;
        }
    }
    for(; i < lenA; i++)
    {
        c[k++]=a[i];
    }
    for(;j<lenB;j++) 
        c[k++]=b[j];
}

int main()
{
    int i[10]={2,3,4,5,6,7,8,9,10,11};  
    int j[10]={0,1,2,5,11,12,13,14,15,20};  //ÖØ¸´µÄÓÐ2,5,11
    int k[20];   //{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,20}
    merge(i,j,k);
    for(int m = 0; m < 20; m++)
    {
        cout<<k[m]<<"   ";
    }
    system("pause");
    return 0;
}
