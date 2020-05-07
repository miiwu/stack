/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "unify_adaptor.h"

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

struct unify_adaptor_adaptee_control_s {
	void *init;

	void *destroy;
};

typedef void (*unify_adaptor_package_adaptee_function_s)(void **adaptee, ...);

typedef size_t(*unify_adaptor_package_get_type_id_s)(void *adaptee);

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

struct unify_adaptor_adaptee_control_s
	*unify_adaptor_adaptee_control_ptr = NULL;

/*
 *********************************************************************************************************
 *                                      LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

errno_t unify_adaptor_control_construct_core(void **adaptor,
											 struct unify_adaptor_package_s package);

errno_t unify_adaptor_control_adapt_core(void **adaptor,
										 void *adaptee,
										 struct unify_adaptor_package_s package);

void *unify_adaptor_package_adaptee_function(void *func,
											 void *arg,
											 void *arg_list[8]);

/*
 *********************************************************************************************************
 *					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                            FUNCTIONS
 *********************************************************************************************************
 */

errno_t unify_adaptor_control_construct(void **adaptor,
										struct unify_adaptor_package_s package)
{
	DEBUG_ERROR_CONTROL_ERRNO_INIT(3, 1, 2, 3);

	unify_adaptor_control_construct_core(adaptor, package);
	DEBUG_ERROR_CONTROL_JUDGE(1, "unify_struct_control_construct():adaptor construct fail");

