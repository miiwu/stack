/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __RANDOM_ACCESS_ITERATOR_H
#define __RANDOM_ACCESS_ITERATOR_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "iterator_def.h"

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
 * @brief This type is the iterator typedef.
 */

typedef struct iterator_s
*random_access_iterator_stp,
**random_access_iterator_stpp;

/**
 * @brief This type is the iterator control structure.
 */

struct random_access_iterator_control_s {
	struct {
		errno_t(*init)(random_access_iterator_stpp iterator,
					   struct iterator_object_unit_s object_unit);

		errno_t(*destroy)(random_access_iterator_stpp iterator);
	}configuration;

	struct {
		void *(*advance)(random_access_iterator_stp iterator,
						 int step);

		size_t(*distance)(random_access_iterator_stp iterator);

		void *(*next)(random_access_iterator_stp iterator);

		void *(*prev)(random_access_iterator_stp iterator);

		void *(*at)(random_access_iterator_stp iterator,
					size_t index);
	}iterator_operations;

	struct {
		void *(*begin)(random_access_iterator_stp iterator);

		void *(*end)(random_access_iterator_stp iterator);

		size_t(*size)(random_access_iterator_stp iterator);

		bool (*empty)(random_access_iterator_stp iterator);

		void *(*data)(random_access_iterator_stp iterator);
	}range_access;
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

errno_t random_access_iterator_control_configuration_init(random_access_iterator_stpp iterator,
                                                          struct iterator_object_unit_s object_unit);

/*
 *********************************************************************************************************
 *                                       EXTERN GLOBAL VARIABLES
 *********************************************************************************************************
 */

/**
 * @brief This type is the iterator control structure.
 */

extern struct random_access_iterator_control_s random_access_iterator_control;

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

#endif // !__RANDOM_ACCESS_ITERATOR_H