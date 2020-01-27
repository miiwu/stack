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

/**
 * @brief This struct is the list structure module
 */

struct list_node_t {
	/* @brief This variables will pointer to the previous list node.										*/
	struct list_node_t *prev;

	/* @brief This variables will point to the address of the list data memory block.					*/
	void *data;

	/* @brief This variables will pointer to the next list node.										*/
	struct list_node_t *next;
};

/**
 * @brief This struct is the list structure module
 */

struct list_t {
	/* @brief RESERVED This variables will record the identity code of container type.					*/
	enum container_type	container_type_id;

	struct {
		/* @brief This variables will record the maximum number of elements.							*/
		CONTAINER_GLOBAL_CFG_SIZE_TYPE max_size;

		/* @brief This variables will record the number of elements that
				  the container has currently allocated space for.										*/
		CONTAINER_GLOBAL_CFG_SIZE_TYPE size;

		/* @brief This variables will record the size that each element will take up.					*/
		CONTAINER_GLOBAL_CFG_SIZE_TYPE mem_size;
	}info;

	/* @brief This variables will point to the allocator.												*/
	void *allocator;

	/* @brief This variables will point to the allocator control.										*/
	struct allocator_control_t *allocator_ctrl;

	/* @brief This variables will pointer to the first list node.										*/
	struct list_node_t *node;

	/* @brief This variables will record the element handler of the container.							*/
	struct element_handler_t element_handler;

	struct {
		/* @brief This variables will point to the address of the list empty exception handler.		*/
		void (*empty)(void);

