#pragma once
#include"BitMap.hpp"
#include<string>

template <typename K>
struct __HashFunc1
{
	size_t BKDRHash(const char* str)
	{
		register size_t hash = 0;
		size_t ch = 0;
		while(ch = (size_t)*str++)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}
	size_t operator()(const  string& key)
	{
		return BKDRHash(key.c_str());
	}
};
template<typename K>
struct __HashFunc2
{
	size_t SDBMHash(const char* str)
	{
		register size_t hash = 0;
		size_t ch = 0;
		while(ch = (size_t)*str++)
		{
			hash = hash * 65599 + ch;
		}
		return hash;
	}
	size_t operator()(const  string& key)
	{
		return SDBMHash(key.c_str());
	}
};
template<typename K>
struct __HashFunc3
{
	size_t RSHash(const char* str)
	{
		register size_t hash = 0;
		size_t magic = 63689;
		size_t ch = 0;
		while(ch = (size_t)*str++)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
	size_t operator()(const  string& key)
	{
		return RSHash(key.c_str());
	}
};
template<typename K>
struct __HashFunc4
{
	size_t RSHash(const char* str)
	{
		register size_t hash = 0;
		size_t magic = 63689;
		size_t ch = 0;
		for(long i = 0; ch = (size_t)*str ++; ++i)
		{
			if((i & 1) == 0)
				hash ^= ((hash << 7) ^ ch ^(hash >> 3));
			else
				hash ^= ((hash << 11) ^ ch ^(hash >> 5));
		}
		return hash;
	}
	size_t operator()(const  string& key)
	{
		return RSHash(key.c_str());
	}
};
template<typename K>
struct __HashFunc5
{
	size_t RSHash(const char* str)
	{
		if(!*str)
			return 0;
		register size_t hash = 1315423911;
		size_t magic = 63689;
		size_t ch = 0;
		while(ch = (size_t)*str++)
		{
			hash ^= ((hash << 5) + ch + (hash >> 2));
		}
		return hash;
	}
	size_t operator()(const  string& key)
	{
		return RSHash(key.c_str());
	}
};
template<typename K = string
,typename HashFunc1 = __HashFunc1<K>
,typename HashFunc2 = __HashFunc2<K>
,typename HashFunc3 = __HashFunc3<K>
,typename HashFunc4 = __HashFunc4<K>
,typename HashFunc5 = __HashFunc5<K> >
class BloomFilter
{
public:
	BloomFilter(size_t num)
		:_bitMap(num * 5)
		,_range(num * 5)
	{}

	void Set(const K& key)
	{
		size_t hash1 = HashFunc1()(key) % _range;
		size_t hash2 = HashFunc2()(key) % _range;
		size_t hash3 = HashFunc3()(key) % _range;
		size_t hash4 = HashFunc4()(key) % _range;
		size_t hash5 = HashFunc5()(key) % _range;

		_bitMap.Set(hash1);
		cout << hash1 <<endl;
		_bitMap.Set(hash2);
		cout << hash2 <<endl;
		_bitMap.Set(hash3);
		cout << hash3 <<endl;
		_bitMap.Set(hash4);
		cout << hash4 <<endl;
		_bitMap.Set(hash5);
		cout << hash5 <<endl;
	}

	bool Test(const K& key)
	{
		size_t hash1 = HashFunc1()(key) % _range;
		if(_bitMap.Test(hash1) == 0)
			return false;
		size_t hash2 = HashFunc2()(key) % _range;
		if(_bitMap.Test(hash2) == 0)
			return false;
		size_t hash3 = HashFunc3()(key) % _range;
		if(_bitMap.Test(hash3) == 0)
			return false;
		size_t hash4 = HashFunc4()(key) % _range;
		if(_bitMap.Test(hash4) == 0)
			return false;
		size_t hash5 = HashFunc5()(key) % _range;
		if(_bitMap.Test(hash5) == 0)
			return false;

		return true;
	}
private:
	BitMap _bitMap;
	size_t _range;
};

void TestBloomFilter()
{
	BloomFilter<> bf(5);
	bf.Set("_bitMap.Test(hash2) == 0");
	cout << endl;
	bf.Set("_bitMap.Test(hash3) == 0");
	cout << endl;
	bf.Set("_bitMap.Test(hash4) == 0");
	cout << endl;
	cout<<bf.Test("_bitMap.Test(hash2) == 0")<<endl;
	cout<<bf.Test("ÑîÍ¬Ñ§")<<endl;
	cout<<bf.Test("_bitMap.Test(hash4) == 0")<<endl;
}