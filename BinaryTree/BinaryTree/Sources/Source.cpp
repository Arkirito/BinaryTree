#include <iostream>
#include <BinarySearchTree.h>

int main(int argc, char** argv)
{
	BinarySearchTree<int> tree(5);

	tree.Insert(2);
	tree.Insert(10);

	tree.Insert(1);
	tree.Insert(3);
	tree.Insert(7);
	tree.Insert(15);

	tree.Insert(6);
	tree.Insert(8);

	tree.Remove(5);
	tree.Remove(7);

	std::vector<BinaryTreeNode<int>*> traversal;
	tree.Traversal(traversal);

	for (auto node : traversal)
	{
		printf("%d ", node->Value);
	}

	printf("\n Tree Height: %d", tree.GetHeight());

	std::cin.get();
	
	return 0;
}