		/* @brief This variables will point to the address of the list full exception handler.			*/
		void (*full)(void);
	}exception;
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

/**
 * @brief This array will contain all the universal list functions address.
 */

void *list_function_address_tables[] =
{
	(void *)&list_control_configuration_init,							/* No.0 : initialize */

	(void *)&list_control_configuration_destroy,						/* No.1 : destroy */

	(void *)&list_control_element_access_at,							/* No.3 : at */

	(void *)&list_control_capacity_empty,								/* No.4 : empty */

	(void *)&list_control_capacity_size,								/* No.5 : size */

	(void *)&list_control_capacity_max_size,							/* No.6 : max_size */

	(void *)&list_control_modifiers_insert_after,						/* No.7 : insert */

	(void *)&list_control_modifiers_erase_after,						/* No.8 : erase */

	(void *)&list_control_modifiers_swap,								/* No.9 : swap */

	(void *)&list_control_modifiers_copy,								/* No.10 : copy */
};

#if (LIST_CFG_INTERGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This struct will control all the list functions conveniently.
 */

struct list_control_t list_ctrl = {
	{
		list_control_configuration_init,
		list_control_configuration_destroy,
		list_control_configuration_element_handler,
		list_control_configuration_exception,
	},
	{
		NULL
	},
	{
		list_control_element_access_front,
	},
	{
		list_control_capacity_empty,
		list_control_capacity_max_size,
		list_control_capacity_size,
	},
	{
		list_control_modifiers_clear,
		list_control_modifiers_insert_after,
		list_control_modifiers_emplace_after,
		list_control_modifiers_erase_after,
		list_control_modifiers_push_front,
		list_control_modifiers_emplace_front,
		list_control_modifiers_pop_front,
		list_control_modifiers_resize,
		list_control_modifiers_swap,
		list_control_modifiers_copy,
	},
	{
		list_control_list_operations_merge,
		list_control_list_operations_splice_after,
		list_control_list_operations_remove,
		list_control_list_operations_remove_if,
		list_control_list_operations_reverse,
		list_control_list_operations_unique,
		list_control_list_operations_sort,
	}
};

#endif

void *list_control_list_operations_remove_value = NULL;

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the list node struct.
 *
 * @param list the pointer to the list struct pointer
 *
 * @return NONE
 */

struct list_node_t *list_control_init_node(LIST_TYPEDEF_PTR list);

/**
 * @brief This function will destroy list node struct and free the space.
 *
 * @param list the pointer to the list struct pointer
 * @param node the pointer to the list node struct pointer
 *
 * @return NONE
 */

void list_control_destroy_node(LIST_TYPEDEF_PTR list,
							   struct list_node_t *node);

/**
 * @brief This function will set the node at the specified location in the container.
 *
 * @param list the pointer to the list struct pointer
 * @param node the pointer to the list node struct pointer
 * @param position the position of node
 *
 * @return NONE
 */

struct list_node_t *list_control_set_node(LIST_TYPEDEF_PTR list,
	CONTAINER_GLOBAL_CFG_SIZE_TYPE position, struct list_node_t *node);

/**
* @brief This function will get the node at the specified location in the container.
*
* @param list the pointer to the list struct pointer
* @param position the position of node,it would be equal or greater than zero
*
* @return the node at the specified location in the container
*/

struct list_node_t *list_control_get_node(LIST_TYPEDEF_PTR list,
	CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
 * @brief This function will delete the node at the specified location in the container.
 *
 * @param list the pointer to the list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

struct list_node_t *list_control_del_node(LIST_TYPEDEF_PTR list,
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

/**
* @brief This function will set elements at the specified location in the container.
*
* @param list the pointer to the list struct pointer
* @param position the position of element,it would be equal or greater than zero
* @param source pointer to the source
*
* @return NONE
*/

void list_node_control_set_data(LIST_TYPEDEF_PTR list,
								CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *source);

/**
* @brief This function will get elements at the specified location node in the container.
*
* @param list the pointer to the list struct pointer
* @param position the position of element,it would be equal or greater than zero
* @param destination pointer to the destination
*
* @return NONE
*/

void *list_node_control_get_data(LIST_TYPEDEF_PTR list,
								 CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
* @brief This function will delete elements at the specified location node in the container.
*
* @param list the pointer to the list struct pointer
* @param position the position of element,it would be equal or greater than zero
*
* @return NONE
*/

void list_node_control_del_data(LIST_TYPEDEF_PTR list,
								CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
* @brief This function will control the remove run under the rule of remove_if.
*
* @param data the pointer to the data list will give
*
* @return if the data match the rule
*	- true	yes
*	- false	no
*/

bool list_control_remove_rule(void *data);

/**
* @brief This function will compare if the left-hand-side lesser than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side lesser than the right-hand-side
*	- true	yes
*	- false	no
*/

bool list_control_default_sort_comp_lesser(void *lhs, void *rhs, size_t len);

/**
* @brief This function will compare if the left-hand-side greater than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side greater than the right-hand-side
*	- true	yes
*	- false	no
*/

bool list_control_default_sort_comp_greater(void *lhs, void *rhs, size_t len);

/**
* @brief This function will compare if the left-hand-side equal with the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side equal with the right-hand-side
*	- true	yes
*	- false	no
*/

bool list_control_default_sort_comp_equal(void *lhs, void *rhs, size_t len);

/**
* @brief This function will callback the handler that container has no elements when the container temp to insert.
*
* @param NODE
*
* @return NONE
*/

void list_control_configration_exception_default_empty_callback(void);

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param NODE
 *
 * @return NONE
 */

void list_control_configration_exception_default_full_callback(void);

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

	void
		*allocator = NULL;

	struct allocator_control_t
		*allocator_ctrl = NULL;

	allocator_ctrl = allocator_control_convert_type_to_func_addr_table(LIST_CFG_ALLOCATOR_TYPE);	/* Variables pointer to	the function address table of
																															specified container type		*/

	allocator_ctrl->configration.init(&allocator, NULL);

	struct list_t
		*list_alloced = (struct list_t *)allocator_ctrl->allocate(allocator,
																  1, sizeof(struct list_t));	/* Allocate #1 */

	if (NULL == list ||																	/* Check if list point to NULL			*/
		NULL == list_alloced) {															/* Check if list_alloced point to NULL	*/
		return;
	}

	list_alloced->container_type_id = LIST;												/* Assign list structure					*/

	list_alloced->info.max_size = LIST_CFG_DEFAULT_MAX_SIZE;
	list_alloced->info.size = 0u;
	list_alloced->info.mem_size = element_size;

	list_alloced->allocator = allocator;
	list_alloced->allocator_ctrl = allocator_ctrl;

	list_alloced->node = NULL;

	list_alloced->element_handler.assign = NULL;
	list_alloced->element_handler.free = NULL;

	list_alloced->exception.empty = list_control_configration_exception_default_empty_callback;
	list_alloced->exception.full = list_control_configration_exception_default_full_callback;

	if (NULL != assign &&																	/* Check if assign point to NULL			*/
		NULL != free) {																		/* Check if free point to NULL				*/
		list_alloced->element_handler.assign = assign;
		list_alloced->element_handler.free = free;
	}

	*list = list_alloced;

	#if (VECTOR_CFG_DEBUG_EN)												/* Debug only								*/

	printf("list.configuration.init:allocator : %p \r\n", allocator);
	printf("list.configuration.init:list block : %p \r\n", list_alloced);

	#endif // (VECTOR_CFG_DEBUG_EN)
}

/**
 * @brief This function will destroy the list struct and free the space
 *
 * @param list the pointer to the list struct pointer
 *
 * @return NONE
 */

void list_control_configuration_destroy(LIST_TYPEDEF_PPTR list)
{
	assert(list);

	void
		*allocator = (*list)->allocator;

	struct allocator_control_t
		*allocator_ctrl = (*list)->allocator_ctrl;

	#if (VECTOR_CFG_DEBUG_EN)

	printf("list.configuration.destroy:allocator : %p \r\n", allocator);
	printf("list.configuration.destroy:list block : %p \r\n", (*list));
	printf("list.configuration.destroy:list node block : %p \r\n", (*list)->node);

	#endif // (VECTOR_CFG_DEBUG_EN)

	if (0 < (*list)->info.size) {
		struct list_node_t
			*node = (*list)->node,
			*node_next = node->next;

		for (size_t cnt = 0; cnt < (*list)->info.size; cnt++) {
			node_next = node->next;

			list_control_destroy_node((*list), node);

			node = node_next;
		}
	}

	(*list)->container_type_id = 0u;														/* Assign list structure					*/

	(*list)->info.max_size = 0u;
	(*list)->info.size = 0u;
	(*list)->info.mem_size = 0u;

	(*list)->allocator = NULL;

	(*list)->node = NULL;

	(*list)->exception.empty = NULL;
	(*list)->exception.full = NULL;

	allocator_ctrl->deallocate(allocator, *list, 1);																			/* deallocate #1 */

	allocator_ctrl->configration.destroy(&allocator);

	*list = NULL;
}

/**
 * @brief This function will configure the list element handler
 *
 * @param list the pointer to the list struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void list_control_configuration_element_handler(LIST_TYPEDEF_PTR list,
												void (*assign)(void *dst, void *src), void(*free)(void *dst))
{
	assert(list);
	assert(assign);
	assert(free);

	list->element_handler.assign = assign;
	list->element_handler.free = free;
}

/**
 * @brief This function will configure the list exception callback
 *
 * @param list the pointer to the list struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void list_control_configuration_exception(LIST_TYPEDEF_PTR list,
										  void (*empty)(void), void (*full)(void))
{
	assert(list);

	if (NULL == empty) {
		list->exception.empty = empty;
	}

	if (NULL == full) {
		list->exception.full = full;
	}
}

/**
 * @brief This function will returns a reference to the first element in the container
 *
 * @param list the pointer to the list struct pointer
 *
 * @return the reference to the first element in the container
 */

void *list_control_element_access_front(LIST_TYPEDEF_PTR list)
{
	assert(list);

	return list_node_control_get_data(list, 0);
}

/**
 * @brief This function will returns a reference to the specified element in the container.
 *
 * @param list the pointer to the list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *list_control_element_access_at(LIST_TYPEDEF_PTR list,
									 CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(list);

	return list_node_control_get_data(list, position);
}

/**
 * @brief This function will checks if the container has no elements
 *
 * @param list the pointer to the list struct pointer
 *
 * @return
	- true,the container has no elements
	- false,the container has elements
 */

inline bool list_control_capacity_empty(LIST_TYPEDEF_PTR list)
{
	assert(list);

	if (list->info.max_size <= list->info.size) {
		return true;
	} else {
		return false;
	}
}

/**
 * @brief This function will returns the maximum number of elements the container
			is able to hold due to system or library implementation limitations
 *
 * @param list the pointer to the list struct pointer
 *
 * @return the maximum number of elements
 */

inline CONTAINER_GLOBAL_CFG_SIZE_TYPE list_control_capacity_max_size(LIST_TYPEDEF_PTR list)
{
	assert(list);

	return list->info.max_size;
}

/**
 * @brief This function will returns the number of elements in the container
 *
 * @param list the pointer to the list struct pointer
 *
 * @return the number of elements in the container
 */

inline CONTAINER_GLOBAL_CFG_SIZE_TYPE list_control_capacity_size(LIST_TYPEDEF_PTR list)
{
	assert(list);

	return list->info.size;
}

/**
 * @brief This function will erases all elements from the container
 *
 * @param list the pointer to the list struct pointer
 *
 * @return NONE
 */

void list_control_modifiers_clear(LIST_TYPEDEF_PTR list)
{
	assert(list);

	for (size_t cnt = list->info.size; cnt > 0; cnt--) {
		list_control_modifiers_erase_after(list, 0);
	}
}

/**
 * @brief This function will inserts elements after the specified position in the container
 *
 * @param list the pointer to the list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param amount the amount of the source
 * @param source pointer to the source
 *
 * @return NONE
 */

void list_control_modifiers_insert_after(LIST_TYPEDEF_PTR list,
										 CONTAINER_GLOBAL_CFG_SIZE_TYPE position,
										 CONTAINER_GLOBAL_CFG_SIZE_TYPE amount, void **source)
{
	assert(list);
	assert(0 <= position);
	assert(0 < amount);
	assert(source);
	assert(*source);

	void
		*source_addr = NULL;

	CONTAINER_GLOBAL_CFG_SIZE_TYPE
		pos_insert_head = list->info.size,
		pos_insert_tail = position + amount;

ENSURE_THE_LIST_HAS_ENOUGH_NODE:

	if (pos_insert_tail > pos_insert_head) {												/* Ensure the list has enough node */
		for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = pos_insert_head; pos < pos_insert_tail; pos++) {
			list_control_set_node(list, pos_insert_head, NULL);
		}
	}

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = position; pos < pos_insert_tail; pos++) {		/* Set the data to the list node */
		source_addr = (void *)((size_t)*source + (pos - position) * list->info.mem_size);

		if ('\0' != *(char *)list_node_control_get_data(list, pos)) {			/* Ensure the list node has no data */
			pos_insert_head = position;

			goto ENSURE_THE_LIST_HAS_ENOUGH_NODE;
		}

		#if (VECTOR_CFG_DEBUG_EN)

		printf("list.modifiers.insert_after:No.%d:\"%s\" \r\n", pos, (char *)source_addr);

		#endif // (VECTOR_CFG_DEBUG_EN)

		list_node_control_set_data(list, pos, source_addr);
	}
}

/**
 * @brief This function will push a new element on top of the stack, and the element is constructed in-place
 *
 * @param list the pointer to the list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void list_control_modifiers_emplace_after(LIST_TYPEDEF_PTR stack,
										  CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
}

/**
 * @brief This function will erases the specified elements from the container
 *
 * @param list the pointer to the list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void list_control_modifiers_erase_after(LIST_TYPEDEF_PTR list,
										CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(list);
	assert(0 <= position);

	#if (LIST_CFG_DEBUG_EN)

	printf("list.modifiers.earse_after no.%d: \" %s \" \r\n",
		   position, (char *)list_node_control_get_data(list, position));

	#endif // (LIST_CFG_DEBUG_EN)

	list_node_control_del_data(list, position);
}

/**
 * @brief This function will prepends the given element value to the beginning of the container
 *
 * @param list the pointer to the list struct pointer
 * @param source pointer to the source
 *
 * @return NONE
 */

void list_control_modifiers_push_front(LIST_TYPEDEF_PTR list,
									   void *source)
{
	assert(list);

	struct list_node_t
		*node_tmp = list_control_init_node(list);						/* Initialize a new node */

	node_tmp->next = list_control_get_node(list, 0);

	list->node = node_tmp;

	list_node_control_set_data(list, 0, source);

	list->info.size++;
}

/**
 * @brief This function will Inserts a new element to the beginning of the container.
			The element is constructed through std::allocator_traits::construct,
			which typically uses placement-new to construct the element in-place
			at the location provided by the container.
			The arguments args... are forwarded to the constructor as std::forward<Args>(args)....
 *
 * @param list the pointer to the list struct pointer
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void list_control_modifiers_emplace_front(LIST_TYPEDEF_PTR stack,
										  void *destination)
{
}

/**
 * @brief This function will removes the first element of the container
 *
 * @param list the pointer to the list struct pointer
 *
 * @return NONE
 */

void list_control_modifiers_pop_front(LIST_TYPEDEF_PTR list)
{
	assert(list);

	list_node_control_del_data(list, 0);
}

/**
 * @brief This function will increase the capacity of the list to a size
			that's greater or equal to new_cap
 *
 * @param list the pointer to the list struct pointer
 * @param size the size of the list struct
 *
 * @return NONE
 */

void list_control_modifiers_resize(LIST_TYPEDEF_PPTR list,
								   CONTAINER_GLOBAL_CFG_SIZE_TYPE size)
{
}

/**
 * @brief This function will exchanges the contents of the container with those of other
 *
 * @param list the pointer to the list struct pointer
 * @param other the pointer to the other list struct pointer
 *
 * @return NONE
 */

void list_control_modifiers_swap(LIST_TYPEDEF_PPTR list,
								 LIST_TYPEDEF_PPTR other)
{
	assert(list);
	assert(other);

	LIST_TYPEDEF_PPTR
		list_swap = (*list)->allocator_ctrl->allocate((*list)->allocator, 1, sizeof(void *));

	*(list_swap) = *list;
	*(list_swap + 1) = *other;

	*list = *(list_swap + 1);
	*other = *list_swap;
}

/**
 * @brief This function will copy the contents of the container to those of other
 *
 * @param destination the pointer to the destination list struct pointer
 * @param source the pointer to the source list struct
 *
 * @return NONE
 */

void list_control_modifiers_copy(LIST_TYPEDEF_PPTR destination,
								 LIST_TYPEDEF_PTR source)
{
	assert(destination);
	assert(source);

	struct list_node_t
		*node_source = (void *)(size_t)(source->node);

	if (NULL == (*destination) ||
		NULL == (*destination)->allocator ||
		NULL == (*destination)->allocator_ctrl ||
		NULL == (*destination)->node) {																	/* Check if destination have been initialized */
		list_control_configuration_init(destination,													/* if not,then initialize it */
										source->info.mem_size, source->element_handler.assign, source->element_handler.free);
	} else {
		(*destination)->info = source->info;															/* if so,just assign */
		(*destination)->element_handler = source->element_handler;
		(*destination)->exception = source->exception;
	}

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = 0; pos < source->info.size; pos++) {
		list_node_control_set_data(*destination, pos, list_node_control_get_data(source, pos));
	}
}

/**
 * @brief This function will merges two sorted lists into one
 *
 * @param destination the pointer to the destination list struct pointer
 * @param source the pointer to the source list struct
 *
 * @return NONE
 */

void list_control_list_operations_merge(LIST_TYPEDEF_PTR destination,
										LIST_TYPEDEF_PTR other)
{
	assert(destination);
	assert(other);

	//list_control_list_operations_sort(destination, NULL);
	//list_control_list_operations_sort(other, NULL);

	list_control_list_operations_splice_after(destination, 0, other, 0, other->info.size);
}

/**
 * @brief This function will moves elements from another list to list
 *
 * @param destination the pointer to the destination list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param other the pointer to the other list struct
 *
 * @return NONE
 */

void list_control_list_operations_splice_after(LIST_TYPEDEF_PTR list,
											   CONTAINER_GLOBAL_CFG_SIZE_TYPE position,
											   LIST_TYPEDEF_PTR other,
											   CONTAINER_GLOBAL_CFG_SIZE_TYPE first,
											   CONTAINER_GLOBAL_CFG_SIZE_TYPE last)
{
	assert(list);
	assert(other);

	struct list_node_t
		*node_other = list_control_get_node(other, first),
		*node_next_other = NULL;

	CONTAINER_GLOBAL_CFG_SIZE_TYPE
		pos_tail_splice = position + last - first;

	if (NULL == node_other) {
		return;
	}

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = position; pos < pos_tail_splice; pos++) {
		#if (LIST_CFG_DEBUG_EN)

		printf("list.list_operatons.splice_after.source data no.%d:\"%s\" \r\n",
			   pos, (char *)node_other->data);

		#endif // (LIST_CFG_DEBUG_EN)

		node_next_other = node_other->next;

		node_other = list_control_del_node(other, first);

		list_control_set_node(list, pos, node_other);

		node_other = node_next_other;
	}
}

