#include "main_cfg.h"

void main_two_three_tree(void)
{
	TWO_THREE_TREE_TYPEDEF_PTR
		tree = NULL;

	printf("\r\n ------------------------+ two three tree demo start +------------------------ \r\n");

	printf("\r\ntwo_three_tree.init start\r\n");
	two_three_tree_control_configuration_init(&tree,sizeof(int),NULL,NULL);

	printf("\r\ntwo_three_tree.insert start\r\n");
	
	for (size_t cnt = 1; cnt <= 10; cnt++) {
		two_three_tree_control_insert_node(tree, cnt);
	}

	printf("\r\ntwo_three_tree.search start\r\n");
	struct two_three_tree_search_node_return_s search = two_three_tree_control_search_node(tree, 5);
	printf("loc:%d node:%p nod_prev:%p \r\n", search.location, search.node, search.node_prev);

	printf("\r\ntwo_three_tree.destroy start\r\n");

	printf("\r\n ------------------------+ two three tree demo end +------------------------\r\n");

	return;
}