#pragma once
#include <Common.h>
#include "BinaryTree.h"

template<typename T>
class BinarySearchTree : public BinaryTree<T>
{
	COMMON_CLASS_DEFINITION(BinarySearchTree, BinaryTree)

public:

	BinarySearchTree();
	virtual ~BinarySearchTree();
	BinarySearchTree(T value);

	virtual void Insert(T value);
	virtual void Remove(T value);

protected:

	void _insert(BinaryTreeNode<T>* node, T value);
	virtual BinaryTreeNode<T>* _find(BinaryTreeNode<T>* node, T value);
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree()
{

}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(T value)
{
	this->m_root = new BinaryTreeNode<T>(value);
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{

}

template<typename T>
void BinarySearchTree<T>::Insert(T value)
{
	Super::Insert(value);

	_insert(this->m_root, value);
}

template<typename T>
void BinarySearchTree<T>::Remove(T value)
{
	Super::Remove(value);

	// TODO
}

template<typename T>
void BinarySearchTree<T>::_insert(BinaryTreeNode<T> * node, T value)
{
	if (node == nullptr)
	{
		node = new BinaryTreeNode<T>(value);
		
		if (this->m_root == nullptr)
		{
			this->m_root = node;
		}
	}
	else
	{
		if (value == node->Value) return;

		if (value > node->Value)
		{
			if (node->Right == nullptr)
			{
				node->Right = new BinaryTreeNode<T>(value);
				node->Right->Parent = node;
			}
			else
			{
				_insert(node->Right, value);
			}
		}
		else if (value < node->Value)
		{
			if (node->Left == nullptr)
			{
				node->Left = new BinaryTreeNode<T>(value);
				node->Left->Parent = node;
			}
			else
			{
				_insert(node->Left, value);
			}
		}
	}
}

template<typename T>
inline BinaryTreeNode<T>* BinarySearchTree<T>::_find(BinaryTreeNode<T>* node, T value)
{
	if (node != nullptr)
	{
		if (node->Value == value)
		{
			return node;
		}
		else if (node->Value > value)
		{
			if (node->Right != nullptr)
			{
				if (node->Right->Value == value) return node->Right;

				_find(node->Right, value);
			}
		}
		else
		{
			if (node->Left != nullptr)
			{
				if (node->Left->Value == value) return node->Left;

				_find(node->Left, value);
			}
		}
	}

	return nullptr;
}
