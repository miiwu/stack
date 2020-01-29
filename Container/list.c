/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "list.h"

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

/**
 * @brief This array will contain all the universal list functions address.
 */

void *list_function_address_tables[] =
{
	(void *)&list_control_configuration_init,							/* No.0 : initialize */

	(void *)&list_like_control_configuration_destroy,						/* No.1 : destroy */

	(void *)&list_like_control_element_access_at,							/* No.3 : at */

	(void *)&list_like_control_capacity_empty,								/* No.4 : empty */

	(void *)&list_like_control_capacity_size,								/* No.5 : size */

	(void *)&list_like_control_capacity_max_size,							/* No.6 : max_size */

	(void *)&list_like_control_modifiers_insert_after,						/* No.7 : insert */

	(void *)&list_like_control_modifiers_erase_after,						/* No.8 : erase */

	(void *)&list_like_control_modifiers_swap,								/* No.9 : swap */

	(void *)&list_like_control_modifiers_copy,								/* No.10 : copy */
};

#if (LIST_CFG_INTERGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This struct will control all the list functions conveniently.
 */

struct list_like_control_t list_ctrl = {
	{
		list_control_configuration_init,
		list_like_control_configuration_destroy,
		list_like_control_configuration_element_handler,
		list_like_control_configuration_exception,
	},
	{
		NULL
	},
	{
		list_like_control_element_access_front,
		list_like_control_element_access_at,
	},
	{
		list_like_control_capacity_empty,
		list_like_control_capacity_max_size,
		list_like_control_capacity_size,
	},
	{
		list_like_control_modifiers_clear,
		list_like_control_modifiers_insert_after,
		list_like_control_modifiers_emplace_after,
		list_like_control_modifiers_erase_after,
		list_like_control_modifiers_push_front,
		list_like_control_modifiers_emplace_front,
		list_like_control_modifiers_pop_front,
		list_like_control_modifiers_resize,
		list_like_control_modifiers_swap,
		list_like_control_modifiers_copy,
	},
	{
		list_like_control_list_operations_merge,
		list_like_control_list_operations_splice_after,
		list_like_control_list_operations_remove,
		list_like_control_list_operations_remove_if,
		list_like_control_list_operations_reverse,
		list_like_control_list_operations_unique,
		list_like_control_list_operations_sort,
	}
};

#endif

/**
 * @brief This variables will record the list_operations_remove's value.
 */

void *list_control_list_operations_remove_value = NULL;

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

void list_control_shared_pack_analysis(void);

/**
 * @brief This function will set the node at the specified location in the container.
 *
 * @param list the pointer to the list struct pointer
 * @param node the pointer to the list node struct pointer
 * @param position the position of node
 *
 * @return NONE
 */

void *list_control_set_node(LIST_TYPEDEF_PTR list,
							CONTAINER_GLOBAL_CFG_SIZE_TYPE position, struct list_node_t *node);

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param list the pointer to the list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return the node at the specified location in the container
 */

