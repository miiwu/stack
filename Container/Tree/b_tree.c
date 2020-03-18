/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "b_tree.h"

#include "container_pte_def.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define B_TREE_GET_EXTRA_INFO()																		\
tree_family_control_get_extra_infomation(b_tree)

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
 * @brief This struct is the binary b_tree link node structure module.
 */

struct b_tree_chain_node_data_s {
	void *left;
};

/**
 * @brief This struct is the binary b_tree link node structure module.
 */

struct b_tree_chain_node_link_s {
	void *parent;

	void *child;
};

/**
 * @brief This enum is the two-three b_tree transform into four-node type node information pack structure module.
 */

struct b_tree_insert_into_greater_pack_s {
	struct tree_family_chain_node_s *node;		/* the four-node inherit from three-node */

	void *data_before_inherit;						/* the data of the previous three-node */
	void *link_before_inherit;						/* the link of the previous three-node */
};

/**
 * @brief This enum is the two-three b_tree transform into two-node type node information pack structure module.
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
 * @brief This function will switch the b_tree-family control.
 *
 * @param void
 *
 * @return void
 */

void b_tree_control_switch_control(b_tree_stp b_tree);

/**
 * @brief This function will control b_tree_control_search()'s match.
 *
 * @param void
 *
 * @return void
 */

container_size_t
b_tree_control_search_match_rule(b_tree_stp b_tree,
								 struct tree_family_chain_node_s *node,
								 void *data);

/**
 * @brief This function will control b_tree_control_search()'s recursion.
 *
 * @param void
 *
 * @return void
 */

container_size_t
b_tree_control_search_recursion_rule(b_tree_stp b_tree,
									 struct tree_family_chain_node_s **node,
									 void *data);

/**
 * @brief This function will control b_tree_control_insert()'s insert.
 *
 * @param void
 *
 * @return void
 */

void *b_tree_control_insert_rule(b_tree_stp b_tree,
								 struct tree_family_search_node_return_s search_return,
								 void *data);

/**
 * @brief This function will control b_tree_control_delete()'s delete.
 *
 * @param void
 *
 * @return void
 */

void *b_tree_control_delete_rule(b_tree_stp b_tree,
								 struct tree_family_search_node_return_s search_return,
								 void *data);

/**
 * @brief This function will transform the b_tree partially.
 *
 * @param void
 *
 * @return void
 */

