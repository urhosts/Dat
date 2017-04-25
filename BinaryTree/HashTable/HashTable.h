#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<string>

//开放地址法
namespace Open
{
	enum Status
	{
		EMPTY,
		EXIST,
		DELETE
	};


	template<typename K, typename V>
	struct KVNode
	{
		K _key;
		V _value;

		Status _status;//保存某个位置的状态
		KVNode(const K& key = K(), const V& value = V())
			:_key(key)
			, _value(value)
			, _status(EMPTY)
		{}
	};
	template<typename K>
	struct __GetK
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	struct __GetStrK
	{
		static size_t BKDRHash(const char* str)
		{
			unsigned int seed = 131;// 31 131 1313 13131 131313
			unsigned int hash = 0;
			while (*str)
			{
				hash = hash * seed + (*str++);
			}
			return(hash & 0x7FFFFFFF);
		}
		size_t operator()(const string& str)
		{
			return BKDRHash(str.c_str());
		}
	};

	template<typename K, typename V, typename GetK = __GetK<K>>
	class HashTable
	{
		typedef KVNode<K, V> Node;

	public:
		HashTable()
			:_size(0)
		{
			_tables.resize(2);
		}

		~HashTable()
		{}


		void Swap(HashTable<K, V, GetK>& ht)
		{
			swap(_size, ht._size);
			_tables.swap(ht._tables);
		}

		bool Insert(const K& key, const V& value)
		{
			_CheckCapacity();
			int index = _GetIndex(key, value);

			while (_tables[index]._status == EXIST)
			{
				if (_tables[index]._key == key)//要插入的值在原表中已经存在
				{
					return false;
				}

				++index;

				if (index == _tables.size())
				{
					index = 0;
				}
			}

			//找到合适的位置
			_tables[index]._key = key;
			_tables[index]._value = value;
			_tables[index]._status = EXIST;//将状态改为存在
			++_size;
		}

		Node* Find(const K& key, const V& value)
		{
			int index = _GetIndex(key, value);
			int begin = index;
			while (_tables[index]._key != key)
			{
				++index;
				if (index == _tables.size())
				{
					index = 0;
				}
				if (index == begin)
				{
					return NULL;
				}
			}
			//有可能是要删除的已经存在的元素
			if (_tables[index]._status == EXIST)
			{
				return &_tables[index];
			}
			else
				return NULL;
		}

		bool Remove(const K& key, const V& value)
		{
			if (_size == 0)
				return false;
			int index = _GetIndex(key, value);
			int begin = index;
			while (_tables[index]._status != EMPTY)
			{
				if (_tables[index]._key == key && _tables[index]._status == EXIST)
				{
					_tables[index]._status = DELETE;
					--_size;
					return true;
				}

				++index;
				if (index == _tables.size())
				{
					index = 0;
				}
				if (index == begin)//已经遍历一圈
				{
					return false;
				}
			}
		}
	protected:
		void _CheckCapacity()
		{
			if (_size * 10 / _tables.size() >= 8)//保证查找效率
			{
				int newSize = _GetNewSize(_tables.size());
				HashTable<K, V, GetK> hash;
				hash._tables.resize(newSize);
				for (size_t i = 0; i < _size; ++i)
				{
					if (_tables[i]._status == EXIST)
					{
						hash.Insert(_tables[i]._key, _tables[i]._value);
					}
				}
				this->Swap(hash);
			}
			else
				return;
		}

		int _GetIndex(const K& key, const V& value)
		{
			GetK getK;
			return getK(key) % _tables.size();
		}
		int _GetNewSize(int num)
		{
			const int _PrimeSize = 28;
			static const unsigned long _PrimeList[_PrimeSize] = {
				53ul, 97ul, 193ul, 389ul, 769ul,
				1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
				49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
				1572869ul, 3145739ul, 6291469ul, 12582917ul,
				25165843ul, 50331653ul, 100663319ul, 201326611ul, 402653189ul,
				805306457ul, 1610612741ul, 3221225473ul, 4294967291ul
			};
			for (int i = 0; i < _PrimeSize; ++i)
			{
				if (_PrimeList[i] > num)
					return _PrimeList[i];
			}
			return _PrimeList[_PrimeSize - 1];
		}
	protected:
		vector<Node> _tables;
		size_t _size;
	};
}


