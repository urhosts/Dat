#include <cstdio>
#include <iostream>

using namespace std;

void BubbleSort_A(int *a, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - i; j++)
		{
			if (a[j - 1] > a[j])
			{
				swap(a[j], a[j - 1]);
			}
		}
	}
}

void BubbleSort_B(int *a, int n)
{
	int j, k;
	bool flag;

	k = n;
	flag = true;
	while (flag)
	{
		flag = false;
		for (j = 1; j < k; j++)
		{
			if (a[j - 1]>a[j])
			{
				swap(a[j - 1], a[j]);
				flag = true;
			}
		}
		k--;
	}
}


void BubbleSort_C(int *a, int n)
{
	int j, k;
	int flag;

	flag = n;
	while (flag > 0)
	{
		k = flag;
		flag = 0;
		for (j = 1; j < k; j++)
		{
			if (a[j - 1]>a[j])
			{
				swap(a[j - 1], a[j]);
				flag = j;
			}
		}
	}
}