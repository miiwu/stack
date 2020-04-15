/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "array_family.h"

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
 * @brief This variables will record the list_family_member_type_e.
 */

enum array_family_member_type_e array_family_control_type_in_control = ARRAY_FAMILY_ARRAY;

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will set elements at the specified location in the container.
 *
 * @param array_family the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param source pointer to the source
 *
 * @return NONE
 */

errno_t array_family_element_control_set_data(array_family_stp array_family,
											  container_size_t position, void *source);

/**
 * @brief This function will get elements at the specified location in the container.
 *
 * @param array_family the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void *array_family_element_control_get_data(array_family_stp array_family,
											container_size_t position);

/**
 * @brief This function will delete elements at the specified location in the container.
 *
 * @param array_family the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

errno_t array_family_element_control_del_data(array_family_stp array_family,
											  container_size_t position);

/**
 * @brief This function will callback the handler that container has no elements when the container temp to insert.
 *
 * @param array_family the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void array_family_control_configuration_exception_default_empty_callback(void);

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param array_family the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void array_family_control_configuration_exception_default_full_callback(void);

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the list struct
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

extern inline void array_family_control_get_control(enum list_family_member_type_e type)
{
	array_family_control_type_in_control = type;
}

/**
 * @brief This function will initialize the array_family struct.
 *
 * @param array_family the pointer to the container struct pointer
 * @param element_size the pointer to container
 * @param string_type the pointer to container
 * @param assign the pointer to the assign element handler of the specified element_ptr type
 * @param free the pointer to the free element handler of the specified element_ptr type
 *
 * @return NONE
 */

errno_t array_family_control_configuration_init(array_family_stpp array_family,
												container_family_switch_control switch_control,
												enum allocator_type_e allocator_type,
												container_size_t element_size,
												generic_type_element_assign_t assign,
												generic_type_element_free_t free)
{
	assert(array_family);
	assert(switch_control);
	assert(allocator_type);
	assert(element_size);

	static struct container_allocte_package_s
		allocate_package = { 0 };
	static struct container_control_configuration_allocate_return_s
		allocate_return = { 0 };

	allocate_package.allocator_type = allocator_type;
	allocate_package.container_mem_size = sizeof(struct container_family_s);
	allocate_package.arg_list_ptr = NULL;

	if ((allocate_return
		 = container_control_configuration_allocate											/* Allocate the adaptor structure */
		 (array_family, allocate_package))
		.error) {
		return 1;
	}

	if (NULL == ((*array_family)->element_ptr
				 = allocate_return.allocator_control_ptr
				 ->allocate(allocate_return.allocator_ptr,
							ARRAY_FAMILY_CFG_DEFAULT_MAX_SIZE, element_size))) {
		return 2;
	}

	(*array_family)->container_type_id = array_family_control_type_in_control;				/* Assign array_family structure */

	(*array_family)->info.max_size = ARRAY_FAMILY_CFG_DEFAULT_MAX_SIZE;
	(*array_family)->info.size = 0u;
	(*array_family)->info.mem_size = element_size;

	(*array_family)->element_handler.assign = assign;
	(*array_family)->element_handler.free = free;

	(*array_family)->allocator_control_ptr = allocate_return.allocator_control_ptr;
	(*array_family)->allocator_ptr = allocate_return.allocator_ptr;

	(*array_family)->switch_control = switch_control;

	array_family_control_configuration_exception(
		(*array_family)
		, array_family_control_configuration_exception_default_empty_callback
		, array_family_control_configuration_exception_default_full_callback);

	return 0;
}

/**
 * @brief This function will destroy the array_family struct and free the space.
 *
 * @param array_family the pointer to the container struct pointer
 *
 * @return
 *  - 0    : succeed,destroy the array_family struct and free the space completely
 *  - else : fail
 */

