#include<iostream>

using namespace std;

/* �ڴ����Ŀ������������һ����ڴ棬���Զ����������ݵ��ڴ���䣬
�ﵽ�ڴ�ĸ��ã���������ʵ�Ŀ�ģ�

���ڷ�����������ͷ��ڴ棬�������һ����Ч�ʣ�
*/

template<class T>
class ObjectPool
{
public:
	struct BlockNode
	{
		void* _memory;    // �ڴ�飻
		BlockNode* _next; // ָ����һ���ڴ棻
		size_t _objNum;   // �ڴ����ĸ�����

		BlockNode(size_t objNum)
			:_objNum(objNum)
			,_next(NULL)
		{
			_memory = malloc(_itemSize*objNum);
			if(_memory == NULL)
				throw -1;
		}

		~BlockNode()
		{
			free(_memory);
			_memory = NULL;
		}
	};

protected:
	size_t _countIn;  // ��ǰ������õļ���
	BlockNode* _first;
	BlockNode* _last;
	size_t _maxNum;   //��������ڴ��������
	static size_t _itemSize; //���������С
	T* _lastDelete; // ����ͷŵĶ����ڴ�

public:
	ObjectPool(size_t initNum = 32,size_t maxNum = 100000)
		:_countIn(0)
		,_maxNum(maxNum)
		,_lastDelete(NULL)
	{
		_first = _last = new BlockNode(initNum);
	}

	~ObjectPool()
	{
		BlockNode* cur = _first;
		while(cur)
		{
			BlockNode* del = cur;
			cur = cur->_next;
			delete del;
		}
		_countIn = 0;
		_first = _last = NULL;

	}

	T* New()
	{
		// 1.����ʹ����ǰ�ͷŵĿռ�
		// 2.���ڴ��������ռ�
		// 3.�����µĽ��

		if(_lastDelete)
		{
			//��Ҫ����һ�ε�_lastDelete������������֤��һ�ε�Ѱ�ң�
			T* obj = _lastDelete;
			//ǿ������ת��������һ���ͷŵĿռ��ж�ȡһ��ָ��Ĵ�С��
			_lastDelete = *((T**)_lastDelete);
			//���ض�λnew���õĹ��캯���õĿռ䣻
			return new(obj) T;
		}
		
		if(_countIn >= _last->_objNum)
		{
			size_t objNum = _last->_objNum * 2;
			if(objNum > _maxNum)
				objNum = _maxNum;
			_last->_next = new BlockNode(objNum);
			_last = _last->_next;
			_countIn = 0;
		}
	
			T* obj = (T*)((char*)(_last->_memory)+_countIn*_itemSize);
			_countIn += 1;
			return new(obj) T;
	}

	//���տռ�
	void Delete(T* obj)
	{
		//���յ��ص���������ȥ_lastDelete;
		T* tmp = _lastDelete;
		_lastDelete = obj;
		*(T**)obj = tmp;
	}

	static size_t GetSize()
	{
		//ÿ���ڴ�Ĵ�С���ٲ�С��һ��ָ��
		if(sizeof(T) > sizeof(void*))
			return sizeof(T);
		else
			return sizeof(void*);
	}
};

template<class T>
size_t ObjectPool<T>::_itemSize = ObjectPool<T>::GetSize();