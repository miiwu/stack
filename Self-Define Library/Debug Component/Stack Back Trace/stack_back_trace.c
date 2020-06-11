/*
 ************************************************************************************************************************
 *                                  DEBUG COMPONENT OF CAPATURE STACK BACK TRACE FUNCTIONS
 *
 * File    : DEBUG_CAPATURE_STACK_BACK_TRACE.C
 * By      : Miao Mico
 * Version : V0.01.00
 *
 * FIRST ENLIGHTENMENT : https://gist.github.com/t-mat/7979300
 * SECONDARY REFERANCE : https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/bb204633(v=vs.85)?redirectedfrom=MSDN
 *
 ************************************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "stack_back_trace.h"

#include "stack_back_trace_pvt_def.h"

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

stack_back_trace_size_t _built_in_stack_back_trace_count_;

struct stack_back_trace_trace_unit_s _built_in_stack_back_trace_trace_unit_ = { 0 };

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

errno_t stack_back_trace_control_trace_address_group(stack_back_trace_stp stack_back_trace,
													 struct stack_back_trace_trace_unit_s trace_unit);

bool stack_back_trace_control_exception_full_types_trap(stack_back_trace_stp stack_back_trace);

bool stack_back_trace_control_exception_full_types_callback(stack_back_trace_stp stack_back_trace);

/*
 *********************************************************************************************************
 *					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
 *********************************************************************************************************
 */

struct stack_back_trace_s _built_in_stack_back_trace_ = {
	.info.types.max = 1,
	.info.count_ptr = &_built_in_stack_back_trace_count_,

	.trace_unit_ptr = &_built_in_stack_back_trace_trace_unit_,

	.exception.full_types_callback = stack_back_trace_control_exception_full_types_callback,
};

/*
 *********************************************************************************************************
 *                                            FUNCTIONS
 *********************************************************************************************************
 */

/**
 * @brief This function will initialize the capture stack back trace struct.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param count the amount of type stack situation
 *
 * @return NONE
 */

errno_t stack_back_trace_control_init(stack_back_trace_stpp stack_back_trace,
									  stack_back_trace_size_t type_count)
{
	assert(stack_back_trace);
	assert(0u < type_count);

	errno_t fail_code = 0;

	if (NULL == stack_back_trace) {
		fail_code = 1;

		goto EXIT;
	}

	(*stack_back_trace)
		= calloc(1, sizeof(struct stack_back_trace_s));
	if (NULL == (*stack_back_trace)) {
		fail_code = 2;

		goto EXIT;

	DEALLOCATE_1:
		free((*stack_back_trace));

		goto EXIT;
	}

	(*stack_back_trace)->trace_unit_ptr
		= calloc(type_count, sizeof(struct stack_back_trace_trace_unit_s));
	if (NULL == (*stack_back_trace)->trace_unit_ptr) {
		fail_code = 3;

		goto DEALLOCATE_1;

	DEALLOCATE_2:
		free((*stack_back_trace)->trace_unit_ptr);

		goto DEALLOCATE_1;
	}

	if (1 < type_count) {
		(*stack_back_trace)->info.count_ptr
			= calloc(type_count, sizeof(stack_back_trace_size_t));
		if (NULL == (*stack_back_trace)->info.count_ptr) {
			fail_code = 4;

			goto DEALLOCATE_2;
		}
	}

	(*stack_back_trace)->info.types.max = type_count;
	(*stack_back_trace)->info.types.current = 0u;

EXIT:

	return fail_code;
}

/**
 * @brief This function will destroy the capture stack back trace struct.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 *
 * @return NONE
 */

void stack_back_trace_control_destroy(stack_back_trace_stpp stack_back_trace)
{
	assert(stack_back_trace);

	if (NULL == stack_back_trace
		|| NULL == (*stack_back_trace)) {
		return;
	}

	free((*stack_back_trace)->trace_unit_ptr);

	if (NULL != (*stack_back_trace)->info.count_ptr) {
		free((*stack_back_trace)->info.count_ptr);
	}

	free((*stack_back_trace));

	(*stack_back_trace) = NULL;
}

/**
 * @brief This function will back trace the stack.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param frames_to_skip the amount of stack the capture back trace will skip
 * @param frames_to_capture the amount of stack the capture back trace will capture
 *
 * @return NONE
 */

errno_t stack_back_trace_control_trace_address(stack_back_trace_stp stack_back_trace,
											   stack_back_trace_frame_t skip,
											   stack_back_trace_frame_t capture)
{
	assert(stack_back_trace);
	assert(0u <= skip);
	assert(0u <= capture);

	errno_t error_code = 0;

	if (NULL == stack_back_trace) {
		error_code = 1;

		goto EXIT;
	}

	stack_back_trace_address_t
		*address_list[STACK_BACK_TRACE_CFG_FRAMES_CAPTURE_MAX] = { NULL };
	struct stack_back_trace_trace_unit_s trace_unit = {
		.address_list = (void*)&address_list,
		.frames.skip = skip + 1,																	/* Skip the stack of this function */
		.frames.capture = capture,
	};

	if (!stack_back_trace_control_platform_trace_address(&trace_unit)) {							/* Trace the stack */
		error_code = 2;
		goto EXIT;
	}

	if (stack_back_trace_control_trace_address_group(stack_back_trace, trace_unit)) {				/* Group the stack */
		error_code = 3;
		goto EXIT;
	}

EXIT:
	return error_code;
}

/**
 * @brief This function will reduce the count of the capture stack back trace type.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 *
 * @return NONE
 */

