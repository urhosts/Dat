#pragma once
#include<iostream>
using namespace std;
#include<assert.h>

enum Type
{
	_HEAD_TYPE,
	_VALUE_TYPE,
	_SUB_TYPE
};
struct GeneralizedNode
{
	Type _type;
	struct GeneralizedNode* _next;
	union
	{
		int _value;
		struct GeneralizedNode* _sublink;
	};
	GeneralizedNode(Type type)
	{
		_type = type;
	}
};

class Generalized
{
public:
	Generalized()
		:_head(NULL)
	{}

	Generalized(char* str)
		:_head(NULL)
	{
		_head = Create(str);
	}
	~Generalized()
	{
		_Destroy(_head);
	}
	void Print()
	{
		_Print(_head);
		cout << endl;
	}
	size_t Size()
	{
		size_t count = _Size(_head);
		return count;
	}
	size_t Depth()
	{
		size_t depth = _Depth(_head);
		return depth;
	}
	Generalized(const Generalized& g)
	{
		_head = _Copy(g._head);
	}
	//现代写法
	/*Generalized& operator=(Generalized g)
	{
		std::swap(_head,g._head);
		return *this;
	}*/
	//传统写法
	Generalized& operator=(const Generalized& g)
	{
		if (this != &g)
		{
			GeneralizedNode* head = _Copy(g._head);
			_Destroy(_head);
			_head = head;
		}
		return *this;
	}
protected:
	void _Destroy(GeneralizedNode* _head)
	{
		GeneralizedNode* cur = _head;
		while (cur)
		{
			GeneralizedNode* del = cur;
			if (del->_type == _SUB_TYPE)
			{
				_Destroy(cur->_sublink);
			}
			cur = cur->_next;
			delete del;
		}
	}
	GeneralizedNode* _Copy(GeneralizedNode* head)
	{
		GeneralizedNode* cur = head->_next;//遍历原表
		GeneralizedNode* NewHead = new GeneralizedNode(_HEAD_TYPE);//指向新表
		GeneralizedNode* pre = NewHead;
		GeneralizedNode* NewNode;

		while (cur)
		{
			if (cur->_type == _SUB_TYPE)
			{
				NewNode = new GeneralizedNode(_SUB_TYPE);

				NewNode->_sublink = _Copy(cur->_sublink);
				pre->_next = NewNode;
				/*pre = NewNode;
				cur = cur->_next;*/
			}
			else if(cur->_type == _VALUE_TYPE)
			{
				NewNode = new GeneralizedNode(_VALUE_TYPE);
				NewNode->_type = _VALUE_TYPE;
				NewNode->_value = cur->_value;

				//NewCur->_next = NewNode;
				pre->_next = NewNode;
				//NewCur = NewNode;
				/*NewCur = NewCur->_next;*/

				/*pre = pre->_next;
				cur = cur->_next;*/
			}
			cur = cur->_next;
			pre = pre->_next;
		}
		pre->_next = NULL;
		return NewHead;
	}
	size_t _Depth(GeneralizedNode* head)
	{
		GeneralizedNode* cur = head;
		size_t maxDepth = 1;
		while (cur)
		{
			size_t depth  = 1;
			if (cur->_type == _SUB_TYPE)
			{
				depth = _Depth(cur->_sublink)+1;
				if (depth > maxDepth)
				{
					maxDepth = depth;
				}
			}
			cur = cur->_next;
		
		}
		return maxDepth;
	}
	void _Print(GeneralizedNode* head)
	{
		cout << "(";
		GeneralizedNode* cur = head;

		while (cur)
		{
			if (cur->_type == _VALUE_TYPE)
			{
				cout << cur->_value;
				if (cur->_next != NULL)
				{
					cout << ",";
				}
				cur = cur->_next;
			}
			else if (cur->_type == _SUB_TYPE)
			{
				_Print(cur->_sublink);
				if (cur->_next != NULL)
				{
					cout << ",";
				}
				cur = cur->_next;
			}
			else
			{
				cur = cur->_next;
			}
		}
		cout << ")";
		
	}
	size_t _Size(GeneralizedNode* &head)
	{
		GeneralizedNode* cur = head;
		size_t count = 0;
		while (cur)
		{
			if (cur->_type == _VALUE_TYPE)
			{
				++count;
				cur = cur->_next;
			}
			else if (cur->_type == _SUB_TYPE)//子表
			{
				count += _Size(cur->_sublink);
				cur = cur->_next;
			}
			else
			{
				cur = cur->_next;
			}
		}
		return count;
	}
	bool isValue(char  c)
	{
		//if (isalpha(c))//小写字母，大写字母
		if((c >= 'a'&&c<= 'z')|| (c >= 'A'&&c <= 'Z'))
			return true;
		else
			return false;
	}
	GeneralizedNode* Create(char* &str)
	{
		assert(*str == '(');
		str++;
		GeneralizedNode* head = new GeneralizedNode(_HEAD_TYPE);
		GeneralizedNode* prev = head;
		GeneralizedNode* cur = NULL;
		head->_next = cur;

		while (*str)
		{
			if (isValue(*str))//字母字符
			{
				cur = new GeneralizedNode(_VALUE_TYPE);
				cur->_value = *str;
				prev->_next = cur;
				str++;
				prev = cur;
			}
			else if (*str == '(')
			{
				GeneralizedNode* pLink = new GeneralizedNode(_SUB_TYPE);
				prev->_next = pLink;

				//cur = cur->_next;
				cur = Create(str);
				pLink->_sublink = cur;

				prev = pLink;
			}
			else if (*str == ')')
			{
				prev->_next = NULL;
				str++;
				return head;
			}
			else
			{
				str++;
			}
		}
		return head;
	}
public:
	GeneralizedNode* _head;
};

void TestGeneralized()
{
	Generalized s1("()");
	Generalized s2("(a,b)");
	Generalized s3("(a,b,(c,d))");
	Generalized s4("(a,b,(c,d),e)");
	Generalized s5("(a,b,(c,(),d),e)");
	Generalized s6(s3);
	s1 = s2;
	s1.Print();
	s2.Print();
	s3.Print();
	s4.Print();
	s6.Print();
	cout << s1.Size() << endl;
	cout << s2.Size() << endl;
	cout << s3.Size() << endl;
	cout << s4.Size() << endl;
	cout << s1.Depth() << endl;
	cout << s2.Depth() << endl;
	cout << s3.Depth() << endl;
	cout << s4.Depth() << endl;
	cout << s5.Depth() << endl;
}