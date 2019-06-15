/*用迪杰斯特拉算法求节点直接的距离*/
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define True 1
#define False 0
#define MAX 32767

typedef char GElemType;
typedef int Status;

typedef struct
{
    GElemType *vexs; //顶点数组
    int **arcs;      //临接矩阵
    int vexnum;      //当前点数
    int arcsnum;     //当前边数
} Graphy;

int Locate(Graphy G, GElemType key)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vexs[i] == key)
            break;
    }
    return i;
}

Status CreateGraphy(Graphy &G)
{ //创建图
    GElemType row, col;
    int value;
    int j, k;
    printf("请输入点个数:");
    scanf("%d", &G.vexnum);
    G.arcs = (int **)malloc(sizeof(int *) * G.vexnum);
    G.vexs = (GElemType *)malloc(sizeof(GElemType) * G.vexnum);
    for (int i = 0; i < G.vexnum; i++)
    {
        G.arcs[i] = (int *)malloc(sizeof(int) * G.vexnum);
        for (j = 0; j < G.vexnum; j++)
            G.arcs[i][j] = MAX;
    }
    printf("输入各节点的值:");
    scanf("%s", G.vexs);
    printf("输入共有几条边：");
    scanf("%d", &G.arcsnum);
    printf("输入各边的起点,终点和权值:");
    getchar();
    for (int i = 0; i < G.arcsnum; i++)
    {
        scanf("%c %c %d", &row, &col, &value);
        getchar();
        j = Locate(G, row);
        k = Locate(G, col);
        G.arcs[j][k] = value;
    }
    return OK;
}

Status DestroyGraphy(Graphy &G)
{
    for (int i = 0; i < G.vexnum; i++)
        free(G.arcs[i]);

    free(G.vexs);
    free(G.arcs);
    G.vexs = NULL;
    G.arcs = NULL;
    return OK;
}

void ShortPath_DIJ(Graphy G, GElemType key)
{
    int n = G.vexnum;
    int min;
    int pos = Locate(G, key);
    int *D = (int *)malloc(sizeof(int) * n);
    int *S = (int *)malloc(sizeof(int) * n);
    int *Path = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        S[i] = False;
        D[i] = G.arcs[pos][i];
        if (D[i] < MAX)
            Path[i] = pos;
        else
            Path[i] = -1;
    }
    S[pos] = True;
    D[pos] = 0;
    for (int i = 1; i < n; ++i)
    {
        min = MAX;
        for (int j = 0; j < n; j++)
        {
            if (!S[j] && D[j] < min)
            {
                pos = j;
                min = D[j];
            }
        }
        S[pos] = True;
        for (int j = 0; j < n; j++)
            if (!S[j] && (D[pos] + G.arcs[pos][j] < D[j]))
            {
                D[j] = D[pos] + G.arcs[pos][j];
                Path[j] = pos;
            }
    }
    for (int i = 0; i < n; i++)
    {
        int pre = Path[i];
        if (pre != -1)
        {
            printf("%c->", G.vexs[i]);
            for (; Path[pre] != -1; pre = Path[pre])
                printf("%c->", G.vexs[pre]);
            printf("%c", G.vexs[pre]);
            printf("\n");
        }
    }
    free(D);
    free(S);
    free(Path);
}

int main()
{
    Graphy G;
    GElemType key;
    CreateGraphy(G);
    printf("请输入源点:");
    scanf("%c", &key);
    ShortPath_DIJ(G, key);
    DestroyGraphy(G);
    return 0;
}

/*
示例输入：
6
abcdef
8
a c 10
a e 30
a f 100
b c 5
c d 50
d f 10
e f 60
e c 20
a
示例输出：
c->a
d->c->a
e->a
f->d->c->a
*/