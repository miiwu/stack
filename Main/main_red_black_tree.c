#include "main_cfg.h"

void main_red_black_tree(void)
{
	struct tree_family_s *tree = NULL;

	printf("\r\n ------------------------+ red black tree demo start +------------------------ \r\n");

	printf("red_black_tree.init start\r\n");
	red_black_tree_control_configuration_init(&tree, sizeof(size_t), NULL, NULL);

	printf("\r\nred_black_tree.insert start\r\n");
	size_t cnt = 0;
	for (cnt = '0' + 10; cnt <= '0' + 20; cnt++) {
		size_t count = cnt - '0';
		printf("\r\nb_tree.insert start: %c-%d \r\n", cnt, count);
		tree_family_control_insert(tree, (void *)&cnt);
		printf("\r\n");
		printf("\r\nb_tree.insert end: %c-%d \r\n", cnt, count);
	}
	for (cnt = '0' + 1; cnt <= '0' + 9; cnt++) {
		size_t count = cnt - '0';
		printf("\r\nb_tree.insert start: %c-%d \r\n", cnt, count);
		tree_family_control_insert(tree, (void *)&cnt);
		printf("\r\n");
		printf("\r\nb_tree.insert end: %c-%d \r\n", cnt, count);
	}

	printf("\r\n");
	tree_family_control_inorder_traversal(tree, tree->root, tree_family_control_traversal_printer);

	printf("\r\nred_black_tree.destroy start\r\n");
	tree_family_control_configuration_destroy(&tree);

	printf("\r\n ------------------------+ red black tree demo end +------------------------\r\n");

	return;
}