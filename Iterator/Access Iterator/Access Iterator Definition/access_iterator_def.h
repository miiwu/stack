/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __ACCESS_ITERATOR_DEFINITION_H
#define __ACCESS_ITERATOR_DEFINITION_H

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

#include "unify_structure.h"

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
 * @brief This type is the access iterator type enum.
 */

enum access_iterator_type_e {
	FORWARD_ITERATOR = 0x01,
	BIDIRECTIONAL_ITERATOR,
	RANDOM_ACCESS_ITERATOR,
	CONTINUOUS_ITERATOR,
};

/**
 * @brief This type is the iterator object control structure.
 */

struct access_iterator_object_control_s {
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

		/* @brief This function will returns the size of the object's single element.	                */
		size_t(*element_size)(void *object);
	}capacity;

	struct {
		/* @brief This function will modify the specific element of the underlying object.			    */
		void *(*modify)(void *object,
						size_t index,
						void *source);
	}modifiers;
};

/**
 * @brief This type is the iterator object unit structure.
 */

struct access_iterator_object_unit_s {
	void *object_ptr;

	struct access_iterator_object_control_s *control_ptr;
};

/**
 * @brief This type is the access iterator access unit structure.
 */

struct access_iterator_access_unit_s {
	void *(*function_ptr)(struct access_iterator_s *access_iterator,
						  ...);

	void *(*extension_ptr)(struct access_iterator_s *access_iterator,
						   size_t index);
};

/**
 * @brief This type is the access iterator access unit structure.
 */

struct access_iterator_advance_unit_s {
	struct access_iterator_access_unit_s access_unit;

	bool (*valid_step_ptr)(int step);
};

/**
 * @brief This type is the iterator control structure.
 */

struct access_iterator_control_s {
	struct {
		void *(*advance)(struct access_iterator_s *access_iterator,
						 struct access_iterator_advance_unit_s advance_unit,
						 int step);

		int(*distance)(struct access_iterator_s *lhs,
					   struct access_iterator_s *rhs);

		void *(*next)(struct access_iterator_s *access_iterator,
					  struct access_iterator_access_unit_s access_unit);

		void *(*prev)(struct access_iterator_s *access_iterator,
					  struct access_iterator_access_unit_s access_unit);

		void *(*front)(struct access_iterator_s *access_iterator,
					   struct access_iterator_access_unit_s access_unit);

		void *(*back)(struct access_iterator_s *access_iterator,
					  struct access_iterator_access_unit_s access_unit);
	}element_access;

	struct {
		size_t(*size)(struct access_iterator_s *access_iterator);

		bool (*empty)(struct access_iterator_s *access_iterator);

		void *(*data)(struct access_iterator_s *access_iterator);

		size_t(*max_size)(struct access_iterator_s *access_iterator);

		size_t(*element_size)(struct access_iterator_s *access_iterator);
	}range_access;

	void *(*modify)(struct access_iterator_s *access_iterator,
					void *source);
};

/*
 *********************************************************************************************************
 *								            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void
*access_iterator_control_element_access_advance(struct access_iterator_s *access_iterator,
												struct access_iterator_advance_unit_s advance_unit,
												int step);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

int
access_iterator_control_element_access_distance(struct access_iterator_s *lhs,
												struct access_iterator_s *rhs);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void
*access_iterator_control_element_access_next(struct access_iterator_s *access_iterator,
											 struct access_iterator_access_unit_s access_unit);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void
*access_iterator_control_element_access_prev(struct access_iterator_s *access_iterator,
											 struct access_iterator_access_unit_s access_unit);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void
*access_iterator_control_iterator_operations_at(struct access_iterator_s *access_iterator,
												struct access_iterator_access_unit_s access_unit,
												size_t index);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void
*access_iterator_control_element_access_front(struct access_iterator_s *access_iterator,
											  struct access_iterator_access_unit_s access_unit);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void
*access_iterator_control_element_access_back(struct access_iterator_s *access_iterator,
											 struct access_iterator_access_unit_s access_unit);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

size_t access_iterator_control_range_access_size(struct access_iterator_s *access_iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

size_t access_iterator_control_range_access_max_size(struct access_iterator_s *access_iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

size_t access_iterator_control_range_access_element_size(struct access_iterator_s *access_iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

bool access_iterator_control_range_access_empty(struct access_iterator_s *access_iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_range_access_data(struct access_iterator_s *access_iterator);

/*
 *********************************************************************************************************
 *                                       EXTERN GLOBAL VARIABLES
 *********************************************************************************************************
 */

/**
 * @brief This type is the iterator control structure.
 */

extern struct access_iterator_control_s access_iterator_control;

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

#endif // !__ACCESS_ITERATOR_DEFINITION_H