/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "binary_search_tree.h"

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
 * @brief This struct is the binary search tree chain node link structure module.
 */

struct binary_search_tree_chain_node_link_s {
	void *parent;

	void *lchild;

	void *rchild;
};

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
 * @brief This function will analysis the shared pack.
 *
 * @param void
 *
 * @return void
 */

void binary_search_tree_control_switch_control(void);

/**
 * @brief This function will control the search()'s match rule.
 *
 * @param void
 *
 * @return void
 */

size_t binary_search_tree_control_search_match_rule(struct tree_family_s *tree,
													void *node,
													void *data);

/**
 * @brief This function will control the search()'s recursion rule.
 *
 * @param void
 *
 * @return void
 */

void *binary_search_tree_control_search_recursion_rule(struct tree_family_s *tree,
													   void *node,
													   void *data);

/**
 * @brief This function will control b_tree_control_insert()'s insert.
 *
 * @param void
 *
 * @return void
 */

void binary_search_tree_control_insert_rule(struct tree_family_s *tree,
											struct tree_family_search_node_return_s search_return,
											void *data);

/**
 * @brief This function will control b_tree_control_delete()'s delete.
 *
 * @param void
 *
 * @return void
 */

void binary_search_tree_control_delete_rule(struct tree_family_s *tree,
											struct tree_family_search_node_return_s search_return,
											void *data);

/*
*********************************************************************************************************
*					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
*********************************************************************************************************
*/

/**
 * @brief This struct will record the red-black tree's environment.
 */

struct tree_family_control_environment_s binary_search_tree_control_environment = {
	{
		TREE_FAMILY_RED_BLACK_TREE,
		sizeof(void *) * 1,
		sizeof(void *) * 3,
		1,
		3,
	},
	{
		binary_search_tree_control_search_match_rule,
		binary_search_tree_control_search_recursion_rule,
		binary_search_tree_control_insert_rule,
		binary_search_tree_control_delete_rule
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

void binary_search_tree_control_configuration_init(struct tree_family_s **tree,
												   CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
												   void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(tree);
	assert(0 <= element_size);

	tree_family_control_configuration_init(tree, binary_search_tree_control_switch_control, 2, TREE_FAMILY_RED_BLACK_TREE,
										   BINARY_SEARCH_TREE_CFG_ALLOCATOR_TYPE, element_size, assign, free);
}

/**
 * @brief This function will analysis the shared pack.
 *
 * @param void
 *
 * @return void
 */

void binary_search_tree_control_switch_control(void)
{
	tree_family_control_get_control(binary_search_tree_control_environment);
}

/**
 * @brief This function will control the search()'s match rule.
 *
 * @param void
 *
 * @return void
 */

size_t binary_search_tree_control_search_match_rule(struct tree_family_s *tree,
													void *node,
													void *data)
{
	assert(tree);

	void *data_operator = ((struct tree_family_chain_node_s *)node)->data;

	CONTAINER_GLOBAL_CFG_SIZE_TYPE count = 0;

	for (; count < tree->info.degree - 1; count++) {
		if (NULL != *((void **)data_operator + count) &&
			compare_control_equal(data, *((void **)data_operator + count), tree->info.mem_size)) {
			goto EXIT;
		}
	}

	count = 0xff;

EXIT:

	#if (TWO_THREE_TREE_CFG_DEBUG_EN)

	printf("search.match rule:node:%p Data ",
		   node);

	for (size_t cnt = 0; cnt < tree->info.degree - 1; cnt++) {
		printf("No.%d:\"%s\"-%p ", cnt, (char *)*((void **)data_operator + cnt), *((void **)data_operator + cnt));
	}

	printf("\r\nmatch:%p location:%d\r\n", (0xff != count) ? *((void **)data_operator + count) : NULL, count);

	#endif // (TWO_THREE_TREE_CFG_DEBUG_EN)

	return count;
}

/**
 * @brief This function will control the search()'s recursion rule.
 *
 * @param void
 *
 * @return void
 */

void *binary_search_tree_control_search_recursion_rule(struct tree_family_s *tree,
													   void *node,
													   void *data)
{
	assert(tree);
	void
		*data_operator = ((struct tree_family_chain_node_s *)node)->data,
		*link_operator = ((struct tree_family_chain_node_s *)node)->link;

	size_t count = 1;

	for (; count < tree->info.degree; count++) {
		if ((NULL == *((void **)data_operator + count - 1) ||
			(NULL != *((void **)data_operator + count - 1) &&
			 compare_control_lesser(data, *((void **)data_operator + count - 1), tree->info.mem_size)))) {
			goto EXIT;
		}
	}

	count = tree->info.degree;

EXIT:

	#if (TWO_THREE_TREE_CFG_DEBUG_EN)

	printf("search.recursion rule:node:%p Link ",
		   node);

	for (size_t cnt = 1; cnt <= tree->info.degree; cnt++) {
		printf("No.%d:%p ", cnt, *((void **)link_operator + cnt));
	}

	printf("\r\nrecursion:%p location:%d\r\n", *((void **)link_operator + count), count);

	#endif // (TWO_THREE_TREE_CFG_DEBUG_EN)

	return *((void **)link_operator + count);
}

/**
 * @brief This function will control b_tree_control_insert()'s insert.
 *
 * @param void
 *
 * @return void
 */

void binary_search_tree_control_insert_rule(struct tree_family_s *tree,
											struct tree_family_search_node_return_s search_return,
											void *data)
{
	assert(tree);
	assert(data);

	void 
		*data_operator = search_return.node_prev->data,
		*link_operatpr = search_return.node_prev->link;

	struct tree_family_chain_node_s *node = tree_family_control_init_node(tree);

	memcpy(node->data,data, tree->info.mem_size);
	*((void **)node->link) = search_return.node_prev;

	if (compare_control_greater(data, data_operator,4)) {
		*((void **)link_operatpr + 2) = node;
	} else {

		*((void **)link_operatpr + 1) = node;
	}
}

/**
 * @brief This function will control b_tree_control_delete()'s delete.
 *
 * @param void
 *
 * @return void
 */

void binary_search_tree_control_delete_rule(struct tree_family_s *tree,
											struct tree_family_search_node_return_s search_return,
											void *data)
{
}