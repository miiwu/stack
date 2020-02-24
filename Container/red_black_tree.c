/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "red_black_tree.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/

/**
 * @brief This enum is the red black tree color enums.
 */

enum red_black_tree_color_e {
	RED_BLACK_TREE_COLOR_NONE,

	RED_BLACK_TREE_COLOR_RED = 'R',

	RED_BLACK_TREE_COLOR_BLACK = 'B'
};

/**
 * @brief This type is the red black tree's rotate function typedef.
 */

typedef void (*red_black_tree_node_control_rotate_t) (struct tree_family_s *tree,
													  struct tree_family_chain_node_s *node);

/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will switch the tree-family control.
 *
 * @param void
 *
 * @return void
 */

void red_black_tree_control_switch_control(struct tree_family_s *tree);

/**
 * @brief This function will  control the tree_family_control_search()'s match rule.
 *
 * @param void
 *
 * @return void
 */

container_size_t
red_black_tree_control_search_match_rule(struct tree_family_s *tree,
										 struct tree_family_chain_node_s *node,
										 void *data);

/**
 * @brief This function will control the tree_family_control_search()'s recursion rule.
 *
 * @param void
 *
 * @return void
 */

container_size_t
red_black_tree_control_search_recursion_rule(struct tree_family_s *tree,
											 struct tree_family_chain_node_s **node,
											 void *data);

/**
 * @brief This function will control tree_family_control_insert()'s insert.
 *
 * @param void
 *
 * @return void
 */

void *red_black_tree_control_insert_rule(struct tree_family_s *tree,
										 struct tree_family_search_node_return_s search_return,
										 void *data);

/**
 * @brief This function will control tree_family_control_delete()'s delete.
 *
 * @param void
 *
 * @return void
 */

void *red_black_tree_control_delete_rule(struct tree_family_s *tree,
										 struct tree_family_chain_node_s *node,
										 void *data);

/**
 * @brief This function will rotate the node to be the left child.
 *
 * @param void
 *
 * @return void
 */

void red_black_tree_control_insert_fix_rule(struct tree_family_s *tree,
											struct tree_family_chain_node_s *node,
											struct tree_family_chain_node_s *parent);

/**
 * @brief This function will paint the node with the color.
 *
 * @param void
 *
 * @return void
 */

void red_black_tree_node_control_paint_color(struct tree_family_s *tree,
											 struct tree_family_chain_node_s *node,
											 enum red_black_tree_color_e color);

/**
 * @brief This function will extract the color of the node.
 *
 * @param void
 *
 * @return void
 */

enum red_black_tree_color_e
	red_black_tree_node_control_extract_color(struct tree_family_s *tree,
											  struct tree_family_chain_node_s *node);

/**
 * @brief This function will rotate the node to be the left child.
 *
 * @param void
 *
 * @return void
 */

void red_black_tree_node_control_left_rotate(struct tree_family_s *tree,
											 struct tree_family_chain_node_s *node);

/**
 * @brief This function will rotate the node to be the right child.
 *
 * @param void
 *
 * @return void
 */

void red_black_tree_node_control_right_rotate(struct tree_family_s *tree,
											  struct tree_family_chain_node_s *node);

/**
 * @brief This function will rotate the node according the rule.
 *
 * @param void
 *
 * @return void
 */

void red_black_tree_node_control_rotate_core(struct tree_family_s *tree,
											 struct tree_family_chain_node_s *node,
											 container_size_t id_rule[2]);

/*
*********************************************************************************************************
*					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
*********************************************************************************************************
*/

/**
 * @brief This struct will record the red-black tree's environment.
 */

