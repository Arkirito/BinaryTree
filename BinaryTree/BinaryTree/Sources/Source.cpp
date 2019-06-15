#include <iostream>
#include <BinarySearchTree.h>

int main(int argc, char** argv)
{
	BinarySearchTree<int> tree(10);

	tree.Insert(5);
	tree.Insert(2);
	tree.Insert(15);
	tree.Insert(-1);

	tree.Remove(10);
	tree.Remove(-1);
	tree.Remove(2);

	tree.Insert(20);
	tree.Insert(-6);

	tree.Remove(101);
	tree.Remove(-6);

	tree.Insert(11);
	tree.Insert(12);
	tree.Insert(13);
	tree.Insert(-50);

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