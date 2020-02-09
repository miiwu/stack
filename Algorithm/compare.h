/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __COMPARE_H
#define __COMPARE_H

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "algorithm_def.h"

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
 * @brief This struct is the compare structure module
 */

typedef bool compare_t(void *lhs, void *rhs, size_t len);

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
* @brief This function will compare if the left-hand-side lesser than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side lesser than the right-hand-side
*	- true	yes
*	- false	no
*/

bool compare_control_lesser(void *lhs, void *rhs, size_t len);

/**
* @brief This function will compare if the left-hand-side greater than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side greater than the right-hand-side
*	- true	yes
*	- false	no
*/

bool compare_control_greater(void *lhs, void *rhs, size_t len);

/**
* @brief This function will compare if the left-hand-side equal with the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side equal with the right-hand-side
*	- true	yes
*	- false	no
*/

bool compare_control_equal(void *lhs, void *rhs, size_t len);

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

#endif // !__COMPARE_H