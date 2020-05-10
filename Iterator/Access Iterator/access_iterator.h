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

/*
 *********************************************************************************************************
 *								            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

/**
 * @brief This function will destroy the iterator.
 *
 * @param
 *
 * @return
 */

errno_t access_iterator_control_configuration_destroy(struct iterator_s **iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_iterator_operations_advance(struct iterator_s *iterator,
												   int step);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_iterator_operations_next(struct iterator_s *iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_iterator_operations_prev(struct iterator_s *iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_iterator_operations_at(struct iterator_s *iterator,
											  size_t index);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_range_access_begin(struct iterator_s *iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_range_access_end(struct iterator_s *iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

size_t access_iterator_control_range_access_size(struct iterator_s *iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

bool access_iterator_control_range_access_empty(struct iterator_s *iterator);

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_range_access_data(struct iterator_s *iterator);

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