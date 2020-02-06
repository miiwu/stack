/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "compare.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            FUNCTIONS
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

bool compare_control_lesser(void *lhs, void *rhs, size_t len)
{
	assert(lhs);
	assert(rhs);
	assert(len);

	for (size_t cnt = 0; cnt < len; cnt++) {
		if (*((char *)lhs + cnt) < *((char *)rhs + cnt)) {
			return true;
		}
	}

	return false;
}

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

bool compare_control_greater(void *lhs, void *rhs, size_t len)
{
	assert(lhs);
	assert(rhs);
	assert(len);

	for (size_t cnt = 0; cnt < len; cnt++) {
		if (*((char *)lhs + cnt) > *((char *)rhs + cnt)) {
			return true;
		}
	}

	return false;
}

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

bool compare_control_equal(void *lhs, void *rhs, size_t len)
{
	assert(lhs);
	assert(rhs);
	assert(len);

	size_t cnt_equal_hit = 0;

	for (size_t cnt = 0; cnt < len; cnt++) {
		if (*((char *)lhs + cnt) == *((char *)rhs + cnt)) {
			cnt_equal_hit++;
		} else {
			return false;
		}
	}

	if (len == cnt_equal_hit) {
		return true;
	} else {
		return false;
	}
}
