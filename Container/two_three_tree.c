/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "two_three_tree.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define TWO_THREE_TREE_GET_DATA_FROM_NODE(node,dir)															\
	(((struct two_three_tree_chain_node_data_s *)(((struct tree_family_chain_node_s *)node)->data))->dir)

#define TWO_THREE_TREE_GET_DATA_FROM_FOUR_NODE_NODE(node,dir)															\
	(((struct two_three_tree_chain_node_four_node_data_s *)(((struct tree_family_chain_node_s *)node)->data))->dir)

#define TWO_THREE_TREE_GET_LINK_FROM_NODE(node)															\
	(((struct tree_family_chain_node_s *)node)->link)

#define TWO_THREE_TREE_GET_FAMILY_MEMBER_FROM_NODE(node,dir)											\
	(((struct two_three_tree_chain_node_link_s *)TWO_THREE_TREE_GET_LINK_FROM_NODE(node))->dir)

#define TWO_THREE_TREE_GET_KEY_FROM_FOUR_NODE_DATA(data,dir)													\
	((NULL != (((struct tree_family_chain_node_data_content_s *)(((struct two_three_tree_chain_node_four_node_data_s *)data)->dir)))) ? 						\
	(((struct tree_family_chain_node_data_content_s *)(((struct two_three_tree_chain_node_four_node_data_s *)data)->dir))->key) :								\
	(0u))

#define TWO_THREE_TREE_GET_KEY_FROM_DATA(data)														\
	((NULL != ((struct tree_family_chain_node_data_content_s *)((struct two_three_tree_chain_node_data_s *)data))) ? 						\
	(((struct tree_family_chain_node_data_content_s *)((struct two_three_tree_chain_node_data_s *)data))->key) :								\
	(0u))

#define TWO_THREE_TREE_GET_FAMILY_MEMBER_FROM_LINK(link,dir)											\
	((dir == mlchild || dir == mrchild) ?																\
	(((struct two_three_tree_chain_node_link_s *)link)->dir) :											\
	(((struct two_three_tree_chain_node_four_node_link_s *)link)->dir))

#define TWO_THREE_TREE_GET_KEY_FROM_NODE(node,dir)														\
	TWO_THREE_TREE_GET_KEY_FROM_DATA(TWO_THREE_TREE_GET_DATA_FROM_NODE(node,dir))

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
 * @brief This struct is the binary tree link node structure module.
 */

struct two_three_tree_chain_node_data_s {
	void *left;

	void *right;
};

/**
 * @brief This struct is the binary tree link node structure module.
 */

struct two_three_tree_chain_node_link_s {
	void *parent;

	void *lchild;

	void *mchild;

	void *rchild;
};

/**
 * @brief This struct is the binary tree link node structure module.
 */

struct two_three_tree_chain_node_four_node_data_s {
	void *left;

	void *middle;

	void *right;
};

/**
 * @brief This struct is the binary tree link node structure module.
 */

struct two_three_tree_chain_node_four_node_link_s {
	void *parent;

	void *lchild;

	void *mlchild;

	void *mrchild;

	void *rchild;
};

/**
 * @brief This enum is the two-three tree transform into four-node type node information pack structure module.
 */

struct two_three_tree_transform_into_four_node_pack_s {
	struct tree_family_chain_node_s *node;		/* the four-node inherit from three-node */

	void *data_before_inherit;						/* the data of the previous three-node */
	void *link_before_inherit;						/* the link of the previous three-node */
};

/**
 * @brief This enum is the two-three tree transform into two-node type node information pack structure module.
 */

struct two_three_tree_transform_into_two_node_pack_s {
	void *data;
	struct tree_family_chain_node_s *node;