errno_t array_family_control_configuration_destroy(array_family_stpp array_family)
{
	assert(array_family);

	concept_allocator_stp
		array_family_allocator = (*array_family)->allocator_ptr;
	struct allocator_control_s
		*array_family_allocator_control = (*array_family)->allocator_control_ptr;
 
	array_family_allocator_control
		->deallocate(array_family_allocator, (*array_family)->element_ptr);					/* Deallocate the element */

	array_family_allocator_control
		->deallocate(array_family_allocator, *array_family);								/* Deallocate the array family */

	array_family_allocator_control
		->configuration.destroy(&array_family_allocator);									/* Destroy the allocator */

	*array_family = NULL;

	return 0;
}

/**
 * @brief This function will configure the array_family element handler.
 *
 * @param array_family the pointer to the container struct
 * @param assign pointer to the address of element assign handler
 * @param free pointer to the address of element free handler
 *
 * @return NONE
 */

errno_t array_family_control_configuration_element_handler(array_family_stp array_family,
														   generic_type_element_assign_t assign,
														   generic_type_element_free_t free)
{
	assert(array_family);
	assert(assign);
	assert(free);

	array_family->element_handler.assign = assign;
	array_family->element_handler.free = free;

	return 0;
}

/**
 * @brief This function will configure the array_family exception callback.
 *
 * @param array_family the pointer to the container struct
 * @param empty the pointer to the handler that container has no elements when the container temp to insert
 * @param full the pointer to the handler that container has no elements when the container temp to erase
 *
 * @return NONE
 */

errno_t array_family_control_configuration_exception(array_family_stp array_family,
													 void (*empty)(void), void (*full)(void))
{
	assert(array_family);

	if (NULL == empty) {
		array_family->exception.empty = empty;
	}

	if (NULL == full) {
		array_family->exception.full = full;
	}

	return 0;
}

/**
 * @brief This function will
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

void array_family_control_iterators_front(array_family_stp array_family)
{
	assert(array_family);

	// TODO ...
}

/**
 * @brief This function will
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

void array_family_control_iterators_back(array_family_stp array_family)
{
	assert(array_family);

	// TODO ...
}

/**
 * @brief This function will returns a reference to the element
 *			at specified location position, with bounds checking.
 *
 * @param array_family the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero,it would be equal or greater than zero
 *
 * @return NONE
 */

void *array_family_control_element_access_at(array_family_stp array_family,
											 container_size_t position)
{
	assert(array_family);
	assert(0 <= position);

	void
		*element = (void *)((size_t)(array_family->element_ptr) +
							position * array_family->info.mem_size);						/* Point destination to the address of the element which at the position location */

	#if (ARRAY_FAMILY_CFG_DEBUG_EN)

	printf("array family control.element access.at:element_ptr block : \
			%p | element : %p \r\n",
		   array_family->element_ptr, element);

	#endif // (ARRAY_FAMILY_CFG_DEBUG_EN)

	return element;
}

/**
 * @brief This function will returns a reference to the first element in the container.
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

extern inline void
*array_family_control_element_access_front(array_family_stp array_family)
{
	assert(array_family);

	return array_family_control_element_access_at(array_family, 0);
}

/**
 * @brief This function will returns reference to the last element in the container.
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

extern inline void
*array_family_control_element_access_back(array_family_stp array_family)
{
	assert(array_family);

	return array_family_control_element_access_at(array_family, array_family->info.size);
}

/**
 * @brief This function will returns pointer to the underlying array serving as element storage.
 *
 * @param array_family the pointer to the container struct
 *
 * @return pointer to the underlying array serving as element storage
 */

extern inline void
*array_family_control_element_access_data(array_family_stp array_family)
{
	assert(array_family);

	return array_family->element_ptr;
}

/**
 * @brief This function will checks if the container has no elements.
 *
 * @param array_family the pointer to the container struct
 *
 * @return
 *  if the container has no elements
 */

extern inline bool
array_family_control_capacity_empty(array_family_stp array_family)
{
	assert(array_family);

	if (0 < array_family->info.size) {
		return true;
	} else {
		return false;
	}
}

/**
 * @brief This function will returns the number of elements in the container.
 *
 * @param array_family the pointer to the container struct
 *
 * @return
 *  the number of elements in the container
 */

extern inline container_size_t
array_family_control_capacity_size(array_family_stp array_family)
{
	assert(array_family);

	return array_family->info.size;
}

