#include "main_cfg.h"

void main_binary_search_tree(void)
{
	struct tree_family_s *
		tree = NULL;

	printf("\r\n ------------------------+ binary search tree demo start +------------------------ \r\n");

	printf("binary_search_tree.init start\r\n");
	binary_search_tree_control_configuration_init(&tree, sizeof(void *), NULL, NULL);

	printf("\r\nb_tree.insert start\r\n");
	for (size_t cnt = '1'; cnt <= '0' + 10; cnt++) {
		size_t count = cnt - '0';
		printf("\r\nb_tree.insert start: %c-%d \r\n", cnt, count);
		tree_family_control_insert(tree, (void *)&cnt);
		printf("\r\nb_tree.insert end: %c-%d \r\n", cnt, count);
	}

	printf("\r\nbinary_search_tree.destroy start\r\n");
	tree_family_control_configuration_destroy(&tree);

	printf("\r\n ------------------------+ binary search tree demo end +------------------------\r\n");

	return;
}