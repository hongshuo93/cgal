#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
template <class T >
struct vertex2D
{
	T x;
	T y;
	vertex2D(T _x, T _y) :x(_x), y(_y) {}
};
template <class T >
bool operator<(const vertex2D<T>& v1, const vertex2D<T>& v2)
{
	
	if (v1.y < v2.y)
	{
		return true;
	}
	if (v1.x < v2.x)
	{
		return true;
	}
	return false;
}
template <class T >
bool ToLeftTest(const vertex2D<T>& v1, const vertex2D<T>& v2)
{
	return (v1.x*v2.y - v1.y*v2.x) > 0;
}
template <class T>
void Sort(vertex2D<T> point)
{

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
	auto i = input.begin();
	

}

int main()
{
	return 0;
}