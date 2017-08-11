#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
template <class T >
struct vertex2D
{
	T x;
	T y;
	vertex2D(T _x, T _y) :x(_x), y(_y) {}
	vertex2D operator-(const vertex2D & t)
	{
		return vertex2D(this->x - t.x, this->y - t.y);
	}
	bool operator<(const vertex2D<T>& v2)
	{

		if (this->y < v2.y)
		{
			return true;
		}
		if (abs(this->y - v2.y)<0.000001)
		{
			if (this->x < v2.x)
			{
				return true;
			}
		}
		return false;
	}
	bool operator==(const vertex2D<T>& v2) const 
	{
		T x2 = (this->x - v2.x)*(this->x - v2.x);
		T y2 = (this->y - v2.y)*(this->y - v2.y);
		return (x2 + y2) < 0.0001;
	}
};


template <class T >
bool ToLeftTest(const vertex2D<T>& v1, const vertex2D<T>& v2)
{
	return (v1.x*v2.y - v1.y*v2.x) > 0.0001;
}
template <class T>
void Sort(vertex2D<T> point, int begin, int end, vector<vertex2D<T>> &data)
{
	if (begin >= end)
	{
		return;
	}
	int left = begin;
	int right = end - 1;
	auto current = data[begin];
	while (left<right)
	{
		while (left < right &&  ToLeftTest(current - point, data[right] - point))
		{
			right--;
		}
		data[left] = data[right];

		while (left < right  &&  ToLeftTest(data[left] - point, current - point))
		{
			left++;
		}
		data[right] = data[left];
	}
	data[left] = current;
	Sort<T>(point, begin, left, data);
	Sort<T>(point, left + 1, end, data);
}
template <class T>
bool IsInSameLine(vertex2D<T>& v1, vertex2D<T>& v2)
{
	if (abs(v1.x - v2.x) < 0.0001 || abs(v1.y - v2.y) < 0.0001)
	{
		return true;
	}
	if (abs((v1.x / v2.x) - (v1.y / v2.y)) < 0.0001)
	{
		return true;
	}
	return false;
}
template <class T>
void log(const vector<vertex2D<T>>& input)
{
	int size = input.size();
	for (int i = 0; i < size; i++)
	{
		cout << i << " " << input[i].x << " " << input[i].y << "\n";
	}
}
template <class T>
vector<vertex2D<T>> ConvexHull(vector<vertex2D<T>>& input)
{
	int inputSize = input.size();
	if (inputSize <= 3)
	{
		return input;
	}
	int min = 0;
	for (int i = 1; i < inputSize; i++)
	{
		if (input[i] < input[min])
		{
			min = i;
		}
	}
	if (min != 0)
	{
		swap(input[min], input[0]);
	}
	auto i = input[0];
	Sort<T>(i, 1, inputSize, input);

	vector<vertex2D<T>> result;

	stack<vertex2D<T>> visitStack;
	visitStack.push(input[0]);
	visitStack.push(input[1]);
	visitStack.push(input[2]);
	for (int i = 3; i < inputSize; )
	{
		auto p1 = visitStack.top();
		visitStack.pop();
		auto p0 = visitStack.top();
		visitStack.pop();
		auto p2 = input[i];
		if (ToLeftTest(p1 - p0, p2 - p1))
		{
			visitStack.push(p0);
			visitStack.push(p1);
			visitStack.push(p2);
			i++;
		}
		else
		{
			visitStack.push(p0);
		}
	}
	result.push_back(input[0]);
	while (!visitStack.empty())
	{
		auto current = visitStack.top();
		visitStack.pop();
		result.push_back(current);
	}

	reverse(result.begin(), result.end());
	return result;

}

template<class  T>
vector<vertex2D<T>> convexHull2(vector<vertex2D<T>>& input)
{
	int inputSize = input.size();
	if (inputSize <= 3) {
		return input;
	}
	sort(input.begin(), input.end());
	auto it = input.begin() + 1;
	for (; it != input.end();)
	{
		if ((*it) == (*(it - 1)))
		{
			it = input.erase(it);
		}
		else
		{
			it = it + 1;
		}
	}
	inputSize = input.size();
	auto up = input[inputSize - 1];
	auto down = input[0];
	vector<vertex2D<T>> result;
	result.push_back(input[0]);
	result.push_back(input[1]);
	for (int i = 2; i < inputSize; )
	{
		auto current = input[i];
		if (result.size() < 2)
		{
			result.push_back(current);
			i++;
			continue;
		}
		auto p0 = *(result.end() - 2);
		auto p1 = *(result.end() - 1);
		if (ToLeftTest(current - p1, p1 - p0))
		{
			result.push_back(current);
			i++;
		}
		else if(IsInSameLine(current-p1,p1-p0))
		{
			result.pop_back();
			result.push_back(current);
			i++;
		}
		else
		{
			result.pop_back();
		}
	}
	result.push_back(input[inputSize - 2]);
	for (int i = inputSize - 3; i >= 0;)
	{
		auto current = input[i];
		auto p0 = *(result.end() - 2);
		auto p1 = *(result.end() - 1);
		if (ToLeftTest(current - p1, p1 - p0))
		{
			result.push_back(current);
			i--;
		}
		else if (IsInSameLine(current - p1, p1 - p0))
		{
			result.pop_back();
			result.push_back(current);
			i--;
		}
		else
		{
			result.pop_back();
		}
	}

	return result;
}