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

#include "access_iterator_def.h"

#include "unify_structure.h"

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

/**
 * @brief This type is the iterator type enum.
 */

enum iterator_type_e {
	INPUT_ITERATOR = 0x10,
	OUTPUT_ITERATOR = 0x20,
};

/**
 * @brief This type is the iterator object control structure.
 */

struct iterator_control_s {
	struct {
		errno_t(*init)(struct iterator_s **iterator,
					   struct access_iterator_object_unit_s object_unit);

		errno_t(*destroy)(struct iterator_s **iterator);
	}configuration;

	struct {
		struct access_iterator_s *(*begin)(struct iterator_s *iterator);

		struct access_iterator_s *(*end)(struct iterator_s *iterator);

		errno_t(*dereferance)(struct iterator_s *iterator,
							  struct access_iterator_s **access_iterator);
	}iterator_operations;

	struct {
		size_t(*size)(struct iterator_s *iterator);

		bool (*empty)(struct iterator_s *iterator);

		void *(*data)(struct iterator_s *iterator);
	}capacity;
};

/**
 * @brief This type is the unit of the iterator.
 */

struct iterator_unit_s {
	struct iterator_s *iterator_ptr;

	struct iterator_control_s *control_ptr;
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
											enum iterator_type_e iterator_type,
											enum allocator_type_e allocator_type,
											struct access_iterator_object_unit_s object_unit,
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
 * @brief This function will .
 *
 * @param
 *
 * @return
 */

struct access_iterator_s
	*iterator_control_iterator_operation_begin(struct iterator_s *iterator);

/**
 * @brief This function will .
 *
 * @param
 *
 * @return
 */

struct access_iterator_s
	*iterator_control_iterator_operation_end(struct iterator_s *iterator);

/**
 * @brief This function will .
 *
 * @param
 *
 * @return
 */

errno_t iterator_control_iterator_operation_dereference(struct iterator_s *iterator,
														struct access_iterator_s **access_iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *iterator_control_access(struct access_iterator_s *access_iterator,
							  struct access_iterator_access_unit_s access_unit,
							  ...);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *iterator_control_modify(struct access_iterator_s *access_iterator,
							  void *source,
							  struct access_iterator_access_unit_s access_unit,
							  ...);

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