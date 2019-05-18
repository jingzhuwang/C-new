#include<iostream>
using namespace std;

int f(int a,int b){
	if(b==0) return a;
	f(b,a%b);
}
int main()
{
	cout<<f(12,16)<<endl;
	return 0;
} 
