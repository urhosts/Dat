#include "InsertSort.h"

int main()
{
	int a[] = { 2, 4, 1, 5, 9, 7, 5, 8, 4 };
	int n = (sizeof(a) / sizeof(a[0]));
	InsertSort(a, n);
	for (size_t i = 0; i < n; i++)
	{
		cout <<" "<< a[i];
	}
	cout << endl;
	system("pause");
	return 0;
}