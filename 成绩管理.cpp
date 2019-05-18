#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef int Status;

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

Status ListInsert(Sqlist &L, int i, ElemType e) //在i位置插入元素
{
    ElemType *newdata;
    if ((i < 1) || i > L.length)
    {
        return ERROR;
    }
    if (L.length >= L.listsize)
    {
        newdata = (ElemType *)realloc(L.elem, (L.listsize + ADD) * sizeof(ElemType));
        if (!newdata)
            exit(OVERFLOW);
        L.elem = newdata;
        L.listsize += ADD;
    }
    for (int j = L.length - 1; j > i - 1; j--)
    {
        L.elem[j + 1] = L.elem[j];
    }
    L.elem[i - 1] = e;
    ++L.length;
    return OK;
}

Status ListDelete(Sqlist &L, int i, ElemType &e) //删除顺序表中位置为i的元素
{
    if ((i < 1) || (i > L.length))
    {
        return ERROR;
    }
    e = L.elem[i - 1];
    for (int j = i; j <= L.length - 1; j++)
    {
        L.elem[j - 1] = L.elem[j];
    }
    --L.length;
    return OK;
}

Status ClearList(Sqlist &L) //清空线性表
{
    delete [] L.elem;
    L.elem = (ElemType*)malloc(L.listsize*sizeof(ElemType));
    L.length = 0;
    return OK;
}

Status ListEmpty(Sqlist L) //查询列表是否为空
{
    return L.length;
}

void Initial_entry(Sqlist& L)  //录入初始数据
{
    printf("请输入初始数据长度：");
    scanf("%d", &L.length);
    if (L.length>L.listsize) {
        ElemType* newbase=(ElemType*)realloc(L.elem,sizeof(ElemType)*L.length);
        L.elem=newbase;
    }

    printf("请输入初始成绩(示例：学期 课程名 学分 成绩 绩点)：\n");
    for (int i = 0; i < L.length; i++)
    {
        scanf("%d %s %f %f %f", L.elem[i].grade, L.elem[i].name, L.elem[i].credit, L.elem[i].score, L.elem[i].grade_point);
    }
    printf("录入成功");
}

void read(Sqlist& L)    //读取文件
{
    FILE *fp;
    int i=0;
    if((fp=fopen("myscore.dat","r"))==NULL)
    {
        printf("cannot open file\n");
        exit(ERROR);
    }
    while(!feof(fp)) //feof()判断文件是否到了结尾，结束返回非零值，不结束返回0
    {
        //fread(L.elem[i],sizeof(ElemType),1,fp);
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
        //fwrite(L.elem[i],sizeof(ElemType),1,fp);
    }
    fclose(fp);
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

void menu() //菜单
{
    printf("******************************\n");
    printf("*********个人成绩管理**********\n");
    printf("******************************\n");
    printf("*     1、显示个人成绩         *\n");
    printf("*     2、计算学期绩点         *\n");
    printf("*     3、查找某科成绩         *\n");
    printf("*     4、删除某科成绩         *\n");
    printf("*     5、清空成绩表           *\n");
    printf("*     6、退出系统             *\n");
    printf("******************************\n");
}
int main()
{
    char res;
    Sqlist list;
    InitList(list);
    for(int i=0;i<3;i++)
        Initial_entry(list);
    
    List_Display(list);
    DestoryList(list);
    return 0;
}

