#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <time.h>
#include <string>
#include "convexHull.h"

#include "AVL.h"
using namespace std;
const int INPUT_SIZE = 2000;


void qsort(int begin, int end, vector<int>& data)
{
	if (begin >= end)
	{
		return;
	}
	int left = begin;
	int right = end-1;
	auto current = data[left];
	while (left<right)
	{
		while (current < data[right]&&left<right)
		{
			right--;
		}
		data[left] = data[right];
		left++;
		while (data[left]<=current&&left<right)
		{
			left++;
		}
		data[right] = data[left];
		right--;
	}
	
	data[left] = current;
	qsort(begin, left, data);
	qsort(left + 1, end, data);
}
int main()
{
	AVL<int> tree;
	for (int i = 0; i < 1000; i++)
	{
		tree.insert(rand() % 2000);
	}
	system("pause");
	string s = "123 123";
	return 0;
}