/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __UNIFY_ADAPTOR_H
#define __UNIFY_ADAPTOR_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "unify_struct.h"

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

#define UNIFY_ADAPTOR_CFG_DEBUG_EN                                                  1

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

enum unify_adaptor_adapt_status_e {
	ADAPT,
	ADAPT_EXIST,
};

struct unify_adaptor_package_s {
	struct {
		size_t
			adaptee_type,
			adaptee_unit_offset,
			adaptee_unit_size,
			adaptor_size,
			adapt_status_offset,
			allocator_unit_offest;

		enum allocator_type_e allocator_type;

		void *get_adaptee_type;
	}adaptor;

	struct {
		void
			*init_arg_ptr[8],
			**function_address_table_set_ptr;

		size_t allocator_unit_offest;
	}adaptee;
};

/*
 *********************************************************************************************************
 *								            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

errno_t unify_adaptor_control_construct(void **adaptor,
										struct unify_adaptor_package_s package);

errno_t unify_adaptor_control_readapt(void **adaptor,
									  struct unify_adaptor_package_s package);

errno_t unify_adaptor_control_adapt_exist(void **adaptor, void *adaptee, struct unify_adaptor_package_s package);

errno_t unify_adaptor_control_destruct(void **adaptor,
									   struct unify_adaptor_package_s package);

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

#endif // !__UNIFY_ADAPTOR_H