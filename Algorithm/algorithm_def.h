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

/* Configure the enum category of sort algorithm.														*/
enum sort_algorithm_category {
	UNSTABLE_SORT = 0x10,

	STABLE_SORT = 0x20,
};

/* Configure the enum type of sort algorithm.															*/
enum sort_algorithm_type {
	QUICK_SORT = UNSTABLE_SORT + 0x01,

	BUBBLE_SORT = STABLE_SORT + 0x01,
};

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