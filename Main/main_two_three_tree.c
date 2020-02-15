#include "main_cfg.h"

void main_two_three_tree(void)
{
	B_TREE_TYPEDEF_PTR
		tree = NULL;

	printf("\r\n ------------------------+ two three tree demo start +------------------------ \r\n");

	printf("\r\ntwo_three_tree.init start\r\n");
	b_tree_control_configuration_init(&tree, 3, sizeof(int), NULL, NULL);

	printf("\r\ntwo_three_tree.insert start\r\n");

	for (size_t cnt = '1'; cnt <= '0' + 10; cnt++) {
		size_t count = cnt - '0';
		printf("\r\ntwo_three_tree.insert start: %c-%d \r\n", cnt, count);
		two_three_tree_control_insert(tree, (void *)&cnt);
		printf("\r\ntwo_three_tree.insert end: %c-%d \r\n", cnt, count);
	}

	printf("\r\ntwo_three_tree.in-order traversal start\r\n");
	tree_family_control_inorder_traversal(tree, tree->root, tree_family_control_traversal_printer);

	printf("\r\ntwo_three_tree.precursor and successor check start\r\n");
	for (size_t key = '1'; key <= ':'; key++) {
		size_t count = key - '0';
		struct tree_family_search_node_return_s search = two_three_tree_control_search(tree, (void *)&key);
		printf("search:\"%c\" loc:%d node:%p nod_prev:%p \r\n", (char)key, search.location, search.node, search.node_prev);

		tree_family_control_get_precursor(tree, search.node, search.location);
		tree_family_control_get_successor(tree, search.node, search.location);
	}

	printf("\r\ntwo_three_tree.search start\r\n");
	size_t key = '7';
	struct tree_family_search_node_return_s search = two_three_tree_control_search(tree, (void *)&key);
	printf("loc:%d node:%p nod_prev:%p \r\n", search.location, search.node, search.node_prev);

	printf("\r\ntwo_three_tree.delete start\r\n");
	tree_family_control_delete(tree, (void *)&key);

	printf("\r\ntwo_three_tree.in-order traversal start\r\n");
	tree_family_control_inorder_traversal(tree, tree->root, tree_family_control_traversal_printer);

	printf("\r\ntwo_three_tree.delete start\r\n");
	key = '5';
	tree_family_control_delete(tree, (void *)&key);

	printf("\r\ntwo_three_tree.in-order traversal start\r\n");
	tree_family_control_inorder_traversal(tree, tree->root, tree_family_control_traversal_printer);

	printf("\r\ntwo_three_tree.destroy start\r\n");
	tree_family_control_configuration_destroy(&tree);

	printf("\r\n ------------------------+ two three tree demo end +------------------------\r\n");

	return;
}