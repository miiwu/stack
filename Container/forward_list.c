/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "forward_list.h"

#include "container_pte_def.h"

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
 * @brief This array will contain all the universal forward_list functions address.
 */

void *forward_list_function_address_tables[] =
{
	(void *)&forward_list_control_configuration_init,										/* No.0 : initialize */

	(void *)&list_family_control_configuration_destroy,										/* No.1 : destroy */

	(void *)&list_family_control_element_access_at,											/* No.3 : at */

	(void *)&list_family_control_capacity_empty,											/* No.4 : empty */

	(void *)&list_family_control_capacity_size,												/* No.5 : size */

	(void *)&list_family_control_capacity_max_size,											/* No.6 : max_size */

	(void *)&list_family_control_modifiers_insert_after,									/* No.7 : insert */

	(void *)&list_family_control_modifiers_erase_after,										/* No.8 : erase */

	(void *)&list_family_control_modifiers_swap,											/* No.9 : swap */

	(void *)&list_family_control_modifiers_copy,											/* No.10 : copy */

	(void *)&list_family_control_list_operations_sort,										/* No.11 : sort */
};

#if (FORWARD_LIST_CFG_INTEGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This struct will control all the forward_list functions conveniently.
 */

struct forward_list_control_s forward_list_ctrl = {
	{
		forward_list_control_configuration_init,
		list_family_control_configuration_destroy,
		list_family_control_configuration_element_handler,
		list_family_control_configuration_exception,
	},
	{
		NULL
	},
	{
		list_family_control_element_access_front,
	},
	{
		list_family_control_capacity_empty,
		list_family_control_capacity_max_size,
		list_family_control_capacity_size,
	},
	{
		list_family_control_modifiers_clear,
		list_family_control_modifiers_insert_after,
		list_family_control_modifiers_emplace_after,
		list_family_control_modifiers_erase_after,
		list_family_control_modifiers_push_front,
		list_family_control_modifiers_emplace_front,
		list_family_control_modifiers_pop_front,
		list_family_control_modifiers_resize,
		list_family_control_modifiers_swap,
		list_family_control_modifiers_copy,
	},
	{
		list_family_control_list_operations_merge,
		list_family_control_list_operations_splice_after,
		list_family_control_list_operations_remove,
		list_family_control_list_operations_remove_if,
		list_family_control_list_operations_reverse,
		list_family_control_list_operations_unique,
		list_family_control_list_operations_sort,
	}
};

#endif

void *forward_list_control_list_operations_remove_value = NULL;

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will switch the list-family control.
 *
 * @param void
 *
 * @return void
 */

void forward_list_control_switch_control(void *arg_list);

/**
* @brief This function will get the node at the specified location in the container.
*
* @param forward_list the pointer to the forward list struct pointer
* @param position the position of node,it would be equal or greater than zero
*
* @return the node at the specified location in the container
*/

void *forward_list_control_get_node(forward_list_stp forward_list,
									container_size_t position);

/**
 * @brief This function will set the node at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param node the pointer to the forward list node struct pointer
 * @param position the position of node
 *
 * @return NONE
 */

void *forward_list_control_set_node(forward_list_stp forward_list,
									container_size_t position, struct forward_list_node_s *node);

/**
 * @brief This function will delete the node at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *forward_list_control_del_node(forward_list_stp forward_list,
									container_size_t position);

 /**
  * @brief This function will swap the node at the specified location in the container
  *			by the stable bubble swap algorithm.
  *
  * @param forward_list the pointer to the forward list struct pointer
  * @param position the position of node,it would be equal or greater than zero
  *
  * @return NONE
  */

void forward_list_control_swap_node(forward_list_stp forward_list,
									container_size_t dst_pos,
									container_size_t src_pos);

/*
*********************************************************************************************************
*					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
*********************************************************************************************************
*/

/**
 * @brief This struct will record the list's node operators.
 */

struct node_operator_s forward_list_control_node_operator = {
	forward_list_control_get_node,
	forward_list_control_set_node,
	forward_list_control_del_node,
	forward_list_control_swap_node,
};

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will switch the list-family control.
 *
 * @param void
 *
 * @return void
 */

