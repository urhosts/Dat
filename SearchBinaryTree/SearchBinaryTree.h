/*************************************************************************
	> File Name: SearchBinaryTree.h
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Fri 09 Jun 2017 11:42:47 PM CST
 ************************************************************************/

#ifndef _SEARCHBINARYTREE_H
#define _SEARCHBINARYTREE_H

#include <iostream>
#include <stack.h>
#include <stdlib.h>

using namespace std;

template<class K>
struct BinarySearchTreeNode
{
    BinarySearchTreeNode<K>* _left;
    BinarySearchTreeNode<K>* _right;
    K _key;

    BinarySearchTreeNode(const K& key)
        :_key(key)
        ,_left(NULL)
        ,_right(NULL)
    {}
};

template<class K>
class BinarySearchTree
{
    typedef BinarySearchTreeNode<K> Node;

public:
    BinarySearchTree()
        :_root(NULL)
    {}

    ~BinarySearchTree()
    {}

    void InorderR()  //中序遍历(递归)
    {
        _InorderR(_root);
    }

    void InorderNonR()  //中序非递归
    {
        _InorderNonR(_root);
        cout << endl;
    }

    void InsertR()   //递归插入
    {
        _InsertR(_root, key);
    }

    void InsertNonR()   //非递归插入
    {
        _InsertNonR(_root, key);
    }

    void RemoveR()  //递归删除
    {
        _RemoveR(_root, key);
    }

    void RemoveNonR()   //非递归删除
    {
        _RemoveNonR(_root, key);
    }

    void FindR()    //递归查找
    {
        _FindR(_root, key);
    }

    void FindNonR()     //非递归查找
    {
        _FindNonR(_root, key);
    }

protected:
    void _InorderR(Node* root)
    {
        if(root == NULL)
        {
            return;
        }
        _InorderR(root->_left);
        cout<<root->_key<<" ";
        _InorderR(root->_right);
    }

    void _InorderNonR(Node* root)
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
            Node *top = s.top();
            cout<<top->_key<<endl;
            s.pop();
            cur = top->_right;
        }
    }

    bool _InsertR(Node*& root, const K& key)
    {
        if(_root == NULL)
        {
            _root = new Node(key);
            return true;
        }
        Node* cur = root;
        if(cur->_key < key)
        {
            _InsertR(cur->_right, key);
        }
        else if(cur->_key > key)
        {
            _InsertR(cur->_left, key);
        }
        else
        {
            return false;
        }
    }
    
    bool _InsertNonR(const K& key) //非递归插入
    {
        if(_root == NULL)    //如果为空树
        {
            _root = new Node(key);
            return true;
        }
        //如果不是空树
        Node* cur = _root;
        Node* parent = NULL;    //用来保存cur的父亲
        while(cur)
        {
            if(cur->_key < key)
            {
                parent = cur;
                cur = cur->_right;
            }
            else if(cur->key > key)
            {
                parent = cur;
                cur = cur->_left;
            }
            else    //要插入的值已经存在
            {
                return false;
            }
        }
        //当前已经走到“合适”的位置，创建新节点进行插入
        Node *newNode = new Node(key);
        if(key < parent->_key)
            parent->_left = newNode;
        else
            parent->_right = newNode;
        return true;
    }

    bool _RemoveR(Node*& root, const K& key)  //递归删除,注意所传为root的引用
    {
        if(root == NULL)
        {
            return false;
        }
        if(root->_key < key)
        {
            _RemoveR(root->_right, key);
        }
        else if(root->_key > key)
        {
            _RemoveR(root->_left, key);
        }
        //执行到这里说明已经找到所要删的节点
        //接下来的过程无法使用递归程序(同非递归)
        else
        {
            Node* del = root;
            Node* parent = root;
            if(root->_left == NULL)     //仅有右孩子
            {
                root = root->_right;
            }
            else if(root->_right == NULL)   //仅有左孩子
            {
                root = root->_left;
            }
            else
            {
                //寻找右子树的最小节点，与要删节点进行替换
                Node* minRight = root->_right;
                while(minRight)
                {
                    parent = minRight;
                    minRight = minRight->_left;//最小节点即为最左节点
                }
                root->_key = minRight->_key;
                
                //没有左孩子，第一个右孩子即为最小节点
                if(minRight == parent->_right)
                {
                    parent->_right = minRight->_right;
                }
                else
                {
                    parent->_left = minRight->_right;
                }
                del = minRight;
            }
            delete del;
        }
        return true;
    }

    bool _RemoveNonR(const K& key)
    {
        if(_root == NULL)
        {
            return false;
        }
        Node* cur = _root;
        Node* parent = NULL;
        while(cur)
        {
            if(cur->_key < key)
            {
                parent = cur;
                cur = cur->_right;
            }
            else if(cur->_key > key)
            {
                parent = cur;
                cur = cur->_left;
            }
            else
            {
                //1.叶子节点,2.左孩子为空
                if(cur->_left == NULL)
                {
                    if(cur == parent->_left)
                    {
                        parent->_left = cur->_right;
                    }
                    else
                    {
                        parent->_right = cur->_right;
                    }
                    delete cur;
                }
                //3.右孩子为空
                else if(cur->_right == NULL)
                {
                    if(cur == parent->_left)
                    {
                        parent->_left = cur->_left;
                    }
                    else
                    {
                        parent->_right = cur->_left;
                    }
                    delete cur;
                }
                //4.既有左也有右
                //方案:寻找cur的右子书的最左节点，与即要删除的节点进行交换
                else
                {
                    Node* minRight = cur->_right;
                    Node* prev = cur;
                    while(minRight->_left)
                    {
                        parent = minRight;
                        minRight = minRight->_left;
                    }
                    swap(cur->_key, minRight->_key);
                    if(prev->_left == minRight)
                    {
                        prev-_left = minRight->_right;
                    }
                    else
                    {
                        prev->_right = minRight->_right;
                    }
                }
                delete minRight;
                return true;
            }
        }
        return false;
    }

    const Node* FindNonR(const T& key)
    {
        Node* cur = _root;
        while(cur)
        {
            if(cur->_key < key)
            {
                cur = cur->_right;
            }
            else if(cur->_key > key)
            {
                cur = cur->_left;
            }
            else
            {
                return cur;
            }
        }
        return NULL;
    }

    bool _FindR(Node* root, const K& key)
    {
        if(root == NULL)
        {
            return false;
        }
        if(root->_key < key)
        {
            return(root->_right, key);
        }
        else if(root->_key > key)
        {
            return(root->_left, key);
        }
        else
        {
            return true;
        }
        return false;
    }
private:
    Node* _root;
};


void TestBSTree()
{
    int a[] = {5,3,4,1,7,8,2,6,0,9};
    BinarySearchTree<int> t1;
    for(size_t i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
    {
        t1.InsertR(a[i]);
    }
    t1.InOrder();

    t1.RemoveR(0);
    t1.RemoveR(1);
    t1.RemoveR(2);
    t1.RemoveR(3);
    t1.RemoveR(4);
    t1.RemoveR(5);
    t1.RemoveR(6);
    t1.RemoveR(7);
    t1.RemoveR(8);
    t1.RemoveR(9);
    t1.RemoveR(10);

    t1.InOrder();
}

#endif
