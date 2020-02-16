/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "b_tree.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define B_TREE_GET_DATA_FROM_NODE(node,id)			(*((void**)(((struct tree_family_chain_node_s *)(node))->data) + (id)))

#define B_TREE_GET_KEY_FROM_DATA(data)				((NULL != data)?((char)*((void**)(data) + (0))):(0u))

#define B_TREE_GET_KEY_FROM_NODE(node,id)			B_TREE_GET_KEY_FROM_DATA(B_TREE_GET_DATA_FROM_NODE(node,id))

#define B_TREE_GET_LINK_FROM_NODE(node)				((void**)(((struct tree_family_chain_node_s *)(node))->link))

#define B_TREE_GET_FAMILY_MEMBER_FROM_LINK(link,id)	((NULL != link)?((*((void**)(link) + (id)))):(0u))

#define B_TREE_GET_FAMILY_MEMBER_FROM_NODE(node,id)	B_TREE_GET_FAMILY_MEMBER_FROM_LINK(B_TREE_GET_LINK_FROM_NODE(node),id)

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

struct b_tree_chain_node_data_s {
	void *left;
};

/**
 * @brief This struct is the binary tree link node structure module.
 */

struct b_tree_chain_node_link_s {
	void *parent;

	void *child;
};

/**
 * @brief This enum is the two-three tree transform into four-node type node information pack structure module.
 */

struct b_tree_insert_into_greater_pack_s {
	struct tree_family_chain_node_s *node;		/* the four-node inherit from three-node */

	void *data_before_inherit;						/* the data of the previous three-node */
	void *link_before_inherit;						/* the link of the previous three-node */
};

/**
 * @brief This enum is the two-three tree transform into two-node type node information pack structure module.
 */

struct b_tree_split_into_lesser_pack_s {
	struct tree_family_chain_node_s *node;
	void *data;

	void *child_last_splited;
	void *child_splited_left_part;
	void *child_splited_right_part;
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

void b_tree_control_switch_control(void);

/**
 * @brief This function will control b_tree_control_search()'s match.
 *
 * @param void
 *
 * @return void
 */

size_t b_tree_control_search_match_rule(struct tree_family_s *tree,
										void *node,
										void *data);

/**
 * @brief This function will control b_tree_control_search()'s recursion.
 *
 * @param void
 *
 * @return void
 */

void *b_tree_control_search_recursion_rule(struct tree_family_s *tree,
										   void *node,
										   void *data);

/**
 * @brief This function will control b_tree_control_insert()'s insert.
 *
 * @param void
 *
 * @return void
 */

void b_tree_control_insert_rule(struct tree_family_s *tree,
								struct tree_family_search_node_return_s search_return,
								void *data);

/**
 * @brief This function will control b_tree_control_delete()'s delete.
 *
 * @param void
 *
 * @return void
 */

void b_tree_control_delete_rule(struct tree_family_s *tree,
								struct tree_family_search_node_return_s search_return,
								void *data);

/**
 * @brief This function will transform the tree partially.
 *
 * @param void
 *
 * @return void
 */

void b_tree_node_control_partial_transformation(struct tree_family_s *tree,
												void *node,
												void *data);

/**
 * @brief This function will transform the three-node into four-node.
 *
 * @param void
 *
 * @return void
 */

struct b_tree_insert_into_greater_pack_s
	b_tree_control_insert_into_greater(struct tree_family_s *tree,
									   struct b_tree_split_into_lesser_pack_s lesser_pack);

/**
 * @brief This function will transform the four-node into two-node.
 *
 * @param void
 *
 * @return void
 */

struct b_tree_split_into_lesser_pack_s
	b_tree_control_split_into_lesser(struct tree_family_s *tree,
									 struct b_tree_insert_into_greater_pack_s greater_pack);

/**
 * @brief This function will fix the tree as a b-tree.
 *
 * @param void
 *
 * @return void
 */

void *b_tree_control_delete_fix_rule(struct tree_family_s *tree,
									 struct tree_family_chain_node_s *node,
									 struct tree_family_chain_node_s *parent);

/**
 * @brief This function will get the node's available brother node.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to node
 *
 * @return the address of the node's available brother node
 */

void *b_tree_control_get_neighbouring_brother(struct tree_family_s *tree,
											  struct tree_family_chain_node_s *node,
											  struct tree_family_chain_node_s *parent,
											  size_t relation_with_parent);