/**
 * @brief This function will removes all elements satisfying specific criteria
 *
 * @param destination the pointer to the destination list struct pointer
 * @param data the pointer of data
 *
 * @return NONE
 */

void list_control_list_operations_remove(LIST_TYPEDEF_PTR list,
										 void *value)
{
	assert(list);
	assert(value);

	list_control_list_operations_remove_value = value;

	list_control_list_operations_remove_if(list, list_control_remove_rule);
}

/**
 * @brief This function will
 *
 * @param destination the pointer to the destination list struct pointer
 * @param rule the pointer to the rule-making function
 *
 * @return NONE
 */

void list_control_list_operations_remove_if(LIST_TYPEDEF_PTR list, bool (*rule)(void *data))
{
	assert(list);
	assert(rule);

	CONTAINER_GLOBAL_CFG_SIZE_TYPE
		cnt_reomve = 0,
		*pos_remove = list->allocator_ctrl->allocate(list->allocator, list->info.size, sizeof(CONTAINER_GLOBAL_CFG_SIZE_TYPE));

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = 0; pos < list->info.size; pos++) {	/* Get which node's data is match */
		if (rule(list_node_control_get_data(list, pos))) {
			*(pos_remove + cnt_reomve++) = pos;
		}
	}

	struct  list_node_t
		*node_del = NULL;

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE cnt = 0; cnt < cnt_reomve; cnt++) {					/* Delete nodes matched */
		#if (LIST_CFG_DEBUG_EN)

		printf("list.list_operatons.remove_if.no.%d: \"%s\" \r\n",
			   *(pos_remove + cnt), (char *)list_node_control_get_data(list, *(pos_remove + cnt) - cnt));

		#endif // (LIST_CFG_DEBUG_EN)

		list_node_control_del_data(list, *(pos_remove + cnt) - cnt);
	}

	list->allocator_ctrl->deallocate(list->allocator, pos_remove, list->info.size);
}

