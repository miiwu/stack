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
#define ARRAY_FAMILY_CFG_ALLOCATOR_TYPE                                 ALLOCATOR_COMMON

/* Configure    if enable array_family debug.														    */
#define ARRAY_FAMILY_CFG_DEBUG_EN										1u

/*
*********************************************************************************************************
*									            DATA TYPES
*********************************************************************************************************
*/

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
	void *(*get)(struct array_family_s *array_family,
				 CONTAINER_GLOBAL_CFG_SIZE_TYPE pos);

	/* @brief This variables will set the node at the specified location in the container and
				return the node.			                                                            */
	void *(*set)(struct array_family_s *array_family,
				 CONTAINER_GLOBAL_CFG_SIZE_TYPE pos, void *node);

	/* @brief This variables will delete the node at the specified location in the container.			*/
	void *(*del)(struct array_family_s *array_family,
				 CONTAINER_GLOBAL_CFG_SIZE_TYPE pos);

	/* @brief This variables will swap the nodes at the specified location in the container.			*/
	void (*swap)(struct array_family_s *array_family,
				 CONTAINER_GLOBAL_CFG_SIZE_TYPE lhs_pos,
				 CONTAINER_GLOBAL_CFG_SIZE_TYPE rhs_pos);
};

/**
 * @brief This struct is the array_family structure module
 */

struct array_family_s {
	/* @brief RESERVED This variables will record the identity code of container type.					*/
	enum container_type_e	container_type_id;

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
	struct allocator_control_s *allocator_ctrl;

	/* @brief This variables will point to the address of the array_family data memory block.					*/
	void *data;

	struct {
		/* @brief This variables will point to the address of the array_family element assign handler.		*/
		void (*assign)(void *dst, void *src);

		/* @brief This variables will point to the address of the array_family element free handler.			*/
		void (*free)(void *dst);
	}element_handler;

	struct {
		/* @brief This variables will point to the address of the array_family empty exception handler.		*/
		void (*empty)(void);

		/* @brief This variables will point to the address of the array_family full exception handler.			*/
		void (*full)(void);
	}exception;

	/* @brief This variables will point to the address of the list-like shared-pack analysis.			*/
	void (*switch_control)(void);
};

/**
 * @brief This struct is the array_family control structure module
 */

struct array_family_control_s {
	struct {
		/* @brief This function will initialize the array_family struct.                                      */
		void (*init)(struct array_family_s **array_family,
					 CONTAINER_GLOBAL_CFG_SIZE_TYPE dst_size,
					 void (*assign)(void *dst, void *src), void (*free)(void *dst));

		/* @brief This function will destroy the array_family struct and free the space.                      */
		void (*destroy)(struct array_family_s **array_family);

		/* @brief This function will configure the array_family element handler.                              */
		void (*element_handler)(struct array_family_s *array_family,
								void (*assign)(void *dst, void *src), void (*free)(void *dst));

		/* @brief This function will configure the array_family exception callback.                           */
		void (*exception)(struct array_family_s *array_family,
						  void (*empty)(void), void (*full)(void));
	}configuration;

	struct {
		/* @brief This function will initialize the array_family struct.                                      */
		void (*begin)(struct array_family_s *array_family);

		/* @brief This function will initialize the array_family struct.                                      */
		void (*end)(struct array_family_s *array_family);
	}iterators;

	struct {
		/* @brief This function will returns a reference to the element
				  at specified location position, with bounds checking.                                 */
		void *(*at)(struct array_family_s *array_family,
					CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

		/* @brief This function will returns pointer to the underlying array
				  serving as element storage.                                                           */
		void *(*data)(struct array_family_s *array_family);

		/* @brief This function will returns a reference to the first element in the container.         */
		void *(*front)(struct array_family_s *array_family);

		/* @brief This function will returns reference to the last element in the container.            */
		void *(*back)(struct array_family_s *array_family);
	}element_access;

	struct {
		/* @brief This function will checks if the container has no elements.                           */
		bool (*empty)(struct array_family_s *array_family);

		/* @brief This function will returns the number of elements in the container.                   */
		CONTAINER_GLOBAL_CFG_SIZE_TYPE(*size)(struct array_family_s *array_family);

		/* @brief This function will returns the maximum number of elements the container
				  is able to hold due to system or library implementation limitations.                  */
		CONTAINER_GLOBAL_CFG_SIZE_TYPE(*max_size)(struct array_family_s *array_family);

		/* @brief This function will returns the number of elements
				  that the container has currently allocated space for.                                 */
		CONTAINER_GLOBAL_CFG_SIZE_TYPE(*capacity)(struct array_family_s *array_family);
	}capacity;

	struct {
		/* @brief This function will erases all elements from the container.                            */
		void (*clear)(struct array_family_s *array_family);

		/* @brief This function will inserts elements at the specified location in the container.       */
		void (*insert)(struct array_family_s *array_family,
					   CONTAINER_GLOBAL_CFG_SIZE_TYPE position,
					   CONTAINER_GLOBAL_CFG_SIZE_TYPE amount, void **source);

