#pragma once
#include<iostream>
using namespace std;
#include<stack>

template<typename K>
struct SearchBinaryTreeNode
{
	K _key;
	SearchBinaryTreeNode<K>* _left;
	SearchBinaryTreeNode<K>* _right;
	SearchBinaryTreeNode(const K& key)
		:_key(key)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<typename K>
class SearchBinaryTree
{
	typedef SearchBinaryTreeNode<K> Node;
public:
	SearchBinaryTree()
		:_root(NULL)
	{}

	void InorderNonR()
	{
		_InorderNonR(_root);
	}
	void InsertR(const  K& key)
	{
		_InsertR(_root,key);
	}

	void InOrderR()
	{
		_InOrderR(_root);
		cout << endl;
	}

	void RemoveR(const K& key)
	{
		_RemoveR(_root,key);
	}
	bool RemoveNonR(const K& key)
	{
		if (NULL == _root)
			return false;
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				Node* del = NULL;
				//叶子节点直接删除
				if (cur->_left == NULL && cur->_right == NULL)
				{
					if (parent && cur == parent->_left)
					{
						parent->_left = NULL;
						del = cur;
					}

					else if (parent && cur == parent->_right)
					{
						parent->_right = NULL;
						del = cur;
					}
					else
					{
						del = cur;
						_root = NULL;
					}
				}
				//只有一个孩子的结点
				else if (cur->_left == NULL || cur->_right == NULL)
				{
					//只有左孩子
					if (cur->_left != NULL)
					{
						if (parent == NULL)
						{
							_root = parent->_left;
							del = cur;
						}
						else if (parent->_left == cur)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
					}
					//只有右孩子
					else
					{
						if (parent == NULL)
						{
							_root = cur->_right;
							del = cur;
						}
						else if (parent->_right == cur)
						{
							parent->_right = cur->_right;
						}
						else//cur是parent的左孩子
						{
							parent->_left = cur->_right;
						}
					}
				}
				else//有两个孩子的结点
				{
					Node* tmp = cur->_right;//查找右子树的最左结点
					while (tmp && tmp->_left)
					{
						parent = tmp;
						tmp = tmp->_left;
					}
					swap(cur->_key,tmp->_key);
					//删除tmp结点
					//tmp是叶子节点 ，tmp只有一个孩子结点
					if (tmp == parent->_left)
					{
						parent->_left = tmp->_right;
					}
					else
					{
						parent->_right = tmp->_right;
					}
					del = tmp;
				}
				delete del;
				del = NULL;
				return true;
			}
		}
		//没有找到要删除的值
		return false;
	}
	bool FindNonR(const K& key)
	{
		if (NULL == _root)
			return false;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else
				return true;
		}
		return false;
	}

	bool Insert(const K& key)
	{
		if (NULL == _root)//空树
		{
			_root = new Node(key);
			return true;
		}
		//不是空树
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else//已经存在的值
			{
				return false;
			}
		}
		Node* NewNode = new Node(key);
		if (key < parent->_key)
			 parent->_left = NewNode ;
		else
			parent->_right = NewNode;
		return true;
	}
protected:
	bool _RemoveR(Node*& root,const K& key)
	{
		if (root == NULL)
			return false;
		
		if (root->_key < key)
		{
			_RemoveR(root->_right,key);
		}
		else if (root->_key > key)
		{
			_RemoveR(root->_left,key);
		}
		else
		{
			Node* del = root;
			Node* parent = root;
			if (root->_left == NULL)//仅有右孩子
			{
				root = root->_right;
			}
			else if (root->_right ==NULL)
			{
				root = root->_left;
			}
			else
			{
				Node* minRight = root->_right;
				//找右子树的最左结点
				while (minRight->_left)
				{
					parent = minRight;
					minRight = minRight->_left;
				}
				root->_key = minRight->_key;

				if (minRight == parent->_right)
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
	void _InOrderR(Node* root)
	{
		if (root == NULL)
			return;
		_InOrderR(root->_left);
		cout << root->_key << " ";
		_InOrderR(root->_right);
	}
	void _InsertR(Node*& root, const K& key)
	{
		if (root == NULL)
		{
			root = new Node(key);
			return;
		}
		Node* cur = root;
		if (cur->_key < key)
		{
			_InsertR(cur->_right,key);
		}
		else if (cur->_key > key)
		{
			_InsertR(cur->_left, key);
		}
		else
			return;
	}
	void _InorderNonR(Node* root)
	{
		if (NULL != root)
		{
			Node* cur = root;
			stack<Node*> s;
			while (cur || !s.empty())
			{
				while (cur)
				{
					s.push(cur);
					cur = cur->_left;
				}
				Node* top = s.top();
				s.pop();
				cout << top->_key << " ";
				cur = top->_right;
			}
		}
		cout << endl;
	}
private:
	Node* _root;
};
void TestBinaySearchNonR()
{
	SearchBinaryTree<int> bs;
	//int array[] = { 2,4,1,3,6,5 };
	int array[] = {5,3,4,1,7,8,2,6,0,9};
	for (size_t i = 0; i < 10; ++i)
	{
		bs.Insert(array[i]);
	}
	bs.InorderNonR();


	bs.RemoveNonR(0);
	bs.InorderNonR();
	bs.RemoveNonR(1);
	bs.RemoveNonR(2);
	bs.RemoveNonR(3);
	bs.RemoveNonR(4);
	bs.RemoveNonR(5);
	bs.RemoveNonR(6);
	bs.RemoveNonR(7);
	bs.RemoveNonR(8);
	bs.RemoveNonR(9);
	bs.InorderNonR();
}

void TestBinaySearchR()
{
	SearchBinaryTree<int> bs;
	//int array[] = { 2,4,1,3,6,5 };
	int array[] = { 5,3,4,1,7,8,2,6,0,9 };
	for (size_t i = 0; i < 10; ++i)
	{
		bs.InsertR(array[i]);
	}
	bs.InOrderR();

	bs.RemoveR(0);
	bs.InorderNonR();
	bs.RemoveR(1);
	bs.RemoveR(2);
	bs.RemoveR(3);
	bs.InorderNonR();
	bs.RemoveR(4);
	bs.RemoveR(5);
	bs.RemoveR(6);
	bs.RemoveR(7);
	bs.RemoveR(8);
	bs.RemoveR(9);
	bs.InOrderR();
}