/**
 * @brief This function will reverses the order of the elements in the container
 *
 * @param destination the pointer to the destination list struct pointer
 *
 * @return NONE
 */

void list_control_list_operations_reverse(LIST_TYPEDEF_PTR list)
{
	assert(list);

	struct  list_node_t
		*node_reverse = NULL;

	CONTAINER_GLOBAL_CFG_SIZE_TYPE pos_last_list_node_valid = list->info.size - 1;

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = 0; pos <= pos_last_list_node_valid; pos++) {
		node_reverse = list_control_get_node(list, pos_last_list_node_valid);

		list_control_del_node(list, pos_last_list_node_valid);

		list_control_set_node(list, pos, node_reverse);
	}
}

/**
 * @brief This function will removes all consecutive duplicate elements from the container
 *
 * @param destination the pointer to the destination list struct pointer
 *
 * @return NONE
 */

void list_control_list_operations_unique(LIST_TYPEDEF_PTR list)
{
	assert(list);

	char
		*data_prev = list_node_control_get_data(list, 0),
		*data = NULL;

	CONTAINER_GLOBAL_CFG_SIZE_TYPE
		size_list = list->info.size,
		cnt_pos_repetitive = 0,
		(*pos_repetitive_store)[2] = list->allocator_ctrl->allocate(list->allocator,
																	size_list, sizeof(CONTAINER_GLOBAL_CFG_SIZE_TYPE) * 2);

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = 1; pos < size_list; pos++) {
		if (list_control_default_sort_comp_equal(data_prev, (data = list_node_control_get_data(list, pos)), list->info.mem_size)) {
			*(*(pos_repetitive_store + cnt_pos_repetitive) + 0) = pos;
		} else {
			if (*(*(pos_repetitive_store + cnt_pos_repetitive) + 0) != *(*(pos_repetitive_store + cnt_pos_repetitive) + 1)) {
				*(*(pos_repetitive_store + cnt_pos_repetitive) + 1) = pos;

				cnt_pos_repetitive++;
			}

			data_prev = data;
		}
	}

	#if (LIST_CFG_DEBUG_EN)

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE cnt = 0; cnt < cnt_pos_repetitive; cnt++) {
		printf("list.list_operatons.unique:no.%d from %d to %d is \"%s\" \r\n",
			   cnt, *(*(pos_repetitive_store + cnt) + 0),
			   *(*(pos_repetitive_store + cnt) + 1),
			   (char *)list_node_control_get_data(list, *(*(pos_repetitive_store + cnt) + 0)));
	}

	#endif // (LIST_CFG_DEBUG_EN)

	struct  list_node_t
		*node_del = NULL;

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE cnt = 0; cnt < cnt_pos_repetitive; cnt++) {
		for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = *(*(pos_repetitive_store + cnt) + 0); pos <= *(*(pos_repetitive_store + cnt) + 1); pos++) {
			list_control_destroy_node(list, list_control_del_node(list, *(*(pos_repetitive_store + cnt) + 0)));
		}
	}

	list->allocator_ctrl->deallocate(list->allocator,
									 pos_repetitive_store, size_list);
}