/**
 * @brief This function will returns the maximum number of elements the container.
 *			is able to hold due to system or library implementation limitations.
 *
 * @param array_family the pointer to the container struct
 *
 * @return
 *  the maximum number of elements the container
 */

extern inline container_size_t
array_family_control_capacity_max_size(array_family_stp array_family)
{
	assert(array_family);

	return ARRAY_FAMILY_CFG_DEFAULT_HARDWARE_MAX_AVAILABLE_HEAP_SIZE
		/ array_family->info.mem_size;
}

/**
 * @brief This function will returns the number of elements that
 *			the container has currently allocated space for.
 *
 * @param array_family the pointer to the container struct
 *
 * @return
 *  the number of elements that the container has currently allocated space for
 */

extern inline container_size_t
array_family_control_capacity_capacity(array_family_stp array_family)
{
	assert(array_family);

	return array_family->info.size * array_family->info.mem_size;
}

/**
 * @brief This function will increase the capacity of the vector to a size
 *			that's greater or equal to new_cap.
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

errno_t array_family_control_capacity_reserve(array_family_stpp array_family,
											  container_size_t size)
{
	assert(array_family);
	assert(0 <= size);

	// TODO...

	return 0;
}

/**
 * @brief This function will requests the removal of unused capacity.
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

errno_t array_family_control_capacity_shrink_to_fit(array_family_stpp array_family)
{
	assert(array_family);

	// TODO...

	return 0;
}

/**
 * @brief This function will erases all elements from the container.
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

errno_t array_family_control_modifiers_clear(array_family_stp array_family)
{
	assert(array_family);

	if (0 >= array_family->info.size) {
		if (NULL != array_family->exception.empty) {
			array_family->exception.empty();
		}

		return 1;
	}

	for (container_size_t element_pos = 0; element_pos < array_family->info.size; element_pos++) {
		array_family_element_control_set_data(array_family, element_pos, "");
	}

	array_family->info.size = 0;

	return 0;
}

/**
 * @brief This function will inserts elements at the specified location in the container.
 *
 * @param array_family the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param amount the amount of elements
 * @param source pointer to the source
 *
 * @return
 *  the address of element the asserted
 */

errno_t array_family_control_modifiers_insert(array_family_stp array_family,
											  container_size_t position,
											  container_size_t amount,
											  void **source)
{
	assert(array_family);
	assert(0 <= position);
	assert(0 <= amount);
	assert(source);
	assert(*source);

	if (array_family->info.max_size <= array_family->info.size) {
		if (NULL != array_family->exception.full) {
			array_family->exception.full();
		}

		return 1;
	}

	container_size_t
		element_amount = array_family->info.size - position,
		back_element_pos = position + amount;

	void
		*element_block = array_family->allocator_control_ptr
		->allocate(array_family->allocator_ptr,							/* Allocate	array_family malloc #3 */
				   element_amount, array_family->info.mem_size),	
		**element = array_family->allocator_control_ptr
		->allocate(array_family->allocator_ptr,							/* Allocate	array_family malloc #4 */
				   1, sizeof(void **));							

	if (NULL == element) {																						/* Check if the element point to NULL */
		return 2;
	}

	*element = element_block;

	#if (ARRAY_FAMILY_CFG_DEBUG_EN)

	printf("array_family.insert -> element amount : %d \r\n", element_amount);

	#endif // (ARRAY_FAMILY_CFG_DEBUG_EN)

	for (container_size_t element_pos = position; element_pos < array_family->info.size; element_pos++) {		/* Copy the array_family to element */
		void *
			element_addr = (void *)((size_t)element_block + element_pos * array_family->info.mem_size);

		element_addr = array_family_element_control_get_data(array_family, element_pos);								/* Copy the element which at the element_pos location to the element */

		#if (ARRAY_FAMILY_CFG_DEBUG_EN)

		printf("array_family.insert -> element no.%d : %s \r\n", element_pos, (char *)element_addr);

		#endif // (ARRAY_FAMILY_CFG_DEBUG_EN)
	}

	for (container_size_t element_pos = 0; element_pos < back_element_pos - position; element_pos++) {			/* Insert the source to the array_family */
		size_t
			source_addr = (size_t)*source + element_pos * array_family->info.mem_size;

		array_family_element_control_set_data(array_family, element_pos + position, (void *)source_addr);

		#if (ARRAY_FAMILY_CFG_DEBUG_EN)

		printf("array_family.insert -> source no.%d : %s \r\n", element_pos, (char *)source_addr);

		#endif // (ARRAY_FAMILY_CFG_DEBUG_EN)
	}

	for (container_size_t element_pos = back_element_pos; element_pos < back_element_pos + element_amount; element_pos++) {	/* Insert the elements to the array_family */
		size_t
			element_plus_insert_addr = (size_t)element_block + (element_pos - back_element_pos) * array_family->info.mem_size;

		array_family_element_control_set_data(array_family, element_pos, (void *)element_plus_insert_addr);
	}

	array_family->allocator_control_ptr->deallocate(array_family->allocator_ptr, element_block);								/* Deallocate #3 */
	array_family->allocator_control_ptr->deallocate(array_family->allocator_ptr, element);													/* Deallocate #4 */
	element_block = NULL;
	element = NULL;																								/* Assign the element to NULL */

	array_family->info.size += amount;																				/* Change the capacity of array_family */

	return 0;
}