struct tree_family_control_environment_s red_black_tree_control_environment = {
	TREE_FAMILY_RED_BLACK_TREE,
	{
		red_black_tree_control_search_match_rule,
		red_black_tree_control_search_recursion_rule,
		red_black_tree_control_insert_rule,
		red_black_tree_control_delete_rule
	}
};

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the tree struct
 *
 * @param tree the pointer to the tree struct pointer
 * @param element_size the element memory size of the tree struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void red_black_tree_control_configuration_init(RED_BLACK_TREE_TYPEDEF_PPTR tree,
											   container_size_t element_size,
											   void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(tree);
	assert(0 <= element_size);

	tree_family_control_configuration_init(tree, red_black_tree_control_switch_control,
										   2, TREE_FAMILY_RED_BLACK_TREE,
										   RED_BLACK_TREE_CFG_ALLOCATOR_TYPE,
										   element_size + sizeof(enum red_black_tree_color_e),
										   assign, free);
}

/**
 * @brief This function will analysis the shared pack.
 *
 * @param void
 *
 * @return void
 */

void red_black_tree_control_switch_control(struct tree_family_s *tree)
{
	tree_family_control_get_control(red_black_tree_control_environment);
}

/**
 * @brief This function will  control the tree_family_control_search()'s match rule.
 *
 * @param void
 *
 * @return void
 */

container_size_t
red_black_tree_control_search_match_rule(struct tree_family_s *tree,
										 struct tree_family_chain_node_s *node,
										 void *data)
{
	assert(tree);
	assert(node);
	assert(data);

	return binary_search_tree_control_node_operator.search_match_rule(tree, node, data);
}

/**
 * @brief This function will control the tree_family_control_search()'s recursion rule.
 *
 * @param void
 *
 * @return void
 */

container_size_t
red_black_tree_control_search_recursion_rule(struct tree_family_s *tree,
											 struct tree_family_chain_node_s **node,
											 void *data)
{
	assert(tree);
	assert(node);
	assert(data);
	assert(*node);

	return binary_search_tree_control_node_operator.search_recursion_rule(tree, node, data);
}

/**
 * @brief This function will control tree_family_control_insert()'s insert.
 *
 * @param void
 *
 * @return void
 */

void *red_black_tree_control_insert_rule(struct tree_family_s *tree,
										 struct tree_family_search_node_return_s search_return,
										 void *data)
{
	assert(tree);
	assert(data);

	struct tree_family_chain_node_s
		*node = binary_search_tree_control_node_operator.insert_rule(tree, search_return, data),
		*parent = *((void **)node->link + LINK_OPERATOR_CODE_PARENT);

	if (NULL == parent) {                                                                   /* Paint the root to black color */
		red_black_tree_node_control_paint_color(tree, tree->root, RED_BLACK_TREE_COLOR_BLACK);

		goto EXIT;
	}

	red_black_tree_node_control_paint_color(tree, node, RED_BLACK_TREE_COLOR_RED);          /* Paint the new node that insert just now to red color */

	if (RED_BLACK_TREE_COLOR_RED == red_black_tree_node_control_extract_color(tree, parent)) {
		red_black_tree_control_insert_fix_rule(tree, node, parent);
	}

EXIT:

	#if (RED_BLACK_TREE_CFG_DEBUG_EN)

	tree_family_control_inorder_traversal(tree, tree->root, tree_family_control_traversal_printer);

	#endif // (RED_BLACK_TREE_CFG_DEBUG_EN)

	return node;
}

/**
 * @brief This function will control tree_family_control_delete()'s delete.
 *
 * @param void
 *
 * @return void
 */

void *red_black_tree_control_delete_rule(struct tree_family_s *tree,
										 struct tree_family_chain_node_s *node,
										 void *data)
{
	assert(tree);
	assert(node);

	return NULL;
}

/**
 * @brief This function will rotate the node to be the left child.
 *
 * @param void
 *
 * @return void
 */

static inline void
red_black_tree_control_insert_fix_rule(struct tree_family_s *tree,
									   struct tree_family_chain_node_s *node,
									   struct tree_family_chain_node_s *parent)
{
	assert(tree);
	assert(node);

	struct tree_family_chain_node_s
		*grand_parent = *((void **)parent->link + LINK_OPERATOR_CODE_PARENT),
		*uncle = NULL;

