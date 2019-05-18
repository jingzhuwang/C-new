#include<iostream>
#include<stdlib.h>
using namespace std;


int main()
{
	float res_1=0,res_2=0;
    float credit;  //每门课程的学分
    float grade;  //每门课程的成绩 
    cout<<"输入学分和成绩:";
	cin>>credit>>grade; 
    while(credit!=0 && grade!=0){
        cin>>credit>>grade;
        res_1 += credit*(grade-50)/10;
        res_2 += credit;
    }
    
    cout<<"绩点为:"<<res_1/res_2<<endl;
    system("pause");
    return 0;
}