	void *node_left;
	void *node_right;
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

/* @brief This variable is the two-three tree global four-node data pointer. */

struct two_three_tree_chain_node_four_node_data_s *two_three_tree_control_four_node_data = NULL;

/* @brief This variable is the two-three tree global four-node link pointer. */

struct two_three_tree_chain_node_four_node_link_s *two_three_tree_control_four_node_link = NULL;

/* @brief This variable is the two-three tree global link memory length. */

struct tree_family_node_infomation_s two_three_tree_control_four_node_type_infomation = {
	.data_mem_len = sizeof(struct two_three_tree_chain_node_four_node_data_s),
	.link_mem_len = sizeof(struct two_three_tree_chain_node_four_node_link_s)
};

/*
*********************************************************************************************************
*									LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will switch the tree-family control.
 *
 * @param void
 *
 * @return void
 */

void two_three_tree_control_switch_control(void);

/**
 * @brief This function will delete the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *two_three_tree_control_delete_node(TWO_THREE_TREE_TYPEDEF_PTR tree,
										 void *key);

/**
 * @brief This function will control two_three_tree_control_search()'s match.
 *
 * @param void
 *
 * @return void
 */

size_t two_three_tree_control_search_match_rule(TWO_THREE_TREE_TYPEDEF_PTR tree,
												void *node,
												void *data);

/**
 * @brief This function will control two_three_tree_control_search()'s recursion.
 *
 * @param void
 *
 * @return void
 */

void *two_three_tree_control_search_recursion_rule(TWO_THREE_TREE_TYPEDEF_PTR tree,
												   void *node,
												   void *data);

/**
 * @brief This function will control two_three_tree_control_insert()'s insert.
 *
 * @param void
 *
 * @return void
 */

void two_three_tree_control_insert_rule(struct tree_family_s *tree,
										struct tree_family_search_node_return_s search_return,
										void *data);

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

void two_three_tree_transform_control_four_node_to_two_node_new_child(TWO_THREE_TREE_TYPEDEF_PTR tree, void *node,
																	  struct tree_family_chain_node_s *four_node,
																	  bool left_child);

/**
 * @brief This function will transform the three-node into four-node.
 *
 * @param void
 *
 * @return void
 */

struct two_three_tree_transform_into_four_node_pack_s
	two_three_tree_transform_control_three_node_to_four_node(TWO_THREE_TREE_TYPEDEF_PTR tree,
															 struct two_three_tree_transform_into_two_node_pack_s two_node_pack);

/**
 * @brief This function will transform the four-node into two-node.
 *
 * @param void
 *
 * @return void
 */

struct two_three_tree_transform_into_two_node_pack_s
	two_three_tree_transform_control_four_node_to_two_node(TWO_THREE_TREE_TYPEDEF_PTR tree,
														   struct two_three_tree_transform_into_four_node_pack_s four_node_pack);

/**
 * @brief This function will transform the tree partially.
 *
 * @param void
 *
 * @return void
 */

void two_three_tree_node_control_partial_transformation(TWO_THREE_TREE_TYPEDEF_PTR tree,
														void *node,
														void *data);

/*
*********************************************************************************************************
*					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
*********************************************************************************************************
*/

/**
 * @brief This struct will record the tree's node operators.
 */

struct tree_family_control_environment_s two_three_tree_control_environment = {
	{
		BINARY_TREE_FAMILY_TWO_THREE_TREE,
		sizeof(struct two_three_tree_chain_node_data_s),
		sizeof(struct two_three_tree_chain_node_link_s),
		sizeof(struct two_three_tree_chain_node_data_s) / sizeof(void *),
		sizeof(struct two_three_tree_chain_node_link_s) / sizeof(void *),
	},
	{
		two_three_tree_control_search_match_rule,
		two_three_tree_control_search_recursion_rule,
		two_three_tree_control_insert_rule
	}
};

/**
 * @brief This struct will record the tree's node operators.
 */

struct tree_family_control_environment_s two_three_four_tree_control_environment = {
	{
		BINARY_TREE_FAMILY_TWO_THREE_TREE,
		sizeof(struct two_three_tree_chain_node_four_node_data_s),
		sizeof(struct two_three_tree_chain_node_four_node_link_s),
		sizeof(struct two_three_tree_chain_node_four_node_data_s) / sizeof(void *),
		sizeof(struct two_three_tree_chain_node_four_node_link_s) / sizeof(void *),
	},
	{
		two_three_tree_control_search_match_rule,
		two_three_tree_control_search_recursion_rule
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

void two_three_tree_control_configuration_init(TWO_THREE_TREE_TYPEDEF_PPTR tree,
											   CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
											   void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(tree);
	assert(0 <= element_size);

	tree_family_control_configuration_init(tree, two_three_tree_control_switch_control, BINARY_TREE_FAMILY_TWO_THREE_TREE,
										   TWO_THREE_TREE_CFG_ALLOCATOR_TYPE, element_size, assign, free);

	two_three_tree_control_four_node_data = (*tree)->allocator_ctrl->allocate((*tree)->allocator, 1, sizeof(struct two_three_tree_chain_node_four_node_data_s));
	two_three_tree_control_four_node_link = (*tree)->allocator_ctrl->allocate((*tree)->allocator, 1, sizeof(struct two_three_tree_chain_node_four_node_link_s));

	printf("init.four_node.data:%p link:%p \r\n", two_three_tree_control_four_node_data, two_three_tree_control_four_node_link);
}

/**
 * @brief This function will analysis the shared pack.
 *
 * @param void
 *
 * @return void
 */

void two_three_tree_control_switch_control(void)
{
	tree_family_control_get_control(two_three_tree_control_environment);
}

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

tree_family_search_node_return_st two_three_tree_control_search(TWO_THREE_TREE_TYPEDEF_PTR tree,
																void *data)
{
	assert(tree);

	return tree_family_control_search(tree, data);
}

/**
 * @brief This function will set the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 * @param position the position of node
 *
 * @return NONE
 */

void two_three_tree_control_insert(TWO_THREE_TREE_TYPEDEF_PTR tree,
								   void *data)
{
	assert(tree);

	tree_family_control_insert(tree, data);
}

/**
 * @brief This function will delete the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *two_three_tree_control_delete_node(TWO_THREE_TREE_TYPEDEF_PTR tree,
										 void *data)
{
	assert(tree);
	assert(data);

	struct tree_family_search_node_return_s
		search_return = { 0 };

	printf("\r\n2-3 tree delete start %c-%d \r\n", *(int *)data, *(int *)data);

	search_return = two_three_tree_control_search(tree, data);

	if (TWO_THREE_TREE_SEARCH_LOCATION_NONE != search_return.location) {		/* Can search the node */
	}

