#include<stdio.h>
#include<stdlib.h>
int ans;

void f(int dian,int hua,int jiu){
    if(dian==0&&hua==0&&jiu==1)
        ans++;
    if (dian>0) f(dian-1,hua,jiu*2);
    if(hua>0) f(dian,hua-1,jiu-1);
}

int main()
{
    f(5,9,2);
    printf("%d\n",ans);
    system("pause");
    return 0;
} 