/**
 * @brief This function will erases the specified elements from the container.
 *
 * @param array_family the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

errno_t array_family_control_modifiers_erase(array_family_stp array_family,
											 container_size_t position)
{
	assert(array_family);
	assert(0 <= position);

	if (0 >= array_family->info.size) {
		if (NULL != array_family->exception.empty) {
			array_family->exception.empty();
		}

		return 1;
	}

	#if (ARRAY_FAMILY_CFG_DEBUG_EN)

	printf("array family control.modifiers.erase:source: %s \r\n", 
		(char *)array_family_element_control_get_data(array_family, position));

	#endif // (ARRAY_FAMILY_CFG_DEBUG_EN)

	array_family_element_control_del_data(array_family, position);

	return 0;
}

/**
 * @brief This function will appends the given element source to the end of the container.
 *
 * @param array_family the pointer to the container struct
 * @param source pointer to source
 *
 * @return NONE
 */

errno_t array_family_control_modifiers_push_back(array_family_stp array_family,
												 void *source)
{
	assert(array_family);
	assert(source);

	if (array_family->info.max_size <= array_family->info.size) {														/* Check if will trigger full array_family exception callback */
		if (NULL != array_family->exception.full) {
			array_family->exception.full();
		}

		return 1;
	}

	array_family_element_control_set_data(array_family, (array_family->info.size), source);

	array_family->info.size++;

	return 0;
}

/**
 * @brief This function will removes the last element of the container.
 *
 * @param array_family the pointer to the container struct
 * @param destination pointer to destination
 *
 * @return NONE
 */

errno_t array_family_control_modifiers_pop_back(array_family_stp array_family)
{
	assert(array_family);

	if (array_family->info.size <= 0) {																			/* Check if will trigger empty array_family exception callback */
		if (NULL != array_family->exception.empty) {
			array_family->exception.empty();
		}

		return 1;
	}

	array_family_element_control_del_data(array_family, (array_family->info.size) ? array_family->info.size - 1 : 0);

	array_family->info.size--;

	return 0;
}

/**
 * @brief This function will resizes the container to contain count elements.
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

errno_t array_family_control_modifiers_resize(array_family_stpp array_family,
											  container_size_t count)
{
	assert(array_family);
	assert(0 <= count);

	if ((*array_family)->info.max_size >= count) {
		return 1;
	}

	(*array_family)->allocator_control_ptr->
		deallocate((*array_family)->allocator_ptr, (*array_family)->element_ptr);					/* Deallocate #2.1 */

	void
		*data_pack_alloced =
		(*array_family)->allocator_control_ptr->allocate((*array_family)->allocator_ptr,
														 count,
														 (*array_family)->info.mem_size);			/* Malloc	vector malloc #2.1 */

	if (NULL == data_pack_alloced) {
		return 2;
	}

	(*array_family)->info.max_size = count;
	(*array_family)->element_ptr = data_pack_alloced;

	return 0;
}