	   /* @brief This function will erases the specified elements from the container.                  */
		void (*erase)(struct array_family_s *array_family,
					  CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

		/* @brief This function will appends the given element source to the end of the container.      */
		void (*push_back)(struct array_family_s *array_family,
						  void *source);

		/* @brief This function will removes the last element of the container.                         */
		void (*pop_back)(struct array_family_s *array_family);

		/* @brief This function will copy the contents of the container to those of other.              */
		void (*copy)(struct array_family_s **destination,
					 struct array_family_s *source);

		/* @brief This function will exchanges the contents of the container with those of other.       */
		void (*swap)(struct array_family_s **array_family,
					 struct array_family_s **other);
	}modifiers;
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
 * @brief This function will get the control of the array_family system.
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

void aray_family_control_get_control(enum array_family_member_type_e member,
									 struct array_family_element_operator_s operator);

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

void array_family_control_configuration_init(struct array_family_s **array_family,
											 void (*switch_control)(void),
											 enum allocator_type_e allocator_type,
											 CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
											 void (*assign)(void *dst, void *src), void (*free)(void *dst));

/**
 * @brief This function will destroy the array_family struct and free the space.
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

void array_family_control_configuration_destroy(struct array_family_s **array_family);

/**
 * @brief This function will configure the array_family element handler.
 *
 * @param array_family the pointer to the container struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void array_family_control_configuration_element_handler(struct array_family_s *array_family,
														void (*assign)(void *dst, void *src), void (*free)(void *dst));

/**
 * @brief This function will configure the array_family exception callback.
 *
 * @param array_family the pointer to the container struct
 * @param empty the pointer to the handler that container has no elements when the container temp to insert
 * @param full the pointer to the handler that container has no elements when the container temp to erase
 *
 * @return NONE
 */

void array_family_control_configuration_exception(struct array_family_s *array_family,
												  void (*empty)(void), void (*full)(void));

/**
 * @brief This function will
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

void array_family_control_iterators_front(struct array_family_s *array_family);

/**
 * @brief This function will
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

void array_family_control_iterators_back(struct array_family_s *array_family);

/**
 * @brief This function will returns a reference to the element at specified location position, with bounds checking.
 *
 * @param array_family the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void *array_family_control_element_access_at(struct array_family_s *array_family,
											 CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
 * @brief This function will returns a reference to the first element in the container.
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

void *array_family_control_element_access_front(struct array_family_s *array_family);

/**
 * @brief This function will returns reference to the last element in the container.
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

void *array_family_control_element_access_back(struct array_family_s *array_family);

/**
 * @brief This function will returns pointer to the underlying array serving as element storage.
 *
 * @param array_family the pointer to the container struct
 *
 * @return pointer to the underlying array serving as element storage
 */

void *array_family_control_element_access_data(struct array_family_s *array_family);

/**
 * @brief This function will checks if the container has no elements.
 *
 * @param array_family the pointer to the container struct
 *
 * @return
 *  if the container has no elements
 */

bool array_family_control_capacity_empty(struct array_family_s *array_family);

/**
 * @brief This function will returns the number of elements in the container.
 *
 * @param array_family the pointer to the container struct
 *
 * @return
 *  the number of elements in the container
 */

CONTAINER_GLOBAL_CFG_SIZE_TYPE array_family_control_capacity_size(struct array_family_s *array_family);

/**
 * @brief This function will returns the maximum number of elements the container.
 * is able to hold due to system or library implementation limitations.
 *
 * @param array_family the pointer to the container struct
 *
 * @return
 *  the maximum number of elements the container
 */

CONTAINER_GLOBAL_CFG_SIZE_TYPE array_family_control_capacity_max_size(struct array_family_s *array_family);

/**
 * @brief This function will returns the number of elements that the container has currently allocated space for.
 *
 * @param array_family the pointer to the container struct
 *
 * @return
 *  the number of elements that the container has currently allocated space for
 */

CONTAINER_GLOBAL_CFG_SIZE_TYPE array_family_control_capacity_capacity(struct array_family_s *array_family);

/**
 * @brief This function will erases all elements from the container.
 *
 * @param array_family the pointer to the container struct
 *
 * @return NONE
 */

void array_family_control_modifiers_clear(struct array_family_s *array_family);

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

void array_family_control_modifiers_insert(struct array_family_s *array_family,
										   CONTAINER_GLOBAL_CFG_SIZE_TYPE position, CONTAINER_GLOBAL_CFG_SIZE_TYPE amount, void **source);

/**
 * @brief This function will erases the specified elements from the container.
 *
 * @param array_family the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void array_family_control_modifiers_erase(struct array_family_s *array_family,
										  CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
 * @brief This function will appends the given element source to the end of the container.
 *
 * @param array_family the pointer to the container struct
 * @param source pointer to source
 *
 * @return NONE
 */

void array_family_control_modifiers_push_back(struct array_family_s *array_family,
											  void *source);

/**
 * @brief This function will removes the last element of the container.
 *
 * @param array_family the pointer to the container struct
 * @param destination pointer to destination
 *
 * @return NONE
 */

void array_family_control_modifiers_pop_back(struct array_family_s *array_family);

/**
 * @brief This function will copy the contents of the container to those of other.
 *
 * @param destination container struct
 * @param source container struct
 *
 * @return NONE
 */

void array_family_control_modifiers_copy(struct array_family_s **destination,
										 struct array_family_s *source);

/**
 * @brief This function will exchanges the contents of the container with those of other.
 *
 * @param array_family the pointer to the container struct
 * @param other container struct
 *
 * @return NONE
 */

void array_family_control_modifiers_swap(struct array_family_s **array_family,
										 struct array_family_s **other);

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