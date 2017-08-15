#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
template <typename T>
struct TreeNode {
	T val;
	TreeNode* left, *right;
	int height;
	TreeNode(const T& _val):val(_val), left(nullptr), right(nullptr),height(1) {}
};
template <typename T>
class  AVL
{
public:
	AVL()
	{
		root = nullptr;
	}
	void insert(const T& data) 
	{
	  this->root = 	_insert(data, this->root);
	}
	
private:
	TreeNode<T>* singleL(TreeNode<T>* node)
	{
		auto newRoot = node->right;
		node->right = newRoot->left;
		newRoot->left = node;
		node->height = max(GetHeight(node->left), GetHeight(node->right)) + 1;
		newRoot->height = max(GetHeight(newRoot->left), GetHeight(newRoot->right)) + 1;
		return newRoot;
	}
	TreeNode<T>* singleR(TreeNode<T>* node)
	{
		auto newRoot = node->left;
		node->left = newRoot->right;
		newRoot->right = node;
		node->height = max(GetHeight(node->left), GetHeight(node->right)) + 1;
		newRoot->height = max(GetHeight(newRoot->left), GetHeight(newRoot->right)) + 1;
		return newRoot;
	}
	TreeNode<T>* doubleRL(TreeNode<T>* node)
	{
		node->right = singleR(node->right);
		return singleL(node);
	}
	TreeNode<T>* doubleLR(TreeNode<T>* node)
	{
		node->left = singleL(node->left);
		return singleR(node);
	}
	TreeNode<T> *root;
	TreeNode<T>* _insert(const T&data, TreeNode<T>* node)
	{
		if (node == nullptr)
		{
			node = new TreeNode<T>(data);

			return node;
		}
		if (node->val == data)
		{
			return node;
		}
		else if (node->val < data)
		{
			node->right = _insert(data, node->right);
			int lHeight = GetHeight(node->left);
			int rHeight = GetHeight(node->right);
			if (rHeight - lHeight > 1)
			{
				if (data > node->right->val)
				{
					node = singleL(node);
				}
				else
				{
					node = doubleRL(node);
				}
			}
		}
		else {
			node->left = _insert(data, node->left);
			int lHeight = GetHeight(node->left);
			int rHeight = GetHeight(node->right);
			if (lHeight - rHeight > 1)
			{
				if (data < node->left->val)
				{
					node = singleR(node);
				}
				else
				{
					node = doubleLR(node);
				}
			}
		}
		node->height = max(GetHeight(node->left), GetHeight(node->right)) + 1;
		return node;
	}
	int GetHeight(TreeNode<T> * node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		return node->height;
	}
};

