/*************************************************************************
	> File Name: BinaryTree.h
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Wed 03 May 2017 08:32:09 PM CST
 ************************************************************************/

#pragma once
#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <iostream>
#include <stack>
#include <assert.h>
#include <queue>

using namespace std;

template <typename T>
struct BinaryTreeNode
{
    T _data;
    BinaryTreeNode<T>* _left;
    BinaryTreeNode<T>* _right;

    BinaryTreeNode(const T& x)
        :_left(NULL)
        ,_right(NULL)
        ,_data(x)
    {}
};

template <typename T>
class BinaryTree
{
    typedef BinaryTreeNode<T> Node;
public:
    BinaryTree()
        :_root(NULL)
    {}

    BinaryTree(T* a, size_t size, const T& invalid)
    {
        size_t index = 0;   //数组下标
        _root= _CreateTree(a, size, invalid, index);
    }

    BinaryTree(const BinaryTree<T>& t)  //拷贝构造
    {
        _root = _CopyTree(t._root);
    }
    
    BinaryTree<T> operator=(const BinaryTree<T> t)
    {
        swap(_root, t._root);
        return *this;
    }

    ~BinaryTree()
    {
        _Destory(_root);
    }

public:
    void PrevOrder()    //前序遍历
    {
        cout << "PrevOrder:";
        _PrevOrder(_root);
        cout << endl;
    }

    void PrevOrder_NonR()
    {
        cout << "PrevOrder_NonR:";
        _PrevOrderNonR(_root);
        cout << endl;
    }

    void InOrder()
    {
        cout << "InOrder:";
        _InOrder(_root);
        cout << endl;
    }

    void InOrder_NonR()
    {
        cout<<"InOrder_NonR:";
        _InOrder_NonR(_root);
        cout << endl;
    }

    void PostOrder()
    {
        cout << "PostOrder:";
        _PostOrder(_root);
        cout << endl;
    }

    void PostOrder_NonR()
    {
        cout<<"PostOrder_NonR:";
        _PostOrderNonR(_root);
        cout << endl;
    }

    //队列先进先出的特性
    void LevelOrder()
    {
        cout << "LevelOrder:";
        _LevelOrder(_root);
        cout << endl;
    }

    void Find(const T& x)
    {
        cout<<"Find:"<<endl;
        _Find(_root, x);
        cout<<endl;
    }

    size_t Size()
    {
        return _Size(_root);
    }

    size_t LeafSize()
    {
        return _LeafSize(_root);
    }

    size_t Depth()
    {
        return _Depth(_root);
    }
    
    size_t GetKLevelSize(size_t k)
    {
        assert(k > 0);
        return _GetKLevel(_root, k);
    }

protected:
    Node* _CreateTree(T *a, size_t size, const T& invalid, size_t& index)
    {
        Node* root = NULL;
        if(index < size && a[index] != invalid)    //防越界，排除空节点
        {
            root = new Node(a[index]);
            root->_left =_CreateTree(a, size, invalid, ++index);
            root->_right = _CreateTree(a, size, invalid, ++index);
        }
        return root;
    }

    //后面来实现
    //Node* _CopyTree(Node* t_root)
    //{
    //    Node* root = NULL;
    //    if(t_root != NULL)
    //    {
    //        root = new Node(t_root->data);
    //    }
    //}

    void _Destory(Node* root)
    {
        if(root == NULL)
        {
            return;
        }
        if(root->_left)
        {
            _Destory(root->_left);
        }
        if(root->_right)
        {
            _Destory(root->_right);
        }
        delete root;
        root = NULL;
    }

    void _PrevOrder(Node* root)
    {
        if(root == NULL)
        {
            return;
        }
        cout << root->_data << " ";
        _PrevOrder(root->_left);
        _PrevOrder(root->_right);
    }
    
    void _PrevOrderNonR(Node* root)
    {
        if(root == NULL)
        {
            return;
        }
        stack<Node*> s;
        Node* cur = root;
        while(!s.empty() || cur)
        {
            while(cur)
            {
                cout<<cur->_data<<" ";
                s.push(cur);
                cur = cur->_left;
            }
            Node* top = s.top();
            s.pop();
            cur = top->_right;
        }
    }

    void _InOrder(Node* root)
    {
        if(root == NULL)
        {
            return;
        }
        _InOrder(root->_left);
        cout << root ->_data << " ";
        _InOrder(root->_right);
    }
    
