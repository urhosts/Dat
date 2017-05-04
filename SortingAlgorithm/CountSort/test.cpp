#include "CountSort.h"

int main()
{
	int a[] = { 2, 4, 5, 1, 7, 6, 9, 3, 8 };
	int n = 8;
	CountSort(a, n);
	for (size_t i = 0; i <= n; i++)
	{
		cout << " ";
		cout << a[i];
	}
	cout << endl;
	system("pause");
	return 0;
}