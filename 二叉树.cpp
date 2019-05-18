typedef char BElemType;

#include"BitTree.cpp"

int main()
{
    BitTree T1;
    Init(T1);
    cout<<"创建第一棵树:";
    Create(T1);
    PreOrderTraver(T1);
    cout<<endl;
    InOrderTraver(T1);
    cout<<endl;
    PostOrderTraver(T1);
    cout<<endl;
    Del(T1);
    system("pause");
    return 0;
}

