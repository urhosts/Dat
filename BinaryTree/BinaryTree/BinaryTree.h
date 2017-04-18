
#pragma once
#include<iostream>
using namespace std;
#include<assert.h>
#include<queue>
#include<stack>

template<typename T>
struct TreeNode
{
	T _data;
	TreeNode* _left;
	TreeNode* _right;
	TreeNode(const T& x = T())
		:_data(x)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<typename T>
class BinaryTree
{
	typedef TreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(T* a,size_t size,const T& invalid)
	{
		size_t index = 0;
		_root = _Create(a,size,index,invalid);
	}
	~BinaryTree()
	{
		_Destroy(_root);
	}
	void PreOrderTraverse()//前序遍历
	{
		_PreOrder(_root);
		cout << endl;
	}
	Node* Find(const T& x)
	{
		return _Find(_root,x);
	}
	void InOrderTraverse()//中序遍历
	{
		_InOrder(_root);
		cout << endl;
	}
	void PostOrderTraverse()//后序遍历
	{
		_PostOrder(_root);
		cout << endl;
	}
	void TierOrderTraverse()//层序遍历
	{
		_TiertOrder(_root);
		cout << endl;
	}
	size_t Size()
	{
		size_t size = _Size(_root);
		return size;
	}
	size_t  Depth()
	{
		size_t depth = _Depth(_root);
		return depth;
	}
	void PreOrderTraverseNonR()
	{
		stack<Node*> s;
		Node* cur = _root;
		if (cur == NULL)
			return;

		while (cur || !s.empty())
		{
			while (cur)
			{
				cout << cur->_data << " ";
				s.push(cur);
				cur = cur->_left;
			}
			
			Node* top = s.top();
			s.pop();
			cur = top->_right;
		}
		cout << endl;
	}
	void InOrderTraverseNonR()
	{
		stack<Node*> s;
		Node* cur = _root;
		if (cur == NULL)
			return;

		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			
			Node* top = s.top();
			cout << top->_data<<" ";
			s.pop();
			cur = top->_right;
		}
		cout << endl;
	}
	void PostOrderTraverseNonR()
	{
		if (NULL == _root)
			return;
		Node* prev = NULL;
		Node* cur = _root;
		stack<Node*> s;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			if (top->_right == NULL || top->_right == prev)
			{
				cout << top->_data << " ";
				prev = top;
				s.pop();
			}
			else
			{
				cur = top->_right;
			}
		}
		cout << endl;
	}
	//void PostOrderTraverseNonR()
	//{
	//	Node* cur = _root;
	//	if (NULL == cur)
	//		return;
	//	
	//	stack<Node*> s;
	//	size_t size = Size();
	//	size_t tag[15] = { 0 };
	//	Node* tmp = NULL;
	//	while (cur || !s.empty())
	//	{
	//		while (cur)
	//		{
	//			s.push(cur);
	//			cur = cur->_left;
	//		}

	//		if (tag[s.size()-1] == 1)//表示是从右子树返回的
	//		{
	//			tmp = s.top();
	//			cout << tmp->_data << " ";
	//			s.pop();
	//		}
	//		else//表示是从左子树返回的
	//		{
	//			tmp = s.top();
	//			cur = tmp->_right;
	//			tag[s.size() - 1] = 1;
	//		}
	//	}
	//	cout << endl;
	//}
	size_t FindKLevel(size_t n)//统计第n层元素的个数
	{
		return _FindKLevel(_root,n);
	}
protected:
	Node* _Create(T* a, size_t size,size_t& index,const T& invalid)
	{
		assert(a);
		Node* root = NULL;
		while (index < size && a[index] != invalid)
		{
		    root = new Node(a[index]);
			root->_left = _Create(a,size,++index,invalid);
			root->_right = _Create(a,size, ++index,invalid);
		}
		return root;
	}
	void _Destroy(Node* root)
	{
		if (root == NULL)
			return;

		_Destroy(root->_left);
		_Destroy(root->_right);
	}
	void _PreOrder(Node* root)
	{
		Node* cur = root;
		if (cur != NULL)
		{
			cout << cur->_data<<" ";
			_PreOrder(cur->_left);
			_PreOrder(cur->_right);
		}
	}
	void _InOrder(Node* root)
	{
		Node* cur = root;
		if (cur != NULL)
		{
			_InOrder(cur->_left);
			cout << cur->_data<<" ";
			_InOrder(cur->_right);
		}
	}
	void _PostOrder(Node* root)
	{
		Node* cur = root;
		if (cur != NULL)
		{
			_PostOrder(cur->_left);
			_PostOrder(cur->_right);
			cout << cur->_data<<" ";
		}
	}
	void _TiertOrder(Node* root)
	{
		queue<Node*> q;
		Node* cur = root;
		q.push(cur);
		while (!q.empty())
		{
			Node* tmp = q.front();
			cout << tmp->_data << " ";
			if (tmp->_left)
			{
				q.push(tmp->_left);
			}
			if (tmp->_right)
			{
				q.push(tmp->_right);
			}
			q.pop();
		}
	}
	size_t _FindKLevel(Node* root,size_t  n)
	{
		assert(n > 0);
		if (root == NULL)
			return 0;

		if (n == 1)
			return 1;

		size_t  left = _FindKLevel(root->_left,n-1);
		size_t  right = _FindKLevel(root->_right,n-1);
		return left + right;
	}
	
	size_t _Size(Node* root)
	{
		
		if (root == NULL)
			return 0;

		return _Size(root->_left) + _Size(root->_right) + 1;
	}
	size_t _Depth(Node* root)
	{
		if (root == NULL)
			return 0;

		size_t left = _Depth(root->_left);
		size_t right = _Depth(root->_right);
		return left > right ? left + 1 : right + 1;
	}
	Node* _Find(Node* root, const T& x)
	{
		Node* cur = root;
		if (cur == NULL)
			return NULL;

		if (cur->_data == x)
			return cur;

		//左子树没有找到才会去遍历 右子树
		if (!_Find(cur->_left, x))
			_Find(cur->_right,x);
	}
private:
	Node* _root;
};