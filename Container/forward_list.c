/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "forward_list.h"

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
 * @brief This struct is the forward_list structure module
 */

struct forward_list_node_t {
	/* @brief This variables will point to the address of the forward_list data memory block.					*/
	void *data;

	/* @brief This variables will pointer to the next list node.										*/
	struct forward_list_node_t *next;
};

/**
 * @brief This struct is the forward_list structure module
 */

struct forward_list_t {
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

	/* @brief This variables will pointer to the first list node.										*/
	struct forward_list_node_t *node;

	/* @brief This variables will record the element handler of the container.							*/
	struct element_handler_t element_handler;

	struct {
		/* @brief This variables will point to the address of the forward_list empty exception handler.		*/
		void (*empty)(void);

		/* @brief This variables will point to the address of the forward_list full exception handler.			*/
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
 * @brief This array will control the allocator.
 */

struct allocator_control_t
	*forward_list_allocator_ctrl = NULL;

/**
 * @brief This array will contain all the universal forward_list functions address.
 */

void *forward_list_function_address_tables[] =
{
	NULL,
	//(void *)&forward_list_control_configuration_init,					/* No.0 : initialize */

	//(void *)&forward_list_control_configuration_destroy,					/* No.1 : destroy */

	//(void *)&forward_list_control_element_access_at,						/* No.3 : at */

	//(void *)&forward_list_control_capacity_empty,						/* No.4 : empty */

	//(void *)&forward_list_control_capacity_size,							/* No.5 : size */

	//(void *)&forward_list_control_capacity_max_size,						/* No.6 : max_size */

	//(void *)&forward_list_control_modifiers_insert,						/* No.7 : insert */

	//(void *)&forward_list_control_modifiers_erase,						/* No.8 : erase */

	//(void *)&forward_list_control_modifiers_swap,						/* No.9 : swap */

	//(void *)&forward_list_control_modifiers_copy,						/* No.10 : copy */
};

#if (FORWARD_LIST_CFG_INTERGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This struct will control all the forward_list functions conveniently.
 */

struct forward_list_control_t forward_list_ctrl = {
	{
		forward_list_control_configuration_init,
		forward_list_control_configuration_destroy,
		forward_list_control_configuration_element_handler,
		forward_list_control_configuration_exception,
	},
	{
		NULL
	},
	{
		forward_list_control_element_access_front,
	},
	{
		forward_list_control_capacity_empty,
		forward_list_control_capacity_max_size,
		forward_list_control_capacity_size,
	},
	{
		forward_list_control_modifiers_clear,
		forward_list_control_modifiers_insert_after,
		forward_list_control_modifiers_emplace_after,
		forward_list_control_modifiers_erase_after,
		forward_list_control_modifiers_push_front,
		forward_list_control_modifiers_emplace_front,
		forward_list_control_modifiers_pop_front,
		forward_list_control_modifiers_resize,
		forward_list_control_modifiers_swap,
		forward_list_control_modifiers_copy,
	},
	{
		forward_list_control_list_operations_merge,
		forward_list_control_list_operations_splice_after,
		forward_list_control_list_operations_remove,
		forward_list_control_list_operations_remove_if,
		forward_list_control_list_operations_reverse,
		forward_list_control_list_operations_unique,
		forward_list_control_list_operations_sort,
	}
};

#endif

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the forward list node struct.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param node the pointer to the forward list node struct pointer
 * @param element_size the pointer to container
 * @param string_type the pointer to container
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

struct forward_list_node_t *forward_list_control_modifiers_init(FORWARD_LIST_TYPEDEF_PTR forward_list);

/**
 * @brief This function will destroy forward list node struct and free the space.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param node the pointer to the forward list node struct pointer
 *
 * @return NONE
 */

void forward_list_control_modifiers_destroy(FORWARD_LIST_TYPEDEF_PTR forward_list,
											struct forward_list_node_t **node);

/**
 * @brief This function will get the node address at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return the node address at the specified location in the container
 */

struct forward_list_node_t **forward_list_control_modifiers_get_node_addr(FORWARD_LIST_TYPEDEF_PTR forward_list,
	CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return the node at the specified location in the container
 */

struct forward_list_node_t *forward_list_control_modifiers_get(FORWARD_LIST_TYPEDEF_PTR forward_list,
	CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return the initialized node at the specified location in the container
 */

struct forward_list_node_t *forward_list_control_modifiers_set_null_node(FORWARD_LIST_TYPEDEF_PTR forward_list,
	CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
 * @brief This function will set elements at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param source pointer to the source
 *
 * @return NONE
 */

void forward_list_node_control_modifiers_set(FORWARD_LIST_TYPEDEF_PTR forward_list,
											 CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *source);

/**
* @brief This function will get elements at the specified location node in the container.
*
* @param forward_list the pointer to the forward list struct pointer
* @param position the position of element,it would be equal or greater than zero
* @param destination pointer to the destination
*
* @return NONE
*/

void *forward_list_node_control_modifiers_get(FORWARD_LIST_TYPEDEF_PTR forward_list,
											  CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

 /**
 * @brief This function will delete elements at the specified location node in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void forward_list_node_control_modifiers_del(FORWARD_LIST_TYPEDEF_PTR forward_list,
											 CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
* @brief This function will callback the handler that container has no elements when the container temp to insert.
*
* @param NODE
*
* @return NONE
*/

void forward_list_control_configration_exception_default_empty_callback(void);

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param NODE
 *
 * @return NONE
 */

void forward_list_control_configration_exception_default_full_callback(void);

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

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

void forward_list_control_configuration_init(FORWARD_LIST_TYPEDEF_PPTR forward_list,
											 CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
											 void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(forward_list);
	assert(0 <= element_size);

	void
		*allocator = NULL;

	forward_list_allocator_ctrl = allocator_control_convert_type_to_func_addr_table(FORWARD_LIST_CFG_ALLOCATOR_TYPE);	/* Variables pointer to	the function address table of
																															specified container type		*/

	forward_list_allocator_ctrl->configration.init(&allocator, NULL);

	struct forward_list_t
		*forward_list_alloced = (struct forward_list_t *)forward_list_allocator_ctrl->allocate(allocator,
																							   1, sizeof(struct forward_list_t));	/* Allocate #1 */

	if (NULL == forward_list ||																	/* Check if forward_list point to NULL			*/
		NULL == forward_list_alloced) {															/* Check if forward_list_alloced point to NULL	*/
		return;
	}

	forward_list_alloced->container_type_id = FORWARD_LIST;												/* Assign forward_list structure					*/

	forward_list_alloced->info.max_size = FORWARD_LIST_CFG_DEFAULT_MAX_SIZE;
	forward_list_alloced->info.size = 0u;
	forward_list_alloced->info.mem_size = element_size;

	forward_list_alloced->allocator = allocator;

	forward_list_alloced->node = NULL;

	forward_list_alloced->element_handler.assign = NULL;
	forward_list_alloced->element_handler.free = NULL;

	forward_list_alloced->exception.empty = forward_list_control_configration_exception_default_empty_callback;
	forward_list_alloced->exception.full = forward_list_control_configration_exception_default_full_callback;

	if (NULL != assign &&																	/* Check if assign point to NULL			*/
		NULL != free) {																		/* Check if free point to NULL				*/
		forward_list_alloced->element_handler.assign = assign;
		forward_list_alloced->element_handler.free = free;
	}

	*forward_list = forward_list_alloced;

	#if (CONTAINER_GLOBAL_CFG_FORWARD_LIST_DBG_EN)												/* Debug only								*/

	printf("forward list.configuration.init:allocator : %p \r\n", allocator);
	printf("forward list.configuration.init:forward_list block : %p \r\n", forward_list_alloced);

	#endif // (CONTAINER_GLOBAL_CFG_FORWARD_LIST_DBG_EN)
}

/**
 * @brief This function will destroy the forward_list struct and free the space
 *
 * @param forward_list the pointer to the forward list struct pointer
 *
 * @return NONE
 */

void forward_list_control_configuration_destroy(FORWARD_LIST_TYPEDEF_PPTR forward_list)
{
	assert(forward_list);

	void
		*allocator = (*forward_list)->allocator;

	#if (CONTAINER_GLOBAL_CFG_FORWARD_LIST_DBG_EN)												/* Debug only								*/

	printf("forward list.configuration.destroy:allocator : %p \r\n", allocator);
	printf("forward list.configuration.destroy:forward_list block : %p \r\n", (*forward_list));
	printf("forward list.configuration.destroy:forward_list node block : %p \r\n", (*forward_list)->node);

	#endif // (CONTAINER_GLOBAL_CFG_FORWARD_LIST_DBG_EN)

	if (0 < (*forward_list)->info.size) {
		for (size_t cnt = 0; cnt < (*forward_list)->info.size; cnt++) {
			struct forward_list_node_t
				**node = forward_list_control_modifiers_get_node_addr((*forward_list), cnt - 1);

			forward_list_control_modifiers_destroy((*forward_list), node);
		}
	}

	(*forward_list)->container_type_id = 0u;														/* Assign forward_list structure					*/

	(*forward_list)->info.max_size = 0u;
	(*forward_list)->info.size = 0u;
	(*forward_list)->info.mem_size = 0u;

	(*forward_list)->allocator = NULL;

	(*forward_list)->node = NULL;

	(*forward_list)->exception.empty = NULL;
	(*forward_list)->exception.full = NULL;

	forward_list_allocator_ctrl->deallocate(allocator, *forward_list, 1);																			/* deallocate #1 */

	forward_list_allocator_ctrl->configration.destroy(&allocator);

	*forward_list = NULL;
}

/**
 * @brief This function will configure the forward_list element handler
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void forward_list_control_configuration_element_handler(FORWARD_LIST_TYPEDEF_PTR forward_list,
														void (*assign)(void *dst, void *src), void(*free)(void *dst))
{
	assert(forward_list);
	assert(assign);
	assert(free);

	forward_list->element_handler.assign = assign;
	forward_list->element_handler.free = free;
}

/**
 * @brief This function will configure the forward_list exception callback
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void forward_list_control_configuration_exception(FORWARD_LIST_TYPEDEF_PTR forward_list,
												  void (*empty)(void), void (*full)(void))
{
	assert(forward_list);

	if (NULL == empty) {
		forward_list->exception.empty = empty;
	}

	if (NULL == full) {
		forward_list->exception.full = full;
	}
}

/**
 * @brief This function will returns a reference to the first element in the container
 *
 * @param forward_list the pointer to the forward list struct pointer
 *
 * @return the reference to the first element in the container
 */

void *forward_list_control_element_access_front(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
	assert(forward_list);

	return forward_list_node_control_modifiers_get(forward_list, 0);
}

/**
 * @brief This function will checks if the container has no elements
 *
 * @param forward_list the pointer to the forward list struct pointer
 *
 * @return
	- true,the container has no elements
	- false,the container has elements
 */

bool forward_list_control_capacity_empty(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
	assert(forward_list);

	if (forward_list->info.max_size <= forward_list->info.size) {
		return true;
	} else {
		return false;
	}
}

/**
 * @brief This function will returns the maximum number of elements the container
			is able to hold due to system or library implementation limitations
 *
 * @param forward_list the pointer to the forward list struct pointer
 *
 * @return the maximum number of elements
 */

CONTAINER_GLOBAL_CFG_SIZE_TYPE forward_list_control_capacity_max_size(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
	assert(forward_list);

	return forward_list->info.max_size;
}

/**
 * @brief This function will returns the number of elements in the container
 *
 * @param forward_list the pointer to the forward list struct pointer
 *
 * @return the number of elements in the container
 */

CONTAINER_GLOBAL_CFG_SIZE_TYPE forward_list_control_capacity_size(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
	assert(forward_list);

	return forward_list->info.size;
}

/**
 * @brief This function will erases all elements from the container
 *
 * @param forward_list the pointer to the forward list struct pointer
 *
 * @return NONE
 */

void forward_list_control_modifiers_clear(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
	assert(forward_list);

	for (size_t cnt = forward_list->info.size; cnt > 0; cnt--) {
		#if (CONTAINER_GLOBAL_CFG_FORWARD_LIST_DBG_EN)
		char
			buffer[100] = { 0 };

		forward_list_control_modifiers_erase_after(forward_list, 0, buffer);

		printf("forward list.modifiers.clear:erase after : \"%s\" and %d time \r\n", buffer, cnt);
		#else

		forward_list_control_modifiers_erase_after(forward_list, 0, NULL);

		#endif // (CONTAINER_GLOBAL_CFG_FORWARD_LIST_DBG_EN)
	}
}

/**
 * @brief This function will inserts elements after the specified position in the container
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param amount the amount of the source
 * @param source pointer to the source
 *
 * @return NONE
 */

void forward_list_control_modifiers_insert_after(FORWARD_LIST_TYPEDEF_PTR forward_list,
												 CONTAINER_GLOBAL_CFG_SIZE_TYPE position,
												 CONTAINER_GLOBAL_CFG_SIZE_TYPE amount, void **source)
{
	assert(forward_list);
	assert(0 <= position);
	assert(0 < amount);
	assert(source);
	assert(*source);

	CONTAINER_GLOBAL_CFG_SIZE_TYPE
		element_amount = forward_list->info.size - position,
		pos_source_expected = position + amount;

	void
		*element_block = forward_list_allocator_ctrl->allocate(forward_list->allocator,
															   element_amount, forward_list->info.mem_size),								/* Allocate	vector malloc #3 */
		**element = forward_list_allocator_ctrl->allocate(forward_list->allocator,
														  1, sizeof(void **));												/* Allocate vector malloc #4 */

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE element_pos = position; element_pos < forward_list->info.size; element_pos++) {		/* Copy the vector to element */
		void
			*element_addr = (void *)((size_t)element_block + element_pos * forward_list->info.mem_size);

		element_addr = forward_list_node_control_modifiers_get(forward_list, element_pos);								/* Copy the element which at the element_pos location to the element */

		#if (CONTAINER_GLOBAL_CFG_FORWARD_LIST_DBG_EN)												/* Debug only								*/

		printf("forward list.modifiers.insert after:element backup no.%d : \"%s\" \r\n", element_pos, (char *)element_addr);

		#endif // (CONTAINER_GLOBAL_CFG_FORWARD_LIST_DBG_EN)
	}

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE element_pos = position; element_pos < pos_source_expected; element_pos++) {			/* Insert the source to the vector */
		size_t
			source_addr = (size_t)*source + element_pos * forward_list->info.mem_size;

		forward_list_node_control_modifiers_set(forward_list, element_pos, (void *)source_addr);

		#if (CONTAINER_GLOBAL_CFG_FORWARD_LIST_DBG_EN)												/* Debug only								*/

		printf("forward list.modifiers.insert after:source no.%d : \"%s\" \r\n", element_pos, (char *)source_addr);

		#endif // (CONTAINER_GLOBAL_CFG_FORWARD_LIST_DBG_EN)

		forward_list->info.size++;

		if (forward_list->info.max_size <= forward_list->info.size) {
			forward_list->exception.full();

			return;
		}
	}

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE element_pos = pos_source_expected; element_pos < pos_source_expected + element_amount; element_pos++) {	/* Insert the elements to the vector */
		CONTAINER_GLOBAL_CFG_SIZE_TYPE
			element_plus_insert_addr = (CONTAINER_GLOBAL_CFG_SIZE_TYPE)element_block +
			(element_pos - pos_source_expected) * forward_list->info.mem_size;

		forward_list_node_control_modifiers_set(forward_list, element_pos, (void *)element_plus_insert_addr);
	}

	forward_list_allocator_ctrl->deallocate(forward_list->allocator, element_block, element_amount);
	forward_list_allocator_ctrl->deallocate(forward_list->allocator, element, 1);
}

/**
 * @brief This function will push a new element on top of the stack, and the element is constructed in-place
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void forward_list_control_modifiers_emplace_after(FORWARD_LIST_TYPEDEF_PTR stack,
												  CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *destination)
{
}

/**
 * @brief This function will erases the specified elements from the container
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void forward_list_control_modifiers_erase_after(FORWARD_LIST_TYPEDEF_PTR forward_list,
												CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *destination)
{
	assert(forward_list);
	assert(0 <= position);

	struct forward_list_node_t
		*node = forward_list_control_modifiers_get(forward_list, position);

	if (0 < position) {
		struct forward_list_node_t
			*node_prev = forward_list_control_modifiers_get(forward_list, position - 1);

		if (NULL == node_prev) {
			return;
		}

		node_prev->next = node_prev->next->next;											/* Link the previous node's next to the specified node's next */
	}