	red_black_tree_node_control_rotate_t red_black_tree_node_control_rotate[2] = { NULL };
	bool left_side = false;

	while (NULL != parent &&
		(NULL != grand_parent ||
		 NULL != (grand_parent = *((void **)parent->link + LINK_OPERATOR_CODE_PARENT))) &&
		   RED_BLACK_TREE_COLOR_RED == red_black_tree_node_control_extract_color(tree, parent)) {
		#if (RED_BLACK_TREE_CFG_DEBUG_EN)

		tree_family_control_inorder_traversal(tree, tree->root, tree_family_control_traversal_printer);
		printf("red_black_tree_control.insert.fix_rule:node:%p parent:%p \r\n", node, parent);
		printf("red_black_tree_control.insert.fix_rule:%s parent \r\n",
			(tree_family_node_control_get_if_left_child(tree, parent, grand_parent)) ? "left" : "right");

		#endif // (RED_BLACK_TREE_CFG_DEBUG_EN)

		if (left_side = tree_family_node_control_get_if_left_child(tree, parent, grand_parent)) {			/* If parent is the left child */
			red_black_tree_node_control_rotate[0] = &red_black_tree_node_control_left_rotate;
			red_black_tree_node_control_rotate[1] = &red_black_tree_node_control_right_rotate;
		} else {
			red_black_tree_node_control_rotate[0] = &red_black_tree_node_control_right_rotate;
			red_black_tree_node_control_rotate[1] = &red_black_tree_node_control_left_rotate;
		}

		uncle = *((void **)grand_parent->link + left_side + 1);

		switch (red_black_tree_node_control_extract_color(tree, uncle)) {
			case RED_BLACK_TREE_COLOR_RED:
				#if (RED_BLACK_TREE_CFG_DEBUG_EN)

				printf("red_black_tree_control.insert.fix_rule:red uncle \r\n");

				#endif // (RED_BLACK_TREE_CFG_DEBUG_EN)

				red_black_tree_node_control_paint_color(tree, grand_parent, RED_BLACK_TREE_COLOR_RED);
				red_black_tree_node_control_paint_color(tree, parent, RED_BLACK_TREE_COLOR_BLACK);
				red_black_tree_node_control_paint_color(tree, uncle, RED_BLACK_TREE_COLOR_BLACK);

				node = grand_parent;
				parent = *((void **)node->link + LINK_OPERATOR_CODE_PARENT);
				grand_parent = NULL;																		/* Refresh the grandparent */
				break;
			case RED_BLACK_TREE_COLOR_BLACK:
				#if (RED_BLACK_TREE_CFG_DEBUG_EN)

				printf("red_black_tree_control.insert.fix_rule:black uncle \r\n");

				#endif // (RED_BLACK_TREE_CFG_DEBUG_EN)

				if (left_side != tree_family_node_control_get_if_left_child(tree, node, parent)) {			/* If node is the left child */
					#if (RED_BLACK_TREE_CFG_DEBUG_EN)

					printf("red_black_tree_control.insert.fix_rule:%s child \r\n",
						(left_side) ? "right" : "left");

					#endif // (RED_BLACK_TREE_CFG_DEBUG_EN)

					ALGORITHM_SWAP((size_t)node, (size_t)parent);

					red_black_tree_node_control_rotate[0](tree, node);
				}

				red_black_tree_node_control_paint_color(tree, grand_parent, RED_BLACK_TREE_COLOR_RED);
				red_black_tree_node_control_paint_color(tree, parent, RED_BLACK_TREE_COLOR_BLACK);

				red_black_tree_node_control_rotate[1](tree, grand_parent);
				break;
			default:
				break;
		}
	}

	red_black_tree_node_control_paint_color(tree, tree->root, RED_BLACK_TREE_COLOR_BLACK);
}

/**
 * @brief This function will paint the node with the color.
 *
 * @param void
 *
 * @return void
 */