	unify_adaptor_control_readapt(adaptor, package);
	DEBUG_ERROR_CONTROL_JUDGE(2, "unify_adaptor_control_readapt():adaptee adapt fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will destroy the iterator adaptor.
 *
 * @param void
 *
 * @return void
 */

errno_t unify_adaptor_control_readapt(void **adaptor,
									  struct unify_adaptor_package_s package)
{
	DBG_ERR(SINGLE_ERROR,
			errno_t,
			1,
			unify_adaptor_control_adapt_core(adaptor, NULL, package),
			"unify_struct_control_construct():adaptor construct fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

extern errno_t
unify_adaptor_control_adapt_exist(void **adaptor, void *adaptee, struct unify_adaptor_package_s package)
{
	DEBUG_ERROR_CONTROL_ERRNO_INIT(3, 1, 2, 3);

	if (NULL == *adaptor) {
		unify_adaptor_control_construct_core(adaptor, package);
		DEBUG_ERROR_CONTROL_JUDGE(1, "unify_struct_control_destruct(): destruct adaptee fail");

	#if UNIFY_ADAPTOR_CFG_DEBUG_EN

		printf("unify_adaptor_control_adapt_exist(): adaptor is NULL \r\n");

	#endif // UNIFY_ADAPTOR_CFG_DEBUG_EN
	}

	unify_adaptor_control_adapt_core(adaptor, adaptee, package);
	DEBUG_ERROR_CONTROL_JUDGE(2, "unify_adaptor_control_adapt_core(): adaptor adapt adaptee fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

errno_t unify_adaptor_control_destruct(void **adaptor,
									   struct unify_adaptor_package_s package)
{
	DEBUG_ASSERT_CONTROL_POINTER(adaptor);

	DEBUG_ERROR_CONTROL_ERRNO_INIT(3, 1, 2, 3);

	enum unify_adaptor_adapt_status_e adapt_status
		= DEBUG_MICRO_CONTROL_FIELD(*adaptor,
									enum unify_adaptor_adapt_status_e,
									package.adaptor.adapt_status_offset);

	if (ADAPT == adapt_status) {
	#if UNIFY_ADAPTOR_CFG_DEBUG_EN

		printf("unify_adaptor_control_destruct(): adapt_status is ADAPT\r\n");

	#endif // UNIFY_ADAPTOR_CFG_DEBUG_EN

		unify_adaptor_adaptee_control_ptr
			= package.adaptee.function_address_table_set_ptr[package.adaptor.adaptee_type];

		void *adaptee = DEBUG_MICRO_CONTROL_FIELD(*adaptor,
												  void *,
												  package.adaptor.adaptee_unit_offset);

		unify_adaptor_package_adaptee_function(unify_adaptor_adaptee_control_ptr->destroy,
											   &adaptee, NULL);
		DEBUG_ERROR_CONTROL_JUDGE(1, "allocator.deallocate():fail");
	}

	struct allocator_unit_s allocator_unit
		= DEBUG_MICRO_CONTROL_FIELD(*adaptor,
									struct allocator_unit_s,
									package.adaptor.allocator_unit_offest);

	unify_struct_control_destruct(adaptor,
								  allocator_unit,
								  true);
	DEBUG_ERROR_CONTROL_JUDGE(2, "allocator.destroy():fail");

	*adaptor = NULL;

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

static inline errno_t
unify_adaptor_control_construct_core(void **adaptor,
									 struct unify_adaptor_package_s package)
{
	DBG_ERR(SINGLE_ERROR,
			errno_t,
			1,
			DEBUG_MICRO_CONTROL_FIELD(*adaptor,
									  struct allocator_unit_s,
									  package.adaptor.allocator_unit_offest)
			= unify_struct_control_construct(adaptor,
											 package.adaptor.allocator_type,
											 package.adaptor.adaptor_size),
			"unify_struct_control_construct():adaptor construct fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

static errno_t
unify_adaptor_control_adapt_core(void **adaptor,
								 void *adaptee,
								 struct unify_adaptor_package_s package)
{
	DEBUG_ASSERT_CONTROL_POINTER(adaptor);
	DEBUG_ASSERT_CONTROL_POINTER(*adaptor);
	DEBUG_ASSERT_CONTROL_VARIABLE(package.adaptor.adaptee_unit_offset, >= , int, 0);

	DEBUG_ERROR_CONTROL_ERRNO_INIT(2, 1, 2);

	unify_adaptor_package_get_type_id_s
		get_type_id_ptr = package.adaptor.get_adaptee_type;

	void *adaptee4adaptor
		= DEBUG_MICRO_CONTROL_FIELD(*adaptor,
									void *,
									package.adaptor.adaptee_unit_offset);

	if (NULL != adaptee4adaptor) {
	#if UNIFY_ADAPTOR_CFG_DEBUG_EN

		printf("unify_adaptor_control_adapt_core(): adaptor have adaptee \r\n");

	#endif // UNIFY_ADAPTOR_CFG_DEBUG_EN

		package.adaptor.adaptee_type = get_type_id_ptr(adaptee);

		unify_adaptor_adaptee_control_ptr
			= package.adaptee.function_address_table_set_ptr[package.adaptor.adaptee_type];

		unify_adaptor_package_adaptee_function(unify_adaptor_adaptee_control_ptr->destroy,
											   &adaptee4adaptor, NULL);
		DEBUG_ERROR_CONTROL_JUDGE(1, "package.adaptee.destroy():adaptee destroy fail");
}

	if (NULL != adaptee) {
		DEBUG_MICRO_CONTROL_FIELD(*adaptor,
								  enum unify_adaptor_adapt_status_e,
								  package.adaptor.adapt_status_offset) = ADAPT_EXIST;

		package.adaptor.adaptee_type = get_type_id_ptr(adaptee);

		unify_adaptor_adaptee_control_ptr
			= package.adaptee.function_address_table_set_ptr[package.adaptor.adaptee_type];
	} else {
	#if UNIFY_ADAPTOR_CFG_DEBUG_EN

		printf("unify_adaptor_control_adapt_core(): adaptee is NULL \r\n");

	#endif // UNIFY_ADAPTOR_CFG_DEBUG_EN

		unify_adaptor_adaptee_control_ptr
			= package.adaptee.function_address_table_set_ptr[package.adaptor.adaptee_type];

		unify_adaptor_package_adaptee_function(unify_adaptor_adaptee_control_ptr->init,
											   &adaptee, NULL);
		DEBUG_ERROR_CONTROL_JUDGE(2, "package.adaptee.init():adaptee init fail");

		DEBUG_MICRO_CONTROL_FIELD(*adaptor,
								  enum unify_adaptor_adapt_status_e,
								  package.adaptor.adapt_status_offset) = ADAPT;
	}

	DEBUG_MICRO_CONTROL_FIELD(*adaptor, void *,
							  package.adaptor.adaptee_unit_offset)
		= adaptee;
	DEBUG_MICRO_CONTROL_FIELD(*adaptor, void *,
							  package.adaptor.adaptee_unit_offset
							  + package.adaptor.adaptee_unit_size
							  - sizeof(void *))
		= unify_adaptor_adaptee_control_ptr;

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

static inline void
*unify_adaptor_package_adaptee_function(void *func, void *arg, void *arg_list[8])
{
	DEBUG_ASSERT_CONTROL_POINTER(func);

	void *(*function)(void *, ...) = func;

	if (NULL == arg_list) {
		return function(arg);
	}

	return function(arg,
					arg_list[0], arg_list[1], arg_list[2], arg_list[3],
					arg_list[4], arg_list[5], arg_list[6], arg_list[7]);
}