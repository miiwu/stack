/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "deque.h"

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
 * @brief This struct is the deque structure module
 */

struct deque_s {
	/* @brief RESERVED This variables will record the identity code of container type.					*/
	enum container_type_e container_type_id;

	/* @brief This variables will record the information of container type.								*/
	struct container_common_information_s info;

	/* @brief This variables will point to the allocator.												*/
	void *allocator;

	/* @brief This variables will point to the allocator control.										*/
	struct allocator_control_s *allocator_ctrl;

	/* @brief This variables will point to the address of the deque data memory block.			*/
	void *data;

	/* @brief This variables will record the element handler of the container.							*/
	struct container_element_handler_s element_handler;

	/* @brief This variables will record the exception handler of the container.						*/
	struct container_common_exception_s exception;

	/* @brief This variables will point to the address of the list-like shared-pack analysis.			*/
	void (*switch_control)(void);
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
 * @brief This struct will control all the deque functions conveniently.
 */

struct deque_control_s deque_ctrl = {
	{
		deque_control_configuration_init,

		deque_control_configuration_destroy,

		deque_control_configuration_element_handler,

		deque_control_configuration_exception,
	},
	{
		deque_control_iterators_front,

		deque_control_iterators_back,
	},
	{
		deque_control_element_access_at,

		deque_control_element_access_front,

		deque_control_element_access_back,
	},
	{
		deque_control_capacity_empty,

		deque_control_capacity_size,

		deque_control_capacity_max_size,

		deque_control_capacity_resize,

		deque_control_capacity_shrink_to_fit,
	},
	{
		deque_control_modifiers_clear,

		deque_control_modifiers_insert,

		deque_control_modifiers_erase,

		deque_control_modifiers_push_front,

		deque_control_modifiers_emplace_front,

		deque_control_modifiers_pop_front,

		deque_control_modifiers_push_back,

		deque_control_modifiers_pop_back,

		deque_control_modifiers_swap,

		deque_control_modifiers_copy,
	}
};

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will callback the handler that container has no elements when the container temp to insert.
 *
 * @param deque the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void deque_control_configration_exception_default_empty_callback(void);

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param deque the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void deque_control_configration_exception_default_full_callback(void);

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the deque struct.
 *
 * @param deque the pointer to the container struct pointer
 * @param element_size the pointer to container
 * @param string_type the pointer to container
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void deque_control_configuration_init(struct deque_s **deque,
									  CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
									  void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(deque);
	assert(0 <= element_size);

	void
		*allocator = NULL;

	struct allocator_control_s
		*allocator_ctrl = NULL;

	allocator_ctrl = allocator_control_convert_type_to_func_addr_table(DEQUE_CFG_ALLOCATOR_TYPE);	/* Variables pointer to	the function address table of
																							specified allocator type		*/

	allocator_ctrl->configration.init(&allocator, NULL);

	struct deque_s
		*deque_alloced = (struct deque_s *)allocator_ctrl->allocate(allocator,
																	1, sizeof(struct deque_s));	/* Allocate #1 */

	if (NULL == deque ||																	/* Check if deque point to NULL			*/
		NULL == deque_alloced) {															/* Check if data_pack_alloced point to NULL		*/
		return;
	}

	deque_alloced->container_type_id = DEQUE;				/* Assign deque structure					*/

	deque_alloced->info.max_size = DEQUE_CFG_MAX_SIZE;
	deque_alloced->info.size = 0u;
	deque_alloced->info.mem_size = element_size;

	deque_alloced->allocator = allocator;
	deque_alloced->allocator_ctrl = allocator_ctrl;

	deque_alloced->element_handler.assign = NULL;
	deque_alloced->element_handler.free = NULL;

	deque_alloced->exception.empty = deque_control_configration_exception_default_empty_callback;
	deque_alloced->exception.full = deque_control_configration_exception_default_full_callback;

	if (NULL != assign &&																	/* Check if assign point to NULL			*/
		NULL != free) {																		/* Check if free point to NULL				*/
		deque_alloced->element_handler.assign = assign;
		deque_alloced->element_handler.free = free;
	}

	// TODO : deque callbacks

	*deque = deque_alloced;

	#if (ARRAY_FAMILY_CFG_DEBUG_EN)

	printf("init.deque allocator : %p \r\n", allocator);									/* Debug only								*/
	printf("init.deque block : %p \r\n", deque_alloced);
	printf("init.deque data block : %p \r\n", data_pack_alloced);

	#endif // (ARRAY_FAMILY_CFG_DEBUG_EN)
}

/**
 * @brief This function will destroy the deque struct and free the space.
 *
 * @param deque the pointer to the container struct pointer
 *
 * @return
 *  - 0    : succeed,destroy the deque struct and free the space completely
 *  - else : fail
 */

void deque_control_configuration_destroy(struct deque_s **deque)
{
	assert(deque);

	#if (ARRAY_FAMILY_CFG_DEBUG_EN)

	printf("destroy.deque data block : %p \r\n", (*deque)->data);

	printf("destroy.deque block : %p \r\n", (*deque));

	printf("destroy.deque allocator : %p \r\n", (*deque)->allocator);

	#endif // (ARRAY_FAMILY_CFG_DEBUG_EN)

	ALLOCATOR_COMMON_TYPEDEF_PTR
		deque_allocator = (*deque)->allocator;
	struct allocator_control_s
		*deque_allocator_ctrl = (*deque)->allocator_ctrl;

	deque_allocator_ctrl->deallocate(deque_allocator, (*deque)->data, (*deque)->info.max_size);	/* Deallocate #2 */

	(*deque)->container_type_id = 0u;													/* Assign deque structure					*/

	(*deque)->info.max_size = 0u;
	(*deque)->info.size = 0u;
	(*deque)->info.mem_size = 0u;

	(*deque)->allocator = NULL;
	(*deque)->allocator_ctrl = NULL;

	(*deque)->data = NULL;

	(*deque)->exception.empty = NULL;
	(*deque)->exception.full = NULL;

	deque_allocator_ctrl->deallocate(deque_allocator, *deque, 1);																			/* deallocate #1 */

	deque_allocator_ctrl->configration.destroy(&deque_allocator);

	*deque = NULL;
}

/**
 * @brief This function will configure the deque element handler.
 *
 * @param deque the pointer to the container struct
 * @param assign pointer to the address of element assign handler
 * @param free pointer to the address of element free handler
 *
 * @return NONE
 */

void deque_control_configuration_element_handler(struct deque_s *deque,
												 void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(deque);
	assert(assign);
	assert(free);

	deque->element_handler.assign = assign;
	deque->element_handler.free = free;
}

/**
 * @brief This function will configure the deque exception callback.
 *
 * @param deque the pointer to the container struct
 * @param empty the pointer to the handler that container has no elements when the container temp to insert
 * @param full the pointer to the handler that container has no elements when the container temp to erase
 *
 * @return NONE
 */

void deque_control_configuration_exception(struct deque_s *deque,
										   void (*empty)(void), void (*full)(void))
{
	assert(deque);

	if (NULL == empty) {
		deque->exception.empty = empty;
	}

	if (NULL == full) {
		deque->exception.full = full;
	}
}

/**
 * @brief This function will
 *
 * @param deque the pointer to the container struct
 *
 * @return NONE
 */

void deque_control_iterators_front(struct deque_s *deque)
{
	assert(deque);

	// TODO ...
}

/**
 * @brief This function will
 *
 * @param deque the pointer to the container struct
 *
 * @return NONE
 */

void deque_control_iterators_back(struct deque_s *deque)
{
	assert(deque);

	// TODO ...
}

/**
 * @brief This function will returns a reference to the element at specified location position, with bounds checking.
 *
 * @param deque the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero,it would be equal or greater than zero
 *
 * @return NONE
 */

void *deque_control_element_access_at(struct deque_s *deque,
									  CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(deque);
	assert(0 <= position);

	void
		*element = (void *)((size_t)(deque->data) + position * deque->info.mem_size);									/* Point destination to the address of the element which at the position location */

	#if (ARRAY_FAMILY_CFG_DEBUG_EN)

	printf("deque.at -> data block : %p | element : %p \r\n", deque->data, element);

	#endif // (ARRAY_FAMILY_CFG_DEBUG_EN)

	return element;
}

/**
 * @brief This function will returns a reference to the first element in the container.
 *
 * @param deque the pointer to the container struct
 *
 * @return NONE
 */

extern inline void *deque_control_element_access_front(struct deque_s *deque)
{
	assert(deque);

	return deque_control_element_access_at(deque, 0);
}

/**
 * @brief This function will returns reference to the last element in the container.
 *
 * @param deque the pointer to the container struct
 *
 * @return NONE
 */

extern inline void *deque_control_element_access_back(struct deque_s *deque)
{
	assert(deque);

	return deque_control_element_access_at(deque, deque->info.size);
}

/**
 * @brief This function will checks if the container has no elements.
 *
 * @param deque the pointer to the container struct
 *
 * @return
 *  if the container has no elements
 */

extern inline bool deque_control_capacity_empty(struct deque_s *deque)
{
	assert(deque);

	if (deque->info.max_size <= deque->info.size) {
		return true;
	} else {
		return false;
	}
}

/**
 * @brief This function will returns the number of elements in the container.
 *
 * @param deque the pointer to the container struct
 *
 * @return
 *  the number of elements in the container
 */

extern inline CONTAINER_GLOBAL_CFG_SIZE_TYPE deque_control_capacity_size(struct deque_s *deque)
{
	assert(deque);

	return deque->info.size;
}

/**
 * @brief This function will returns the maximum number of elements the container.
 * is able to hold due to system or library implementation limitations.
 *
 * @param deque the pointer to the container struct
 *
 * @return
 *  the maximum number of elements the container
 */

extern inline CONTAINER_GLOBAL_CFG_SIZE_TYPE deque_control_capacity_max_size(struct deque_s *deque)
{
	assert(deque);

	return deque->info.max_size;
}

/**
 * @brief This function will increase the capacity of the deque to a size that's greater or equal to new_cap.
 *
 * @param deque the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param size the size of elements
 *
 * @return NONE
 */

void deque_control_capacity_resize(struct deque_s **deque,
								   CONTAINER_GLOBAL_CFG_SIZE_TYPE size)
{
	assert(deque);
	assert(0 <= size);

	// TODO...
}

/**
 * @brief This function will requests the removal of unused capacity.
 *
 * @param deque the pointer to the container struct
 *
 * @return NONE
 */

void deque_control_capacity_shrink_to_fit(struct deque_s **deque)
{
	assert(deque);

	// TODO...
}

/**
 * @brief This function will erases all elements from the container.
 *
 * @param deque the pointer to the container struct
 *
 * @return NONE
 */

void deque_control_modifiers_clear(struct deque_s *deque)
{
	assert(deque);
}

/**
 * @brief This function will inserts elements at the specified location in the container.
 *
 * @param deque the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param amount the amount of elements
 * @param source pointer to the source
 *
 * @return
 *  the address of element the asserted
 */

void deque_control_modifiers_insert(struct deque_s *deque,
									CONTAINER_GLOBAL_CFG_SIZE_TYPE position, 
                                    CONTAINER_GLOBAL_CFG_SIZE_TYPE amount, void **source)
{
	assert(deque);
	assert(0 <= position);
	assert(0 <= amount);
	assert(source);
	assert(*source);
}

/**
 * @brief This function will erases the specified elements from the container.
 *
 * @param deque the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void deque_control_modifiers_erase(struct deque_s *deque,
								   CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(deque);
	assert(0 <= position);
}

/**
 * @brief This function will prepends the given element value to the beginning of the container
 *
 * @param list the pointer to the list struct pointer
 * @param source pointer to the source
 *
 * @return NONE
 */

void deque_control_modifiers_push_front(struct deque_s *deque,
										void *source)
{
	assert(deque);
	assert(source);
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

void deque_control_modifiers_emplace_front(struct deque_s *deque,
										   void *source)
{
}

/**
 * @brief This function will removes the first element of the container
 *
 * @param list the pointer to the list struct pointer
 *
 * @return NONE
 */

void deque_control_modifiers_pop_front(struct deque_s *deque)
{
	assert(deque);
}

/**
 * @brief This function will appends the given element source to the end of the container.
 *
 * @param deque the pointer to the container struct
 * @param source pointer to source
 *
 * @return NONE
 */

void deque_control_modifiers_push_back(struct deque_s *deque,
									   void *source)
{
	assert(deque);
	assert(source);
}

/**
 * @brief This function will removes the last element of the container.
 *
 * @param deque the pointer to the container struct
 * @param destination pointer to destination
 *
 * @return NONE
 */

void deque_control_modifiers_pop_back(struct deque_s *deque)
{
	assert(deque);
}

/**
 * @brief This function will copy the contents of the container to those of other.
 *
 * @param destination container struct
 * @param source container struct
 *
 * @return NONE
 */

void deque_control_modifiers_copy(struct deque_s **destination,
								  struct deque_s *source)
{
	assert(destination);
	assert(source);
}

/**
 * @brief This function will exchanges the contents of the container with those of other.
 *
 * @param deque the pointer to the container struct
 * @param other container struct
 *
 * @return NONE
 */

void deque_control_modifiers_swap(struct deque_s **deque,
								  struct deque_s **other)
{
	assert(deque);
	assert(other);

}

/**
 * @brief This function will get elements at the specified location in the container.
 *
 * @param deque the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void *deque_element_control_get_data(struct deque_s *deque,
                                     CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
    assert(deque);
    assert(0 <= position);

    void
        *source = (void *)((size_t)(deque->data) + position * deque->info.mem_size);							/* Point source to the address of the element which at the position location */

    return source;
}

/**
 * @brief This function will set elements at the specified location in the container.
 *
 * @param deque the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param source pointer to the source
 *
 * @return NONE
 */

void deque_element_control_set_data(struct deque_s *deque,
									CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *source)
{
	assert(deque);
	assert(0 <= position);
	assert(source);

	void
		*destination = (void *)((size_t)(deque->data) + position * deque->info.mem_size);									/* Point destination to the address of the element which at the position location */

	if (NULL != deque->element_handler.assign) {																		/* Check if assign point to NULL */
		deque->element_handler.assign(destination, source);
	} else {
		memcpy(destination, source, deque->info.mem_size);															/* Memcpy source to destination */
	}
}

/**
 * @brief This function will delete elements at the specified location in the container.
 *
 * @param deque the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void deque_element_control_del_data(struct deque_s *deque,
									CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(deque);
	assert(0 <= position);

	deque_element_control_set_data(deque, position, "");

	deque->info.size--;
}

/**
 * @brief This function will callback the handler that container has no elements when the container temp to insert.
 *
 * @param deque the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void deque_control_configration_exception_default_empty_callback(void)
{
	printf("\r\n the deque has no elements when you temp to insert \r\n");
}

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param deque the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void deque_control_configration_exception_default_full_callback(void)
{
	printf("\r\n the deque has no elements when you temp to erase \r\n");
}