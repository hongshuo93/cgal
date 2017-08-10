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
};
template <class T >
bool operator<(const vertex2D<T>& v1, const vertex2D<T>& v2)
{
	
	if (v1.y < v2.y)
	{
		return true;
	}
	if ( abs( v1.y - v2.y)<0.000001)
	{
		if (v1.x < v2.x)
		{
			return true;
		}
	}
	return false;
}
template <class T >
bool ToLeftTest(const vertex2D<T>& v1, const vertex2D<T>& v2)
{
	return (v1.x*v2.y - v1.y*v2.x) >= 0;
}
template <class T>
void Sort(vertex2D<T> point,int begin,int end,vector<vertex2D<T>> &data)
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
		left++;
		while (left < right  &&  ToLeftTest( data[left] - point, current - point))
		{
			left++;
		}
		data[right] = data[left];
		right--;
	}
	data[left] = current;
	Sort<T>(point, begin, left, data);
	Sort<T>(point, left + 1, end, data);
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

	while (!visitStack.empty())
	{
		auto current = visitStack.top();
		visitStack.pop();
		result.push_back(current);
	}
	reverse(result.begin(), result.end());
	return result; 

}

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
	vector<vertex2D<float>>  input;
	for (int i = 0; i < 100; i++)
	{
		float x = rand() % 1280 - 1280/2;
		float y = rand() % 760- 760/2;
		input.push_back(vertex2D<float>(x, y));
	}
	auto result = ConvexHull(input);
	cout << 100 << " " << result.size() << "\n";
	log(input);
	log(result);
	system("pause");

	return 0;
}