	if (NULL != destination) {
		void
			*source = forward_list_node_control_modifiers_get(forward_list, position);

		if (NULL == source) {
			return;
		}

		if (NULL != forward_list->element_handler.assign) {																		/* Check if assign point to NULL */
			forward_list->element_handler.assign(destination, source);
		} else {
			memcpy(destination, source, forward_list->info.mem_size);															/* Memcpy source to destination */
		}
	}

	forward_list_node_control_modifiers_del(forward_list, position);
}

/**
 * @brief This function will prepends the given element value to the beginning of the container
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param source pointer to the source
 *
 * @return NONE
 */

void forward_list_control_modifiers_push_front(FORWARD_LIST_TYPEDEF_PTR forward_list,
											   void *source)
{
}

/**
 * @brief This function will Inserts a new element to the beginning of the container.
			The element is constructed through std::allocator_traits::construct,
			which typically uses placement-new to construct the element in-place
			at the location provided by the container.
			The arguments args... are forwarded to the constructor as std::forward<Args>(args)....
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void forward_list_control_modifiers_emplace_front(FORWARD_LIST_TYPEDEF_PTR stack,
												  void *destination)
{
}

/**
 * @brief This function will removes the first element of the container
 *
 * @param forward_list the pointer to the forward list struct pointer
 *
 * @return NONE
 */

void forward_list_control_modifiers_pop_front(FORWARD_LIST_TYPEDEF_PTR forward_list,
											  void *destination)
{
}

/**
 * @brief This function will increase the capacity of the forward_list to a size
			that's greater or equal to new_cap
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param size the size of the forward list struct
 *
 * @return NONE
 */

void forward_list_control_modifiers_resize(FORWARD_LIST_TYPEDEF_PPTR forward_list,
										   CONTAINER_GLOBAL_CFG_SIZE_TYPE size)
{
}

/**
 * @brief This function will exchanges the contents of the container with those of other
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param other the pointer to the other forward list struct pointer
 *
 * @return NONE
 */

void forward_list_control_modifiers_swap(FORWARD_LIST_TYPEDEF_PPTR forward_list,
										 FORWARD_LIST_TYPEDEF_PPTR other)
{
}

/**
 * @brief This function will copy the contents of the container to those of other
 *
 * @param destination the pointer to the destination forward list struct pointer
 * @param source the pointer to the source forward list struct
 *
 * @return NONE
 */

void forward_list_control_modifiers_copy(FORWARD_LIST_TYPEDEF_PPTR destination,
										 FORWARD_LIST_TYPEDEF_PTR source)
{
}

/**
 * @brief This function will merges two sorted lists into one
 *
 * @param destination the pointer to the destination forward list struct pointer
 * @param source the pointer to the source forward list struct
 *
 * @return NONE
 */

void forward_list_control_list_operations_merge(FORWARD_LIST_TYPEDEF_PPTR destination,
												FORWARD_LIST_TYPEDEF_PTR other)
{
}

/**
 * @brief This function will moves elements from another forward_list to forward_list
 *
 * @param destination the pointer to the destination forward list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param other the pointer to the other forward list struct
 *
 * @return NONE
 */

void forward_list_control_list_operations_splice_after(FORWARD_LIST_TYPEDEF_PTR forward_list,
													   CONTAINER_GLOBAL_CFG_SIZE_TYPE position,
													   FORWARD_LIST_TYPEDEF_PTR other)
{
}

/**
 * @brief This function will removes all elements satisfying specific criteria
 *
 * @param destination the pointer to the destination forward list struct pointer
 * @param data the pointer of data
 *
 * @return NONE
 */

void forward_list_control_list_operations_remove(FORWARD_LIST_TYPEDEF_PTR forward_list,
												 void *data)
{
}

/**
 * @brief This function will
 *
 * @param destination the pointer to the destination forward list struct pointer
 *
 * @return NONE
 */

void forward_list_control_list_operations_remove_if(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
}

/**
 * @brief This function will reverses the order of the elements in the container
 *
 * @param destination the pointer to the destination forward list struct pointer
 *
 * @return NONE
 */

void forward_list_control_list_operations_reverse(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
}

/**
 * @brief This function will removes all consecutive duplicate elements from the container
 *
 * @param destination the pointer to the destination forward list struct pointer
 *
 * @return NONE
 */

void forward_list_control_list_operations_unique(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
}

/**
 * @brief This function will sorts the elements in ascending order
 *
 * @param destination the pointer to the destination forward list struct pointer
 *
 * @return NONE
 */

void forward_list_control_list_operations_sort(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
}

/**
 * @brief This function will initialize the forward list node struct.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param node the pointer to the forward list node struct pointer
 * @param element_size the pointer to container
 * @param string_type the pointer to container
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

struct forward_list_node_t *forward_list_control_modifiers_init(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
	assert(forward_list);

	struct forward_list_node_t
		*node_alloced = forward_list_allocator_ctrl->allocate(forward_list->allocator,
															  1, sizeof(struct forward_list_node_t));

	void
		*data_pack_allocated = forward_list_allocator_ctrl->allocate(forward_list->allocator,
																	 1, forward_list->info.mem_size);			/* Allocate #2 */

