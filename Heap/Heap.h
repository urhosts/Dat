/*************************************************************************
	> File Name: Heap.h
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Sat 03 Jun 2017 01:39:57 PM CST
 ************************************************************************/

#pragma once

#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
using namespace std;

//默认建立最大堆
template <typename T /*typename Compare = Greater<T>*/>
class Heap
{
public:
    Heap()
    {}

    Heap(T* a, int n)
    {
        _a.reserve(n);
        for(size_t i = 0; i < n; ++i)
        {
            _a.push_back(a[i]);
        }
        //建堆，从最后一个非叶子节点开始向下调整
        //父子下标关系：父 = (子 - 1) >> 1
        for(int i = (_a.size() - 2) / 2; i >= 0; --i)
        {
            //调整的前提是左右子树的都满足堆
            _AdjustDown(i);
        }
    }

    //插入到最后一个位置
    void Push(const T& x)
    {
        _a.push_back(x);
        //从最后一个节点开始往上调整
        _AdjustUp(_a.size() - 1);
    }

    void Pop()
    {
        assert(!_a.empty());
        //先交换最后一个节点与堆顶元素
        swap(_a[0],_a[_a.size() - 1]);
        //删除最后一个节点
        _a.pop_back();
        //从堆顶开始向下调整一次即可
        _AdjustDown(0);
    }

    T Top()
    {
        return _a[0];
    }

    size_t Size()
    {
        return _a.size();
    }

    bool Empty()
    {
        return _a.size();
    }

protected:
    void _AdjustDown(int root)
    {
        size_t parent = root;
        size_t child = parent * 2 + 1;     //父子关系公式
        while(child < _a.size())
        {
            if(child + 1 < _a.size() && _a[child] < _a[child + 1])
            {
                ++child;
            }
            if(_a[parent] < _a[child])
            {
                swap(_a[parent], _a[child]);
                parent = child;
                child = parent * 2 + 1;
            }
            else
            {
                break;
            }
        }
        //Compare compare;    //仿函数
    }

    void _AdjustUp(int child)
    {
        int parent = (child - 1) / 2;
        
        while(child > 0)
        {
            if(_a[child] > _a[parent])
            {
                swap(_a[child], _a[parent]);
                child = parent;
                parent = (child - 1) / 2;
            }
            else
            {
                break;
            }
        }
    }
private:
    vector<T> _a;
};

void TestHeap()
{
    int a[] = {10, 16, 18, 12, 11, 13, 15, 17, 14, 19};
    Heap<int> hp1(a, sizeof(a)/sizeof(a[0]));
    for(size_t i = 0; i < 10; ++i)
    {
        cout << hp1[i] << " "<<endl;
    }
}

#endif
