//头文件的引用
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctime>

#include "dsexceptions.h"
#include "List.h"
#include "Vector.h"

using namespace std;

static const int NUMS_PER_LINE = 14;  //定义全局常量


//定义链式堆栈类模板
template <typename Object>
class Stack 
{
  public:
    bool isEmpty( ) const //判断堆栈是否为空
      { return theList.empty( ); }
    
    const Object & top( ) const //取栈顶元素
      { return theList.front( ); }

    void push( const Object & x ) //将元素x压入栈顶
      { theList.push_front( x ); }

    void pop( Object & x ) //将栈顶元素出栈
      { x = theList.front( ); theList.pop_front( ); }
  private:
    List<Object> theList; //类的元素
};

//定义链式队列模板
template <typename Object>
class Queue  
{
  public:
    bool isEmpty( ) const //判断队列是否为空
      { return theList.empty( ); }
    const Object & getFront( ) const  //取队头元素
      { return theList.front( ); }
    void enqueue( const Object & x ) //将元素x入队
      { theList.push_back( x ); }
    void dequeue( Object & x ) //出队
      { x = theList.front( ); theList.pop_front( ); }
  private:
    List<Object> theList;  //类中元素
};

//定义打印数据体中的元素函数模板
template <typename Collection>
void printCollection( const Collection & c )
{
    cout << "Collection contains: " << c.size( ) << " items" << endl;
    int i = 1;

    if( c.empty( ) ) //当c为空时，输出"Empty container."
        cout << "Empty container." << endl;
    //当c不为空时
    else
    {
        for( auto x : c  ) //将c中的元素依次取出赋值给x
        {
            cout << x << " "; //输出x的值
            if( i++ % NUMS_PER_LINE == 0 ) //每输出14个元素输出一个换行
                cout << endl;
        }
        cout << endl;

        if( c.size( ) > NUMS_PER_LINE ) //如果c中的元素个数大于NUMS_PER_LINE，退出函数
            return;

        //c中的元素个数小于NUMS_PER_LINE，倒叙输出c中的内容
        cout << "In reverse: " << endl;
        for( auto ritr = end( c ); ritr != begin( c ); ) //倒序输出c中的值
            cout << *--ritr << " ";
        cout << endl << endl;
    }
}


int jos( int people, int passes, List<int> & order ) 
{
    List<int> theList;  //声明一个链表
    List<int>::iterator p = begin( theList ); //定义变量指向链表头节点
    List<int>::iterator tmp;   //声明变量
    Stack<int> s;  //建立堆栈s
    Queue<int> q;  //建立队列q

    order = List<int>{ };  //为order赋初值

    int i;
    for( i = people; i >= 1; --i )  //当i小于people时，循环
        p = theList.insert( p, i ); //将数据插入链表，采用头插法

    while( people-- != 1 ) //当people不等于1时  
    {
        for( i = 0; i < passes; ++i ) 
            if( ++p == end( theList ) ) //当p等于链表最后一个节点时
                p = begin( theList ); //将p置为表的首元节点

        order.push_back( *p ); //将p指向的节点插入到表尾
        s.push( *p );  //将p指向的节点压入栈中
        q.enqueue( *p );  //将p指向的节点入队
        tmp = p; //将tmp指向p
        if( ++p == end( theList ) ) //p加一，当p指向表尾时 
            p = begin( theList); //将p置为表头
        theList.erase( tmp ); //删除表中节点为tmp的值
    }

    if( order.size( ) % 2 == 0 ) //如果order的长度为偶数
    {
        s.push( 0 );  //入栈元素0
        q.enqueue( 0 );  //入队元素0 
    }

    while( !s.isEmpty( ) && !q.isEmpty( ) ) //当栈和队列都不为空时
    {
        int x, y;
        s.pop( x ); //弹出栈顶元素
        q.dequeue( y );   //队尾元素出队
        if( x == y )  //如果x与y值相等
            cout << "Middle removed is " << x << endl;
    }
    cout << "Only unremoved is ";
    return *begin( theList );  //返回首元节点的值
}

    
void nonsense( int people, int passes )
{
    List<int> lastFew; //声明变量

    cout << jos( people, passes, lastFew ) << endl;
    
    cout << "(Removal order) "; 
    printCollection( lastFew ); //调用函数
}


class CompareList 
{
public:
    bool operator() ( const List<int> & lhs, const List<int> & rhs ) const
    { return lhs.size( ) < rhs.size( ); }  //比较两个链表的长度，当lhs长度大于rhs时返回false
};

// Call by value, to test copy constructor
void print( const Vector<List<int>> arr )  //打印数组的值
{
    int N = arr.size( ); //N等于顺序表的长度
    
    for( int i = 0; i < N; ++i )
    {
        cout << "arr[" << i << "]:";
        
        for( auto x : arr[ i ] )  //取arr中的值依次输出
            cout << " " << x; 
        
        cout << endl;
    }
}

int main( )
{
    const int N = 20;  //常变量N
    Vector<List<int>> arr( N ); //声明顺序表对象arr
    List<int> lst; //声明链表对象lst
    
    for( int i = N - 1; i > 0; --i ) //当i>0的时候
    {
        lst.push_front( i ); //将i插入到链表中，头插法
        arr[ i ] = lst; //将lst插入到顺序表中
    }

    print( arr ); //打印数组中的值
    
    clock_t start = clock( );  //start类型为long，获取当前时间
    std::sort( begin( arr ), end( arr ), CompareList{ } );  //从小到大排序
    clock_t end = clock( );   //获取当前时间
    cout << "Sorting time: " << ( end - start ) << endl;  //输出运行程序共用多长时间
    
    print( arr ); //输出打印数组中的值
    
    nonsense( 12, 0 );  //调用函数
    nonsense( 12, 1 );
  //  nonsense( 3737, 37 );
    system("pause");
    return 0;
}
