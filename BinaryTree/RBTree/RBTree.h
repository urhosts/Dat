#pragma once
#include<iostream>
using namespace std;

enum Colour
{
	RED,
	BLACK
};

template<typename K, typename V>
struct RBTreeNode
{
	K _key;
	V _value;

	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	Colour _col;

	RBTreeNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _col(RED)
	{}
};

template<typename K, typename V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_col = BLACK;
			return true;
		}

		Node* cur = _root;
		Node* parent = cur;
		while (cur)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(key, value);
		if (key > parent->_key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		//调整
		//parent肯定不为空
		//如果parent为黑色，则不用调整

		while (cur != _root && parent->_col == RED)//保证下一次循环parent不为空
		{
			Node* Gparent = parent->_parent;
			if (parent == Gparent->_left)
			{
				//判断叔叔节点的颜色
				//叔叔节点为RED
				//叔叔节点为BLACK或者不存在
				Node* uncle = Gparent->_right;

				if (uncle && uncle->_col == RED)//叔叔节点为RED
				{
					uncle->_col = parent->_col = BLACK;
					Gparent->_col = RED;// Gparent 可能为子树，保证黑色节点数量不变

					//继续向上调整
					cur = Gparent;
					parent = cur->_parent;
				}
				else//叔叔节点为BLACK或者不存在
				{
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(parent, cur);//保证parent指针所指向的位置不变
					}
					RotateR(Gparent);

					//保证左右子树的黑色节点数量不变
					parent->_col = BLACK;
					Gparent->_col = RED;
					//继续向上调整

					cur = parent;
					parent = cur->_parent;
				}
			}
			else
			{
				Node* uncle = Gparent->_left;

				if (uncle && uncle->_col == RED)
				{
					uncle->_col = parent->_col = BLACK;
					Gparent->_col = RED;

					cur = Gparent;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(parent, cur);
					}
					RotateL(Gparent);

					parent->_col = BLACK;
					Gparent->_col = RED;

					cur = parent;
					parent = cur->_parent;

				}
			}
		}
		_root->_col = BLACK;
		return true;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	bool IsRBTree()
	{
		if (_root == NULL)
		{
			return true;
		}
		if (_root->_col == RED)
		{
			return false;
		}

		Node* cur = _root;
		size_t count = 0;
		while (cur)
		{
			if (cur->_col == BLACK)
				count++;
			cur = cur->_left;
		}
		size_t k = 0;
		return _IsRBTree(_root, count, k++);
	}
protected:
	void RotateL(Node* parent)
	{
		Node* SubR = parent->_right;
		Node* SubRL = SubR->_left;
		parent->_right = SubRL;

		if (SubRL)
		{
			SubRL->_parent = parent;
		}

		Node* ppNode = parent->_parent;

		SubR->_left = parent;
		parent->_parent = SubR;

		if (ppNode)
		{
			if (ppNode->_left == parent)
				ppNode->_left = SubR;
			else
				ppNode->_right = SubR;
			SubR->_parent = ppNode;
		}
		else
		{
			SubR->_parent = NULL;
			_root = SubR;
		}
	}
	void RotateR(Node* parent)
	{
		Node* SubL = parent->_left;
		Node* SubLR = SubL->_right;
		parent->_left = SubLR;

		if (SubLR)
		{
			SubLR->_parent = parent;
		}

		Node* ppNode = parent->_parent;

		SubL->_right = parent;
		parent->_parent = SubL;

		if (ppNode)
		{
			if (ppNode->_left == parent)
				ppNode->_left = SubL;
			else
				ppNode->_right = SubL;
			SubL->_parent = ppNode;
		}
		else
		{
			SubL->_parent = NULL;
			_root = SubL;
		}
	}
	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
	bool _IsRBTree(Node* root, const size_t& count, size_t k)
	{
		if (root == NULL)
		{
			return count == k;
		}

		Node * parent = root->_parent;
		if (parent && parent->_col == RED && root->_col == RED)
		{
			return false;
		}

		if (root->_col == BLACK)
		{
			k++;
		}

		return _IsRBTree(root->_left, count, k) && _IsRBTree(root->_right, count, k);

	}
protected:
	Node* _root;
};

void TestRBTree()
{
	RBTree<int, int> tree;
	int a[9] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (int i = 0; i < 9; i++)
	{
		tree.Insert(a[i], i);
		cout << tree.IsRBTree() << "->" << a[i] << endl;
	}
	tree.InOrder();
	cout << tree.IsRBTree() << endl;
}