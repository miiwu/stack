/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __ALGORITHM_DEFINITION_H
#define __ALGORITHM_DEFINITION_H

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

/*
*********************************************************************************************************
*									            DEFINES
*********************************************************************************************************
*/

#pragma warning( disable : 4996)
#pragma warning( disable : 26812)

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/**
 * @brief This type is the compare function prototype typedef.
 */

typedef bool (*compare_t)(void *lhs, void *rhs, size_t len);

/**
 * @brief This type is the swap function prototype typedef.
 */

typedef errno_t(*swap_t)(void *lhs, void *rhs, size_t len);

/**
 * @brief This type is the sort package object operator structure.
 */

struct sort_package_object_operator_s {
	void *(*get_element_ptr)(void *object, size_t loc);
	void *(*get_address_ptr)(void *object, size_t loc);
};

/**
 * @brief This type is the sort package structure.
 */

struct sort_package_s {
	size_t mem_len;
	size_t mem_len_key;
	void *object_ptr;
	swap_t swap_ptr;
	compare_t compare_ptr;

	struct sort_package_object_operator_s object_operator;
};

/**
 * @brief This type is the sort function prototype typedef.
 */

typedef errno_t(*sort_t)(struct sort_package_s package,
						 size_t left,
						 size_t right);

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__ALGORITHM_DEFINITION_H