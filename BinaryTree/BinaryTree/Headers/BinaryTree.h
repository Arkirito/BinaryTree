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

	int GetNodesCount();

	void SwitchNodes(BinaryTreeNode<T>*node, BinaryTreeNode<T>* child);

	int Height = 0;

	bool IsLeaf();

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

	int GetHeight();

	BinaryTreeNode<T>* FindDeepestLeaf();
	BinaryTreeNode<T>* FindDeepestLeft(BinaryTreeNode<T>* fromNode);

protected:

	BinaryTreeNode<T>* m_root = nullptr;

	int m_size = 0;

	void _traversal(BinaryTreeNode<T>* node, std::vector<BinaryTreeNode<T>*>& out);
	virtual BinaryTreeNode<T>* _find(BinaryTreeNode<T>* node, T value);
	void _backpropagateHeight(BinaryTreeNode<T>* node);
	void _findDeepestLeaf(BinaryTreeNode<T>* current, BinaryTreeNode<T>*& leaf, int depth, int& maxDepth);
	virtual void _remove(T value);
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

	_remove(value);
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
int BinaryTree<T>::GetHeight()
{
	return m_root == nullptr ? 0 : m_root->Height;
}

template<typename T>
void BinaryTreeNode<T>::SwitchNodes(BinaryTreeNode<T>* node, BinaryTreeNode<T>* child)
{
	if (node == Left)
	{
		Left = child;
	}
	else if (node == Right)
	{
		Right = child;
	}
	else
	{
		return;
	}

	if (child != nullptr)
	{
		child->Parent = this;
	}
}

template<typename T>
inline bool BinaryTreeNode<T>::IsLeaf()
{
	return Nodes[0] == nullptr && Nodes[1] == nullptr;
}

template<typename T>
 BinaryTreeNode<T>* BinaryTree<T>::FindDeepestLeaf()
{
	BinaryTreeNode<T>* leaf = m_root;
	int maxDepth = 0;
	_findDeepestLeaf(m_root, leaf, 0, maxDepth);
	return leaf;
}

 template<typename T>
 inline BinaryTreeNode<T>* BinaryTree<T>::FindDeepestLeft(BinaryTreeNode<T>* fromNode)
 {
	 BinaryTreeNode<T>* out = fromNode;

	 while (out->Left != nullptr)
	 {
		 out = out->Left;
	 }

	 return out;
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
			BinaryTreeNode<T>* out = _find(node->Left, value);
			if (out != nullptr) return out;
		}

		if (node->Right != nullptr)
		{
			BinaryTreeNode<T>* out = _find(node->Right, value);
			if (out != nullptr) return out;
		}
	}

	return nullptr;
}

template<typename T>
 void BinaryTree<T>::_backpropagateHeight(BinaryTreeNode<T>* node)
{
	BinaryTreeNode<T>* parent = node->Parent;

	while (parent)
	{
		++parent->Height;
		parent = parent->Parent;
	}
}

template<typename T>
void BinaryTree<T>::_findDeepestLeaf(BinaryTreeNode<T>* node, BinaryTreeNode<T>*& leaf, int depth, int& maxDepth)
{
	if (node != nullptr)
	{
		if (node->Left != nullptr)
		{
			_findDeepestLeaf(node->Left, leaf, ++depth, maxDepth);
		}

		if (node->Right != nullptr)
		{
			_findDeepestLeaf(node->Right, leaf, ++depth, maxDepth);
		}

		if (node->Left == nullptr && node->Right == nullptr)
		{
			if (depth > maxDepth)
			{
				maxDepth = depth;
				leaf = node;
			}
		}
	}
}

template<typename T>
inline void BinaryTree<T>::_remove(T value)
{
	BinaryTreeNode<T>* node = Find(value);

	if (node != nullptr)
	{
		if (node->IsLeaf())
		{
			if (node->Parent != nullptr)
			{
				node->Parent->SwitchNodes(node, nullptr);
			}
			else
			{
				m_root = nullptr;
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
				m_root = child;
			}

			delete node;
		}
		else
		{
			// just replace with some leaf

			BinaryTreeNode<T>* leaf = FindDeepestLeaf();

			if (leaf->Parent != nullptr)
			{
				leaf->Parent->SwitchNodes(leaf, nullptr);
			}

			if (node->Parent != nullptr)
			{
				node->Parent->SwitchNodes(node, leaf);
				leaf->Parent = node->Parent;
			}
			else
			{
				m_root = leaf;
				leaf->Parent = nullptr;
			}

			if (node->Left != nullptr) node->Left->Parent = leaf;
			if (node->Right != nullptr)	node->Right->Parent = leaf;


			leaf->Left = node->Left;
			leaf->Right = node->Right;

			delete node;
		}
	}
}

template<typename T>
 int BinaryTreeNode<T>::GetNodesCount()
{
	int count = 0;

	if (Left != nullptr) ++count;
	if (Right != nullptr) ++count;

	return count;
}