void forward_list_control_switch_control(void *arg_list)
{
	list_family_control_get_control(LIST_FAMILY_LIST, forward_list_control_node_operator);
}

/**
 * @brief This function will initialize the forward_list struct
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param element_size the element memory size of the forward list struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

errno_t  forward_list_control_configuration_init(forward_list_stpp forward_list,
												 container_size_t element_size,
												 generic_type_element_assign_t assign,
												 generic_type_element_free_t free)
{
	assert(forward_list);
	assert(0 <= element_size);

	return list_family_control_configuration_init(forward_list, forward_list_control_switch_control,
												  FORWARD_LIST_CFG_ALLOCATOR_TYPE, element_size, assign, free);
}

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *forward_list_control_get_node(forward_list_stp forward_list,
									container_size_t position)
{
	assert(forward_list);
	assert((0 <= position));

	if (forward_list->info.max_size <= position ||
		0 > position) {
		return NULL;
	}

	struct forward_list_node_s
		**current_node = (struct forward_list_node_s **) & forward_list->element_ptr;

	container_size_t
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
 * @brief This function will set the node at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param node the pointer to the forward list node struct pointer
 * @param position the position of node
 *
 * @return NONE
 */

void *forward_list_control_set_node(forward_list_stp forward_list,
									container_size_t position, struct forward_list_node_s *node)
{
	assert(forward_list);
	assert((0 <= position));

	if (forward_list->info.max_size <= position ||
		0 > position) {
		return NULL;
	}

	if (NULL == node) {
		node = list_family_control_init_node(forward_list);

		if (NULL == node) {
			return NULL;
		}
	}

	struct forward_list_node_s
		*node_prev = NULL;

	node->next = forward_list_control_get_node(forward_list, position);				/* Merge the node that in forward_list position to node */

	node_prev = forward_list_control_get_node(forward_list, position - 1);

	if (NULL == node_prev) {														/* If the previous node is NULL,the node must be the head. */
		forward_list->element_ptr = node;
	} else {
		node_prev->next = node;
	}

	forward_list->info.size++;

	return node;
}

/**
 * @brief This function will delete the node at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *forward_list_control_del_node(forward_list_stp forward_list,
									container_size_t position)
{
	assert(forward_list);
	assert((0 <= position));

	struct forward_list_node_s
		*node_del = forward_list_control_get_node(forward_list, position),
		*node_prev = forward_list_control_get_node(forward_list, position - 1);

	if (forward_list->info.max_size <= position ||
		0 > position ||
		NULL == node_del ||
		((0 < position - 1) ?
		(false) :
		 (NULL == node_prev))) {
		return NULL;
	}

	if (NULL != node_prev) {
		node_prev->next = node_del->next;
	} else {
		forward_list->element_ptr = node_del->next;
	}

	forward_list->info.size--;

	return node_del;
}

/**
 * @brief This function will swap the node at the specified location in the container
 *			by the stable bubble swap algorithm.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void forward_list_control_swap_node(forward_list_stp forward_list,
									container_size_t dst_pos,
									container_size_t src_pos)
{
	assert(forward_list);

	if (forward_list->info.size <= dst_pos ||
		forward_list->info.size <= src_pos) {
		return;
	}

	if (dst_pos > src_pos) {
		container_size_t tmp = dst_pos;

		dst_pos = src_pos;
		src_pos = tmp;
	}

	struct forward_list_node_s
		*node_dst = forward_list_control_get_node(forward_list, dst_pos),
		*node_dst_prev = forward_list_control_get_node(forward_list, dst_pos - 1),
		*node_dst_next = node_dst->next,
		*node_src = forward_list_control_get_node(forward_list, src_pos),
		*node_src_prev = forward_list_control_get_node(forward_list, src_pos - 1),
		*node_src_next = node_src->next;

	if ((size_t)node_src != (size_t)node_dst_next) {
		node_src->next = node_dst_next;
	}

	if (NULL != node_dst_prev) {
		node_dst_prev->next = node_src;
	} else {
		forward_list->element_ptr = node_src;
	}

	if ((size_t)node_dst != (size_t)node_src_prev) {
		node_src_prev->next = node_dst;
	} else {
		node_src->next = node_dst;
	}

	node_dst->next = node_src_next;
}