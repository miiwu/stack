/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __CONTAINER_CONFIGURATION_H
#define __CONTAINER_CONFIGURATION_H

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

/* User-defined     container global allocator file.													*/
#include "allocator.h"

/* User-defined     container global algorithm file.													*/
#include "algorithm.h"

/*
********************************************************************************************************
*									            DEFINES
********************************************************************************************************
*/

/**
 *                               G L O B L E   C O N F I G U R A T I O N
 */

/* Configure        container global size type.															*/
#define CONTAINER_GLOBAL_CFG_SIZE_TYPE											size_t

#pragma warning( disable : 4996)
#pragma warning( disable : 26812)

/**
 *                      G L O B L E   C A T E G O R Y   C O N F I G U R A T I O N
 */

/* Configure        if enable sequence containers.													    */
#define CONTAINER_GLOBAL_CATEGORY_CFG_SEQUENCE_CONTAINERS_EN				    1u

/* Configure        if enable associative containers.												    */
#define CONTAINER_GLOBAL_CATEGORY_CFG_ASSOCIATIVE_CONTAINERS_EN				    0u

/* Configure        if enable unordered associative containers.										    */
#define CONTAINER_GLOBAL_CATEGORY_CFG_UNORDERED_ASSOCIATIVE_CONTAINERS_EN	    0u

/* Configure        if enable container adaptors.													    */
#define CONTAINER_GLOBAL_CATEGORY_CFG_CONTAINER_ADAPTORS_EN				        1u

/**
 *                          G L O B L E   T Y P E   C O N F I G U R A T I O N
 */

/*                  S E Q U E N C E   C O N T A I N E R S   C O N F I G U R A T I O N                   */
/* If			    enable the sequence containers.													    */
#if (CONTAINER_GLOBAL_CATEGORY_CFG_SEQUENCE_CONTAINERS_EN)

/* Configure        if enable tree family.																*/
#define CONTAINER_GLOBAL_TYPE_CFG_TREE_FAMILT_EN							    1u

/* Configure        if enable array family.																*/
#define CONTAINER_GLOBAL_TYPE_CFG_ARRAY_FAMILY_EN								1u

/* Configure        if enable list family.														        */
#define CONTAINER_GLOBAL_TYPE_CFG_LIST_FAMILY_EN								1u

#endif // (CONTAINER_GLOBAL_CATEGORY_CFG_SEQUENCE_CONTAINERS_EN)

/*              A S S O C I A T I V E   C O N T A I N E R S   C O N F I G U R A T I O N                 */
/* If			    enable the associative containers.												    */
#if (CONTAINER_GLOBAL_CATEGORY_CFG_ASSOCIATIVE_CONTAINERS_EN)

#endif // (CONTAINER_GLOBAL_CATEGORY_CFG_ASSOCIATIVE_CONTAINERS_EN)

/*      U N O R D E R E D   A S S O C I A T I V E   C O N T A I N E R S   C O N F I G U R A T I O N     */
/* If			    enable the unordered associative containers.									    */
#if (CONTAINER_GLOBAL_CATEGORY_CFG_UNORDERED_ASSOCIATIVE_CONTAINERS_EN)

#endif // (CONTAINER_GLOBAL_CATEGORY_CFG_UNORDERED_ASSOCIATIVE_CONTAINERS_EN)

/*                   C O N T A I N E R   A D A P T O R S   C O N F I G U R A T I O N                    */
/* If			    enable the container tree family													*/
#if (CONTAINER_GLOBAL_CATEGORY_CFG_CONTAINER_ADAPTORS_EN)

/* Configure        if enable stack.															        */
#define CONTAINER_GLOBAL_TYPE_CFG_STACK_EN										1u

/* Configure        if enable queue.															        */
#define CONTAINER_GLOBAL_TYPE_CFG_QUEUE_EN										1u

#endif // (CONTAINER_GLOBAL_CATEGORY_CFG_CONTAINER_ADAPTORS_EN)

/**
 *                         F A M I L Y   L E V E L   C O N F I G U R A T I O N
 */

/*                          T R E E   F A M I L Y   C O N F I G U R A T I O N                           */
/* If			    enable the container tree family													*/
#if (CONTAINER_GLOBAL_TYPE_CFG_TREE_FAMILT_EN)

/* Configure        if enable binary search tree.														*/
#define CONTAINER_FAMILY_LEVEL_CFG_BINARY_TREE_EN								1u

/* Configure        if enable red black tree.															*/
#define CONTAINER_FAMILY_LEVEL_CFG_RED_BLACK_TREE_EN							1u

/* Configure        if enable b tree.																    */
#define CONTAINER_FAMILY_LEVEL_CFG_B_TREE_EN									1u

#endif // (CONTAINER_GLOBAL_TYPE_CFG_TREE_FAMILT_EN)

/*                          A R R A Y   F A M I L Y   C O N F I G U R A T I O N                         */
/* If			    enable the container array family													*/
#if (CONTAINER_GLOBAL_TYPE_CFG_ARRAY_FAMILY_EN)

/* Configure        if enable red black tree.															*/
#define CONTAINER_FAMILY_LEVEL_CFG_ARRAY_EN                                     1u

/* Configure        if enable red black tree.															*/
#define CONTAINER_FAMILY_LEVEL_CFG_VECTOR_EN                                    1u

#endif // (CONTAINER_GLOBAL_TYPE_CFG_ARRAY_FAMILY_EN)

/*                          L I S T   F A M I L Y   C O N F I G U R A T I O N                           */
/* If			    enable the container list family													*/
#if (CONTAINER_GLOBAL_TYPE_CFG_LIST_FAMILY_EN)

/* Configure        if enable forward list.																*/
#define CONTAINER_FAMILY_LEVEL_CFG_FORWARD_LIST_EN								1u

/* Configure        if enable list.																		*/
#define CONTAINER_FAMILY_LEVEL_CFG_LIST_EN										1u

#endif // (CONTAINER_GLOBAL_TYPE_CFG_LIST_FAMILY_EN)

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

#endif // !__CONTAINER_CONFIGURATION_H