void TestHashTableOpen()
{
	Open::HashTable<int, int>  ht1;//模板参数3是采用缺省的参数
	int array1[] = { 89, 18, 8, 58, 2, 3, 4, 9, 0 };
	for (int i = 0; i < sizeof(array1) / sizeof(array1[0]); ++i)
	{
		ht1.Insert(array1[i], 0);
	}
	ht1.Remove(8, 0);
	ht1.Remove(1, 0);

	Open::HashTable<string, int, Open::__GetStrK> ht2;
	char* array2[] = { "hello", "world", "sort", "find", "sort" };
	for (int i = 0; i < sizeof(array2) / sizeof(array2[0]); ++i)
	{
		Open::KVNode<string, int>* node = ht2.Find(array2[i], 0);
		if (node)//结点已经存在
		{
			node->_value++;
		}
		else
		{
			ht2.Insert(array2[i], 0);
		}
	}
}


//开链法
namespace Link
{
	template<typename K, typename V>
	struct KVNode
	{
		K _key;
		V _value;
		KVNode<K, V>* _next;

		KVNode(const K& key = K(), const V& value = V())
			:_key(key)
			, _value(value)
			, _next(NULL)
		{}
	};

	template<typename K>
	struct __GetK
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	template<>
	struct __GetK<string>
	{
		static size_t BKDRHash(const char* str)
		{
			unsigned int seed = 131;
			unsigned int hash = 0;
			while (*str)
			{
				hash = hash * seed + (*str++);
			}
			return(hash & 0x7FFFFFFF);
		}
		size_t operator()(const string& str)
		{
			return BKDRHash(str.c_str());
		}
	};

	template<typename K, typename V, typename GetK = __GetK<K>>
	class HashTable
	{
		typedef KVNode<K, V> Node;
	public:
		HashTable()
			:_size(0)
		{
			_tables.resize(2);//初始化开辟2个空间
		}

		~HashTable()
		{
			Node* cur = NULL;
			Node* del = NULL;
		
			for (int i = 0; i <(int)_tables.size(); ++i)
			{
				cur = _tables[i];
				while (cur)
				{
					del = cur;
					cur = cur->_next;
					delete del;
					del = NULL;
				}
				
			}
			_tables.clear();
			_size = 0;
		}
		bool Insert(const K& key, const V& value)
		{
			//检查容量
			_CheckCapacity();
			int index = _GetIndex(key, _tables.size());
			//先查找，看要插入的元素是否已经存在
			if (Find(key))
			{
				return false;
			}
			//插入元素分两种情况
			//1.插入的结点是第一个结点
			//2.插入的结点不是第一个结点
			Node* newNode = new Node(key, value);
			newNode->_next = _tables[index];
			_tables[index] = newNode;
			++_size;
		}

		Node* Find(const K& key)
		{
			if (_size == 0)
			{
				return false;
			}
			int index = _GetIndex(key, _tables.size());
			Node* cur = _tables[index];
			while (cur)
			{
				if (cur->_key == key)
					return cur;
				cur = cur->_next;
			}
			return NULL;
		}

		bool Remove(const K& key)
		{
			if (_size == 0)
			{
				return false;
			}
			int index = _GetIndex(key, _tables.size());
			//删除分3种情况
			//1.删除第一个节点
			//2.删除中间结点
			//3.删除最后一个结点
			Node* cur = _tables[index];
			//记录要删除结点的上一个结点
			Node* prev = NULL;
			while (cur)
			{
				if (cur->_key == key)//找到要删除的结点
				{
					if (prev == NULL)//要删除的就是第一个结点
					{
						_tables[index] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}
					delete cur;
					--_size;
					return true;
				}
				prev = cur;
				cur = cur->_next;
			}
			return false;
		}

		void Print()
		{
			if (_size == 0)
				return;
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				cout << "_tables[" << i << "]" << "->";
				while (cur)
				{
					cout << cur->_key << "->";
					cur = cur->_next;
				}
				cout << "NULL" << endl;
			}
		}
	protected:
		int _GetIndex(const K& key, size_t size)
		{
			GetK getK;
			return getK(key) % size;
		}


