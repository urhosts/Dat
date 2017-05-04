#include <iostream>
#include <cassert>

using namespace std;

void CountSort(int *a, int n)
{
	assert(a);
	int min = a[0];
	int max = a[0];
	for (size_t i = 1; i <= n; i++)
	{
		if (a[i] < min)
			min = a[i];
		if (a[i]>max)
			max = a[i];
	}
	int range = max - min + 1;
	int *count = new int[range];
	memset(count, 0, sizeof(int)*range);
	//read
	for (size_t i = 0; i < n; i++)
	{
		count[a[i] - min]++;
	}
	//write
	int index = 0;
	for (size_t i = 0; i < range; i++)
	{
		while (count[i]--)
		{
			a[index++] = i + min;
		}
	}
}
//void CountSort(int a[], int n)
//{
//	assert(a);
//	//找到数组中的最大元素和最小元素  
//	int min = a[0];
//	int max = a[0];
//	for (int i = 1; i < n; ++i)
//	{
//		if (a[i] > max)
//			max = a[i];
//		if (a[i] < min)
//			min = a[i];
//	}
//	int range = max - min + 1;
//
//	//开辟range大的count数组  
//	int* count = new int[range];
//	memset(count, 0, sizeof(int)* range);
//
//	//写count数组  
//	for (int i = 0; i < n; ++i)
//	{
//		count[a[i] - min]++;
//	}
//
//	//读count数组，并写a数组  
//	int index = 0;
//	for (int i = 0; i < range; ++i)
//	{
//		while (count[i]--)
//		{
//			a[index++] = i + min;
//		}
//	}
//}