static inline void
red_black_tree_node_control_paint_color(struct tree_family_s *tree,
										struct tree_family_chain_node_s *node,
										enum red_black_tree_color_e color)
{
	assert(tree);

	if (NULL == node) {
		return;
	}

	enum red_black_tree_color_e
		*color_operator = (enum red_black_tree_color_e *)((size_t)(*((void **)node->data)) +
														  tree->info.mem_size_key);

	*color_operator = color;
}

/**
 * @brief This function will extract the color of the node.
 *
 * @param void
 *
 * @return void
 */

static inline enum red_black_tree_color_e
red_black_tree_node_control_extract_color(struct tree_family_s *tree,
										  struct tree_family_chain_node_s *node)
{
	assert(tree);

	if (NULL == node) {
		return RED_BLACK_TREE_COLOR_BLACK;
	}

	enum red_black_tree_color_e
		*color_operator = (enum red_black_tree_color_e *)((size_t)(*((void **)node->data)) +
														  tree->info.mem_size_key);

	return *color_operator;
}

/**
 * @brief This function will rotate the node to be the left child.
 *
 * @param void
 *
 * @return void
 */

void red_black_tree_node_control_left_rotate(struct tree_family_s *tree,
											 struct tree_family_chain_node_s *node)
{
	assert(tree);
	assert(node);

	#if (RED_BLACK_TREE_CFG_DEBUG_EN)

	printf("red_black_tree_node_control.left rotate:%p \r\n", node);

	#endif // (RED_BLACK_TREE_CFG_DEBUG_EN)

	container_size_t id_rule[2] = { 2,1 };

	red_black_tree_node_control_rotate_core(tree, node, id_rule);
}

/**
 * @brief This function will rotate the node to be the right child.
 *
 * @param void
 *
 * @return void
 */

void red_black_tree_node_control_right_rotate(struct tree_family_s *tree,
											  struct tree_family_chain_node_s *node)
{
	assert(tree);
	assert(node);

	#if (RED_BLACK_TREE_CFG_DEBUG_EN)

	printf("red_black_tree_node_control.right rotate:%p \r\n", node);

	#endif // (RED_BLACK_TREE_CFG_DEBUG_EN)

	container_size_t id_rule[2] = { 1,2 };

	red_black_tree_node_control_rotate_core(tree, node, id_rule);
}

/**
 * @brief This function will rotate the node according the rule.
 *
 * @param void
 *
 * @return void
 */

static inline void
red_black_tree_node_control_rotate_core(struct tree_family_s *tree,
										struct tree_family_chain_node_s *node,
										container_size_t id_rule[2])
{
	assert(tree);
	assert(node);

	struct tree_family_chain_node_s
		*father = *((void **)node->link + LINK_OPERATOR_CODE_PARENT),
		*child = *((void **)node->link + id_rule[0]);

	#if (RED_BLACK_TREE_CFG_DEBUG_EN)

	printf("red_black_tree_node_control.rotate core:node:%p child:%p \r\n",
		   node, child);

	#endif // (RED_BLACK_TREE_CFG_DEBUG_EN)

	if (NULL == child) {
		goto FAIL;
	}

	*((void **)child->link + LINK_OPERATOR_CODE_PARENT) = father;		/* Link child as father's child */

	if (NULL == father) {
		tree->root = child;
	} else if (*((void **)father->link + 1) == node) {
		*((void **)father->link + 1) = child;
	} else if (*((void **)father->link + 2) == node) {
		*((void **)father->link + 2) = child;
	}

	struct tree_family_chain_node_s
		*temp = *((void **)child->link + id_rule[1]);

	*((void **)node->link + id_rule[0]) = temp;
	if (NULL != temp) {
		*((void **)temp->link + LINK_OPERATOR_CODE_PARENT) = node;
	}

	*((void **)child->link + id_rule[1]) = node;
	*((void **)node->link + LINK_OPERATOR_CODE_PARENT) = child;

FAIL:
	return;
}