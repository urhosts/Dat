#pragma once
#include<iostream>
using namespace std;

template<typename T>
class SymmetricMatrix
{
public:
	SymmetricMatrix(T* matrix,int size)
		:_matrix(new T[size*(size + 1) / 2])
		,_size(size)
		,_n(size*(size+1)/2)
	{
		int index = 0;
		for (size_t i = 0; i < _size; ++i)
		{
			for (size_t j = 0; j < _size; ++j)
			{
				if (i >= j)
				{
					_matrix[index] = matrix[i * size + j];
					index++;
				}
				else
				{
					continue;
				}
			}
		}
	}
	~SymmetricMatrix()
	{
		if (_matrix)
		{
			delete[] _matrix;
		}
	}

	T& Access(size_t i, size_t j)
	{
		if (i < j)
		{
			std::swap(i,j);
		}
		return _matrix[i*(i + 1) /2 + j];
	}

	void Display()
	{
		for (size_t i = 0; i < _size; ++i)
		{
			for (size_t j = 0; j < _size; ++j)
			{
				cout << Access(i,j) << " ";
			}
			cout << endl;
		}
	}
private:
	T* _matrix;
	size_t _size;
	size_t _n;
};

void TestSymmetricMatrix()
{
	int a[5][5] = {
		{0,1,2,3,4},
		{1,0,1,2,3},
		{2,1,0,1,2},
		{3,2,1,0,1},
		{4,3,2,1,0}
	};
	SymmetricMatrix<int> sm((int*)a,5);
	sm.Display();
}