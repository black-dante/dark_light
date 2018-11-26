#include "diff.cpp"

int main(int argc, char* argv[])
	{
		FILE* read = fopen("read.txt", "r");
		FILE* error = fopen("error_tree.txt", "w");
		
		printf("ok");
		tree_t* tree1 = tree_create("tree1", "x", error);
		tree_t* tree2 = tree_create("tree2", "x", error);
		tree_t* tree3 = tree1;
		printf("ok");
		tree_read(tree1, read);
		printf("ok");
		//tree_print_dot(tree1, tree1->root);
		
		for(int i = 0; i < 10; i++)
		{
		printf("\ni = %d\n", i);
		
		//tree_clear(tree2);
		tree2->root = diff(tree1, tree1->root, tree2);
		//tree1->root = copy(tree2, tree2->root, tree1);
		printf("\ni = %d\n", i);
		//tree_print_dot(tree2, tree2->root);
		tree1 = tree2;
		}
		printf("oklyyyyyyyyl");
		//tree_print_dot(tree3, tree3->root);
		//tree_print_dot(tree2, tree2->root);
		printf("ok");
		tree_print_latex(tree3, tree3->root);
		tree_print_latex(tree2, tree2->root);
		printf("ok");
		
		fclose(read);
	}