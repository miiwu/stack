/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __CONTAINER_ADAPTOR_FAMILY_H
#define __CONTAINER_ADAPTOR_FAMILY_H

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "container.h"

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
 * @brief This struct is the container adaptor structure.
 */

struct container_adaptor_s;

/**
 * @brief This struct is the container adaptor structure.
 */

struct container_adaptor_adapt_package_s {
	void *container;

	enum container_type_e container_type;
	container_size_t element_size;
	generic_type_element_assign_t assign;
	generic_type_element_free_t free;
};

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the container adaptor.
 *
 * @param void
 *
 * @return void
 */

errno_t container_adapotr_control_configuration_init(struct container_adaptor_s **adaptor,
                                                     enum container_type_e adaptor_type,
                                                     struct container_allocte_package_s allocate_package,
                                                     struct container_adaptor_adapt_package_s adapt_package,
                                                     void *addon,
                                                     size_t addon_size);

/**
 * @brief This function will initialize the container struct and attach to the specified container.
 *
 * @param container the container adapter struct
 *
 * @return the pointer to the specified container function address table.
 */

extern void *container_adaptor_control_get_container_func_addr_table(enum container_type_e type);

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

#endif // !__CONTAINER_ADAPTOR_FAMILY_H