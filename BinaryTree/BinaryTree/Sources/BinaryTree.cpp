#include "..\Headers\BinaryTree.h"

BinaryTree::~BinaryTree()
{
	Clear(m_root);
}

void BinaryTree::Clear(BinaryTreeNode* fromNode)
{
	if (fromNode->Left())
	{
		Clear(fromNode->Left());
	}

	if (fromNode->Right())
	{
		Clear(fromNode->Right());
	}

	delete fromNode;
}