	if (NULL == forward_list ||																	/* Check if forward_list point to NULL			*/
		NULL == node_alloced ||																	/* Check if forward_list node point to NULL			*/
		NULL == data_pack_allocated) {															/* Check if data_pack_alloced point to NULL	*/
		return NULL;
	}

	node_alloced->data = data_pack_allocated;													/* Assign forward_list_node structure					*/
	node_alloced->next = NULL;

	#if (CONTAINER_GLOBAL_CFG_FORWARD_LIST_DBG_EN)												/* Debug only								*/

	printf("forward list.modifiers.init node:node block : %p \r\n", node_alloced);
	printf("forward list.modifiers.init node:node date block : %p \r\n", data_pack_allocated);

	#endif // (CONTAINER_GLOBAL_CFG_FORWARD_LIST_DBG_EN)

	return node_alloced;
}

/**
 * @brief This function will destroy forward list node struct and free the space.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param node the pointer to the forward list node struct pointer
 *
 * @return NONE
 */

void forward_list_control_modifiers_destroy(FORWARD_LIST_TYPEDEF_PTR forward_list,
											struct forward_list_node_t **node)
{
	assert(forward_list);

	if (NULL == node) {
		return;
	}

	#if (CONTAINER_GLOBAL_CFG_FORWARD_LIST_DBG_EN)												/* Debug only								*/

