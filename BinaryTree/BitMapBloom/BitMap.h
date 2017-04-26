#pragma once
#include<iostream>
using namespace std;
#include<vector>
class BitMap
{
public:
	BitMap(size_t range)
	{
		_tables.resize((range >> 5)+1);
	}

	void Set(size_t num)
	{
		//确定num在第几个数
		int index = num >> 5;
		//确定num在 index的哪一位
		int pos = num % 32;
		//置位
		_tables[index] |= (1 << pos);
	}

	void ReSet(size_t num)
	{
		int index = num >> 5;
		int pos = num % 32;

		_tables[index] &= (~(1 << pos));
	}

	bool Test(size_t num)
	{
		int index = num >> 5;
		int pos = num % 32;
		return _tables[index] & (1 << pos);
	}

protected:
	vector<size_t> _tables;
};

void TestBitMap()
{
	BitMap bm(-1);
	bm.Set(100);
	bm.Set(200);
	bm.Set(468);

	cout << "100:"<<bm.Test(100)<<endl;
	cout << "200:"<<bm.Test(200)<<endl;
	cout << "800:"<<bm.Test(800)<<endl;
	cout << "468:"<<bm.Test(468)<<endl;

	bm.ReSet(100);
	

	cout << "100:"<<bm.Test(100)<<endl;
	cout << "200:"<<bm.Test(200)<<endl;
	cout << "800:"<<bm.Test(800)<<endl;
	cout << "468:"<<bm.Test(468)<<endl;
}