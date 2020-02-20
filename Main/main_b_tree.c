#include "main_cfg.h"

void main_b_tree(void)
{
	struct tree_family_s *
		tree = NULL;

	printf("\r\n ------------------------+ two three tree demo start +------------------------ \r\n");

	printf("\r\nb_tree.init start\r\n");
	b_tree_control_configuration_init(&tree, 4, sizeof(int), NULL, NULL);

	printf("\r\nb_tree.insert start\r\n");
	for (size_t cnt = '1'; cnt < '0' + 30; cnt++) {
		size_t count = cnt - '0';
		printf("\r\nb_tree.insert start: %c-%d \r\n", cnt, count);
		tree_family_control_insert(tree, (void *)&cnt);
		printf("\r\nb_tree.insert end: %c-%d \r\n", cnt, count);
	}

	printf("\r\nb_tree.in-order traversal start\r\n");
	tree_family_control_inorder_traversal(tree, tree->root, tree_family_control_traversal_printer);

	printf("\r\nb_tree.search start\r\n");
	size_t key = 'A';
	struct tree_family_search_node_return_s search = tree_family_control_search(tree, (void *)&key);
	printf("search:\"%c\" location:%d node:%p nod_prev:%p \r\n", (char)key, search.location, search.node, search.node_prev);

	printf("\r\nb_tree.precursor and successor check start\r\n");
	for (size_t key = '1'; key < '0' + 30; key++) {
		size_t count = key - '0';
		struct tree_family_search_node_return_s search = tree_family_control_search(tree, (void *)&key);
		printf("search:\"%c\" location:%d node:%p nod_prev:%p \r\n", (char)key, search.location, search.node, search.node_prev);

		tree_family_control_get_precursor(tree, search.node, search.location);
		tree_family_control_get_successor(tree, search.node, search.location);
	}

	printf("\r\nb_tree.delete start\r\n");
	#define B_TREE_DELETE_CASE								5
	size_t key_pool[B_TREE_DELETE_CASE] = { 'M','I','E','8','6' };

	for (size_t cnt = 0; cnt < B_TREE_DELETE_CASE; cnt++) {
		printf("\r\nb_tree.delete \"%s\"-%d start\r\n", (char *)&key_pool[cnt], key_pool[cnt] - '0');

		struct tree_family_search_node_return_s search = tree_family_control_search(tree, (void *)&key_pool[cnt]);
		printf("\r\nsearch:\"%c\" location:%d node:%p nod_prev:%p \r\n", (char)key_pool[cnt], search.location, search.node, search.node_prev);

		tree_family_control_delete(tree, (void *)&key_pool[cnt]);
		tree_family_control_inorder_traversal(tree, tree->root, tree_family_control_traversal_printer);

		printf("\r\nb_tree.delete \"%s\"-%d end\r\n", (char *)&key_pool[cnt], key_pool[cnt] - '0');
	}

	printf("\r\nb_tree.destroy start\r\n");
	tree_family_control_configuration_destroy(&tree);

	printf("\r\n ------------------------+ two three tree demo end +------------------------\r\n");

	return;
}