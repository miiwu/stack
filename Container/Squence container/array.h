/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __ARRAY_H
#define __ARRAY_H

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "array_family.h"

/*
*********************************************************************************************************
*									            DEFINES
*********************************************************************************************************
*/

/* Configure    the default max size of array.                                                         */
#define ARRAY_CFG_DEFAULT_MAX_SIZE								100u

/* Configure    if enable integrated structure.                                                         */
#define ARRAY_CFG_DEFAULT_HARDWARE_MAX_AVAILABLE_HEAP_SIZE		1024u

/* Configure    the type of allocator.                                                                  */
#define ARRAY_CFG_ALLOCATOR_TYPE                                ALLOCATOR_COMMON

/* Configure    if enable integrated structure.                                                         */
#define ARRAY_CFG_INTEGRATED_STRUCTURE_MODE_EN			        1u

/*
*********************************************************************************************************
*									            DATA TYPES
*********************************************************************************************************
*/

/**
 * @brief This type is the array typedef
 */

typedef array_family_stp
array_stp,
*array_stpp;

/**
 * @brief This struct is the array_family control structure module
 */

struct array_control_s {
	struct {
		/* @brief This function will initialize the array_family struct.                                */
		void (*init)(array_stpp array_family,
					 container_size_t dst_size,
					 generic_type_element_assign_t assign,
					 generic_type_element_free_t free);

		/* @brief This function will destroy the array_family struct and free the space.                */
		void (*destroy)(array_stpp array_family);

		/* @brief This function will configure the array_family element handler.                        */
		void (*element_handler)(array_stp array_family,
								generic_type_element_assign_t assign,
								generic_type_element_free_t free);

		/* @brief This function will configure the array_family exception callback.                     */
		void (*exception)(array_stp array_family,
						  void (*empty)(void), void (*full)(void));
	}configuration;

	struct {
		/* @brief This function will initialize the array_family struct.                                */
		void (*begin)(array_stp array_family);

		/* @brief This function will initialize the array_family struct.                                */
		void (*end)(array_stp array_family);
	}iterators;

	struct {
		/* @brief This function will returns a reference to the element
				  at specified location position, with bounds checking.                                 */
		void *(*at)(array_stp array_family,
					container_size_t position);

		/* @brief This function will returns pointer to the underlying array
				  serving as element storage.                                                           */
		void *(*data)(array_stp array_family);

		/* @brief This function will returns a reference to the first element in the container.         */
		void *(*front)(array_stp array_family);

		/* @brief This function will returns reference to the last element in the container.            */
		void *(*back)(array_stp array_family);
	}element_access;

	struct {
		/* @brief This function will checks if the container has no elements.                           */
		bool (*empty)(array_stp array_family);

		/* @brief This function will returns the number of elements in the container.                   */
		container_size_t(*size)(array_stp array_family);

		/* @brief This function will returns the maximum number of elements the container
				  is able to hold due to system or library implementation limitations.                  */
		container_size_t(*max_size)(array_stp array_family);

		/* @brief This function will returns the number of elements
				  that the container has currently allocated space for.                                 */
		container_size_t(*capacity)(array_stp array_family);
	}capacity;

	struct {
		/* @brief This function will erases all elements from the container.                            */
		void (*clear)(array_stp array_family);

		/* @brief This function will inserts elements at the specified location in the container.       */
		void (*insert)(array_stp array_family,
					   container_size_t position,
					   container_size_t amount, void **source);

	   /* @brief This function will erases the specified elements from the container.                   */
		void (*erase)(array_stp array_family,
					  container_size_t position);

		/* @brief This function will appends the given element source to the end of the container.      */
		void (*push_back)(array_stp array_family,
						  void *source);

		/* @brief This function will removes the last element of the container.                         */
		void (*pop_back)(array_stp array_family);

		/* @brief This function will exchanges the contents of the container with those of other.       */
		void (*swap)(array_stpp array_family,
					 array_stpp other);

		/* @brief This function will copy the contents of the container to those of other.              */
		void (*copy)(array_stpp destination,
					 array_stp source);
	}modifiers;
};

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the array struct.
 *
 * @param array the pointer to the container struct pointer
 * @param element_size the pointer to container
 * @param string_type the pointer to container
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void array_control_configuration_init(array_stpp array,
									  container_size_t element_size,
									  generic_type_element_assign_t assign,
									  generic_type_element_free_t free);

/*
*********************************************************************************************************
*                                       EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

/**
 * @brief This array will contain all the universal array functions address.
 */

extern void *array_function_address_tables[];

#if (ARRAY_CFG_INTEGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This struct will control all the array functions conveniently.
 */

extern struct array_control_s array_ctrl;

#endif

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__ARRAY_H