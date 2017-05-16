/*************************************************************************
	> File Name: Search.cpp
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Tue 16 May 2017 02:07:28 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>

#include "BinarySearch.h"
using namespace std;

int main()
{
    int a[] = {1,2,3,4,5,6,7,8,9};
    vector<int> vec(a,a+9);
    Search<int> sea_vec;
    cout<<sea_vec.BinarySearch_div(vec,3)<<endl;//index从0开始
    cout<<sea_vec.BinarySearch_nor(vec,4)<<endl;
    cout<<sea_vec.BinarySearch_div(vec,0)<<endl;//index从0开始
    cout<<sea_vec.BinarySearch_nor(vec,10)<<endl;
    return 0;
}