/**
 * @brief This function will copy the contents of the container to those of other.
 *
 * @param destination container struct
 * @param source container struct
 *
 * @return NONE
 */

errno_t array_family_control_modifiers_copy(array_family_stpp destination,
											array_family_stp source)
{
	assert(destination);
	assert(source);

	void
		*source_data = (void *)(size_t)(source->element_ptr);

	if (NULL == (*destination) ||
		NULL == (*destination)->allocator_ptr ||
		NULL == (*destination)->allocator_control_ptr ||														/* Check if destination have been initialized */
		NULL == (*destination)->element_ptr) {																	/* if not,then initialize it */
		enum allocator_type_e *allocator_type = source->allocator_ptr;

		array_family_control_configuration_init(destination,
												source->switch_control, *allocator_type,
												source->info.mem_size, source->element_handler.assign, source->element_handler.free);
	} else {
		(*destination)->info = source->info;															/* if so,just assign */
		(*destination)->element_handler = source->element_handler;
		(*destination)->exception = source->exception;
	}

	(*destination)->info.size = source->info.size;

	for (container_size_t element_amt = 0; element_amt < source->info.size; element_amt++) {
		array_family_element_control_set_data(*destination,
											  element_amt,
											  (void *)((size_t)source_data + element_amt * source->info.mem_size));/* Copy the destination to source */
	}

	return 0;
}

/**
 * @brief This function will exchanges the contents of the container with those of other.
 *
 * @param array_family the pointer to the container struct
 * @param other container struct
 *
 * @return NONE
 */

errno_t array_family_control_modifiers_swap(array_family_stpp array_family,
											array_family_stpp other)
{
	assert(array_family);
	assert(other);

	array_family_stp
		array_family_swap = NULL;

	array_family_control_modifiers_copy(&array_family_swap, *other);

	array_family_control_modifiers_copy(other, *array_family);

	array_family_control_modifiers_copy(array_family, array_family_swap);

	return 0;
}

/**
 * @brief This function will set elements at the specified location in the container.
 *
 * @param array_family the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param source pointer to the source
 *
 * @return NONE
 */

errno_t array_family_element_control_set_data(array_family_stp array_family,
											  container_size_t position, void *source)
{
	assert(array_family);
	assert(0 <= position);
	assert(source);

	void
		*destination =
		(void *)((size_t)(array_family->element_ptr) + position * array_family->info.mem_size);	/* Point destination to the address of the element which at the position location */

	if (NULL != array_family->element_handler.assign) {										/* Check if assign point to NULL */
		array_family->element_handler.assign(destination, source);
	} else {
		memcpy(destination, source, array_family->info.mem_size);							/* Memcpy source to destination */
	}

	return 0;
}

/**
 * @brief This function will get elements at the specified location in the container.
 *
 * @param array_family the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

static inline void
*array_family_element_control_get_data(array_family_stp array_family,
									   container_size_t position)
{
	assert(array_family);
	assert(0 <= position);

	void
		*source = (void *)((size_t)(array_family->element_ptr) +									/* Point source to the address of the element which at the position location */
						   position * array_family->info.mem_size);

	return source;
}

/**
 * @brief This function will delete elements at the specified location in the container.
 *
 * @param array_family the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

errno_t array_family_element_control_del_data(array_family_stp array_family,
											  container_size_t position)
{
	assert(array_family);
	assert(0 <= position);

	void *element_ptr = array_family_element_control_get_data(array_family, position);

	if (NULL != array_family->element_handler.free) {										/* Check if assign point to NULL */
		array_family->element_handler.free(element_ptr);
	} else {
		memset(element_ptr, '0', array_family->info.mem_size);								/* Memcpy source to destination */
	}

	array_family->info.size--;

	return 0;
}

/**
 * @brief This function will callback the handler that container has no elements when the container temp to insert.
 *
 * @param array_family the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void array_family_control_configuration_exception_default_empty_callback(void)
{
	printf("\r\n the array_family has no elements when you temp to insert \r\n");
}

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param array_family the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void array_family_control_configuration_exception_default_full_callback(void)
{
	printf("\r\n the array_family has no elements when you temp to erase \r\n");
}