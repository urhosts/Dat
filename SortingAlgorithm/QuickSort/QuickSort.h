#include <iostream>
#include <stack>
using namespace std;


int GetMidNum(int* a, int begin, int end)
{
	int mid = begin + (end - begin) / 2;
	//找出个数中处于中间位置的数  
	// a[begin] > a[mid]  
	if (a[begin] > a[mid])
	{
		if (a[mid] > a[end])//a[begin] > a[mid] > a[end]  
			return mid;
		//a[begin] > a[mid] < a[end]  
		else if (a[begin] > a[end])//a[begin] > a[end] > a[mid]  
			return end;
		else  //  a[end] > a[begin]> a[mid]  
			return begin;
	}
	//a[mid]> a[begin]  
	else
	{
		if (a[begin] > a[end])//a[mid]> a[begin]> a[end]  
			return begin;
		//a[mid]> a[begin]< a[end]  
		else if (a[mid] > a[end])//a[mid] > a[end]> a[begin]  
			return end;
		else     //a[end] > a[mid] > a[begin]  
			return mid;
	}
}

int PartSort_A(int *a, int begin, int end)
{
	int midNumIndex = GetMidNum(a, begin, end);
	if (end != midNumIndex)
	{
		swap(a[end], a[midNumIndex]);
	}
	int key = a[end];
	int left = begin;
	int right = end - 1;
	while (left < right)
	{
		while (left < right && a[left] <= key)
		{
			++left;
		}
		while (left < right && a[right] >= key)
		{
			--right;
		}
		swap(a[left], a[right]);
	}
	if (a[left] > a[end])
	{
		swap(a[left], a[end]);
	}
	return left;
}

int PartSort_B(int *a, int begin, int end)
{
	int midNumIndex = GetMidNum(a, begin, end);
	if (end != midNumIndex)
	{
		swap(a[end], a[midNumIndex]);
	}
	int key = a[end];
	int left = begin;
	int right = end;
	while (left < right)
	{
		if (left < right && a[left] <= key)
		{
			++left;
		}
		a[right] = a[left];
		if (left < right && a[right] >= key)
		{
			--right;
		}
		a[left] = a[right];
	}
	a[left] = key;
	return left;
}

int PartSort_C(int* a, int begin, int end)
{
	int midNumIndex = GetMidNum(a, begin, end);
	if (end != midNumIndex)
	{
		swap(a[end], a[midNumIndex]);
	}
	int key = a[end];
	int prev = begin - 1;
	int cur = begin;
	while (cur < end)
	{
		if (/*cur < end*/ a[cur] < key && ++prev != cur)
		{
			swap(a[prev], a[cur]);
		}
		++cur;
	}
	swap(a[++prev], a[end]);
	return prev;
}

void QuickSort(int* a, int begin, int end)
{
	if (begin < end)
	{
		int key = PartSort_A(a, begin, end);
		QuickSort(a, begin, key - 1);
		QuickSort(a, key + 1, end);
	}
}

void QuickSortOP(int* a,int begin,int end)  
{  
    //由于递归太深会导致栈溢出，效率低，所以，当区间比较小时采用插入排序。  
    if(end - begin > 13)  
    {  
       int key = PartSort3(a,begin,end);  
       QuickSort(a,begin,key-1);  
       QuickSort(a,key + 1,end);  
    }  
    else  
       InsertSort(a+begin,end-begin + 1);  
} 

void QuickSortNonR(int* a, int begin, int end)
{
	stack<int> s;
	if (begin < end)
	{
		s.push(end);
		s.push(begin);
		while (!s.empty())
		{
			int low = s.top();
			s.pop();
			int high = s.top();
			s.pop();
			int mid = PartSort_A(a, low, high);
			if (low < mid - 1)
			{
				s.push(mid - 1);
				s.push(low);
			}
			if (high > mid + 1)
			{
				s.push(high);
				s.push(mid + 1);
			}
		}
	}
}
