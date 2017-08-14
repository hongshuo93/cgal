#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <time.h>
#include "convexHull.h"
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
	vector<vertex2D<double>>  input;
	
	for (int i = 0; i < INPUT_SIZE; i++)
	{
		
		double x = (rand() % 1280)- 1280;
		double y = (rand() % 760)- 760;
		x = x + 0.00001*(rand() % 100000);
		y = y + 0.00001*(rand() % 100000);
		input.push_back(vertex2D<double>(x, y));
	}
	auto result = convexHull2(input);
	cout << INPUT_SIZE << " " << result.size() << "\n";
	log(input);
	log(result);
	

	return 0;
}