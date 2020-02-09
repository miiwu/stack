#include "main_cfg.h"

void main_two_three_tree(void)
{
	TWO_THREE_TREE_TYPEDEF_PTR
		tree = NULL;

	printf("\r\n ------------------------+ two three tree demo start +------------------------ \r\n");

	printf("\r\ntwo_three_tree.init start\r\n");
	two_three_tree_control_configuration_init(&tree, sizeof(int), NULL, NULL);

	printf("\r\ntwo_three_tree.insert start\r\n");

	for (size_t cnt = '1'; cnt <= '0' + 10; cnt++) {
		size_t count = cnt - '0';
		printf("\r\ntwo_three_tree.insert start: %c-%d \r\n", cnt, count);
		two_three_tree_control_insert(tree, (void *)&cnt);
		printf("\r\ntwo_three_tree.insert end: %c-%d \r\n", cnt, count);
	}

	printf("\r\ntwo_three_tree.search start\r\n");
	size_t key = 51;
	struct tree_family_search_node_return_s search = two_three_tree_control_search(tree, (void *)&key);
	printf("loc:%d node:%p nod_prev:%p \r\n", search.location, search.node, search.node_prev);

	printf("\r\ntwo_three_tree.pre-order traversal start\r\n");
	tree_family_control_preorder_traversal(tree, tree->root);

	printf("\r\ntwo_three_tree.in-order traversal start\r\n");
	tree_family_control_inorder_traversal(tree, tree->root);

	printf("\r\ntwo_three_tree.postorder traversal start\r\n");
	tree_family_control_posorder_traversal(tree, tree->root);

	printf("\r\ntwo_three_tree.destroy start\r\n");

	printf("\r\n ------------------------+ two three tree demo end +------------------------\r\n");

	return;
}