void *list_control_get_node(LIST_TYPEDEF_PTR list,
							CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
 * @brief This function will delete the node at the specified location in the container.
 *
 * @param list the pointer to the list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *list_control_del_node(LIST_TYPEDEF_PTR list,
							CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
 * @brief This function will swap the node at the specified location in the container
 *			by the stable bubble swap algorithm.
 *
 * @param list the pointer to the list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void list_control_swap_node(LIST_TYPEDEF_PTR list,
							CONTAINER_GLOBAL_CFG_SIZE_TYPE dst_pos,
							CONTAINER_GLOBAL_CFG_SIZE_TYPE src_pos);

/*
*********************************************************************************************************
*					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
*********************************************************************************************************
*/

/**
 * @brief This struct will record the list's node operators.
 */

struct node_operator_t list_control_node_operator = {
	list_control_get_node,
	list_control_set_node,
	list_control_del_node,
	list_control_swap_node,
};

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the list struct
 *
 * @param list the pointer to the list struct pointer
 * @param element_size the element memory size of the list struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void list_control_configuration_init(LIST_TYPEDEF_PPTR list,
									 CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
									 void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(list);
	assert(0 <= element_size);

	list_like_control_configuration_init(list, list_control_shared_pack_analysis,
										 LIST_CFG_ALLOCATOR_TYPE, element_size, assign, free);
}

/**
 * @brief This function will analysis the shared pack.
 *
 * @param void
 *
 * @return void
 */

void list_control_shared_pack_analysis(void)
{
	list_like_control_get_list_control(LIST_LIKE_TYPE_LIST, list_control_node_operator);
}

/**
 * @brief This function will set the node at the specified location in the container.
 *
 * @param list the pointer to the list struct pointer
 * @param node the pointer to the list node struct pointer
 * @param position the position of node
 *
 * @return NONE
 */

void *list_control_set_node(LIST_TYPEDEF_PTR list,
							CONTAINER_GLOBAL_CFG_SIZE_TYPE position, struct list_node_t *node)
{
	assert(list);
	assert((0 <= position));

	if (list->info.max_size <= position ||
		0 > position) {
		return NULL;
	}

	if (NULL == node &&
		NULL == (node = list_like_control_init_node(list))) {
		return NULL;
	}

	struct list_node_t
		*node_prev = list_control_get_node(list, position - 1),
		*node_next = list_control_get_node(list, position);

	if (NULL != node_prev) {
		node_prev->next = node;					/* Recover the previous node's link */
	} else {
		list->node = node;
	}

	if (NULL != node_next) {
		node_next->prev = node;					/* Recover the next node's link */
	}

	node->prev = node_prev;						/* Merge the node that in list position to node */

	node->next = node_next;

	list->info.size++;

	return node;
}

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param list the pointer to the list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *list_control_get_node(LIST_TYPEDEF_PTR list,
							CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(list);
	assert((0 <= position));

	if (list->info.max_size <= position ||
		0 > position) {
		return NULL;
	}

	struct list_node_t
		**current_node = (struct list_node_t **)&list->node;

	CONTAINER_GLOBAL_CFG_SIZE_TYPE
		currrent_position = 0;

LOOP:

	if (NULL == current_node ||
		NULL == *current_node ||
		currrent_position >= position) {
		return *current_node;
	}

	current_node = &(*current_node)->next;

	currrent_position++;

	goto LOOP;
}

/**
 * @brief This function will delete the node at the specified location in the container.
 *
 * @param list the pointer to the list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *list_control_del_node(LIST_TYPEDEF_PTR list,
							CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(list);
	assert((0 <= position));

	struct list_node_t
		*node_del = list_control_get_node(list, position);

	if (list->info.max_size <= position ||
		0 > position ||
		NULL == node_del) {
		return NULL;
	}

	if (NULL != node_del->prev) {
		node_del->prev->next = node_del->next;			/* Recover the previous node's link */
	} else {
		list->node = node_del->next;
	}

	if (NULL != node_del->next) {
		node_del->next->prev = node_del->prev;			/* Recover the next node's link */
	}

	list->info.size--;

	node_del->prev = NULL;
	node_del->next = NULL;

	return node_del;
}

/**
 * @brief This function will swap the node at the specified location in the container.
 *
 * @param list the pointer to the list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void list_control_swap_node(LIST_TYPEDEF_PTR list,
							CONTAINER_GLOBAL_CFG_SIZE_TYPE lhs_pos,
							CONTAINER_GLOBAL_CFG_SIZE_TYPE rhs_pos)
{
	assert(list);

	if (list->info.size <= lhs_pos ||
		list->info.size <= rhs_pos) {
		return;
	}

	if (lhs_pos > rhs_pos) {
		CONTAINER_GLOBAL_CFG_SIZE_TYPE tmp = lhs_pos;

		lhs_pos = rhs_pos;
		rhs_pos = tmp;
	}

	struct list_node_t
		*node_lhs = list_control_get_node(list, lhs_pos),
		*node_lhs_prev = node_lhs->prev,
		*node_lhs_next = node_lhs->next,
		*node_rhs = list_control_get_node(list, rhs_pos),
		*node_rhs_prev = node_rhs->prev,
		*node_rhs_next = node_rhs->next;

	if (NULL != node_lhs_prev) {
		node_lhs_prev->next = node_rhs;
	} else {
		list->node = node_rhs;
	}

	if (NULL != node_rhs_next) {
		node_rhs_next->prev = node_lhs;
	}

	node_rhs->prev = node_lhs_prev;
	node_lhs->next = node_rhs_next;

	if ((size_t)node_lhs == (size_t)node_rhs_prev ||
		(size_t)node_rhs == (size_t)node_lhs_next) {
		node_rhs->next = node_lhs;
		node_lhs->prev = node_rhs;
	} else {
		node_rhs->next = node_lhs_next;
		node_lhs->prev = node_rhs_prev;

		node_rhs_prev->next = node_lhs;
		node_lhs_next->prev = node_rhs;
	}
}