	return NULL;
}

/**
 * @brief This function will control two_three_tree_control_search()'s match.
 *
 * @param void
 *
 * @return void
 */

size_t two_three_tree_control_search_match_rule(TWO_THREE_TREE_TYPEDEF_PTR tree,
												void *node,
												void *data)
{
	struct two_three_tree_chain_node_data_s
		*node_data = ((struct tree_family_chain_node_s *)node)->data;

	if (NULL == node_data->left &&
		NULL == node_data->right) {
		goto EXIT;
	}

	#if (TWO_THREE_TREE_CFG_DEBUG_EN)

	printf("search.match rule:node:%p L:%c-%d R:%c-%d \r\n",
		   node,
		   TWO_THREE_TREE_GET_KEY_FROM_NODE(node, left), TWO_THREE_TREE_GET_KEY_FROM_NODE(node, left),
		   TWO_THREE_TREE_GET_KEY_FROM_NODE(node, right), TWO_THREE_TREE_GET_KEY_FROM_NODE(node, right));

	#endif // (TWO_THREE_TREE_CFG_DEBUG_EN)

	if (NULL != node_data->left &&
		compare_control_equal(data, node_data->left, tree->info.mem_size)) {
		return TWO_THREE_TREE_SEARCH_LOCATION_LEFT;
	} else if (NULL != node_data->right &&
			   compare_control_equal(data, node_data->right, tree->info.mem_size)) {
		return TWO_THREE_TREE_SEARCH_LOCATION_RIGHT;
	}

EXIT:

	return TWO_THREE_TREE_SEARCH_LOCATION_NONE;
}

/**
 * @brief This function will control two_three_tree_control_search()'s recursion.
 *
 * @param void
 *
 * @return void
 */

void *two_three_tree_control_search_recursion_rule(TWO_THREE_TREE_TYPEDEF_PTR tree,
												   void *node,
												   void *data)
{
	struct two_three_tree_chain_node_data_s
		*node_data = ((struct tree_family_chain_node_s *)node)->data;

	struct two_three_tree_chain_node_link_s
		*link = ((struct tree_family_chain_node_s *)node)->link;

	if (NULL == node_data->left &&
		NULL == node_data->right) {
		goto EXIT;
	}

	if (NULL != node_data->left) {
		if (compare_control_greater(data, node_data->left, tree->info.mem_size)) {
			return link->rchild;
		} else {
			return link->lchild;
		}
	} else if (NULL != node_data->right) {
		if (compare_control_greater(data, node_data->right, tree->info.mem_size)) {
			return link->rchild;
		} else {
			return link->lchild;
		}
	}

	if (compare_control_lesser(data, node_data->left, tree->info.mem_size) &&
		compare_control_greater(data, node_data->right, tree->info.mem_size)) {
		return link->mchild;
	} else if (compare_control_lesser(data, node_data->right, tree->info.mem_size)) {
		return link->lchild;
	} else if (compare_control_greater(data, node_data->left, tree->info.mem_size)) {
		return link->rchild;
	}

EXIT:
	return NULL;
}

/**
 * @brief This function will control two_three_tree_control_insert()'s insert.
 *
 * @param void
 *
 * @return void
 */

void two_three_tree_control_insert_rule(struct tree_family_s *tree,
										struct tree_family_search_node_return_s search_return,
										void *data)
{
	switch (tree_family_node_control_get_node_type(tree, search_return.node_prev)) {
		case 2:																		/* Two-node type parent */
			tree_family_node_control_set_data(tree, search_return.node_prev, data);
			break;
		case 3:																		/* Three-node type parent */
			two_three_tree_node_control_partial_transformation(tree, search_return.node_prev, data);
			break;
		default:
			break;
	}
}

/**
 * @brief This function will transform the tree partially.
 *
 * @param void
 *
 * @return void
 */

void two_three_tree_node_control_partial_transformation(TWO_THREE_TREE_TYPEDEF_PTR tree,
														void *node,
														void *data)
{
	struct two_three_tree_transform_into_four_node_pack_s four_node_pack = { 0 };

	struct two_three_tree_transform_into_two_node_pack_s two_node_pack = { data,node };

	while (NULL != two_node_pack.data) {
		struct two_three_tree_chain_node_link_s
			*link = ((struct tree_family_chain_node_s *)two_node_pack.node)->link;

		printf("partial transformation:node:%p parent:%p key:%d \r\n", two_node_pack.node, link->parent, TWO_THREE_TREE_GET_KEY_FROM_DATA(two_node_pack.data));

		four_node_pack = two_three_tree_transform_control_three_node_to_four_node(tree, two_node_pack);

		two_node_pack = two_three_tree_transform_control_four_node_to_two_node(tree, four_node_pack);
	}
}

/**
 * @brief This function will transform the three-node into four-node.
 *
 * @param void
 *
 * @return void
 */

struct two_three_tree_transform_into_four_node_pack_s
	two_three_tree_transform_control_three_node_to_four_node(TWO_THREE_TREE_TYPEDEF_PTR tree,
															 struct two_three_tree_transform_into_two_node_pack_s two_node_pack)
{
	struct two_three_tree_chain_node_data_s
		*three_node_data = ((struct tree_family_chain_node_s *)two_node_pack.node)->data;
	struct two_three_tree_chain_node_link_s
		*three_node_link = ((struct tree_family_chain_node_s *)two_node_pack.node)->link;

