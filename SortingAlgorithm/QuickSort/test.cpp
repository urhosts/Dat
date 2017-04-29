#include "QuickSort.h"

int main()
{
	int a[10] = { 3, 4, 7, 5, 1, 2, 9, 0, 6, 8 };
	int begin = 0;
	int end = 9;
	QuickSortNonR(a, begin, end);
	for (size_t i = 0; i <= 9; i++)
	{
		cout << a[i];
		cout << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}
