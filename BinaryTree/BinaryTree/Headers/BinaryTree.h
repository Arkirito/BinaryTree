#pragma once

struct BinaryTreeNode
{
	int Value;

	BinaryTreeNode* Nodes[2];

	BinaryTreeNode* Left() { return Nodes[0]; };
	BinaryTreeNode* Right() { return Nodes[1]; };
};

class BinaryTree
{
public:
	virtual ~BinaryTree();

	void Clear(BinaryTreeNode* fromNode);
	
	// Clear binary tree usage has no sence here, lets leave it as an interface
	virtual void Insert(int value) = 0;
	virtual void Remove(int value) = 0;

protected:

	BinaryTreeNode* m_root;
};

