/*************************************************************************
	> File Name: RBTree.h
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Mon 19 Jun 2017 11:37:02 PM CST
 ************************************************************************/

#ifndef _RBTREE_H
#define _RBTREE_H

#include <iostream>

enum Color
{
    BLACK,
    RED,
};

template<class K, class V>
struct RBTreeNode
{
    K _key;
    V _value;

    RBTreeNode<K, V>* _left;
    RBTreeNode<K, V>* _right;
    RBTreeNode<K, V>* _parent;

    Color _color;

    RBTreeNode(const K& key, const V& value, Color color = RED)
        :_key(key)
        ,_value(value)
        ,_left(NULL)
        ,_right(NULL)
        ,_parent(NULL)
        ,_color(color)
    {}

};

template<class K, class V>
class RBTree
{
    typedef RBTreeNode<K, V> Node;
public:
    RBTree()
        :_root(NULL)
    {}
private:
    Node* _root;
};

#endif
