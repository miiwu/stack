/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __ITERATOR_DEFINITION_H
#define __ITERATOR_DEFINITION_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include <malloc.h>

#include "debug_component.h"

#include "allocator.h"

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/* Disable			compiler warning.										                            */
#pragma warning( disable : 4996)
#pragma warning( disable : 26812)

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

/**
 * @brief This type is the iterator type enum.
 */

enum iterator_type_e {
	INPUT_ITORATER = 1,
	FORWARD_ITORATER,
	BIDIRECTIONAL_ITORATER,
	RANDOM_ACCESS_ITORATER,
	OUTPUT_ITORATER,
	CONTIGUOUS_ITERATOR,
};

/**
 * @brief This type is the iterator object control structure.
 */

struct iterator_object_control_s {
	struct {
		/* @brief This function will returns a reference to the element
			at specified location position, with bounds checking.								        */
		void *(*at)(void *object, size_t position);

		/* @brief This function will returns pointer to the underlying array
				  serving as element storage.                                                           */
		void *(*data)(void *object);
	}element_access;

	struct {
		/* @brief This function will check if the underlying object has no elements.					*/
		bool(*empty)(void *object);

		/* @brief This function will returns the number of elements in the object.					    */
		size_t(*size)(void *object);

		/* @brief This function will returns the maximum number of elements
					the object is able to hold due to system or library implementation limitations.	    */
		size_t(*max_size)(void *object);
	}capacity;

	struct {
		/* @brief This function will modify the specific element of the underlying object.			    */
		errno_t(*modify)(void *object,
						 size_t index,
						 void *source);
	}modifiers;
};

/**
 * @brief This type is the iterator common information structure.
 */

struct iterator_common_information_s {
	size_t position;

	bool featured;
};

/**
 * @brief This type is the iterator object unit structure.
 */

struct iterator_object_unit_s {
	/* @brief This variables will point to the object.						                            */
	void *object_ptr;

	/* @brief This variables will point to the control structure of the object_ptr.				        */
	struct iterator_object_control_s *control_ptr;
};

/**
 * @brief This type is the iterator allocate package structure.
 */

struct iterator_allocate_package_s {
	enum iterator_type_e type;

	size_t mem_size;
};

/**
 * @brief This type is the iterator allocate package structure.
 */

struct iterator_allocate_return_package_s {
    errno_t error;

    struct allocator_unit_s allocator_unit;
};

/**
 * @brief This type is the iterator feature package structure.
 */

struct iterator_feature_package_s {
	/* @brief This variables will point to the object.						                            */
	bool (*advance)(int step);
};

/**
 * @brief This type is the iterator feature package structure.
 */

struct iterator_adaptor_allocate_package_s {
    enum iterator_type_e type;

    struct iterator_object_unit_s object_unit;

    size_t addon_size;
};

/*
 *********************************************************************************************************
 *								            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

/**
 * @brief This function will allocate the iterator.
 *
 * @param
 *
 * @return
 */

struct iterator_allocate_return_package_s
    iterator_control_configuration_allocate(void **iterator,
                                            struct iterator_allocate_package_s package);

/**
 * @brief This function will initialize the iterator.
 *
 * @param
 *
 * @return
 */

errno_t iterator_control_configuration_init(struct iterator_s **iterator,
											enum iterator_type_e type,
											struct iterator_object_unit_s object_unit,
											size_t addon_size);

/**
 * @brief This function will destroy the iterator.
 *
 * @param
 *
 * @return
 */

errno_t iterator_control_configuration_destroy(struct iterator_s **iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *iterator_control_iterator_operations_advance(struct iterator_s *iterator,
												   int step);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *iterator_control_iterator_operations_next(struct iterator_s *iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *iterator_control_iterator_operations_prev(struct iterator_s *iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *iterator_control_iterator_operations_at(struct iterator_s *iterator,
											  size_t index);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *iterator_control_range_access_begin(struct iterator_s *iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *iterator_control_range_access_end(struct iterator_s *iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

size_t iterator_control_range_access_size(struct iterator_s *iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

bool iterator_control_range_access_empty(struct iterator_s *iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *iterator_control_range_access_data(struct iterator_s *iterator);

/**
 * @brief This function will inquire for the allocator unit of the iterator.
 *
 * @param iterator the pointer to the iterator
 *
 * @return the allocator unit of the iterator
 */

struct allocator_unit_s iterator_control_inquire_allocator_unit(struct iterator_s *iterator);

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

#endif // !__ITERATOR_DEFINITION_H