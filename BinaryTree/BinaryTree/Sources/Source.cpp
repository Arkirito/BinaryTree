#include <iostream>
#include <BinarySearchTree.h>

int main(int argc, char** argv)
{
	BinarySearchTree<int> tree(10);

	tree.Insert(5);
	tree.Insert(2);
	tree.Insert(15);
	tree.Insert(-1);
 
	std::vector<BinaryTreeNode<int>*> traversal;
	tree.Traversal(traversal);

	for (auto node : traversal)
	{
		printf("%d ", node->Value);
	}

	std::cin.get();
	
	return 0;
}