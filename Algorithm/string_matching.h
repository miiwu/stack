/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __STRING_MATCHING_H
#define __STRING_MATCHING_H

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

/* Configure        if enable string matching debug.													*/
#define STRING_MATCHING_CFG_DEBUG_EN										1u

/* Configure        if enable max match rate.															*/
#define STRING_MATCHING_CFG_MAX_MATCH_RATE_EN								1u

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
* @brief This function will search the substring upon the string by the brute force algorithm.
*
* @param str the pointer to the string.
* @param substr the pointer to the substring.
* @param len the length of the substring.
*
* @return the max matching rate.
*/

float substring_search_control_brute_force_algorithm(const char *str, size_t len,
													 const char *substr, size_t sublen);

/**
* @brief This function will search the substring upon the string by the sunday algorithm.
*
* @param str the pointer to the string.
* @param substr the pointer to the substring.
* @param len the length of the substring.
*
* @return the max matching rate.
*/

float substring_search_control_sunday_algorithm(const char *str, size_t len,
												const char *substr, size_t sublen);

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

#endif // !__STRING_MATCHING_H