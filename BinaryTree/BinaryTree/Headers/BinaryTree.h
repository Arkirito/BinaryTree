#pragma once
#include <vector>

template<typename T>
struct BinaryTreeNode
{
	T Value;

	BinaryTreeNode(int value) : Value(value) 
	{
		Nodes[0] = nullptr; 
		Nodes[1] = nullptr;
	}

	BinaryTreeNode* Parent = nullptr;
	BinaryTreeNode* Nodes[2];

    #define Left Nodes[0]
    #define Right Nodes[1]

	BinaryTreeNode* PushLeft(int value) { }
};

template<typename T>
class BinaryTree
{
public:
	virtual ~BinaryTree();

	void Clear(BinaryTreeNode<T>* fromNode);
	
	// Clear binary tree usage has no sence here, lets leave it as an interface
	virtual void Insert(T value);
	virtual void Remove(T value);

	virtual BinaryTreeNode<T>* Find(T value);

	void Traversal(std::vector<BinaryTreeNode<T>*>& out);

protected:

	BinaryTreeNode<T>* m_root = nullptr;

	int m_size = 0;

	void _traversal(BinaryTreeNode<T>* node, std::vector<BinaryTreeNode<T>*>& out);
	virtual BinaryTreeNode<T>* _find(BinaryTreeNode<T>* node, T value);
};

template<typename T>
BinaryTree<T>::~BinaryTree()
{
	Clear(m_root);
}

template<typename T>
void BinaryTree<T>::Clear(BinaryTreeNode<T>* fromNode)
{
	if (fromNode->Left)
	{
		Clear(fromNode->Left);
	}

	if (fromNode->Right)
	{
		Clear(fromNode->Right);
	}

	delete fromNode;
}

template<typename T>
void BinaryTree<T>::Insert(T value)
{
	++m_size;
}

template<typename T>
void BinaryTree<T>::Remove(T value)
{
	--m_size;

	// TODO
}

template<typename T>
BinaryTreeNode<T> * BinaryTree<T>::Find(T value)
{
	return _find(m_root, value);
}

template<typename T>
void BinaryTree<T>::Traversal(std::vector<BinaryTreeNode<T>*>& out)
{
	out.reserve(m_size);

	_traversal(m_root, out);
}

template<typename T>
void BinaryTree<T>::_traversal(BinaryTreeNode<T> * node, std::vector<BinaryTreeNode<T>*>& out)
{
	if (node != nullptr)
	{
		if (node->Left != nullptr)
		{
			_traversal(node->Left, out);
		}

		if (node->Right != nullptr)
		{
			_traversal(node->Right, out);
		}

		out.push_back(node);
	}
}

template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::_find(BinaryTreeNode<T>* node, T value)
{
	if (node != nullptr)
	{
		if (node->Value == value) return node;

		if (node->Left != nullptr)
		{
			_find(node->Left, value);
		}

		if (node->Right != nullptr)
		{
			_find(node->Right, value);
		}
	}

	return nullptr;
}
