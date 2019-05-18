#include<iostream>
#include<stdlib.h>
using namespace std;
typedef int QElemType;
#include"ListQueue.cpp"

int main()
{
    ListQueue Q;
    Init(Q);
    for(int i=0;i<9;i++)
        EnQueue(Q,i);

    cout<<GetQueue(Q)<<endl;
    Display(Q);
    Del(Q); 
    system("pause");
    return 0;
}