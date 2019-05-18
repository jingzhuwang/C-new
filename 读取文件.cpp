#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define False 0
#define True 1
#define OVERFLOW -1
#define MAXSIZE 100
#define ADD 10

typedef struct
{
    int grade;
    char name[10];
    float credit;
    float score;
    float grade_point;
} ElemType;

typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
} Sqlist;

void InitList(Sqlist &L) //创建顺序表
{
    L.elem = (ElemType *)malloc(sizeof(ElemType) * MAXSIZE); //为顺序表分配空间
    if (! L.elem)
        exit(ERROR);
    L.listsize = MAXSIZE;
    L.length=0;
}

void DestoryList(Sqlist &L) //销毁线性表
{
    free(L.elem);
    L.elem = NULL;
}

void read(Sqlist& L)    //读取文件
{
    FILE *fp;
    int i=0;
    fp=fopen("my_score.dat","r");
    if(fp==NULL)
    {
        printf("cannot open file\n");
        exit(ERROR);
    }
    while(!feof(fp)) //feof()判断文件是否到了结尾，结束返回非零值，不结束返回0
    {
        fread(&L.elem[i],sizeof(ElemType),1,fp);
        L.length++;
        i++;
    }
}

void save(Sqlist L)    //将数据写入文件
{
    FILE *fp;
    int i=0;
    fp=fopen("my_score.dat","wb");
    if (fp==NULL) {
        printf("打开文件失败！\n");
        exit(ERROR);
    }
    for( i = 0; i < L.length; i++)
    {
        fwrite(&L.elem[i],sizeof(ElemType),1,fp);
    }
    fclose(fp);
}

int ListEmpty(Sqlist L) //查询列表是否为空
{
    return L.length;
}

void Initial_entry(Sqlist& L)  //录入初始数据
{
    printf("请输入初始数据长度：");
    scanf("%d", &L.length);
    if (L.length>L.listsize) {
        L.elem=(ElemType*)realloc(L.elem,sizeof(ElemType)*L.length);
    }

    printf("请输入初始成绩(示例：学期 课程名 学分 成绩 绩点)：\n");
    for (int i = 0; i < L.length; i++)
    {
        scanf("%d %s %f %f %f", L.elem[i].grade, L.elem[i].name, L.elem[i].credit, L.elem[i].score, L.elem[i].grade_point);
    }
    printf("录入成功");
}

void List_Display(Sqlist L) //显示顺序表全部元素
{
    printf("学期       课程名       学分     成绩      绩点");
    for (int i = 0; i < L.length; i++)
    {
        printf("*********************************\n");
        printf("%d    %s      %f       %f      %f\n",L.elem[i].grade,L.elem[i].name,L.elem[i].credit,L.elem[i].score,L.elem[i].grade_point);
    }
    printf("\n");
}

int main()
{
    Sqlist m;
    InitList(m);
    read(m);
    if(!ListEmpty(m))
        Initial_entry(m);
        save(m);
    
    List_Display(m);
    DestoryList(m);
    system("pause");
    return 0;
}