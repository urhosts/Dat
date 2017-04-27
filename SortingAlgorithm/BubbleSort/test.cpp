#include "BubbleSort.h"

int main()
{
	int a[10] = { 9, 1, 5, 8, 3, 7, 4, 6, 2 };
	int n = sizeof(a) / sizeof(a[0]);
	BubbleSort_C(a, n);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}