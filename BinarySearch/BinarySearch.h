/*************************************************************************
	> File Name: BinarySearch.h
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Tue 16 May 2017 09:40:58 AM CST
 ************************************************************************/

//#pragma once

#ifndef _BINARYSEARCH_H
#define _BINARYSEARCH_H
#include <vector>
using namespace std;

template<typename T>
class Search
{
public:
    int BinarySearch_div(vector<T> A, T value);
    int BinarySearch_nor(vector<T> A, T value);
private:
    int Sub_BinarySearch(vector<T> A, int Begin, int End, T value);
};

template<typename T>
int Search<T>::BinarySearch_div(vector<T> A, T value)
{
    return Sub_BinarySearch(A, 0, A.size()-1, value);
}

template<typename T>
int Search<T>::Sub_BinarySearch(vector<T> A, int Begin, int End, T value)
{
    if(Begin > End)
        return - 1;
    int mid = Begin + (End - Begin)/2;
    if(A[mid] > value)
    {
        return Sub_BinarySearch(A, Begin, mid - 1, value);
    }
    else if(A[mid] < value)
    {
        return Sub_BinarySearch(A, mid + 1, End ,value);
    }
    else
        return mid;
}

template<typename T>
int Search<T>::BinarySearch_nor(vector<T> A, T value)
{
    int Begin = 0, End = A.size() - 1;
    while(Begin <= End)
    {
        int mid = Begin + (End - Begin)/2;
        if(A[mid] == value)
            return mid;
        else if(A[mid] > value)
            End = mid - 1;
        else
            Begin = mid + 1;
    }
    return - 1;
}

#endif
