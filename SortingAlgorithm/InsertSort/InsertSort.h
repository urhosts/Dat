#include <iostream>

using namespace std;

void InsertSort(int *a, int n)
{
	int i = 0;
	int j = 0;
	int tmp = 0;
	for (i = 0; i < n; i++)
	{
		tmp = a[i];
		for (j = i; j>0 && a[j - 1] > tmp; j--)
		{
			a[j] = a[j - 1];
		}
		a[j] = tmp;
	}
}
