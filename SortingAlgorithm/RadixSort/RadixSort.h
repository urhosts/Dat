#include<iostream>
#include<vector>

using namespace std;

//��ȡ���λ��
int GetMaxBit(int* arr, int size)
{
	int count = 1;
	int num = 10;

	for(int i = 0; i < size; ++i)
	{
		while(arr[i] >= num)
		{
			count += 1;
			num *= 10;
		}
	}
	return count;
}


//��������
//ʱ�临�ӶȽӽ�O(n),���ǿռ临�ӶȱȽϴ�
//������������÷�Χ��С��ֻ�������޷�������������
void RadixSort(int* arr, const int size)
{
	//����λ��������
	//��ȡ���λ��
	int maxbit = GetMaxBit(arr,size);

	int x = 1;
	while(maxbit--)
	{
		//����ϡ�����Ŀ���ת�������㷨
		int count[10] = {0};   //ͳ�Ƴ��ִ���
		int start[10] = {0};   //��¼��ʼ��λ��

		//ͳ�Ƶ�ǰλ��Ԫ�ظ���
		//��ȡ�࣬��ȡ��
		for(int i = 0; i < size; ++i)
			count[(arr[i]/x)%10]++;

		//����ÿ����Ӧ�÷ŵ�λ�ã�
		start[0] = 0;
		for(int i = 1; i < size; ++i)
			start[i] = start[i-1] + count[i-1];

		//�����ռ�
		int* tmp = new int[size]();
		//int tmp[10] = {0};
		//����start��count������˳�����µ���
		for(int i = 0; i < size; ++i)
		{  
			//if(count[(arr[i]/x)%10])
				tmp[start[(arr[i]/x)%10]++] = arr[i];
		}

		//�����յ�ǰλ�ź�������и���ԭ���飻
		memcpy(arr,tmp,sizeof(int)*size);

		//�´��Ǹ���λ
		x *= 10;

		//�ͷ������tmp
		delete[] tmp;
	}
}
