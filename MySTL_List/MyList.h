/*************************************************************************
	> File Name: MyList.h
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Tue 16 May 2017 08:38:52 PM CST
 ************************************************************************/
#pragma once

#ifndef _MYLIST_H
#define _MYLIST_H
#include <iostream>
#include <cstddef>
#include <assert.h>
using namespace std;
template<class T>       //定义成员变量：_next, _prev, _data
struct __ListNode
{
    T _data;
    __ListNode<T>* _prev;
    __ListNode<T>* _next;

    __ListNode(const T& x)
        :_data(x)
        ,_prev(NULL)
        ,_next(NULL)
    {}
};

template<class T, class Ref, class Ptr>
struct __ListIterator
{
    typedef __ListNode<T> Node;
    Node* _node;
    typedef __ListIterator<T, Ref, Ptr> Self;

    __ListIterator(){}      //无参构造函数
    __ListIterator(Node* node)
        :_node(node)
    {}

    Ref operator*()
    {
        return _node->_data;
    }

    Ptr operator->()
    {
        return &(operator*()); //复用
    }

    Self& operator++()
    {
        _node = _node->_next;
        return *this;
    }

    Self& operator--()
    {
        _node = _node->_prev;
        return *this;
    }

    Self operator++(int)
    {
        Self tmp(*this);
        _node = _node->_next;
        return *tmp;
    }

    Self operator--(int)
    {
        Self tmp(*this);
        _node = _node->_prev;
        return *tmp;
    }

    bool operator != (const Self& s) const
    {
        return _node != s._node;
    }

    bool operator == (const Self& s) const 
    {
        return _node == s._node;
    }
};

template<class T>               //List的成员变量_head
class List
{
    typedef __ListNode<T> Node;
public:
    typedef __ListIterator<T, T&, T*> Iterator;
    typedef __ListIterator<T, const T&, const T*> ConstIterator;

    List()
    {
        _head = _BuyNode(T());
        _head->_next = _head;
        _head->_prev = _head;
    }

    ~List()
    {
        Clear();
        delete _head;
        _head = NULL;
    }

    Iterator Begin()
    {
        return Iterator(_head->_next);
    }
    Iterator End()
    {
        return Iterator(_head->_prev);
    }

    ConstIterator Begin() const
    {
        return ConstIterator(_head->_next);
    }
    ConstIterator End() const
    {
        return ConstIterator(_head);
    }

    void Clear()
    {
        Node* cur = _head->_next;
        while(cur != _head)
        {
            Node* next = cur->_next;
            delete cur;
            cur = next;
        }
        _head->_next = _head;
        _head->_prev = _head;
    }

    void PushBack(const T& x)       //尾插
    {
        Node* tail = _head->_prev;
        Node* tmp = _BuyNode(x);

        tail->_next = tmp;
        tmp->_prev = tail;
        tmp->_next = _head;
        _head->_prev = tmp;
    }

    void PopBack()                  //尾删
    {
        assert(_head->_prev);   //首先得保证有这个尾函数
        Node* tail = _head->_prev;
        Node* prev = tail->_prev;
        Node* next = tail->_next;

        prev->_next = next;
        next->_prev = prev;
        delete tail;
    }

    void PushFront(const T& x)  //头插
    {
        Node* tmp = _BuyNode(x);
        Node* next = _head->_next;

        tmp->_next = next;
        next->_prev = tmp;
        _head->_next = tmp;
        tmp->_prev = _head;
    }

    void PopFront()                 //头删
    {
        assert(_head->_next);
        Node* cur = _head->_next;
        Node* next = cur->_next;

        _head->_next = next;
        next->_prev = _head;
        delete cur;
    }

    void Insert(Iterator pos, const T& x)
    {
        Node* next = pos._node;         //断言插入的位置
        Node* prev = next->_prev;
        Node* cur = _BuyNode(x);

        cur->_prev = prev;
        prev->_next = cur;
        cur->_next = next;
        next->_prev = cur;
    }
    Iterator Erase(Iterator pos)
    {
        //不能删除头结点
        assert(pos._node && pos._node != _head);
        Node* next = pos._node->_next;
        Node* prev = pos._node->_prev;

        prev->_next = next;
        next->_prev = prev;

        delete pos._node;

        return Iterator(next);
    }

   //Iterator Find();

protected:
    Node* _BuyNode(const T& x)
    {
        return new Node(x);
    }

private:
    Node* _head;
};

void PrintMyList(const List<int>& l1)
{
    List<int>::ConstIterator it1 = l1.Begin();
    while(it1 != l1.End())
    {
        cout<<*it1<<" ";
        ++it1;
    }
    cout<<endl;
}

void test()
{
    List<int> l1;
    l1.PushBack(1);
    l1.PushBack(2);
    l1.PushBack(3);
    l1.PushBack(4);
    PrintMyList(l1);
    
    l1.PopFront();
    l1.PopBack();
    PrintMyList(l1);
}

#endif
