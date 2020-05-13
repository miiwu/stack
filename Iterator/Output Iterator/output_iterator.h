/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __OUTPUT_ITERATOR_H
#define __OUTPUT_ITERATOR_H

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

/* Configure    the allocator type of the output iterator.                                              */
#define OUTPUT_ITERATOR_CFG_ALLOCATOR_TYPE                                                              \
    CONCEPT_ALLOCATOR

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

/**
 * @brief This type is the output iterator structure typedef.
 */

typedef struct iterator_s
*output_iterator_stp,
**output_iterator_stpp;

/**
 * @brief This type is the output iterator control structure.
 */

struct output_iterator_control_s {
	struct iterator_control_s;

	void *(*access)(struct access_iterator_s *access_iterator,
					struct access_iterator_access_unit_s access_unit,
					...);

	void *(*modify)(struct access_iterator_s *access_iterator,
					void *source,
					struct access_iterator_access_unit_s access_unit,
					...);
};

/*
 *********************************************************************************************************
 *								            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

errno_t output_iterator_control_configuration_init(output_iterator_stpp output_iterator,
												   struct access_iterator_object_unit_s object_unit);

/*
 *********************************************************************************************************
 *                                       EXTERN GLOBAL VARIABLES
 *********************************************************************************************************
 */

/**
 * @brief This type is the output iterator control structure.
 */

extern struct output_iterator_control_s output_iterator_control;

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

#endif // !__OUTPUT_ITERATOR_H