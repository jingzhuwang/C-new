#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "dsexceptions.h"


//顺序表哦模板类定义
template <typename Object>
class Vector
{
  public:
    explicit Vector( int initSize = 0 ) //显示声明构造函数，防止防止类构造函数的隐式自动转换
      : theSize{ initSize }, theCapacity{ initSize + SPARE_CAPACITY }
      { objects = new Object[ theCapacity ]; }  //类的初始化
      
    Vector( const Vector & rhs )  //拷贝构造函数
      : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr }
    { 
        objects = new Object[ theCapacity ]; //申请数组空间，长度为theCapacity
        for( int k = 0; k < theSize; ++k ) //拷贝rhs中的值
            objects[ k ] = rhs.objects[ k ];
    }
    
    Vector & operator= ( const Vector & rhs )  //运算符重载
    {
        Vector copy = rhs;  //调用拷贝构造函数
        std::swap( *this, copy );  //将this的值与copy的值交换
        return *this; 
    }
    
    ~Vector( )  //销毁顺序表
      { delete [ ] objects; }

    Vector( Vector && rhs )  //重载构造函数，调用后，后一个顺序表为空
      : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
    {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }
   
    Vector & operator= ( Vector && rhs ) //运算符重载 ，交换前后两个顺序表的值
    {    
        std::swap( theSize, rhs.theSize );
        std::swap( theCapacity, rhs.theCapacity );
        std::swap( objects, rhs.objects );
        
        return *this;
    }
    
    bool empty( ) const //判断顺序表是否为空，为空返回true
      { return size( ) == 0; }
    int size( ) const  //返回顺序表的长度
      { return theSize; }
    int capacity( ) const //返回顺序表的最大长度
      { return theCapacity; }

    Object & operator[]( int index ) //运算符重载，返回顺序表下标为index的元素值
    {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= size( ) )  //判断index值是否越界
            throw ArrayIndexOutOfBoundsException{ };
                                                     #endif
        return objects[ index ]; 
    }

    const Object & operator[]( int index ) const  //运算符重载，作用同上，函数类型为常函数
    {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= size( ) ) //判断index值是否合理
            throw ArrayIndexOutOfBoundsException{ };
                                                     #endif
        return objects[ index ];
    }

    void resize( int newSize ) //对顺序表进行扩容
    {
        if( newSize > theCapacity ) //判断新的顺序表大小是否超过原顺序表的最大长度
            reserve( newSize * 2 );  //调用函数对顺序表进行扩容，并将原顺序表的值拷贝到新数组
        theSize = newSize;
    }

    void reserve( int newCapacity ) //顺序表的扩容
    {
        if( newCapacity < theSize ) //判断新的顺序表长度是否超过原顺序表大小
            return;

        Object *newArray = new Object[ newCapacity ]; //申请新的数组空间
        for( int k = 0; k < theSize; ++k ) //将原顺序表的值拷贝到新的顺序表
            newArray[ k ] = std::move( objects[ k ] );

        theCapacity = newCapacity; //顺序表的最大长度等于新开辟空间的长度
        std::swap( objects, newArray ); //将两个指针交换值
        delete [ ] newArray; //释放原数组的空间
    }

      // Stacky stuff
    void push_back( const Object & x ) //将x插入到顺序表中
    {
        if( theSize == theCapacity ) //判断顺序表是否满
            reserve( 2 * theCapacity + 1 ); //如果顺序表已满，则对顺序表进行扩容
        objects[ theSize++ ] = x; //将x插入到顺序表表尾
    }
      // Stacky stuff
    void push_back( Object && x ) //函数重载，功能同上
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = std::move( x );
    }

    void pop_back( ) //删除顺序表最后一个元素
    {
        if( empty( ) ) //判断顺序表是否为空
            throw UnderflowException{ }; //抛出异常
        --theSize; //顺序表下标减一
    }

    const Object & back ( ) const //取顺序表最后一个元素值
    {
        if( empty( ) ) //判断是否为空
            throw UnderflowException{ }; //抛出异常
        return objects[ theSize - 1 ]; //返回顺序表最后一个元素值
    }

      // Iterator stuff: not bounds checked
    typedef Object * iterator;  //为Object类型起别名
    typedef const Object * const_iterator; 

    iterator begin( )  //取顺序表第一个元素
      { return &objects[ 0 ]; }
    const_iterator begin( ) const //函数重载，功能同上，函数类型为常函数类型
      { return &objects[ 0 ]; }
    iterator end( ) //取数组最后一个元素
      { return &objects[ size( ) ]; }
    const_iterator end( ) const //函数重载，功能同上，函数类型为常函数类型
      { return &objects[ size( ) ]; }

    static const int SPARE_CAPACITY = 2; //静态常量

  private:
    //数据元素
    int theSize;  //顺序表实际长度  
    int theCapacity; //顺序表最大长度
    Object * objects;  //数组指针
};

#endif