	two_node_pack.node->data = two_three_tree_control_four_node_data;
	two_node_pack.node->link = two_three_tree_control_four_node_link;

	struct two_three_tree_transform_into_four_node_pack_s
		four_node_pack = {
		.node = two_node_pack.node,					/* the node shell of the origin 3-node */
		.data_before_inherit = three_node_data,		/* the data address of the origin 3-node */
		.link_before_inherit = three_node_link		/* the link address of the origin 3-node */
	};

	printf("transform 3-node into 4-node.3-node:%p DATA.left:%d .right:%d LINK.parent:%p root:%p \r\n",
		   two_node_pack.node,
		   TWO_THREE_TREE_GET_KEY_FROM_DATA(three_node_data->left), TWO_THREE_TREE_GET_KEY_FROM_DATA(three_node_data->right),
		   three_node_link->parent, tree->root);

	two_three_tree_control_four_node_data->left = three_node_data->left;
	two_three_tree_control_four_node_data->middle = three_node_data->right;
	two_three_tree_control_four_node_data->right = NULL;

	tree_family_control_get_control_in_sandbox(tree, two_three_four_tree_control_environment,
											   tree_family_node_control_set_data, 3,
											   tree, four_node_pack.node, (void *)two_node_pack.data);

	two_three_tree_control_four_node_link->parent = three_node_link->parent;

