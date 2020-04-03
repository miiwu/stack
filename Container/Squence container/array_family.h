/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __ARRAY_FAMILY_H
#define __ARRAY_FAMILY_H

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "container_def.h"

/*
*********************************************************************************************************
*									            DEFINES
*********************************************************************************************************
*/

/* Configure    the default max size of array_family.                                                   */
#define ARRAY_FAMILY_CFG_DEFAULT_MAX_SIZE								100u

/* Configure    if enable integrated structure.                                                         */
#define ARRAY_FAMILY_CFG_DEFAULT_HARDWARE_MAX_AVAILABLE_HEAP_SIZE		1024u

/* Configure    the type of allocator.                                                                  */
#define ARRAY_FAMILY_CFG_ALLOCATOR_TYPE                                 CONCEPT_ALLOCATOR

/* Configure    if enable array_family debug.														    */
#define ARRAY_FAMILY_CFG_DEBUG_EN										1u

/*
*********************************************************************************************************
*									            DATA TYPES
*********************************************************************************************************
*/

/**
 * @brief This type is the array family typedef
 */

typedef struct container_family_s
*array_family_stp,
**array_family_stpp;

/**
 * @brief This struct is the array_family member type enum structure module
 */

enum array_family_member_type_e {
	ARRAY_FAMILY_ARRAY,

	ARRAY_FAMILY_VECTOR
};

/**
 * @brief This struct is the array_family element operator structure module
 */

struct array_family_element_operator_s {
	/* @brief This function will return the node at the specified location in the container.			*/
	void *(*get)(array_family_stp array_family,
				 container_size_t pos);

	/* @brief This variables will set the node at the specified location in the container and
				return the node.			                                                            */
	void *(*set)(array_family_stp array_family,
				 container_size_t pos, void *node);

	/* @brief This variables will delete the node at the specified location in the container.			*/
	void *(*del)(array_family_stp array_family,
				 container_size_t pos);

	/* @brief This variables will swap the nodes at the specified location in the container.			*/
	void (*swap)(array_family_stp array_family,
				 container_size_t lhs_pos,
				 container_size_t rhs_pos);
};

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the list struct
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

void array_family_control_get_control(enum list_family_member_type_e type);

/**
 * @brief This function will initialize the array_family struct.
 *
 * @param array_family the pointer to the container struct pointer
 * @param element_size the pointer to container
 * @param string_type the pointer to container
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

errno_t array_family_control_configuration_init(array_family_stpp array_family,
												container_family_switch_control switch_control,
												enum allocator_type_e allocator_type,
												container_size_t element_size,
												generic_type_element_assign_t assign,
												generic_type_element_free_t free);

/**
 * @brief This function will destroy the array_family struct and free the space.
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

errno_t array_family_control_configuration_destroy(array_family_stpp array_family);

/**
 * @brief This function will configure the array_family element handler.
 *
 * @param array_family the pointer to the container struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

errno_t array_family_control_configuration_element_handler(array_family_stp array_family,
														   generic_type_element_assign_t assign,
														   generic_type_element_free_t free);

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
													 void (*empty)(void), void (*full)(void));

/**
 * @brief This function will
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

void array_family_control_iterators_front(array_family_stp array_family);

/**
 * @brief This function will
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

void array_family_control_iterators_back(array_family_stp array_family);

/**
 * @brief This function will returns a reference to the element at specified location position, with bounds checking.
 *
 * @param array_family the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void *array_family_control_element_access_at(array_family_stp array_family,
											 container_size_t position);

/**
 * @brief This function will returns a reference to the first element in the container.
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

void *array_family_control_element_access_front(array_family_stp array_family);

/**
 * @brief This function will returns reference to the last element in the container.
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

void *array_family_control_element_access_back(array_family_stp array_family);

/**
 * @brief This function will returns pointer to the underlying array serving as element storage.
 *
 * @param array_family the pointer to the container struct
 *
 * @return pointer to the underlying array serving as element storage
 */

void *array_family_control_element_access_data(array_family_stp array_family);

/**
 * @brief This function will checks if the container has no elements.
 *
 * @param array_family the pointer to the container struct
 *
 * @return
 *  if the container has no elements
 */

bool array_family_control_capacity_empty(array_family_stp array_family);

/**
 * @brief This function will returns the number of elements in the container.
 *
 * @param array_family the pointer to the container struct
 *
 * @return
 *  the number of elements in the container
 */

container_size_t
array_family_control_capacity_size(array_family_stp array_family);

/**
 * @brief This function will returns the maximum number of elements the container.
 * is able to hold due to system or library implementation limitations.
 *
 * @param array_family the pointer to the container struct
 *
 * @return
 *  the maximum number of elements the container
 */

container_size_t
array_family_control_capacity_max_size(array_family_stp array_family);

/**
 * @brief This function will returns the number of elements that
 *          the container has currently allocated space for.
 *
 * @param array_family the pointer to the container struct
 *
 * @return
 *  the number of elements that the container has currently allocated space for
 */

container_size_t
array_family_control_capacity_capacity(array_family_stp array_family);

/**
 * @brief This function will increase the capacity of the vector to a size that's greater or equal to new_cap.
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

errno_t array_family_control_capacity_reserve(array_family_stpp array_family,
											  container_size_t size);

/**
 * @brief This function will requests the removal of unused capacity.
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

errno_t array_family_control_capacity_shrink_to_fit(array_family_stpp array_family);

/**
 * @brief This function will erases all elements from the container.
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

errno_t array_family_control_modifiers_clear(array_family_stp array_family);

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
											  container_size_t amount, void **source);

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
											 container_size_t position);

/**
 * @brief This function will appends the given element source to the end of the container.
 *
 * @param array_family the pointer to the container struct
 * @param source pointer to source
 *
 * @return NONE
 */

errno_t array_family_control_modifiers_push_back(array_family_stp array_family,
												 void *source);

/**
 * @brief This function will removes the last element of the container.
 *
 * @param array_family the pointer to the container struct
 * @param destination pointer to destination
 *
 * @return NONE
 */

errno_t array_family_control_modifiers_pop_back(array_family_stp array_family);

/**
 * @brief This function will resizes the container to contain count elements.
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

errno_t array_family_control_modifiers_resize(array_family_stpp array_family,
											  container_size_t count);

/**
 * @brief This function will exchanges the contents of the container with those of other.
 *
 * @param array_family the pointer to the container struct
 * @param other container struct
 *
 * @return NONE
 */

errno_t array_family_control_modifiers_swap(array_family_stpp array_family,
											array_family_stpp other);

/**
 * @brief This function will copy the contents of the container to those of other.
 *
 * @param destination container struct
 * @param source container struct
 *
 * @return NONE
 */

errno_t array_family_control_modifiers_copy(array_family_stpp destination,
											array_family_stp source);

/*
*********************************************************************************************************
*                                       EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__ARRAY_FAMILY_H