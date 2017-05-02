#include <iostream>
#include <cassert>

using namespace std;

void _MergeSort(int *a, int begin, int end, int *tmp)
{
	int mid = begin + (end - begin) / 2;
	if (begin < mid)
	{
		_MergeSort(a, begin, mid, tmp);
	}
	if (mid + 1 < end)
	{
		_MergeSort(a, mid + 1, end, tmp);
	}

	int begin1 = begin;
	int end1 = mid;
	int begin2 = mid + 1;
	int end2 = end;
	int index = begin;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] <= a[begin2])
		{
			tmp[index++] = a[begin1++];
		}
		else
		{
			tmp[index++] = a[begin2++];
		}
	}
	while (begin1 <= end1)
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = a[begin2++];
	}
	while (begin <= end)
	{
		a[begin] = tmp[begin++];
	}
}


void _MergeSortOP(int *a,int begin,int end,int* tmp)  
{  
       int mid = ((begin^end) >> 1) + (begin&end);  
       if (begin<mid)  
       {  
              if (mid - begin>13)  
              {  
                     _MergeSort(a, begin, mid, tmp);  
              }  
              else  
              {  
                     InsertSort(a+begin, end - begin + 1);  
              }  
       }  
       if (mid + 1 < end)  
       {  
              if (end - mid - 1 > 13)  
              {  
                     _MergeSort(a,mid+1,end,tmp);  
              }  
              else  
              {  
                     InsertSort(a+mid+1,end-mid);  
              }  
       }  
       int begin1 = begin;  
       int end1 = mid;  
       int begin2 = mid + 1;  
       int end2 = end;  
       int index = begin;  
       while (begin1 <= end1&&begin2 <= end2)  
       {  
              if (a[begin1] < a[begin2])  
                     tmp[index++] = a[begin1++];  
              else  
                     tmp[index++] = a[begin2++];  
       }  
       while (begin1 <= end1)  
              tmp[index++] = a[begin1++];  
       while (begin2 <=end2)  
              tmp[index++] = a[begin2++];  
       while(begin<=end)  
       {  
              a[begin] = tmp[begin++];  
       }  
}  

void MergeSort(int *a, int begin, int end)
{
	assert(a);
	int *tmp = new int[end - begin + 1];
	_MergeSort(a, begin, end, tmp);
	delete[] tmp;
}