/**
 * @brief This function will sorts the elements in ascending order
 *
 * @param destination the pointer to the destination list struct pointer
 * @param comp the pointer to the compare function that you wish
 *
 * @return NONE
 */

void list_control_list_operations_sort(LIST_TYPEDEF_PTR list,
									   bool (*comp)(void *dst, void *src, size_t len))
{
	assert(list);

	if (NULL == comp) {
		comp = list_control_default_sort_comp_greater;
	}

	struct list_node_t
		*node_lhs = NULL,
		*node_rhs = NULL;

	char
		*data_lhs = NULL,
		*data_rhs = NULL;
	
	for (size_t cnt = 0; cnt < list->info.size - 1; cnt++) {
		for (size_t ct = 0; ct < list->info.size - cnt - 1; ct++) {
			node_lhs = list_control_get_node(list, ct);
			node_rhs = list_control_get_node(list, ct + 1);

			data_lhs = list_node_control_get_data(list, ct);
			data_rhs = list_node_control_get_data(list, ct + 1);

			if (comp(data_lhs, data_rhs, list->info.mem_size)) {
				#if (LIST_CFG_DEBUG_EN)

				printf("list.list_operatons.sort.no.%d-%d: %d \"%s\" swap %d \"%s\" \r\n",
					   cnt, ct, ct, data_lhs, ct + 1, data_rhs);

				#endif // (LIST_CFG_DEBUG_EN)

				list_control_swap_node(list, ct, ct + 1);
			}
		}
	}
}

