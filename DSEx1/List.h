#ifndef LIST_H
#define LIST_H

#include <algorithm>
using namespace std;

template <typename Object>  //Object为节点数据域的基本数据类型
class List  //定义链表模版 
{
  private:    
    // The basic doubly linked list node.
    // Nested inside of List, can be public
    // because the Node is itself private
    struct Node
    {
        Object  data; //数据域 
        Node   *prev;  //指向前一个节点 
        Node   *next;  //指向后一个节点 

        //默认构造函数（结构体构造函数）
        Node( const Object & d = Object{ }, Node * p = nullptr, Node * n = nullptr ) 
          : data{ d }, prev{ p }, next{ n } { }  //初始化结构体
        
        Node( Object && d, Node * p = nullptr, Node * n = nullptr )  //Object && d 右值引用（不能改变d的值）或通用引用类型
          : data{ std::move( d ) }, prev{ p }, next{ n } { }  //std::move() 将对象转换为右值引用，将d中的值转移给data，d中变为空值
    }; 

  public:
    class const_iterator
    {
      public:
  
        // Public constructor for const_iterator.
        const_iterator( ) : current{ nullptr } //构造函数（初始化列表）
          { }

        // Return the object stored at the current position.
        // For const_iterator, this is an accessor with a
        // const reference return type.

        //运算符重载 
        const Object & operator* ( ) const  //*运算符重载，取当前节点的数据元素
          { return retrieve( ); } 
        
        const_iterator & operator++ ( ) //后置++
        {
            current = current->next; //将current指向下一个节点
            return *this;
        }

        const_iterator operator++ ( int ) //前置++
        {
            const_iterator old = *this; 
            ++( *this );
            return old;
        }

        const_iterator & operator-- ( ) //后置--
        {
            current = current->prev;
            return *this;
        }

        const_iterator operator-- ( int ) //前置--
        {
            const_iterator old = *this;
            --( *this );
            return old;
        }
            
        bool operator== ( const const_iterator & rhs ) const //== 运算符重载
          { return current == rhs.current; }

        bool operator!= ( const const_iterator & rhs ) const  // ！= 运算符重载
          { return !( *this == rhs ); }

      protected:
        Node *current; //定义类中的节点

        // Protected helper in const_iterator that returns the object
        // stored at the current position. Can be called by all
        // three versions of operator* without any type conversions.
        Object & retrieve( ) const //获取当前值，返回类型为引用
          { return current->data; }

        // Protected constructor for const_iterator.
        // Expects a pointer that represents the current position.
        const_iterator( Node *p ) :  current{ p } //设定current的值
          { }
        
        friend class List<Object>;  //声明友元类
    };

    class iterator : public const_iterator  //iterator公有继承const_iterator
    {
      public:

        // Public constructor for iterator.
        // Calls the base-class constructor.
        // Must be provided because the private constructor
        // is written; otherwise zero-parameter constructor
        // would be disabled.
        iterator( ) //类的初始化
          { }

        Object & operator* ( )  //*运算符重载 ，取值
          { return const_iterator::retrieve( ); }

        // Return the object stored at the current position.
        // For iterator, there is an accessor with a
        // const reference return type and a mutator with
        // a reference return type. The accessor is shown first.
        const Object & operator* ( ) const  //运算符 * 重载，取值运算
          { return const_iterator::operator*( ); }
        
        //运算符重载
        iterator & operator++ ( ) //后置++
        {
            this->current = this->current->next;  //将this指向后面的值
            return *this;
        }

        iterator operator++ ( int ) //前置++
        {
            iterator old = *this;
            ++( *this );
            return old;
        }

        iterator & operator-- ( ) //后置--
        {
            this->current = this->current->prev;
            return *this;
        }

        iterator operator-- ( int ) //前置--
        {
            iterator old = *this;
            --( *this );
            return old;
        }

      protected:
        // Protected constructor for iterator.
        // Expects the current position.
        iterator( Node *p ) : const_iterator{ p }  //有参构造函数
          { }

        friend class List<Object>; //声明友元类
    };

  public:
    List( ) //类的初始化
      { init( ); }

    ~List( ) //销毁类
    {
        clear( ); //调用clear（）函数
        //释放内存
        delete head; 
        delete tail;
    }

