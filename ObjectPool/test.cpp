// �����ڴ����صĳ���ʹ�ú��ڴ������ظ�ʹ��
#include<iostream>
#include<vector>
#include<string>
#include"ObjectPool.h"

using namespace std;

//void TestObjectPool()
//{
//	vector<string*> v;
//
//	ObjectPool<string> pool;
//	for (size_t i = 0; i < 32; ++i)
//	{
//		v.push_back(pool.New());
//		printf("Pool New [%d]: %p\n", i, v.back());
//	}
//
//	while (!v.empty())
//	{
//		pool.Delete(v.back());
//		v.pop_back();
//	}
//
//	for (size_t i = 0; i < 32; ++i)
//	{
//		v.push_back(pool.New());
//		printf("Pool New [%d]: %p\n", i, v.back());
//	}
//
//	//v.push_back(pool.New());
//	for (size_t i = 0; i < 4; ++i)
//	{
//		v.push_back(pool.New());
//		printf("Pool New [%d]: %p\n", i, v.back());
//	}
//}



#include <Windows.h>

 //��Ե�ǰ���ڴ����ؽ��м򵥵����ܲ���
void TestObjectPoolOP()
{
	size_t begin , end;
	vector<string*> v;
	const size_t N = 100000;
	v.reserve(N);

	cout<<"pool new/delete==============================="<<endl;
	// ���������ͷ�5��
	begin = GetTickCount();
	ObjectPool<string> pool;
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}


	end = GetTickCount();
	cout<<"Pool:"<<end - begin<<endl;

	cout<<"new/delete==============================="<<endl;
	begin = GetTickCount();

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}

	end = GetTickCount();
	cout<<"new/delete:"<<end - begin<<endl;
}

int main()
{
	//TestObjectPool();
	TestObjectPoolOP();

	system("pause");
	return 0;
}