void *b_tree_node_control_partial_transformation(b_tree_stp b_tree,
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
	b_tree_control_insert_into_greater(b_tree_stp b_tree,
									   struct b_tree_split_into_lesser_pack_s lesser_pack);

/**
 * @brief This function will transform the four-node into two-node.
 *
 * @param void
 *
 * @return void
 */

struct b_tree_split_into_lesser_pack_s
	b_tree_control_split_into_lesser(b_tree_stp b_tree,
									 struct b_tree_insert_into_greater_pack_s greater_pack);

/**
 * @brief This function will split the greater into the new lesser.
 *
 * @param void
 *
 * @return void
 */

void b_tree_control_split_greater_into_new_lesser(b_tree_stp b_tree,
												  struct tree_family_chain_node_s *node_lesser[2],
												  struct tree_family_chain_node_s *node_greater,
												  container_size_t id_data_split);

/**
 * @brief This function will fix the b_tree as a b-b_tree.
 *
 * @param void
 *
 * @return void
 */

void *b_tree_control_delete_fix_rule(b_tree_stp b_tree,
									 struct tree_family_chain_node_s *node,
									 struct tree_family_chain_node_s *parent);

/*
*********************************************************************************************************
*					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
*********************************************************************************************************
*/

/**
 * @brief This struct will record the b_tree's node operators.
 */

struct tree_family_control_environment_s b_tree_control_environment = {
	TREE_FAMILY_3D_NODE_TYPE,
	{
		b_tree_control_search_match_rule,
		b_tree_control_search_recursion_rule,
		b_tree_control_insert_rule,
		b_tree_control_delete_rule
	}
};

/**
 * @brief This struct will record the b_tree's node operators.
 */

struct tree_family_control_environment_s b_tree_control_greater_environment = {
	TREE_FAMILY_4D_NODE_TYPE,
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
 * @brief This function will initialize the b_tree struct
 *
 * @param b_tree the pointer to the b_tree struct pointer
 * @param element_size the element memory size of the b_tree struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void b_tree_control_configuration_init(b_tree_stpp b_tree,
									   container_size_t degree,
									   container_size_t key_size,
									   container_size_t element_size,
									   generic_type_element_assign_t assign,
									   generic_type_element_free_t free)
{
	assert(b_tree);
	assert(0 <= element_size);

	tree_family_control_configuration_init(b_tree,
										   b_tree_control_switch_control,
										   degree,
										   key_size,
										   TREE_FAMILY_B_TREE,
										   B_TREE_CFG_ALLOCATOR_TYPE, 
										   element_size, assign, free);
}

/**
 * @brief This function will analysis the shared pack.
 *
 * @param void
 *
 * @return void
 */

static inline void b_tree_control_switch_control(b_tree_stp b_tree)
{
	struct tree_family_extra_infomation_s
		*extra_info = (struct tree_family_extra_infomation_s *)&b_tree->addon;

	enum tree_family_member_type_e
		member_type = extra_info->degree;

	if (b_tree_control_environment.member_type != member_type) {
		b_tree_control_environment.member_type = member_type;
		b_tree_control_environment.extra_info = *extra_info;
		b_tree_control_greater_environment.member_type = member_type + 0x01;
	}

	tree_family_control_get_control(b_tree_control_environment);
}

/**
 * @brief This function will control b_tree_control_search()'s match.
 *
 * @param void
 *
 * @return void
 */

container_size_t b_tree_control_search_match_rule(b_tree_stp b_tree,
												  struct tree_family_chain_node_s *node,
												  void *data)
{
	struct b_tree_chain_node_data_s
		*data_operator = ((struct tree_family_chain_node_s *)node)->data;

	container_size_t count = 0;

	for (; count < B_TREE_GET_EXTRA_INFO().degree - 1; count++) {
		if (NULL != *((void **)data_operator + count) &&
			compare_control_equal(data, *((void **)data_operator + count), B_TREE_GET_EXTRA_INFO().mem_size_key)) {
			goto EXIT;
		}
	}

	count = SEARCH_CODE_NO_SUCH_ELEMENT;

EXIT:

	#if (B_TREE_CFG_DEBUG_EN)

	printf("search.match rule:node:%p Data ",
		   node);

	for (size_t cnt = 0; cnt < B_TREE_GET_EXTRA_INFO().degree - 1; cnt++) {
		printf("No.%d:\"%s\"-%p ", cnt, (char *)*((void **)data_operator + cnt), *((void **)data_operator + cnt));
	}

	printf("\r\nmatch:%p location:%d\r\n", (0xff != count) ? *((void **)data_operator + count) : NULL, count);

	#endif // (B_TREE_CFG_DEBUG_EN)

	return count;
}

/**
 * @brief This function will control b_tree_control_search()'s recursion.
 *
 * @param void
 *
 * @return void
 */

container_size_t
b_tree_control_search_recursion_rule(b_tree_stp b_tree,
									 struct tree_family_chain_node_s **node,
									 void *data)
{
	container_size_t evaluation_level = 1;

	for (; evaluation_level < B_TREE_GET_EXTRA_INFO().degree; evaluation_level++) {
		if ((NULL == *((void **)(*node)->data + evaluation_level - 1) ||
			(NULL != *((void **)(*node)->data + evaluation_level - 1) &&
			 compare_control_lesser(data, *((void **)(*node)->data + evaluation_level - 1),
									B_TREE_GET_EXTRA_INFO().mem_size_key)))) {
			goto EXIT;
		}
	}

	evaluation_level = B_TREE_GET_EXTRA_INFO().degree;

EXIT:

	#if (B_TREE_CFG_DEBUG_EN)

	printf("search.recursion rule:(*node):%p Link ",
		(*node));

	for (size_t cnt = 1; cnt <= B_TREE_GET_EXTRA_INFO().degree; cnt++) {
		printf("No.%d:%p ", cnt, *((void **)(*node)->link + cnt));
	}

	printf("\r\nrecursion:%p location:%d\r\n", *((void **)(*node)->link + evaluation_level), evaluation_level);

	#endif // (B_TREE_CFG_DEBUG_EN)

	*node = *((void **)(*node)->link + evaluation_level);								/* Recursion to it's child */

	return evaluation_level;
}

/**
 * @brief This function will control b_tree_control_insert()'s insert.
 *
 * @param void
 *
 * @return void
 */

void *b_tree_control_insert_rule(b_tree_stp b_tree,
								 struct tree_family_search_node_return_s search_return,
								 void *data)
{
	if (B_TREE_GET_EXTRA_INFO().degree - 1 > tree_family_node_control_get_node_type(b_tree, search_return.node_prev)) {
		tree_family_node_control_insert_data(b_tree, search_return.node_prev, data);
		return search_return.node_prev;
	} else {
		return b_tree_node_control_partial_transformation(b_tree, search_return.node_prev, data);
	}
}

/**
 * @brief This function will control b_tree_control_delete()'s delete.
 *
 * @param void
 *
 * @return void
 */

void *b_tree_control_delete_rule(b_tree_stp b_tree,
								 struct tree_family_search_node_return_s search_return,
								 void *data)
{
	struct tree_family_chain_node_s
		*node = search_return.node,
		*parent = search_return.node_prev;

	container_size_t location = search_return.location;

	void *data_delete = NULL;

	#if (B_TREE_CFG_DEBUG_EN)

	printf("b b_tree.delete rule:\"%s\"-%d \r\n", (char *)data, *(char *)data - '0');

	#endif // (B_TREE_CFG_DEBUG_EN)

	while (NULL != node) {
		if (tree_family_node_control_get_if_leaf(b_tree, node)) {										/* Delete the node that is a leaf node */
			MODIFY_SEQUENCE_CONTROL_SWAP((size_t)data_delete, (size_t) * ((void **)node->data + location));

			while ((NULL != node) && (NULL != parent || NULL != (parent = *((void **)node->link))) &&
				(B_TREE_GET_EXTRA_INFO().minimum_amt_key > tree_family_node_control_get_node_type(b_tree, node))) {
				printf("b b_tree delete fix.node:%p parent:%p \r\n", node, parent);
				node = b_tree_control_delete_fix_rule(b_tree, node, parent);
				parent = NULL;

				#if (B_TREE_CFG_DEBUG_EN)

				tree_family_control_inorder_traversal(b_tree, b_tree->element_ptr, tree_family_control_traversal_printer);

				#endif // (B_TREE_CFG_DEBUG_EN)
			}

			goto EXIT;
		} else {																					/* Delete the node that is a parent node of somebody */
			tree_family_get_precursor_and_successor_return_st
				get_precursor_successor_return = tree_family_control_get_precursor(b_tree, node, location);

			if (NULL == get_precursor_successor_return.data &&
				(get_precursor_successor_return = tree_family_control_get_successor(b_tree, node, location),
				 NULL == get_precursor_successor_return.data)) {
				goto FAIL;
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

EXIT:

	return data_delete;
FAIL:

	return NULL;
}

/**
 * @brief This function will transform the b_tree partially.
 *
 * @param void
 *
 * @return void
 */

void *b_tree_node_control_partial_transformation(b_tree_stp b_tree,
												 void *node,
												 void *data)
{
	struct b_tree_insert_into_greater_pack_s greater_pack = { 0 };

	struct b_tree_split_into_lesser_pack_s lesser_pack = { node,data, };

	while (NULL != lesser_pack.data) {
		greater_pack = b_tree_control_insert_into_greater(b_tree, lesser_pack);

		lesser_pack = b_tree_control_split_into_lesser(b_tree, greater_pack);
	}

	return lesser_pack.node;
}

/**
 * @brief This function will transform the three-node into four-node.
 *
 * @param void
 *
 * @return void
 */

struct b_tree_insert_into_greater_pack_s
	b_tree_control_insert_into_greater(b_tree_stp b_tree,
									   struct b_tree_split_into_lesser_pack_s lesser_pack)
{
	struct b_tree_chain_node_data_s
		*lesser_data = ((struct tree_family_chain_node_s *)lesser_pack.node)->data,
		*greater_data = b_tree->allocator_control_ptr->allocate(b_tree->allocator_ptr, B_TREE_GET_EXTRA_INFO().degree, sizeof(void *));
	struct b_tree_chain_node_link_s
		*lesser_link = ((struct tree_family_chain_node_s *)lesser_pack.node)->link,
		*greater_link = b_tree->allocator_control_ptr->allocate(b_tree->allocator_ptr, B_TREE_GET_EXTRA_INFO().degree + 2, sizeof(void *));

	struct b_tree_insert_into_greater_pack_s
		greater_pack = {
		.node = lesser_pack.node,							/* the node shell of the origin lesser */
		.data_before_inherit = lesser_pack.node->data,		/* the data address of the origin lesser */
		.link_before_inherit = lesser_pack.node->link		/* the link address of the origin lesser */
	};

	#if (B_TREE_CFG_DEBUG_EN)

	printf("transform lesser into greater.lesser:%p DATA->", lesser_pack.node);

	for (size_t id_data = 0; id_data < B_TREE_GET_EXTRA_INFO().degree - 1; id_data++) {
		printf("No.%d:\"%c\" ", id_data, TREE_FAMILY_DEBUG_OPERATOR_GET_KEY_FROM_NODE(lesser_pack.node, id_data));
	}

	printf("LINK->No.0:%p root:%p\r\n", lesser_link->parent, b_tree->element_ptr);

	#endif // (B_TREE_CFG_DEBUG_EN)

	greater_pack.node->data = greater_data;
	greater_pack.node->link = greater_link;

	for (size_t cnt = 0; cnt < B_TREE_GET_EXTRA_INFO().degree - 1; cnt++) {
		*((void **)greater_data + cnt) = *((void **)lesser_data + cnt);
	}

	tree_family_control_get_control_in_sandbox(b_tree, b_tree_control_greater_environment,
											   tree_family_node_control_insert_data, 3,
											   b_tree, greater_pack.node, (void *)lesser_pack.data);

	greater_link->parent = lesser_link->parent;

	if (NULL != lesser_pack.child_last_splited) {
		container_size_t id_sub = 1;
		for (size_t id = 1; id <= B_TREE_GET_EXTRA_INFO().degree; id++) {
			if (lesser_pack.child_last_splited == *((void **)lesser_link + id)) {
				*((void **)greater_link + id_sub) = lesser_pack.child_splited_left_part;
				*((void **)greater_link + ++id_sub) = lesser_pack.child_splited_right_part;
			} else {
				*((void **)greater_link + id_sub) = *((void **)lesser_link + id);
			}

			id_sub++;
		}

		#if (B_TREE_CFG_DEBUG_EN)

		printf("transform lesser into greater.greater:%p LINK->", greater_pack.node);

		for (size_t id_link = 1; id_link <= B_TREE_GET_EXTRA_INFO().degree; id_link++) {
			printf("No.%d:%p ", id_link, TREE_FAMILY_DEBUG_OPERATOR_GET_FAMILY_MEMBER_FROM_NODE(greater_pack.node, id_link));
		}

		printf("\r\n");

		#endif // (B_TREE_CFG_DEBUG_EN)
	}

	#if (B_TREE_CFG_DEBUG_EN)

	printf("transform lesser into greater.greater:%p DATA->", greater_pack.node);

	for (size_t id_data = 0; id_data < B_TREE_GET_EXTRA_INFO().degree; id_data++) {
		printf("No.%d:\"%c\" ", id_data, TREE_FAMILY_DEBUG_OPERATOR_GET_KEY_FROM_NODE(greater_pack.node, id_data));
	}

	printf("LINK->No.0:%p \r\n", TREE_FAMILY_DEBUG_OPERATOR_GET_FAMILY_MEMBER_FROM_NODE(greater_pack.node, 0));

	#endif // (B_TREE_CFG_DEBUG_EN)

	return greater_pack;
}

/**
 * @brief This function will transform the four-node into two-node.
 *
 * @param void
 *
 * @return void
 */

struct b_tree_split_into_lesser_pack_s
	b_tree_control_split_into_lesser(b_tree_stp b_tree,
									 struct b_tree_insert_into_greater_pack_s greater_pack)
{
	struct tree_family_chain_node_s *node_new_inited[2] = {
		tree_family_control_init_node(b_tree),
		tree_family_control_init_node(b_tree)
	};

	struct b_tree_split_into_lesser_pack_s lesser_pack = { 0 };

	if (NULL == node_new_inited[0] ||
		NULL == node_new_inited[1]) {
		goto EXIT;
	}

	struct b_tree_chain_node_data_s
		*data_greater = greater_pack.node->data,
		*data_lesser = greater_pack.data_before_inherit;
	struct b_tree_chain_node_link_s
		*link_greater = greater_pack.node->link,
		*link_lesser = greater_pack.link_before_inherit;

	container_size_t id_split_data = ((0 == B_TREE_GET_EXTRA_INFO().degree % 2) ? B_TREE_GET_EXTRA_INFO().degree - 1 : B_TREE_GET_EXTRA_INFO().degree) / 2;

	b_tree_control_split_greater_into_new_lesser(b_tree, node_new_inited,
												 greater_pack.node, id_split_data);

	if (NULL == link_greater->parent) {					/* If the parent of the four-node is NULL,the node will be the root,recycle the origin three-node */
		#if (B_TREE_CFG_DEBUG_EN)

		printf("-----> split greater into lesser.root greater \r\n");

		#endif // (B_TREE_CFG_DEBUG_EN)

		for (size_t cnt = 0; cnt < B_TREE_GET_EXTRA_INFO().degree; cnt++) {
			*((void **)data_lesser + cnt) = NULL;
		}
		for (size_t cnt = 0; cnt <= B_TREE_GET_EXTRA_INFO().degree; cnt++) {
			*((void **)link_lesser + cnt) = NULL;
		}

		*((void **)data_lesser) = *((void **)data_greater + id_split_data);

		*((void **)link_lesser + 1 + 0) = node_new_inited[0];
		*((void **)link_lesser + 1 + 1) = node_new_inited[1];

		greater_pack.node->data = data_lesser;
		greater_pack.node->link = link_lesser;

		b_tree->element_ptr = greater_pack.node;

		lesser_pack.node = b_tree->element_ptr;

		goto EXIT;
	} else {
		if (B_TREE_GET_EXTRA_INFO().degree - 1 > tree_family_node_control_get_node_type(b_tree, link_greater->parent)) {		/* This node is not full */
			#if (B_TREE_CFG_DEBUG_EN)

			printf("-----> split greater into lesser.not full parent \r\n");

			#endif // (B_TREE_CFG_DEBUG_EN)

			link_lesser = ((struct tree_family_chain_node_s *)link_greater->parent)->link;
			data_lesser = ((struct tree_family_chain_node_s *)link_greater->parent)->data;

			for (size_t id_link = 1; id_link <= B_TREE_GET_EXTRA_INFO().degree; id_link++) {
				if (greater_pack.node == *((void **)link_lesser + id_link)) {
					if (B_TREE_GET_EXTRA_INFO().degree >= id_link + 2) {
						*((void **)link_lesser + id_link + 2) = *((void **)link_lesser + id_link + 1);
					}

					*((void **)link_lesser + id_link) = node_new_inited[0];
					*((void **)link_lesser + id_link + 1) = node_new_inited[1];

					tree_family_node_control_insert_data(b_tree, link_greater->parent, *((void **)data_greater + id_split_data));

					#if (B_TREE_CFG_DEBUG_EN)

					printf("transform greater into lesser.greater's parent:%p DATA->", link_greater->parent);

					for (size_t id_data = 0; id_data < B_TREE_GET_EXTRA_INFO().degree - 1; id_data++) {
						printf("No.%d:\"%c\" ", id_data, TREE_FAMILY_DEBUG_OPERATOR_GET_KEY_FROM_NODE(link_greater->parent, id_data));
					}

					printf("\r\n");

					#endif // (B_TREE_CFG_DEBUG_EN)

					lesser_pack.node = link_greater->parent;

					goto EXIT;
				}
			}
		} else {
			#if (B_TREE_CFG_DEBUG_EN)

			printf("-----> split greater into lesser.full parent \r\n");

			#endif // (B_TREE_CFG_DEBUG_EN)

			lesser_pack.data = *((void **)data_greater + id_split_data);
			lesser_pack.node = link_greater->parent;
			lesser_pack.child_last_splited = greater_pack.node;
			lesser_pack.child_splited_left_part = node_new_inited[0];
			lesser_pack.child_splited_right_part = node_new_inited[1];
		}
	}

EXIT:

	return lesser_pack;
}

/**
 * @brief This function will split the greater into the new lesser.
 *
 * @param void
 *
 * @return void
 */

void b_tree_control_split_greater_into_new_lesser(b_tree_stp b_tree,
												  struct tree_family_chain_node_s *node_lesser[2],
												  struct tree_family_chain_node_s *node_greater,
												  container_size_t id_data_split)
{
	struct b_tree_chain_node_data_s
		*data_lesser[2] = { node_lesser[0]->data,node_lesser[1]->data },
		*data_greater = node_greater->data;

	struct b_tree_chain_node_link_s
		*link_lesser[2] = { node_lesser[0]->link,node_lesser[1]->link },
		*link_greater = node_greater->link;

	container_size_t
		offset_initial[2] = { 0 ,id_data_split + 1 },
		offset_end[2] = { id_data_split ,B_TREE_GET_EXTRA_INFO().degree };

	for (size_t part = 0; part < 2; part++) {
		if (NULL == link_greater->parent) {
			link_lesser[part]->parent = node_greater;
		} else {
			link_lesser[part]->parent = link_greater->parent;
		}

		container_size_t id_sub = DATA_OPERATOR_CODE_DATA_FAR_LEFT;
		for (size_t id_data = offset_initial[part]; id_data < offset_end[part]; id_data++) {
			*((void **)data_lesser[part] + id_sub++) = *((void **)data_greater + id_data);
			*((void **)data_greater + id_data) = NULL;
		}

		offset_initial[part]++;
		offset_end[part]++;

		id_sub = LINK_OPERATOR_CODE_CHILD_FAR_LEFT;
		for (size_t id = offset_initial[part]; id <= offset_end[part]; id++) {
			if (NULL != *((void **)link_greater + id)) {
				*((void **)link_lesser[part] + id_sub) = *((void **)link_greater + id);

				struct b_tree_chain_node_link_s
					*link_child = ((struct tree_family_chain_node_s *) * ((void **)link_lesser[part] + id_sub))->link;

				link_child->parent = node_lesser[part];
			}

			id_sub++;
		}

		#if (B_TREE_CFG_DEBUG_EN)

		printf("split greater into new lesser.%s new node:%p DATA->", 0 == part ? "Left " : "Right", node_lesser[part]);

		for (size_t id_data = 0; id_data < B_TREE_GET_EXTRA_INFO().degree - 1; id_data++) {
			printf("No.%d:\"%c\" ", id_data, TREE_FAMILY_DEBUG_OPERATOR_GET_KEY_FROM_NODE(node_lesser[part], id_data));
		}

		printf("LINK->");

		for (size_t id_link = 0; id_link <= B_TREE_GET_EXTRA_INFO().degree; id_link++) {
			printf("No.%d:%p ", id_link, TREE_FAMILY_DEBUG_OPERATOR_GET_FAMILY_MEMBER_FROM_NODE(node_lesser[part], id_link));
		}

		printf("\r\n");

		#endif // (B_TREE_CFG_DEBUG_EN)
	}
}

/**
 * @brief This function will fix the b_tree as a b-b_tree.
 *
 * @param void
 *
 * @return void
 */

void *b_tree_control_delete_fix_rule(b_tree_stp b_tree,
									 struct tree_family_chain_node_s *node,
									 struct tree_family_chain_node_s *parent)
{
	assert(b_tree);
	assert(node);
	assert(parent);

	struct tree_family_chain_node_s *node_brother =
		tree_family_node_control_get_neighbour(b_tree, node, parent, LINK_OPERATOR_CODE_PARENT);

	container_size_t
		location = tree_family_node_control_get_relation_with_parent(b_tree, node, parent),
		location_brother = tree_family_node_control_get_relation_with_parent(b_tree, node_brother, parent);

	bool node_on_the_right_side = false;

	if (location > location_brother) {
		MODIFY_SEQUENCE_CONTROL_SWAP(location, location_brother);

		node_on_the_right_side = true;
	}

	if (B_TREE_GET_EXTRA_INFO().minimum_amt_key < tree_family_node_control_get_node_type(b_tree, node_brother)) {	/* If the brother node has enough keys */
		#if (B_TREE_CFG_DEBUG_EN)

		printf("b_tree_control.delete.fix_rule:brother have enough keys \r\n");

		#endif // (B_TREE_CFG_DEBUG_EN)

		enum tree_family_data_operator_code_type_e data_operator = DATA_OPERATOR_CODE_DATA_FAR_LEFT;
		enum tree_family_link_operator_code_type_e link_operator[2] = {
			LINK_OPERATOR_CODE_CHILD_FAR_LEFT , LINK_OPERATOR_CODE_CHILD_FAR_RIGHT };

		if (node_on_the_right_side) {
			data_operator = DATA_OPERATOR_CODE_DATA_FAR_RIGHT;
			MODIFY_SEQUENCE_CONTROL_SWAP(link_operator[0], link_operator[1]);
		}

		*((void **)node->data + B_TREE_GET_EXTRA_INFO().minimum_amt_key - 1) = *((void **)parent->data + location - 1);
		*((void **)parent->data + location - 1) =
			tree_family_node_control_del_data(b_tree, node_brother, data_operator);

		void *family_member = tree_family_node_control_del_family_member(b_tree, node_brother, link_operator[0]);
		tree_family_node_control_set_child(b_tree, node, family_member, link_operator[1]);

		return NULL;
	} else {
		#if (B_TREE_CFG_DEBUG_EN)

		printf("b_tree_control.delete.fix_rule:brother have not enough keys \r\n");

		#endif // (B_TREE_CFG_DEBUG_EN)

		container_size_t id_set_data = B_TREE_GET_EXTRA_INFO().minimum_amt_key - 1;
		container_size_t id_del_data = DATA_OPERATOR_CODE_DATA_FAR_LEFT;

		if (node_on_the_right_side) {
			MODIFY_SEQUENCE_CONTROL_SWAP((size_t)node, (size_t)node_brother);									/* Let node always is the left one */
			id_set_data = B_TREE_GET_EXTRA_INFO().minimum_amt_key;
		}

		tree_family_node_control_set_data(b_tree, node,
										  tree_family_node_control_del_data(b_tree, parent, location - 1),
										  id_set_data++);

		for (; id_set_data < B_TREE_GET_EXTRA_INFO().degree; id_set_data++) {								/* Compound to a normal node */
			tree_family_node_control_set_data(b_tree, node, *((void **)node_brother->data + id_del_data++), id_set_data);
		}

		container_size_t id_set_link = id_set_data + LINK_OPERATOR_CODE_CHILD_FAR_LEFT + 1;
		container_size_t id_del_link = LINK_OPERATOR_CODE_CHILD_FAR_LEFT;

		while (NULL != *((void **)node_brother->link + id_del_link)) {
			tree_family_node_control_set_child(b_tree, node, *((void **)node_brother->link + id_del_link++), id_set_link++);
		}

		tree_family_node_control_del_family_member(b_tree, parent, location_brother);				/* Delete the node_brother from parent */
		tree_family_control_destroy_node(b_tree, &node_brother);									/* Destroy the node_brother */

		return parent;
	}
}