    void _InOrder_NonR(Node* root)
    {
        if(root == NULL)
        {
            return;
        }
        stack<Node*> s;
        Node* cur = root;
        while(!s.empty() || cur)
        {
            while(cur)
            {
                s.push(cur);
                cur = cur->_left;
            }
            Node* top = s.top();
            cout<<top->_data<<" ";
            s.pop();
            cur = top->_right;
        }
    }
    void _PostOrder(Node* root)
    {
        if(root == NULL)
        {
            return;
        }
        _PostOrder(root->_left);
        _PostOrder(root->_right);
        cout << root->_data << " ";
    }

    void _PostOrderNonR(Node* root)
    {
        if(root == NULL)
        {
            return;
        }
        stack<Node*> s;
        Node* cur = root;
        Node* prev = NULL;
        while(!s.empty() || cur)
        {
            while(cur)
            {
                s.push(cur);
                cur = cur->_left;
            }
            Node* top = s.top();
            if(top->_right == NULL || top->_right == prev)
            {
                cout<<top->_data<<" ";
                prev = top;
                s.pop();
            }
            else
            {
                cur = top->_right;
            }
        }
    }

    void _LevelOrder(Node* root)
    {
        if(root == NULL)
        {
            return;
        }
        queue<Node*> q;
        q.push(root);
        while(!q.empty())
        {
            Node* front = q.front();
            cout << front->_data << " ";    //访问并记录对头元素
            q.pop();                    //访问完之后踢出对头元素
            if(front->_left != NULL)
            {
                q.push(front->_left);
            }
            if(front->_right != NULL)
            {
                q.push(front->_right);
            }
        }
        cout << endl;
    }

    Node* _Find(Node* root, const T& x)
    {
        if(root == NULL)
        {
            return;
        }
        if(root->_data == x)
        {
            return root;
        }
        Node* ret = _Find(root->_left, x);
        if(ret)
        {
            return ret;
        }
        else
        {
            return _Find(root->_right, x);
        }
    }

    size_t _Size(Node* root)
    {
        if(root == NULL)
        {
            return 0;
        }
        return _Size(root->_left) + _Size(root->_right) + 1;
    }

    size_t _Depth(Node* root)
    {
        if(root == NULL)
        {
            return 0;
        }
        size_t LeftDepth = _Depth(root->_left) + 1;
        size_t RightDepth = _Depth(root->_right) + 1;
        return LeftDepth < RightDepth ? RightDepth : LeftDepth;
    }

    size_t _LeafSize(Node* root)
    {
        if(root == NULL)
        {
            return 0;
        }
        if(root->_left == NULL && root->_right == NULL)
        {
            return 1;
        }
        return _LeafSize(root->_left) + _LeafSize(root->_right);
    }

    void _LeafSize(Node* root, size_t& size)
    {
        if(root == NULL)
        {
            return 0;
        }
        if(root->_left == NULL && root->_right == NULL)
        {
            ++size;
        }
        _LeafSize(root->_left, size);
        _LeafSize(root->_right, size);
    }

    size_t _GetKLevel(Node* root, int k)
    {
        if(root == NULL)
        {
            return 0;
        }
        if( k == 1 )
        {
            return 1;
        }
        size_t leftLevel = _GetKLevel(root->_left, k - 1);
        size_t rightLevel = _GetKLevel(root->_right, k - 1);
        return leftLevel + rightLevel;
    }

    size_t _GetKLevel(Node* root, int k, size_t& size, int level)
    {
        if(root == NULL)
        {
            return 0;
        }
        if( level == k )
        {
            ++size;
        }
        _GetKLevel(k, root->_left, size, level + 1);
        _GetKLevel(k, root->_right, size, level + 1);
        return size;
    }
private:
    Node* _root;
};

void test1()
{
    int a1[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6  };
    int a2[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8  };
    BinaryTree<int> t1(a1, 10, '#');
    BinaryTree<int> t2(a2, 15, '#');
   
    t1.PrevOrder();
    t1.PrevOrder_NonR();
    t1.InOrder();
    t1.InOrder_NonR();
    t1.PostOrder();
    t1.PostOrder_NonR();
    t1.LevelOrder();
    cout << "Size: " << t1.Size() << endl;
    cout << "Depth: " << t1.Depth() << endl;
    cout << "LeafSize: " << t1.LeafSize() << endl;
    cout << "GetKLevel: " << t1.GetKLevelSize(3) << endl;

    cout<<endl;
    cout<<"#################################################"<<endl<<endl;
    
    t2.PrevOrder();
    t2.PrevOrder_NonR();
    t2.InOrder();
    t2.InOrder_NonR();
    t2.PostOrder();
    t2.PostOrder_NonR();
    t2.LevelOrder();
    cout << "Size: " << t2.Size() << endl;
    cout << "Depth: " << t2.Depth() << endl;
    cout << "LeafSize: " << t2.LeafSize() << endl;
    cout << "GetKLevel: " << t2.GetKLevelSize(4) << endl;
}
 
#endif