/**
 * @brief This function will initialize the list node struct.
 *
 * @param list the pointer to the list struct pointer
 *
 * @return NONE
 */

struct list_node_t *list_control_init_node(LIST_TYPEDEF_PTR list)
{
	assert(list);

	struct list_node_t
		*node_alloced = list->allocator_ctrl->allocate(list->allocator,
													   1, sizeof(struct list_node_t));

	void
		*data_pack_allocated = list->allocator_ctrl->allocate(list->allocator,
															  1, list->info.mem_size);			/* Allocate #2 */

	if (NULL == list ||																			/* Check if list point to NULL			*/
		NULL == node_alloced ||																	/* Check if list node point to NULL			*/
		NULL == data_pack_allocated) {															/* Check if data_pack_alloced point to NULL	*/
		return NULL;
	}

	node_alloced->prev = NULL;
	node_alloced->data = data_pack_allocated;													/* Assign list_node structure					*/
	node_alloced->next = NULL;

	return node_alloced;
}

/**
 * @brief This function will destroy list node struct and free the space.
 *
 * @param list the pointer to the list struct pointer
 * @param node the pointer to the list node struct pointer
 *
 * @return NONE
 */

void list_control_destroy_node(LIST_TYPEDEF_PTR list,
							   struct list_node_t *node)
{
	assert(list);

