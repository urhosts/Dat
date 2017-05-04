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
//	//�ҵ������е����Ԫ�غ���СԪ��  
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
//	//����range���count����  
//	int* count = new int[range];
//	memset(count, 0, sizeof(int)* range);
//
//	//дcount����  
//	for (int i = 0; i < n; ++i)
//	{
//		count[a[i] - min]++;
//	}
//
//	//��count���飬��дa����  
//	int index = 0;
//	for (int i = 0; i < range; ++i)
//	{
//		while (count[i]--)
//		{
//			a[index++] = i + min;
//		}
//	}
//}

