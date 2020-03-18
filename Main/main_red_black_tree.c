#include "main_cfg.h"

void main_red_black_tree(void)
{
	tree_family_stp tree_family = NULL;

	printf("\r\n ------------------------+ red black tree_family demo start +------------------------ \r\n");

	printf("red_black_tree.init start\r\n");
	red_black_tree_control_configuration_init(&tree_family, sizeof(size_t), NULL, NULL);

	printf("\r\nred_black_tree.insert start\r\n");
	size_t cnt = 0;
	for (cnt = '0' + 10; cnt <= '0' + 20; cnt++) {
		size_t count = cnt - '0';
		printf("\r\nb_tree.insert start: %c-%d \r\n", cnt, count);
		tree_family_control_insert(tree_family, (void *)&cnt);
		printf("\r\n");
		printf("\r\nb_tree.insert end: %c-%d \r\n", cnt, count);
	}
	for (cnt = '0' + 1; cnt <= '0' + 9; cnt++) {
		size_t count = cnt - '0';
		printf("\r\nb_tree.insert start: %c-%d \r\n", cnt, count);
		tree_family_control_insert(tree_family, (void *)&cnt);
		printf("\r\n");
		printf("\r\nb_tree.insert end: %c-%d \r\n", cnt, count);
	}

	printf("\r\n");
	tree_family_control_inorder_traversal(tree_family, tree_family_control_get_root(tree_family), tree_family_control_traversal_printer);

	printf("\r\nred_black_tree.delete start\r\n");
	#define RED_BLACK_TREE_DELETE_CASE								6
	size_t key_pool[RED_BLACK_TREE_DELETE_CASE] = {
		'9',																					/* TAG:
																									Node is left child of parent,
																									RED-node + BLACK-node-child/nil */
		'>',																					/* TAG:
																									Node is left child of parent,
																									BLACK-node + BLACK-both-node-child/nil +
																									RED-brother */
		'1',																					/* TAG:
																									Node is left child of parent,
																									BLACK-node + BLACK-both-node-child/nil +
																									BLACK-brother + BLACK-both-brother-child/nil */
		'@','?',																				/* TAG:
																									Node is left child of parent,
																									BLACK-node + BLACK-both-node-child/nil +
																									BLACK-brother + ANY-brother-left-child/nil + RED-brother-right-child/nil */
		'D',																					/* TAG:
																									Node is right child of parent,
																									BLACK-node + BLACK-both-node-child/nil +
																									BLACK-brother + BLACK-brother-left-child/nil + RED-brother-right-child/nil */
	};

	for (size_t cnt = 0; cnt < RED_BLACK_TREE_DELETE_CASE; cnt++) {
		printf("\r\nred_black_tree.delete \"%s\"-%d start\r\n", (char *)&key_pool[cnt], key_pool[cnt] - '0');

		struct tree_family_search_node_return_s search = tree_family_control_search(tree_family, (void *)&key_pool[cnt]);
		printf("\r\nsearch:\"%c\" location:%d node:%p nod_prev:%p \r\n", (char)key_pool[cnt], search.location, search.node, search.node_prev);

		tree_family_control_delete(tree_family, (void *)&key_pool[cnt]);
		tree_family_control_inorder_traversal(tree_family, tree_family_control_get_root(tree_family), tree_family_control_traversal_printer);

		printf("\r\nred_black_tree.delete \"%s\"-%d end\r\n", (char *)&key_pool[cnt], key_pool[cnt] - '0');
	}

	printf("\r\n");
	tree_family_control_inorder_traversal(tree_family, tree_family_control_get_root(tree_family), tree_family_control_traversal_printer);

	printf("\r\nred_black_tree.destroy start\r\n");
	tree_family_control_configuration_destroy(&tree_family);

	printf("\r\n ------------------------+ red black tree_family demo end +------------------------\r\n");

	return;
}