	printf("forward list.modifiers.destroy node:node block : %p \r\n", (*node));
	printf("forward list.modifiers.destroy node:node date block : %p \r\n", (*node)->data);

	#endif // (CONTAINER_GLOBAL_CFG_FORWARD_LIST_DBG_EN)

	forward_list_allocator_ctrl->deallocate(forward_list->allocator, (*node)->data, 1);																	/* Deallocate #2 */

	(*node)->data = NULL;												/* Assign forward_list structure					*/
	(*node)->next = NULL;

	forward_list_allocator_ctrl->deallocate(forward_list->allocator, (*node), 1);																		/* deallocate #1 */

	*node = NULL;
}

/**
 * @brief This function will get the node address at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return the node address at the specified location in the container
 */

struct forward_list_node_t **forward_list_control_modifiers_get_node_addr(FORWARD_LIST_TYPEDEF_PTR forward_list,
	CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(forward_list);
	assert((0 <= position));

	if (forward_list->info.max_size <= position) {
		return NULL;
	}

	struct forward_list_node_t
		**current_node = &forward_list->node;

	CONTAINER_GLOBAL_CFG_SIZE_TYPE
		currrent_position = 0;

LOOP:

	if (NULL == current_node ||
		NULL == *current_node ||
		currrent_position >= position) {
		return current_node;
	}

	current_node = &(*current_node)->next;

	currrent_position++;

	goto LOOP;
}

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

