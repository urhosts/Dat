#include "MergeSort.h"


int main()
{
	int a[] = { 5, 1, 9, 3, 7, 4, 8, 6, 2 };
	int begin = 0;
	int end = 8;
	MergeSort(a, begin, end);
	for (size_t i = 0; i <= 8; i++)
	{
		cout << a[i]<<" ";
	}
	cout << endl;
	system("pause");
	return 0;
}