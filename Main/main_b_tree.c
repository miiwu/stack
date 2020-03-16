#include "main_cfg.h"

void main_b_tree(void)
{
	tree_family_stp 
		tree_family = NULL;

	struct b_tree_data {
		size_t key;
		char string[10];
	} data = { '1',"B-Tree" };

	printf("\r\n ------------------------+ two three tree_family demo start +------------------------ \r\n");

	printf("\r\nb_tree.init start\r\n");
	b_tree_control_configuration_init(&tree_family, 4, 4, sizeof(data), NULL, NULL);

	printf("\r\nb_tree.insert start\r\n");
	for (; data.key < '0' + 30; data.key++) {
		size_t count = data.key - '0';
		printf("\r\nb_tree.insert start: %c-%d \r\n", data.key, count);
		tree_family_control_insert(tree_family, &data);
		data.string[0]++;
		printf("\r\nb_tree.insert end: %c-%d \r\n", data.key, count);
	}

	printf("\r\nb_tree.search start\r\n");
	size_t key = '1';
	struct tree_family_search_node_return_s search = tree_family_control_search(tree_family, (void *)&key);
	printf("search:\"%c\" location:%d content:\"%s\" node:%p nod_prev:%p \r\n", (char)key, search.location, (char *)search.content, search.node, search.node_prev);

	printf("\r\nb_tree.in-order traversal start\r\n");
	tree_family_control_inorder_traversal(tree_family, tree_family_control_get_root(tree_family), tree_family_control_traversal_printer);

	printf("\r\nb_tree.precursor and successor check start\r\n");
	for (size_t key = '1'; key < '0' + 30; key++) {
		size_t count = key - '0';
		struct tree_family_search_node_return_s search = tree_family_control_search(tree_family, (void *)&key);
		printf("search:\"%c\" location:%d node:%p nod_prev:%p \r\n", (char)key, search.location, search.node, search.node_prev);

		tree_family_control_get_precursor(tree_family, search.node, search.location);
		tree_family_control_get_successor(tree_family, search.node, search.location);
	}

	printf("\r\nb_tree.delete start\r\n");
	#define B_TREE_DELETE_CASE								5
	size_t key_pool[B_TREE_DELETE_CASE] = { 'M','I','E','8','6' };

	for (size_t cnt = 0; cnt < B_TREE_DELETE_CASE; cnt++) {
		printf("\r\nb_tree.delete \"%s\"-%d start\r\n", (char *)&key_pool[cnt], key_pool[cnt] - '0');

		struct tree_family_search_node_return_s search = tree_family_control_search(tree_family, (void *)&key_pool[cnt]);
		printf("\r\nsearch:\"%c\" location:%d node:%p nod_prev:%p \r\n", (char)key_pool[cnt], search.location, search.node, search.node_prev);

		tree_family_control_delete(tree_family, (void *)&key_pool[cnt]);
		tree_family_control_inorder_traversal(tree_family, tree_family_control_get_root(tree_family), tree_family_control_traversal_printer);

		printf("\r\nb_tree.delete \"%s\"-%d end\r\n", (char *)&key_pool[cnt], key_pool[cnt] - '0');
	}

	printf("\r\nb_tree.destroy start\r\n");
	tree_family_control_configuration_destroy(&tree_family);

	printf("\r\n ------------------------+ two three tree_family demo end +------------------------\r\n");

	return;
}