#include "main_cfg.h"

void main_binary_search_tree(void)
{
	struct tree_family_s *
		tree = NULL;

	printf("\r\n ------------------------+ binary search tree demo start +------------------------ \r\n");

	printf("binary_search_tree.init start\r\n");
	binary_search_tree_control_configuration_init(&tree, sizeof(void *), NULL, NULL);

	printf("\r\nb_tree.insert start\r\n");
	for (size_t cnt = '1'; cnt <= '0' + 20; cnt += 2) {
		size_t count = cnt - '0';
		printf("\r\nb_tree.insert start: %c-%d \r\n", cnt, count);
		tree_family_control_insert(tree, (void *)&cnt);
		printf("\r\nb_tree.insert end: %c-%d \r\n", cnt, count);
	}

	tree_family_control_inorder_traversal(tree, tree->root, tree_family_control_traversal_printer);

	for (size_t cnt = '2'; cnt <= '0' + 20; cnt += 2) {
		size_t count = cnt - '0';
		printf("\r\nb_tree.insert start: %c-%d \r\n", cnt, count);
		tree_family_control_insert(tree, (void *)&cnt);
		printf("\r\nb_tree.insert end: %c-%d \r\n", cnt, count);
	}

	tree_family_control_inorder_traversal(tree, tree->root, tree_family_control_traversal_printer);

	printf("\r\nbinary_search_tree.delete start\r\n");
	#define BINARY_SEARCH_TREE_DELETE_CASE								3
	size_t key_pool[BINARY_SEARCH_TREE_DELETE_CASE] = { '1','3','D' };

	for (size_t cnt = 0; cnt < BINARY_SEARCH_TREE_DELETE_CASE; cnt++) {
		printf("\r\nbinary_search_tree.delete \"%s\"-%d start\r\n", (char *)&key_pool[cnt], key_pool[cnt] - '0');

		struct tree_family_search_node_return_s search = tree_family_control_search(tree, (void *)&key_pool[cnt]);
		printf("\r\nsearch:\"%c\" location:%d node:%p nod_prev:%p \r\n", (char)key_pool[cnt], search.location, search.node, search.node_prev);

		tree_family_control_delete(tree, (void *)&key_pool[cnt]);
		tree_family_control_inorder_traversal(tree, tree->root, tree_family_control_traversal_printer);

		printf("\r\nbinary_search_tree.delete \"%s\"-%d end\r\n", (char *)&key_pool[cnt], key_pool[cnt] - '0');
	}

	printf("\r\nb_tree.insert start\r\n");
	for (size_t cnt = 0; cnt < BINARY_SEARCH_TREE_DELETE_CASE; cnt++) {
		size_t count = cnt - '0';
		printf("\r\nb_tree.insert start: %c-%d \r\n", key_pool[cnt], count);
		tree_family_control_insert(tree, (void *)&key_pool[cnt]);
		printf("\r\nb_tree.insert end: %c-%d \r\n", cnt, count);
	}

	tree_family_control_inorder_traversal(tree, tree->root, tree_family_control_traversal_printer);

	printf("\r\nbinary_search_tree.destroy start\r\n");
	tree_family_control_configuration_destroy(&tree);

	printf("\r\n ------------------------+ binary search tree demo end +------------------------\r\n");

	return;
}