extern struct stack_back_trace_string_package_s
stack_back_trace_control_trace_string(stack_back_trace_stp stack_back_trace,
									  enum stack_back_trace_string_option_e option,
									  size_t index)
{
	assert(stack_back_trace);

	struct stack_back_trace_string_s
		string_list[STACK_BACK_TRACE_CFG_FRAMES_CAPTURE_MAX] = { 0 };
	struct stack_back_trace_string_package_s string_package = {
		.frames = 0,
		.string_list = string_list,
	};

	if (NULL != stack_back_trace) {
		string_package.frames
			= stack_back_trace_control_platform_trace_string(string_package.string_list,
															 stack_back_trace->trace_unit_ptr[index],
															 option);

		if (string_package.frames) {
			struct stack_back_trace_string_s *string_list = NULL;
			stack_back_trace_size_t string_length = string_package.frames * sizeof(struct stack_back_trace_string_s);

			if (NULL == (string_list = malloc(string_length))) {
				string_package.frames = 0;
				goto EXIT;
			}

			memcpy(string_list,
				   string_package.string_list,
				   string_length);

			string_package.string_list = string_list;
		}
	}

EXIT:
	return string_package;
}

/**
 * @brief This function will return the specified hash.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param hash the hash of the capture stack back trace
 *
 * @return NONE
 */

stack_back_trace_hash_t stack_back_trace_control_get_hash(stack_back_trace_stp stack_back_trace,
														  stack_back_trace_size_t index)
{
	assert(stack_back_trace);

	if (NULL == stack_back_trace) {
		return 0;
	}

	return stack_back_trace->trace_unit_ptr[index].hash;
}

/**
 * @brief This function will return the count package.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 *
 * @return NONE
 */

extern inline struct stack_back_trace_count_package_s
stack_back_trace_control_get_count_package(stack_back_trace_stp stack_back_trace)
{
	assert(stack_back_trace);

	struct stack_back_trace_count_package_s package = { 0 };

	if (NULL == stack_back_trace) {
		return package;
	}

	package.types = stack_back_trace->info.types.current;
	package.back_trace_count_ptr = stack_back_trace->info.count_ptr;

	return package;
}

errno_t stack_back_trace_control_trace_address_group(stack_back_trace_stp stack_back_trace,
													 struct stack_back_trace_trace_unit_s trace_unit)
{
	struct stack_back_trace_trace_unit_s
		*trace_unit_ptr = stack_back_trace->trace_unit_ptr;

	errno_t error_code = 0;
	stack_back_trace_size_t type = 0;

	if (0u == trace_unit.hash) {															/* Compare address list */
		stack_back_trace_size_t frame = 0, frames = 0;

		while (stack_back_trace->info.types.current > type) {
			frames = trace_unit_ptr->frames.capture;

			if (frames != trace_unit.frames.capture) {
				goto CONTINUE;
			}

			do {
				if (trace_unit_ptr->address_list[frame] != trace_unit.address_list[frame]) {
					goto CONTINUE;
				}

				frame++;
			} while (frames < frame);

			goto EXISTING_TYPE;

		CONTINUE:
			trace_unit_ptr++;
			type++;
		};
	} else {																				/* Compare the hash value */
		while (stack_back_trace->info.types.current > type) {
			if (trace_unit_ptr->hash == trace_unit.hash) {
				goto EXISTING_TYPE;
			}

			trace_unit_ptr++;
			type++;
		};
	}

	if (stack_back_trace_control_exception_full_types_trap(stack_back_trace)) {				/* Trap the full types */
		error_code = 1;
		goto EXIT;
	}

	stack_back_trace_size_t
		address_list_length = trace_unit.frames.capture * sizeof(stack_back_trace_address_t);

	if (NULL == (trace_unit_ptr->address_list = malloc(address_list_length))) {
		error_code = 2;
		goto EXIT;
	}

	trace_unit.frames.skip--;																/* Remove the affect skip the stack of this function */

	memcpy(trace_unit_ptr->address_list, 													/* Copy the trace_unit */
		   trace_unit.address_list,
		   address_list_length);
	memcpy(&trace_unit_ptr->frames,
		   &trace_unit.frames,
		   sizeof(struct stack_back_trace_trace_unit_s) - sizeof(stack_back_trace_address_tp));

	stack_back_trace->info.types.current++;

EXISTING_TYPE:
	stack_back_trace->info.count_ptr[type] ++;

EXIT:
	return error_code;
}

static inline bool
stack_back_trace_control_exception_full_types_trap(stack_back_trace_stp stack_back_trace)
{
	assert(stack_back_trace);

	if (NULL == stack_back_trace) {
		return true;
	}

	if (stack_back_trace->info.types.max <= stack_back_trace->info.types.current &&
		0u < (stack_back_trace->info.types.current / stack_back_trace->info.types.max) &&			/* Exclude it have been reduced to a negative number */
		false == stack_back_trace->exception.full_types_callback(stack_back_trace)) {
	#if STACK_BACK_TRACE_CFG_DEBUG_EN

		LOG_DIAGNOSE("%s\r\n", "traped");

	#endif // STACK_BACK_TRACE_CFG_DEBUG_EN
		return true;
	}

	return false;
}

bool stack_back_trace_control_exception_full_types_callback(stack_back_trace_stp stack_back_trace)
{
	assert(stack_back_trace);

	if (NULL == stack_back_trace) {
		return false;
	}

	stack_back_trace->info.types.current -= 1;

	return true;
}