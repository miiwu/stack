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

/* Define			iterator control assert variable.										            */
#define ITERATOR_CONTROL_ASSERT_VARIABLE(variable, comp, value_type, value)                             \
    DEBUG_ASSERT_CONTROL_VARIABLE(variable, comp, value_type, value,                                    \
        printf("Assert Failed: \r\n\tfunc:\"%s\" assert:\"%s %s %s\"\r\n\tfile:\"%s\" line:%ld\r\n",    \
               __FUNCTION__,#variable,#comp,#value,                                                     \
               __FILE__,(size_t)__LINE__))

/* Define			iterator control assert pointer.										            */
#define ITERATOR_CONTROL_ASSERT_POINTER(pointer)                                                        \
    DEBUG_ASSERT_CONTROL_POINTER(pointer,                                                               \
        printf("Assert Failed: \r\n\tfunc:\"%s\" assert:\"%s\"\r\n\tfile:\"%s\" line:%ld\r\n",          \
               __FUNCTION__,#pointer,                                                                   \
               __FILE__,(size_t)__LINE__))

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

/**
 * @brief This type is the iterator type enum.
 */

enum iterator_type {
	ITORATER,
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
 * @brief This type is the iterator allocator unit structure.
 */

struct iterator_allocator_unit_s {
	/* @brief This variables will point to the object.						                            */
	void *allocator_ptr;

	/* @brief This variables will point to the control structure of the object_ptr.				        */
	struct allocator_control_s *control_ptr;
};

/**
 * @brief This type is the iterator feature package structure.
 */

struct iterator_feature_package_s {
	/* @brief This variables will point to the object.						                            */
	bool (*advance)(int step);
};

/*
 *********************************************************************************************************
 *								            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

/**
 * @brief This function will initialize the iterator.
 *
 * @param
 *
 * @return
 */

errno_t iterator_control_configuration_init(struct iterator_s **iterator,
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

errno_t iterator_control_iterator_operations_modify(struct iterator_s *iterator,
													void *source);

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
 * @brief This function will check if the at iterator operations can perform.
 *
 * @param
 *
 * @return
 */

bool iterator_control_iterator_operations_at_check(struct iterator_s *iterator,
												   size_t index);

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