struct forward_list_node_t *forward_list_control_modifiers_get(FORWARD_LIST_TYPEDEF_PTR forward_list,
	CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(forward_list);
	assert((0 <= position));

	if (forward_list->info.max_size <= position) {
		return NULL;
	}

	struct forward_list_node_t
		*node = *forward_list_control_modifiers_get_node_addr(forward_list, position);

	return node;
}

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return the initialized node at the specified location in the container
 */

struct forward_list_node_t *forward_list_control_modifiers_set_null_node(FORWARD_LIST_TYPEDEF_PTR forward_list,
	CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(forward_list);
	assert((0 <= position));

	if (forward_list->info.max_size <= position) {
		return NULL;
	}

	struct forward_list_node_t
		**node = forward_list_control_modifiers_get_node_addr(forward_list, position);

	if (NULL == *node) {
		*node = forward_list_control_modifiers_init(forward_list);
	}

	return *node;
}

/**
 * @brief This function will set elements at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param node the pointer to the forward list node struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param source pointer to the source
 *
 * @return NONE
 */

void forward_list_node_control_modifiers_set(FORWARD_LIST_TYPEDEF_PTR forward_list,
											 CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *source)
{
	assert(forward_list);
	assert(0 <= position);
	assert(source);

	struct forward_list_node_t
		*node = forward_list_control_modifiers_get(forward_list, position);

	if (NULL == node) {
		node = forward_list_control_modifiers_set_null_node(forward_list, position);

		if (NULL == node) {
			return;
		}
	}

	if (NULL == (node)->data) {
		(node)->data = forward_list_allocator_ctrl->allocate(forward_list->allocator,
															 1, forward_list->info.mem_size);/* Allocate #2 */

		if (NULL == (node)->data) {
			return;
		}
	}

	if (NULL != forward_list->element_handler.assign) {																		/* Check if assign point to NULL */
		forward_list->element_handler.assign((node)->data, source);
	} else {
		memcpy((node)->data, source, forward_list->info.mem_size);															/* Memcpy source to destination */
	}
}

