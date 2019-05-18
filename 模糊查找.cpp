#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int search(const char *key,char *str) 
{
    typedef struct
    {
        char son[10];
    }Elem; 
    
    int i,j,m,l,k=0;
    int num1=0,num2=0;

    int f=0;  //f=1是匹配成功的标志

    num1=strlen(str);  //num1为str的长度

    //i控制子字符串的长度
    //j控制赋值
    //k控制新的线性结构b的下标
    //l控制子数组的首项在原数组中的位置
    //m控制即将用作赋值的str的下标
    //num2=0;
    for(i=1;i<=num1;i++)
        num2=num2+i;    //num2表示key字符串的长度大于等于2的全部子串个数 
    
    printf("%d   %d\n",num1,num2);
    Elem *b=(Elem *)malloc(sizeof(Elem)*num2);
    for( i = 1; i <= num1; i++)
    {
        l=0;
        while(1)
        {
            m=l;
            for( j = 0; j < i; j++)
            {
                b[k].son[j]=str[m];
                m++;
            }
            printf("%s\n",b[k].son);
            l++;
            k++;
            if (m==num1)
                break;
        }
    }
    for( i = 0; i < num2; i++)
    { 
        printf("%s\n",b[i].son);
        if (strcmp(key,b[i].son)==0) {
            f=1;
            break;
        }
    }
    free(b);
    b=NULL;
    return f;
}



int main()
{
    char s[]="HUAWEI";
    char k[]="WE";
    int res;
    res=search(k,s);
    if(res==1)
        printf("匹配成功\n");
    else
    {
        printf("匹配失败");
    }
    system("pause");
    return 0;
}

/*int main()
{
    char s[]="中华传统礼仪";
    char a[]="传统";
    if (strstr(s,a)) {
        printf("匹配成功！\n");
    }
    else
    {
        printf("匹配失败！\n");
    }
    system("pause");
    return 0;
    
}
*/