	if (NULL != two_node_pack.node_left &&
		NULL != two_node_pack.node_right) {
		if (compare_control_equal(two_node_pack.data, two_three_tree_control_four_node_data->left, tree->info.mem_size)) {
			two_three_tree_control_four_node_link->lchild = two_node_pack.node_left;
			two_three_tree_control_four_node_link->mlchild = two_node_pack.node_right;
			two_three_tree_control_four_node_link->mrchild = three_node_link->mchild;
			two_three_tree_control_four_node_link->rchild = three_node_link->rchild;
		} else if (compare_control_equal(two_node_pack.data, two_three_tree_control_four_node_data->middle, tree->info.mem_size)) {
			two_three_tree_control_four_node_link->lchild = three_node_link->lchild;
			two_three_tree_control_four_node_link->mlchild = two_node_pack.node_left;
			two_three_tree_control_four_node_link->mrchild = two_node_pack.node_right;
			two_three_tree_control_four_node_link->rchild = three_node_link->rchild;
		} else {
			two_three_tree_control_four_node_link->lchild = three_node_link->lchild;
			two_three_tree_control_four_node_link->mlchild = three_node_link->mchild;
			two_three_tree_control_four_node_link->mrchild = two_node_pack.node_left;
			two_three_tree_control_four_node_link->rchild = two_node_pack.node_right;
		}

		printf("transform 3-node into 4-node.4-node:%p LINK.lchild:%p .mlchild:%p .mrchild:%p .rchild:%p \r\n",
			   four_node_pack.node,
			   two_three_tree_control_four_node_link->lchild, two_three_tree_control_four_node_link->mlchild,
			   two_three_tree_control_four_node_link->mrchild, two_three_tree_control_four_node_link->rchild);
	}

	printf("transform 3-node into 4-node.4-node:%p DATA.left:%d .middle:%d .right:%d LINK.parent:%p \r\n",
		   four_node_pack.node,
		   TWO_THREE_TREE_GET_KEY_FROM_FOUR_NODE_DATA(two_three_tree_control_four_node_data, left),
		   TWO_THREE_TREE_GET_KEY_FROM_FOUR_NODE_DATA(two_three_tree_control_four_node_data, middle),
		   TWO_THREE_TREE_GET_KEY_FROM_FOUR_NODE_DATA(two_three_tree_control_four_node_data, right),
		   two_three_tree_control_four_node_link->parent);

