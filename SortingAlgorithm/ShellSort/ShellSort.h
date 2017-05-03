#include <iostream>

using namespace std;

void ShellSort(vector<int>& v)
{
	if(v.size() == 0 || v.size() == 1)
		return;
	int gap = v.size();
	while(gap > 1)
	{
		gap = gap / 3 + 1;
		for(size_t i = gap; i < v.size(); ++i)
		{
			//进行直接插入排序
			int tmp = v[i];
			int j = i - gap;
			while(j >= 0 && v[j] >= tmp)
			{
				v[j + gap] = v[j];
				j -= gap;
			}

			v[j + gap] = tmp;
		}
	}
}