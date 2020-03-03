/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __VECTOR_H
#define __VECTOR_H

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

/* Configure    the default max size of vector.                                                         */
#define VECTOR_CFG_DEFAULT_MAX_SIZE								100u

/* Configure    if enable integrated structure.                                                         */
#define VECTOR_CFG_DEFAULT_HARDWARE_MAX_AVAILABLE_HEAP_SIZE		1024u

/* Configure    the type of allocator.                                                                  */
#define VECTOR_CFG_ALLOCATOR_TYPE                           ALLOCATOR_COMMON

/* Configure    if enable integrated structure.                                                         */
#define VECTOR_CFG_INTEGRATED_STRUCTURE_MODE_EN			    1u

/* Configure    if enable vector debug.																    */
#define VECTOR_CFG_DEBUG_EN										0u

/*
*********************************************************************************************************
*									            DATA TYPES
*********************************************************************************************************
*/

/* Configure    vector ptr type.                                                                        */
typedef struct array_family_s
*vector_tp,
**vector_tpp;

#if (VECTOR_CFG_INTEGRATED_STRUCTURE_MODE_EN)

struct vector_control_s {
	struct {
		/* @brief This function will initialize the vector struct.                                      */
		void (*init)(vector_tpp vector,
					 container_size_t dst_size,
					 generic_type_element_assign_t assign,
					 generic_type_element_free_t free);

		/* @brief This function will destroy the vector struct and free the space.                      */
		void (*destroy)(vector_tpp vector);

		/* @brief This function will configure the vector element handler.                              */
		void (*element_handler)(vector_tp vector,
								generic_type_element_assign_t assign,
								generic_type_element_free_t free);

		/* @brief This function will configure the vector exception callback.                           */
		void (*exception)(vector_tp vector,
						  void (*empty)(void), void (*full)(void));
	}configuration;

	struct {
		/* @brief This function will initialize the vector struct.                                      */
		void (*begin)(vector_tp vector);

		/* @brief This function will initialize the vector struct.                                      */
		void (*end)(vector_tp vector);
	}iterators;

	struct {
		/* @brief This function will returns a reference to the element
				  at specified location position, with bounds checking.                                 */
		void *(*at)(vector_tp vector,
					container_size_t position);

		/* @brief This function will returns pointer to the underlying array
				  serving as element storage.                                                           */
		void *(*data)(vector_tp vector);

		/* @brief This function will returns a reference to the first element in the container.         */
		void *(*front)(vector_tp vector);

		/* @brief This function will returns reference to the last element in the container.            */
		void *(*back)(vector_tp vector);
	}element_access;

	struct {
		/* @brief This function will checks if the container has no elements.                           */
		bool (*empty)(vector_tp vector);

		/* @brief This function will returns the number of elements in the container.                   */
		container_size_t(*size)(vector_tp vector);

		/* @brief This function will returns the maximum number of elements the container
				  is able to hold due to system or library implementation limitations.                  */
		container_size_t(*max_size)(vector_tp vector);

		/* @brief This function will returns the number of elements
				  that the container has currently allocated space for.                                 */
		container_size_t(*capacity)(vector_tp vector);

		/* @brief This function will increase the capacity of the vector to a size
				  that's greater or equal to new_cap. */
		void (*reserve)(vector_tpp vector,
						container_size_t size);

		/* @brief This function will requests the removal of unused capacity.                           */
		void (*shrink_to_fit)(vector_tpp vector);
	}capacity;

	struct {
		/* @brief This function will erases all elements from the container.                            */
		void (*clear)(vector_tp vector);

		/* @brief This function will inserts elements at the specified location in the container.       */
		void (*insert)(vector_tp vector,
					   container_size_t position, container_size_t amount, void **source);

	   /* @brief This function will erases the specified elements from the container.                  */
		void (*erase)(vector_tp vector,
					  container_size_t position);

		/* @brief This function will appends the given element source to the end of the container.      */
		void (*push_back)(vector_tp vector,
						  void *source);

		/* @brief This function will removes the last element of the container.                         */
		void (*pop_back)(vector_tp vector);

		/* @brief This function will resizes the container to contain count elements.                   */
		void (*resize)(vector_tpp vector,
					   container_size_t size);

		/* @brief This function will copy the contents of the container to those of other.              */
		void (*copy)(vector_tpp destination,
					 vector_tp source);

		/* @brief This function will exchanges the contents of the container with those of other.       */
		void (*swap)(vector_tpp vector,
					 vector_tpp other);
	}modifiers;
};

#endif // (VECTOR_CONTROL_INTEGRATED_STRUCTURE_MODE_EN)

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
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

void vector_control_configuration_init(vector_tpp vector,
									   container_size_t element_size,
									   generic_type_element_assign_t assign,
									   generic_type_element_free_t free);

/*
*********************************************************************************************************
*                                       EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

/**
 * @brief This array will contain all the universal vector functions address.
 */

extern void *vector_function_address_tables[];

#if (VECTOR_CFG_INTEGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This struct will control all the vector functions conveniently.
 */
extern struct vector_control_s vector_ctrl;

#endif

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__VECTOR_H