/**
* @brief This function will get elements at the specified location in the container.
*
* @param forward_list the pointer to the forward list struct pointer
* @param node the pointer to the forward list node struct pointer
* @param position the position of element,it would be equal or greater than zero
* @param destination pointer to the destination
*
* @return NONE
*/

void *forward_list_node_control_modifiers_get(FORWARD_LIST_TYPEDEF_PTR forward_list,
											  CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(forward_list);
	assert(0 <= position);

	struct forward_list_node_t
		*node = forward_list_control_modifiers_get(forward_list, position);

	if (NULL == node) {
		return NULL;
	}

	return node->data;
}

/**
* @brief This function will delete elements at the specified location in the container.
*
* @param forward_list the pointer to the forward list struct pointer
* @param node the pointer to the forward list node struct pointer
* @param position the position of element,it would be equal or greater than zero
*
* @return NONE
*/

void forward_list_node_control_modifiers_del(FORWARD_LIST_TYPEDEF_PTR forward_list,
											 CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(forward_list);
	assert(0 <= position);

	forward_list_node_control_modifiers_set(forward_list, position, "");

	#if (FORWARD_LIST_CFG_DELETE_ELEMENT_EQUAL_DESTROY_NODE_EN)

	struct forward_list_node_t
		**node = forward_list_control_modifiers_get_node_addr(forward_list, position),
		*node_destroy = *node;

	if (NULL == node ||
		NULL == node_destroy) {
		return;
	}

	(*node) = (*node)->next;

	forward_list_control_modifiers_destroy(forward_list,
										   &node_destroy);

	#endif // (FORWARD_LIST_CFG_DELETE_ELEMENT_EQUAL_DESTROY_NODE_EN)

	if (0 >= forward_list->info.size) {
		forward_list->exception.empty();

		return;
	}

	forward_list->info.size--;
}

/**
* @brief This function will callback the handler that container has no elements when the container temp to insert.
*
* @param NODE
*
* @return NONE
*/

void forward_list_control_configration_exception_default_empty_callback(void)
{
}

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param NODE
 *
 * @return NONE
 */

void forward_list_control_configration_exception_default_full_callback(void)
{
}