	if (NULL == node) {
		return;
	}

	list->allocator_ctrl->deallocate(list->allocator, node->data, 1);																/* Deallocate #2 */

	node->prev = NULL;												/* Assign list structure					*/
	node->data = NULL;
	node->next = NULL;

	list->allocator_ctrl->deallocate(list->allocator, node, 1);																		/* deallocate #1 */

	node = NULL;
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

struct list_node_t *list_control_set_node(LIST_TYPEDEF_PTR list,
	CONTAINER_GLOBAL_CFG_SIZE_TYPE position, struct list_node_t *node)
{
	assert(list);
	assert((0 <= position));

	if (list->info.max_size <= position ||
		0 > position) {
		return NULL;
	}

	if (NULL == node &&
		NULL == (node = list_control_init_node(list))) {
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

struct list_node_t *list_control_get_node(LIST_TYPEDEF_PTR list,
	CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(list);
	assert((0 <= position));

	if (list->info.max_size <= position ||
		0 > position) {
		return NULL;
	}

	struct list_node_t
		**current_node = &list->node;

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

struct list_node_t *list_control_del_node(LIST_TYPEDEF_PTR list,
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

/**
 * @brief This function will set elements at the specified location in the container.
 *
 * @param list the pointer to the list struct pointer
 * @param node the pointer to the list node struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param source pointer to the source
 *
 * @return NONE
 */

void list_node_control_set_data(LIST_TYPEDEF_PTR list,
								CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *source)
{
	assert(list);
	assert(0 <= position);
	assert(source);

	struct list_node_t
		*node = list_control_get_node(list, position);

	if (NULL == node) {
		node = list_control_set_node(list, position, NULL);

		if (NULL == node) {
			return;
		}
	}

	if (NULL == (node)->data) {
		(node)->data = list->allocator_ctrl->allocate(list->allocator,
													  1, list->info.mem_size);/* Allocate #2 */

		if (NULL == (node)->data) {
			return;
		}
	}

	if (NULL != list->element_handler.assign) {																		/* Check if assign point to NULL */
		list->element_handler.assign((node)->data, source);
	} else {
		memcpy((node)->data, source, list->info.mem_size);															/* Memcpy source to destination */
	}
}

/**
* @brief This function will get elements at the specified location in the container.
*
* @param list the pointer to the list struct pointer
* @param node the pointer to the list node struct pointer
* @param position the position of element,it would be equal or greater than zero
* @param destination pointer to the destination
*
* @return NONE
*/

void *list_node_control_get_data(LIST_TYPEDEF_PTR list,
								 CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(list);
	assert(0 <= position);

	struct list_node_t
		*node = list_control_get_node(list, position);

	if (NULL == node) {
		return NULL;
	}

	return node->data;
}

/**
* @brief This function will delete elements at the specified location in the container.
*
* @param list the pointer to the list struct pointer
* @param node the pointer to the list node struct pointer
* @param position the position of element,it would be equal or greater than zero
*
* @return NONE
*/

void list_node_control_del_data(LIST_TYPEDEF_PTR list,
								CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(list);
	assert(0 <= position);

	list_node_control_set_data(list, position, "");

	#if (LIST_CFG_DELETE_ELEMENT_EQUAL_DESTROY_NODE_EN)

	list_control_destroy_node(list, list_control_del_node(list, position));

	#endif // (LIST_CFG_DELETE_ELEMENT_EQUAL_DESTROY_NODE_EN)

	if (0 >= list->info.size) {
		list->exception.empty();

		return;
	}
}

/**
* @brief This function will control the remove run under the rule of remove_if.
*
* @param data the pointer to the data list will give
*
* @return if the data match the rule
*	- true	yes
*	- false	no
*/

bool list_control_remove_rule(void *data)
{
	if (0 == strcmp(data, list_control_list_operations_remove_value)) {
		return true;
	}

	return false;
}

/**
* @brief This function will compare if the left-hand-side lesser than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side lesser than the right-hand-side
*	- true	yes
*	- false	no
*/

bool list_control_default_sort_comp_lesser(void *lhs, void *rhs, size_t len)
{
	assert(lhs);
	assert(rhs);
	assert(len);

	for (size_t cnt = 0; cnt < len; cnt++) {
		if (*((char *)lhs + cnt) < *((char *)rhs + cnt)) {
			return true;
		}
	}

	return false;
}

/**
* @brief This function will compare if the left-hand-side greater than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side greater than the right-hand-side
*	- true	yes
*	- false	no
*/

bool list_control_default_sort_comp_greater(void *lhs, void *rhs, size_t len)
{
	assert(lhs);
	assert(rhs);
	assert(len);

	for (size_t cnt = 0; cnt < len; cnt++) {
		if (*((char *)lhs + cnt) > *((char *)rhs + cnt)) {
			return true;
		}
	}

	return false;
}

/**
* @brief This function will compare if the left-hand-side equal with the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side equal with the right-hand-side
*	- true	yes
*	- false	no
*/

bool list_control_default_sort_comp_equal(void *lhs, void *rhs, size_t len)
{
	assert(lhs);
	assert(rhs);
	assert(len);

	size_t cnt_equal_hit = 0;

	for (size_t cnt = 0; cnt < len; cnt++) {
		if (*((char *)lhs + cnt) == *((char *)rhs + cnt)) {
			cnt_equal_hit++;
		} else {
			return false;
		}
	}

	if (len == cnt_equal_hit) {
		return true;
	} else {
		return false;
	}
}

/**
* @brief This function will callback the handler that container has no elements when the container temp to insert.
*
* @param NODE
*
* @return NONE
*/

void list_control_configration_exception_default_empty_callback(void)
{
}

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param NODE
 *
 * @return NONE
 */

void list_control_configration_exception_default_full_callback(void)
{
}