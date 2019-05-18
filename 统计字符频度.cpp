#include<stdio.h>
#include<stdlib.h>

int len;

void Count(int *num,char *ch){
    int tmp;
    for(int i=0;i<len;i++){
        tmp = ch[i];
        if(tmp>=48 && tmp<=57)
            tmp = tmp - 48;
        else
            tmp = tmp-55;
        num[tmp]++;
    }
}

int main()
{
    int nums[36];
    char c[100];
    char tmp;
    for(int i=0;i<36;i++)
        nums[i] = 0;
    printf("输入要统计的字符串(输入'#'停止输入，字符串最大长度100):\n");
    scanf("%c",&tmp);
    while(tmp!='#'){
        c[len] = tmp;
        len++;
        scanf("%c",&tmp);
    }
    Count(nums,c);
    for(int i=0;i<36;i++)
    {  
        if(nums[i]!=0) 
        {   if(i<10)
                printf("[%c:%d]\n",i+48,nums[i]);
            else
                printf("[%c:%d]\n",i+55,nums[i]);
        }
    }
    printf("\n");
    system("pause");
    return 0;
}