 /*
 *********************************************************************************************************
 *					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
 *********************************************************************************************************
 */

 /**
  * @brief This struct will record the tree's node operators.
  */

struct tree_family_control_environment_s b_tree_control_environment = {
	{
		TREE_FAMILY_B_TREE,
		sizeof(void *) * 2,
		sizeof(void *) * 4,
		2,
		4,
	},
	{
		b_tree_control_search_match_rule,
		b_tree_control_search_recursion_rule,
		b_tree_control_insert_rule,
		b_tree_control_delete_rule
	}
};

/**
 * @brief This struct will record the tree's node operators.
 */

struct tree_family_control_environment_s b_tree_control_greater_environment = {
	{
		TREE_FAMILY_B_TREE + 1,
		sizeof(void *) * 3,
		sizeof(void *) * 5,
		3,
		5,
	},
	{
		b_tree_control_search_match_rule,
		b_tree_control_search_recursion_rule,
		b_tree_control_insert_rule,
		b_tree_control_delete_rule
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

void b_tree_control_configuration_init(struct tree_family_s **tree,
									   CONTAINER_GLOBAL_CFG_SIZE_TYPE degree,
									   CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
									   void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(tree);
	assert(0 <= element_size);

	tree_family_control_configuration_init(tree, b_tree_control_switch_control, degree, TREE_FAMILY_B_TREE,
										   TWO_THREE_TREE_CFG_ALLOCATOR_TYPE, element_size, assign, free);
}

/**
 * @brief This function will analysis the shared pack.
 *
 * @param void
 *
 * @return void
 */

void b_tree_control_switch_control(void)
{
	tree_family_control_get_control(b_tree_control_environment);
}

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

tree_family_search_node_return_st b_tree_control_search(struct tree_family_s *tree,
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

void b_tree_control_insert(struct tree_family_s *tree,
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

void *b_tree_control_delete(struct tree_family_s *tree,
							void *data)
{
	assert(tree);
	assert(data);

	return tree_family_control_delete(tree, data);
}

/**
 * @brief This function will control b_tree_control_search()'s match.
 *
 * @param void
 *
 * @return void
 */

size_t b_tree_control_search_match_rule(struct tree_family_s *tree,
										void *node,
										void *data)
{
	struct b_tree_chain_node_data_s
		*data_operator = ((struct tree_family_chain_node_s *)node)->data;

	size_t count = 0;

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
 * @brief This function will control b_tree_control_search()'s recursion.
 *
 * @param void
 *
 * @return void
 */

void *b_tree_control_search_recursion_rule(struct tree_family_s *tree,
										   void *node,
										   void *data)
{
	struct b_tree_chain_node_data_s
		*data_operator = ((struct tree_family_chain_node_s *)node)->data;

	struct b_tree_chain_node_link_s
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

void b_tree_control_insert_rule(struct tree_family_s *tree,
								struct tree_family_search_node_return_s search_return,
								void *data)
{
	if (tree->info.degree - 1 > tree_family_node_control_get_node_type(tree, search_return.node_prev)) {
		tree_family_node_control_set_data(tree, search_return.node_prev, data);
	} else {
		b_tree_node_control_partial_transformation(tree, search_return.node_prev, data);
	}
}

/**
 * @brief This function will control b_tree_control_delete()'s delete.
 *
 * @param void
 *
 * @return void
 */

void b_tree_control_delete_rule(struct tree_family_s *tree,
								struct tree_family_search_node_return_s search_return,
								void *data)
{
	struct tree_family_chain_node_s
		*node = search_return.node,
		*parent = search_return.node_prev;

	size_t location = search_return.location;

	while (NULL != node) {
		if (tree_family_node_control_get_if_leaf(tree, node)) {										/* Delete the node that is a leaf node */
			tree_family_node_control_destroy_data(tree, ((void **)node->data + location));

			while (NULL != node &&
				   tree->info.minimum_key > tree_family_node_control_get_node_type(tree, node)) {
				printf("b tree delete fix.node:%p \r\n", node);
				node = b_tree_control_delete_fix_rule(tree, node, parent);
			}

			node = NULL;
		} else {																					/* Delete the node that is a parent node of somebody */
			tree_family_get_precursor_and_successor_return_st
				get_precursor_successor_return = tree_family_control_get_precursor(tree, node, location);

			if (NULL == get_precursor_successor_return.data &&
				(get_precursor_successor_return = tree_family_control_get_successor(tree, node, location),
				 NULL == get_precursor_successor_return.data)) {
				return;
			}

			void
				*data_tmp = get_precursor_successor_return.data;

			*((void **)get_precursor_successor_return.node->data + get_precursor_successor_return.location)
				= *((void **)node->data + search_return.location);
			*((void **)node->data + search_return.location) = data_tmp;

			node = get_precursor_successor_return.node;
			location = get_precursor_successor_return.location;
			if (NULL != node) {
				parent = *((void **)node->link);
			}
		}
	}
}

/**
 * @brief This function will transform the tree partially.
 *
 * @param void
 *
 * @return void
 */

void b_tree_node_control_partial_transformation(struct tree_family_s *tree,
												void *node,
												void *data)
{
	struct b_tree_insert_into_greater_pack_s greater_pack = { 0 };

	struct b_tree_split_into_lesser_pack_s lesser_pack = { node,data, };

	while (NULL != lesser_pack.data) {
		greater_pack = b_tree_control_insert_into_greater(tree, lesser_pack);

		lesser_pack = b_tree_control_split_into_lesser(tree, greater_pack);
	}
}

/**
 * @brief This function will transform the three-node into four-node.
 *
 * @param void
 *
 * @return void
 */

struct b_tree_insert_into_greater_pack_s
	b_tree_control_insert_into_greater(struct tree_family_s *tree,
									   struct b_tree_split_into_lesser_pack_s lesser_pack)
{
	struct b_tree_chain_node_data_s
		*lesser_data = ((struct tree_family_chain_node_s *)lesser_pack.node)->data,
		*greater_data = tree->allocator_ctrl->allocate(tree->allocator, tree->info.degree, sizeof(void *));
	struct b_tree_chain_node_link_s
		*lesser_link = ((struct tree_family_chain_node_s *)lesser_pack.node)->link,
		*greater_link = tree->allocator_ctrl->allocate(tree->allocator, tree->info.degree + 2, sizeof(void *));

	struct b_tree_insert_into_greater_pack_s
		greater_pack = {
		.node = lesser_pack.node,							/* the node shell of the origin lesser */
		.data_before_inherit = lesser_pack.node->data,		/* the data address of the origin lesser */
		.link_before_inherit = lesser_pack.node->link		/* the link address of the origin lesser */
	};

	printf("transform 3-node into 4-node.3-node:%p DATA.left:%c .right:%c LINK.parent:%p root:%p \r\n",
		   lesser_pack.node,
		   B_TREE_GET_KEY_FROM_NODE(lesser_pack.node, 0), B_TREE_GET_KEY_FROM_NODE(lesser_pack.node, 1),
		   lesser_link->parent, tree->root);

	greater_pack.node->data = greater_data;
	greater_pack.node->link = greater_link;

	for (size_t cnt = 0; cnt < tree->info.degree - 1; cnt++) {
		*((void **)greater_data + cnt) = *((void **)lesser_data + cnt);
	}

	tree_family_control_get_control_in_sandbox(tree, b_tree_control_greater_environment,
											   tree_family_node_control_set_data, 3,
											   tree, greater_pack.node, (void *)lesser_pack.data);

	greater_link->parent = lesser_link->parent;

	if (NULL != lesser_pack.child_last_splited) {
		size_t id_sub = 1;
		for (size_t id = 1; id <= tree->info.degree; id++) {
			if (lesser_pack.child_last_splited == *((void **)lesser_link + id)) {
				*((void **)greater_link + id_sub) = lesser_pack.child_splited_left_part;
				*((void **)greater_link + ++id_sub) = lesser_pack.child_splited_right_part;
			} else {
				*((void **)greater_link + id_sub) = *((void **)lesser_link + id);
			}

			id_sub++;
		}

		printf("transform 3-node into 4-node.4-node:%p LINK.lchild:%p .mlchild:%p .mrchild:%p .rchild:%p \r\n",
			   greater_pack.node,
			   B_TREE_GET_FAMILY_MEMBER_FROM_NODE(greater_pack.node, 1),
			   B_TREE_GET_FAMILY_MEMBER_FROM_NODE(greater_pack.node, 2),
			   B_TREE_GET_FAMILY_MEMBER_FROM_NODE(greater_pack.node, 3),
			   B_TREE_GET_FAMILY_MEMBER_FROM_NODE(greater_pack.node, 4));
	}

	printf("transform 3-node into 4-node.4-node:%p DATA.left:%c .middle:%c .right:%c LINK.parent:%p \r\n",
		   greater_pack.node,
		   B_TREE_GET_KEY_FROM_NODE(greater_pack.node, 0),
		   B_TREE_GET_KEY_FROM_NODE(greater_pack.node, 1),
		   B_TREE_GET_KEY_FROM_NODE(greater_pack.node, 2),
		   B_TREE_GET_FAMILY_MEMBER_FROM_NODE(greater_pack.node, 0));

	return greater_pack;
}

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

void b_tree_control_split_greater_into_lesser_new_lesser_init(struct tree_family_s *tree, void *lesser_node,
															  struct tree_family_chain_node_s *greater_node,
															  bool left_child)
{
	struct b_tree_chain_node_data_s
		*data_lesser = ((struct tree_family_chain_node_s *)lesser_node)->data,
		*data_greater = greater_node->data;
	struct b_tree_chain_node_link_s
		*link_lesser = ((struct tree_family_chain_node_s *)lesser_node)->link,
		*link_greater = greater_node->link;

	bool is_root_four_node = false;

	if (NULL == link_greater->parent) {
		link_lesser->parent = greater_node;

		is_root_four_node = true;
	} else {
		link_lesser->parent = link_greater->parent;
	}

	size_t
		offset_initial = 0,
		offset_end = 0;

	if (left_child) {
		offset_initial = 0;
		offset_end = tree->info.degree / 2;
	} else {
		offset_initial = tree->info.degree / 2 + 1;
		offset_end = tree->info.degree;
	}

	for (size_t id = offset_initial; id < offset_end; id++) {
		tree_family_node_control_set_data(tree, lesser_node, *((void **)data_greater + offset_initial));
	}

	offset_initial++;
	offset_end++;

	size_t id_sub = 1;
	for (size_t id = offset_initial; id <= offset_end; id++) {
		if (NULL != *((void **)link_greater + id)) {
			*((void **)link_lesser + id_sub) = *((void **)link_greater + id);

			struct b_tree_chain_node_link_s
				*link_child = ((struct tree_family_chain_node_s *) * ((void **)link_lesser + id_sub))->link;

			link_child->parent = lesser_node;
		}

		id_sub++;
	}

	#if (TWO_THREE_TREE_CFG_DEBUG_EN)

	printf("transform 4-node into new 2-node.%s new node:%p DATA.left:%c right:%c LINK.parent:%p left:%p right:%p \r\n",
		   left_child ? "Left " : "Right",
		   lesser_node,
		   B_TREE_GET_KEY_FROM_NODE(lesser_node, 0), B_TREE_GET_KEY_FROM_NODE(lesser_node, 1),
		   B_TREE_GET_FAMILY_MEMBER_FROM_NODE(lesser_node, 0),
		   B_TREE_GET_FAMILY_MEMBER_FROM_NODE(lesser_node, 1),
		   B_TREE_GET_FAMILY_MEMBER_FROM_NODE(lesser_node, 2));

	#endif // (TWO_THREE_TREE_CFG_DEBUG_EN)
}

/**
 * @brief This function will transform the four-node into two-node.
 *
 * @param void
 *
 * @return void
 */

struct b_tree_split_into_lesser_pack_s
	b_tree_control_split_into_lesser(struct tree_family_s *tree,
									 struct b_tree_insert_into_greater_pack_s greater_pack)
{
	void
		*node_left_new_part = tree_family_control_init_node(tree),
		*node_right_new_part = tree_family_control_init_node(tree);

	struct b_tree_split_into_lesser_pack_s lesser_pack = { 0 };

	if (NULL == node_left_new_part ||
		NULL == node_right_new_part) {
		goto EXIT;
	}

	struct b_tree_chain_node_data_s
		*data_greater = greater_pack.node->data,
		*data_lesser = greater_pack.data_before_inherit;
	struct b_tree_chain_node_link_s
		*link_greater = greater_pack.node->link,
		*link_lesser = greater_pack.link_before_inherit;

	b_tree_control_split_greater_into_lesser_new_lesser_init(tree, node_left_new_part, greater_pack.node, true);
	b_tree_control_split_greater_into_lesser_new_lesser_init(tree, node_right_new_part, greater_pack.node, false);

	if (NULL == link_greater->parent) {					/* If the parent of the four-node is NULL,the node will be the root,recycle the origin three-node */
		#if (TWO_THREE_TREE_CFG_DEBUG_EN)

		printf("-----> split greater into lesser.root greater \r\n");

		#endif // (TWO_THREE_TREE_CFG_DEBUG_EN)

		for (size_t cnt = 0; cnt < tree->info.degree; cnt++) {
			*((void **)data_lesser + cnt) = NULL;
		}
		for (size_t cnt = 0; cnt <= tree->info.degree; cnt++) {
			*((void **)link_lesser + cnt) = NULL;
		}

		*((void **)data_lesser) = *((void **)data_greater + tree->info.degree / 2);

		*((void **)link_lesser + 1 + 0) = node_left_new_part;
		*((void **)link_lesser + 1 + 1) = node_right_new_part;

		greater_pack.node->data = data_lesser;
		greater_pack.node->link = link_lesser;

		tree->root = greater_pack.node;

		goto EXIT;
	} else {
		if (tree->info.degree - 1 > tree_family_node_control_get_node_type(tree, link_greater->parent)) {		/* This node is not full */
			#if (TWO_THREE_TREE_CFG_DEBUG_EN)

			printf("-----> split greater into lesser.not full parent \r\n");

			#endif // (TWO_THREE_TREE_CFG_DEBUG_EN)

			link_lesser = ((struct tree_family_chain_node_s *)link_greater->parent)->link;
			data_lesser = ((struct tree_family_chain_node_s *)link_greater->parent)->data;

			for (size_t id = 1; id <= tree->info.degree; id++) {
				if (greater_pack.node == *((void **)link_lesser + id)) {
					if (tree->info.degree >= id + 2) {
						*((void **)link_lesser + id + 2) = *((void **)link_lesser + id + 1);
					}

					*((void **)link_lesser + id) = node_left_new_part;
					*((void **)link_lesser + id + 1) = node_right_new_part;

					tree_family_node_control_set_data(tree, link_greater->parent, *((void **)data_greater + tree->info.degree / 2));

					break;
				}
			}

			printf("transform 4-node into 2-node.4-node parent:%p  DATA.left:%c right:%c\r\n",
				   link_greater->parent,
				   B_TREE_GET_KEY_FROM_NODE(link_greater->parent, 0),
				   B_TREE_GET_KEY_FROM_NODE(link_greater->parent, 1));
		} else {
			#if (TWO_THREE_TREE_CFG_DEBUG_EN)

			printf("-----> split greater into lesser.full parent \r\n");

			#endif // (TWO_THREE_TREE_CFG_DEBUG_EN)

			lesser_pack.data = *((void **)data_greater + tree->info.degree / 2);
			lesser_pack.node = link_greater->parent;
			lesser_pack.child_last_splited = greater_pack.node;
			lesser_pack.child_splited_left_part = node_left_new_part;
			lesser_pack.child_splited_right_part = node_right_new_part;
		}
	}

EXIT:

	return lesser_pack;
}

/**
 * @brief This function will fix the tree as a b-tree.
 *
 * @param void
 *
 * @return void
 */

void *b_tree_control_delete_fix_rule(struct tree_family_s *tree,
									 struct tree_family_chain_node_s *node,
									 struct tree_family_chain_node_s *parent)
{
	struct tree_family_chain_node_s *node_brother = b_tree_control_get_neighbouring_brother(tree, node, parent, 0);

	size_t
		location = tree_family_node_control_get_relation_with_parent(tree, node, parent),
		location_brother = tree_family_node_control_get_relation_with_parent(tree, node_brother, parent);

	bool node_right = false;

	if (location > location_brother) {
		location = location_brother;

		node_right = true;
	}

	if (tree->info.minimum_key < tree_family_node_control_get_node_type(tree, node_brother)) {	/* If the brother node has enough keys */

		tree_family_node_control_set_data(tree, node, *((void **)parent->data + location - 1));

		tree_family_node_control_destroy_data(tree, ((void **)parent->data + location - 1));

		if (node_right) {
			*((void **)parent->data + location - 1) = tree_family_node_control_del_data(tree, node_brother, tree->info.degree);
		} else {
			*((void **)parent->data + location - 1) = tree_family_node_control_del_data(tree, node_brother, 0);
		}

		return NULL;
	} else {
		tree_family_node_control_set_data(tree, node, tree_family_node_control_del_data(tree, parent, location - 1));

		for (size_t id = 0; id < tree->info.degree - 1; id++) {
			tree_family_node_control_set_data(tree, node, *((void **)node_brother->data + id));
		}

		tree_family_control_destroy_node(tree, &node_brother);

		*((void **)parent->link + location_brother) = NULL;

		return parent;
	}
}

/**
 * @brief This function will get the node's available brother node.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to node
 *
 * @return the address of the node's available brother node
 */

void *b_tree_control_get_neighbouring_brother(struct tree_family_s *tree,
											  struct tree_family_chain_node_s *node,
											  struct tree_family_chain_node_s *parent,
											  size_t relation_with_parent)
{
	assert(tree);
	assert(node);

	if (NULL == parent &&
		NULL == (parent = *((void **)node->link))) {
		goto FAIL;
	}

	if (0 >= relation_with_parent) {
		relation_with_parent = tree_family_node_control_get_relation_with_parent(tree, node, parent);
	}

	struct b_tree_chain_node_link_s
		*link = parent->link;

	size_t
		minimum = tree->info.minimum_key,
		type_node = 0,
		id_next_node = relation_with_parent + 1,
		location = 0;

	for (size_t id = relation_with_parent - 1; id <= id_next_node; id++) {
		if (minimum <= (type_node = tree_family_node_control_get_node_type(tree, *((void **)link + id)))) {
			location = id;
			minimum = type_node;
		}
	}

	if (0 >= location) {
	FAIL:
		return NULL;
	}

	return *((void **)link + location);
}