    List( const List & rhs ) //拷贝构造函数
    {
        init( );
        //循环从rhs中取值赋给x
        for( auto & x : rhs ) //auto的自动类型推导，用于从初始化表达式中推断出变量的数据类型
            push_back( x );  //将x的值插入到链表中
    }

    List & operator= ( const List & rhs ) // = 运算符重载
    {
        List copy = rhs; //将rhs中的值拷贝到copy中
        std::swap( *this, copy );  //将copy和this指向的表中的元素交换
        return *this;
    }

    
    List( List && rhs )  //拷贝构造函数（初始化列表）
      : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
   
    List & operator= ( List && rhs ) // = 运算符重载
    {    
        //将两个顺序表中的值相互交换
        std::swap( theSize, rhs.theSize ); 
        std::swap( head, rhs.head );
        std::swap( tail, rhs.tail );
        
        return *this;
    }
    
    // Return iterator representing beginning of list.
    // Mutator version is first, then accessor version.
    iterator begin( )  //取链表首元节点的地址
      { return iterator( head->next ); }

    const_iterator begin( ) const  //函数重载，取链表首元节点
      { return const_iterator( head->next ); }

    // Return iterator representing endmarker of list.
    // Mutator version is first, then accessor version.
    iterator end( ) //取链表表尾元素
      { return iterator( tail ); }

    const_iterator end( ) const  ////函数重载，取链表表尾节点
      { return const_iterator( tail ); }

    // Return number of elements currently in the list.
    int size( ) const //返回链表的长度
      { return theSize; }

    // Return true if the list is empty, false otherwise.
    bool empty( ) const  //判断链表是否为空，为空返回true，不空返回false
      { return size( ) == 0; }

    void clear( )  //清除链表元素
    //当链表不为空时，取首元节点
    {
        while( !empty( ) ) //当表不为空时
            pop_front( ); //删除首元节点
    }
 
    // front, back, push_front, push_back, pop_front, and pop_back
    // are the basic double-ended queue operations.
    Object & front( ) //取链表首元节点，函数返回值为引用
      { return *begin( ); }

    const Object & front( ) const  //函数重载，功能同上
      { return *begin( ); }

    Object & back( ) //取队尾元素，函数返回值类型为引用
      { return *--end( ); }

    const Object & back( ) const //函数重载，功能同上
      { return *--end( ); }

    void push_front( const Object & x ) //采用头插法将元素x插入链表
      { insert( begin( ), x ); }

    void push_back( const Object & x ) //尾插法插入元素
      { insert( end( ), x ); }

    void push_front( Object && x )  //头插法插入元素x
      { insert( begin( ), std::move( x ) ); }

    void push_back( Object && x ) //尾插法插入数据元素
      { insert( end( ), std::move( x ) ); }

    void pop_front( )  //删除首元节点
      { erase( begin( ) ); }

    void pop_back( ) //删除表尾节点
      { erase( --end( ) ); }

    // Insert x before itr.
    iterator insert( iterator itr, const Object & x ) //插入数据元素
    {
        Node *p = itr.current;  //声明变量  
        ++theSize;  //长度加一
        return iterator( p->prev = p->prev->next = new Node{ x, p->prev, p } );
    }

    // Insert x before itr.
    iterator insert( iterator itr, Object && x ) //函数重载，功能同上
    {
        Node *p = itr.current;
        ++theSize;
        return iterator( p->prev = p->prev->next = new Node{ std::move( x ), p->prev, p } );
    }
    
    // Erase item at itr.
    iterator erase( iterator itr ) //删除表中节点为itr的元素
    {
        Node *p = itr.current; //声明变量
        iterator retVal( p->next ); 
        p->prev->next = p->next; //将p的前一个节点的next域指向p的下一个节点
        p->next->prev = p->prev; //将p的下一个节点的prev域指向p的前一个节点
        delete p;  //释放p所指向的空间
        --theSize; //表长减一

        return retVal; //返回删除的节点的下一个节点
    }

    iterator erase( iterator from, iterator to ) //删除表中从from到to的全部节点
    {
        for( iterator itr = from; itr != to; )
            itr = erase( itr );

        return to;
    }

  private:
    int   theSize;  //链表长度
    Node *head;  //头指针
    Node *tail; //尾指针

    void init( )  //初始化数据元素函数
    {
        theSize = 0;
        head = new Node;  //申请空间
        tail = new Node;  //申请空间
        head->next = tail;
        tail->prev = head;
    }
};

//结束定义
#endif
