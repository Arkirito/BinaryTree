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
	virtual void _remove(T value) override;
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree()
{

}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(T value)
{
	this->m_root = new BinaryTreeNode<T>(value);
	++this->m_size;
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{

}

template<typename T>
void BinarySearchTree<T>::Insert(T value)
{
	Super::Insert(value);

	BinaryTreeNode<T>* node = Super::Find(value);

	if (node == nullptr)
	{
		_insert(this->m_root, value);
	}
}

template<typename T>
void BinarySearchTree<T>::Remove(T value)
{
	Super::Remove(value);
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
			++this->m_root->Height;
		}
	}
	else
	{
		if (value > node->Value)
		{
			if (node->Right == nullptr)
			{
				node->Right = new BinaryTreeNode<T>(value);
				node->Right->Parent = node;
				Super::_backpropagateHeight(node);
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
				Super::_backpropagateHeight(node);
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
		else if (value > node->Value)
		{
			if (node->Right != nullptr)
			{
				if (node->Right->Value == value) return node->Right;

				return _find(node->Right, value);
			}
		}
		else
		{
			if (node->Left != nullptr)
			{
				if (node->Left->Value == value) return node->Left;

				return _find(node->Left, value);
			}
		}
	}

	return nullptr;
}

template<typename T>
inline void BinarySearchTree<T>::_remove(T value)
{
	BinaryTreeNode<T>* node = Super::Find(value);

	if (node != nullptr)
	{
		if (node->GetNodesCount() == 0)
		{
			if (node->Parent != nullptr)
			{
				node->Parent->SwitchNodes(node, nullptr);
			}
			else
			{
				Super::m_root = nullptr;
			}

			delete node;
		}
		else if (node->GetNodesCount() == 1)
		{
			BinaryTreeNode<T>* child = node->Left != nullptr ? node->Left : node->Right;

			if (node->Parent != nullptr)
			{
				node->Parent->SwitchNodes(node, child);
			}
			else
			{
				Super::m_root = child;
			}

			delete node;
		}
		else
		{
			BinaryTreeNode<T>* left = Super::FindDeepestLeft(node->Right);

			if (left->IsLeaf())
			{
				if (left->Parent != nullptr)
				{
					left->Parent->SwitchNodes(left, nullptr);
				}

				node->Value = left->Value;

				delete left;
			}
			else if (left->GetNodesCount() == 1)
			{
				BinaryTreeNode<T>* child = left->Left != nullptr ? left->Left : left->Right;

				if (left->Parent != nullptr)
				{
					left->Parent->SwitchNodes(left, child);
				}

				node->Value = left->Value;

				delete left;
			}
		}
	}
}