		//增容过程中，多一次释放，多一次开辟，导致空间 利用率不是很高
		//void _CheckCapacity()
		//{
		//	if(_size == _tables.size())
		//	{
		//		int newSize = _GetNewSize(_size);//容量扩大
		//		HashTable<K,V,GetK> tmp;
		//		tmp._tables.resize(newSize);
		//		vector<K> v;
		//		Node* del = NULL;

		//		//把所有元素放进vector中
		//		for(size_t i = 0; i < _size; ++i)
		//		{
		//			//找到有存储元素的链
		//			if(_tables[i] != NULL)
		//			{
		//				Node* cur = _tables[i];
		//				while(cur)
		//				{
		//				    //cur = _tables[i];
		//					v.push_back(cur->_key);
		//					cur = cur->_next;
		//				}

		//				//清理空间
		//				cur = _tables[i];
		//				while(cur)
		//				{
		//					del = cur;
		//					cur = cur->_next;
		//					delete del;
		//				}
		//			}
		//			else
		//				continue;
		//		}
		//		//将vector中的所有元素重新插入
		//		for(size_t i = 0 ; i < v.size(); ++i)
		//		{
		//			tmp.Insert(v[i],0);
		//			//v.pop_back();
		//		}
		//		//已经移动完成
		//		this->_Swap(tmp);
		//	}
		//}


		//直接将原来表中的结点连接到新的表中
		void _CheckCapacity()
		{
			if (_size == _tables.size())
			{
				int newSize = _GetNewSize(_size);//容量扩大
				HashTable<K, V, GetK> tmp;
				tmp._tables.resize(newSize);
				for (size_t i = 0; i < _size; ++i)
				{
					Node* cur = _tables[i];
					Node* next = NULL;
					while (cur)
					{
						next = cur->_next;
						//获得该节点在新的表中的下标
						int index = _GetIndex(cur->_key, newSize);

						//将对应的结点插入到新的表中
						//头插法
						//两种情况，可以一起处理 
						cur->_next = tmp._tables[index];
						tmp._tables[index] = cur;

						cur = next;
					}
					_tables[i] = NULL;//这里必须置空，不要让两个空间同时指向一块内存
				}
				_Swap(tmp);
			}
		}

		int _GetNewSize(int num)
		{
			const int _PrimeSize = 28;
			static const unsigned long _PrimeList[_PrimeSize] = {
				53ul, 97ul, 193ul, 389ul, 769ul,
				1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
				49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
				1572869ul, 3145739ul, 6291469ul, 12582917ul,
				25165843ul, 50331653ul, 100663319ul, 201326611ul, 402653189ul,
				805306457ul, 1610612741ul, 3221225473ul, 4294967291ul
			};
			for (int i = 0; i < _PrimeSize; ++i)
			{
				if (_PrimeList[i] > num)
					return _PrimeList[i];
			}
		}

		void _Swap(HashTable<K, V, GetK>& ht)
		{
			//std::swap(ht._tables,_tables);
			_tables.swap(ht._tables);
			swap(ht._size, _size);
		}

	protected:
		vector<Node* > _tables;
		size_t _size;
	};
}
void TestHashTableLink()
{
	Link::HashTable<int, int>  ht1;
	int array1[] = { 89, 21, 8, 58, 53, 12, 3, 4, 9, 0 };
	for (int i = 0; i < sizeof(array1) / sizeof(array1[0]); ++i)
	{
		ht1.Insert(array1[i], 0);
	}
	ht1.Print();
	ht1.Remove(4);
	ht1.Remove(12);
	ht1.Print();


	Link::HashTable<string,int> ht2;
	char* array2[] = {"hello","yang","hello","sort","wang","zip","huffman"};
	for(int i = 0; i < sizeof(array2)/sizeof(array2[0]); ++i)
	{
	Link::KVNode<string,int>* ret = ht2.Find(array2[i]);
	if(!ret)
	ht2.Insert(array2[i],0);
	}
	ht2.Remove("hello");
	ht2.Remove("sort");

	ht2.Print();
}