	return four_node_pack;
}

/**
 * @brief This function will transform the four-node into two-node.
 *
 * @param void
 *
 * @return void
 */

struct two_three_tree_transform_into_two_node_pack_s
	two_three_tree_transform_control_four_node_to_two_node(TWO_THREE_TREE_TYPEDEF_PTR tree,
														   struct two_three_tree_transform_into_four_node_pack_s four_node_pack)
{
	void
		*node_left = tree_family_control_init_node(tree),
		*node_right = tree_family_control_init_node(tree);

	struct two_three_tree_transform_into_two_node_pack_s two_node_pack = { 0 };

	if (NULL == node_left ||
		NULL == node_right) {
		goto EXIT;
	}

	struct two_three_tree_chain_node_four_node_data_s
		*four_node_data = four_node_pack.node->data;
	struct two_three_tree_chain_node_four_node_link_s
		*four_node_link = four_node_pack.node->link;

	struct two_three_tree_chain_node_data_s
		*data = four_node_pack.data_before_inherit;
	struct two_three_tree_chain_node_link_s
		*link = four_node_pack.link_before_inherit;

	two_three_tree_transform_control_four_node_to_two_node_new_child(tree, node_left, four_node_pack.node, true);
	two_three_tree_transform_control_four_node_to_two_node_new_child(tree, node_right, four_node_pack.node, false);

	if (NULL == four_node_link->parent) {					/* If the parent of the four-node is NULL,the node will be the root,recycle the origin three-node */
		printf("-----> transform 4-node into 2-node.3-node root \r\n");

		data->left = four_node_data->middle;
		data->right = 0;

		link->lchild = node_left;
		link->mchild = NULL;
		link->rchild = node_right;

		four_node_pack.node->data = data;
		four_node_pack.node->link = link;

		tree->root = four_node_pack.node;

		goto EXIT;
	} else {
		link = ((struct tree_family_chain_node_s *)four_node_link->parent)->link;
		data = ((struct tree_family_chain_node_s *)four_node_link->parent)->data;

		printf("transform 4-node into 2-node.4-node parent:%p  DATA.left:%d .right:%d\r\n",
			   four_node_link->parent,
			   TWO_THREE_TREE_GET_KEY_FROM_DATA(data->left), TWO_THREE_TREE_GET_KEY_FROM_DATA(data->right));

		switch (tree_family_node_control_get_node_type(tree, four_node_link->parent)) {
			case 2:
				printf("-----> transform 4-node into 2-node.2-node parent \r\n");

				if (four_node_pack.node == link->lchild) {
					link->lchild = node_left;
					link->mchild = node_right;

					data->left = four_node_data->middle;
				} else if (four_node_pack.node == link->rchild) {
					link->mchild = node_left;
					link->rchild = node_right;

					data->right = four_node_data->middle;
				}

				printf("transform 4-node into 2-node.4-node parent:%p  DATA.left:%d right:%d\r\n",
					   four_node_link->parent,
					   TWO_THREE_TREE_GET_KEY_FROM_DATA(data->left), TWO_THREE_TREE_GET_KEY_FROM_DATA(data->right));

				break;
			case 3:
				printf("-----> transform 4-node into 3-node.3-node parent \r\n");

				two_node_pack.data = four_node_data->middle;
				two_node_pack.node = four_node_link->parent;
				two_node_pack.node_left = node_left;
				two_node_pack.node_right = node_right;
				break;
			default:
				break;
		}
	}

EXIT:

	return two_node_pack;
}

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

void two_three_tree_transform_control_four_node_to_two_node_new_child(TWO_THREE_TREE_TYPEDEF_PTR tree, void *node,
																	  struct tree_family_chain_node_s *four_node,
																	  bool left_child)
{
	struct two_three_tree_chain_node_data_s *data = ((struct tree_family_chain_node_s *)node)->data;
	struct two_three_tree_chain_node_link_s *link = ((struct tree_family_chain_node_s *)node)->link;
	struct two_three_tree_chain_node_four_node_data_s *four_node_data = four_node->data;
	struct two_three_tree_chain_node_four_node_link_s *four_node_link = four_node->link;

	bool is_root_four_node = false;

	if (NULL == four_node_link->parent) {
		link->parent = four_node;

		is_root_four_node = true;
	} else {
		link->parent = four_node_link->parent;
	}

	void
		*data_left = four_node_data->left,
		*four_node_link_rltv_lchild = four_node_link->lchild,
		*four_node_link_rltv_rchild = four_node_link->lchild;

	if (left_child) {
		data_left = four_node_data->left;
		four_node_link_rltv_lchild = four_node_link->lchild;
		four_node_link_rltv_rchild = four_node_link->mlchild;
	} else {
		data_left = four_node_data->right;
		four_node_link_rltv_lchild = four_node_link->mrchild;
		four_node_link_rltv_rchild = four_node_link->rchild;
	}

	tree_family_node_control_set_data(tree, node, data_left);

	if (is_root_four_node && (
		NULL != four_node_link_rltv_lchild ||
		NULL != four_node_link_rltv_rchild)) {
		link->lchild = four_node_link_rltv_lchild;
		link->rchild = four_node_link_rltv_rchild;

		if (NULL != four_node_link_rltv_lchild) {
			link = ((struct tree_family_chain_node_s *)four_node_link_rltv_lchild)->link;

			link->parent = node;

			#if (TWO_THREE_TREE_CFG_DEBUG_EN)

			printf("transform 4-node into new 2-node.%s old node:%p DATA.lchild:%d rchild:%d LINK.parent:%p lchild:%p rchild:%p \r\n",
				   left_child ? "Left " : "Middle Right",
				   four_node_link_rltv_lchild,
				   TWO_THREE_TREE_GET_KEY_FROM_NODE(four_node_link_rltv_lchild, left), TWO_THREE_TREE_GET_KEY_FROM_NODE(four_node_link_rltv_lchild, right),
				   link->parent, link->lchild, link->rchild);

			#endif // (TWO_THREE_TREE_CFG_DEBUG_EN)
		}
		if (NULL != four_node_link_rltv_rchild) {
			link = ((struct tree_family_chain_node_s *)four_node_link_rltv_rchild)->link;

			link->parent = node;

			#if (TWO_THREE_TREE_CFG_DEBUG_EN)

			printf("transform 4-node into new 2-node.%s old node:%p DATA.lchild:%d rchild:%d LINK.parent:%p lchild:%p rchild:%p \r\n",
				   left_child ? "Middle Left " : "Right",
				   four_node_link_rltv_rchild,
				   TWO_THREE_TREE_GET_KEY_FROM_NODE(four_node_link_rltv_rchild, left), TWO_THREE_TREE_GET_KEY_FROM_NODE(four_node_link_rltv_rchild, right),
				   link->parent, link->lchild, link->rchild);

			#endif // (TWO_THREE_TREE_CFG_DEBUG_EN)
		}
	}

	data = ((struct tree_family_chain_node_s *)node)->data;
	link = ((struct tree_family_chain_node_s *)node)->link;

	#if (TWO_THREE_TREE_CFG_DEBUG_EN)

	printf("transform 4-node into new 2-node.%s new node:%p DATA.lchild:%d rchild:%d LINK.parent:%p lchild:%p rchild:%p \r\n",
		   left_child ? "Left " : "Right",
		   node,
		   TWO_THREE_TREE_GET_KEY_FROM_DATA(data->left), TWO_THREE_TREE_GET_KEY_FROM_DATA(data->right),
		   link->parent, link->lchild, link->rchild);

	#endif // (TWO_THREE_TREE_CFG_DEBUG_EN)
}