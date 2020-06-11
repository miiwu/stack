/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "stack_back_trace_windows.h"

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

struct stack_back_trace_windows_symbol_handler_s {
	HANDLE process;
	DWORD64 displacement_symbol;
	DWORD displacement_line;
};

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

struct stack_back_trace_windows_symbol_handler_s symbol_handler;

/*
 *********************************************************************************************************
 *                                      LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

/**
 * @brief This function will convert the back trace struct to the symbol description.
 *
 * @param symbol the pointer to symbol description buffer
 * @param trace the pointer to the trace of stack back trace captured
 * @param frames the amount of captured
 *
 * @return NONE
 */

errno_t stack_back_trace_control_convert_to_symbol(struct stack_back_trace_string_s *string,
												   stack_back_trace_address_t address);

/**
 * @brief This function will convert the back trace struct to the line description.
 *
 * @param symbol the pointer to line description buffer
 * @param trace the pointer to the trace of stack back trace captured
 * @param frames the amount of captured
 *
 * @return NONE
 */

errno_t stack_back_trace_control_convert_to_line(struct stack_back_trace_string_s *string,
												 stack_back_trace_address_t address);

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

/**
 * @brief This function will back trace the stack.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param frames_to_skip the amount of stack the capture back trace will skip
 * @param frames_to_capture the amount of stack the capture back trace will capture
 *
 * @return NONE
 */

extern inline stack_back_trace_frame_t
stack_back_trace_control_platform_trace_address(struct stack_back_trace_trace_unit_s *trace_unit)
{
	assert(NULL != trace_unit);

	if (NULL != trace_unit) {
		return trace_unit->frames.capture													/* Capture the stack */
			= CaptureStackBackTrace(trace_unit->frames.skip + 1,							/* Skip the top frame, the stack of this function */
									trace_unit->frames.capture,
									trace_unit->address_list,
									&trace_unit->hash)
			- STACK_BACK_TRACE_WINDOWS_CFG_FRAMES_BEFORE_MAIN;								/* Exclude the stacks before main() */
	}

	return 0u;
}

/**
 * @brief This function will reduce the count of the capture stack back trace type.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 *
 * @return NONE
 */

extern stack_back_trace_frame_t
stack_back_trace_control_platform_trace_string(struct stack_back_trace_string_s *string_list,
											   struct stack_back_trace_trace_unit_s trace_unit,
											   enum stack_back_trace_string_option_e option)
{
	assert(NULL != string_list);

	stack_back_trace_frame_t error_code = 0;

	if (NULL != string_list) {
		if (NULL == (symbol_handler.process
					 = GetCurrentProcess())) {
			error_code = -1;
			goto EXIT;
		}

		if (!SymInitialize(symbol_handler.process, NULL, TRUE)) {							/* Initialize the symbol handler */
			error_code = -2;
			goto EXIT;
		}

		stack_back_trace_address_tp address_list = trace_unit.address_list;
		struct stack_back_trace_string_s *string_list_ptr = string_list;
		for (stack_back_trace_frame_t i = 0; i < trace_unit.frames.capture; ++i) {
			switch (option) {
				case FUNC_FILE_LINE:
					if (stack_back_trace_control_convert_to_line(string_list,
																 *address_list)) {
						error_code = -3;
						goto EXIT;
					}
				case FUNC_ONLY:
					if (stack_back_trace_control_convert_to_symbol(string_list,
																   *address_list)) {
						error_code = -4;
						goto EXIT;
					}
					break;
				default:
					break;
			}

			address_list++;
			string_list++;
		}

		if (!SymCleanup(symbol_handler.process)) {											/* Cleanup the symbol handler resource */
			error_code = -5;
			goto EXIT;
		}

		error_code = trace_unit.frames.capture;
	}

EXIT:
	return error_code;
}

/**
 * @brief This function will convert the back trace struct to the symbol description.
 *
 * @param symbol the pointer to symbol description buffer
 * @param trace the pointer to the trace of stack back trace captured
 * @param frames the amount of captured
 *
 * @return NONE
 */

errno_t stack_back_trace_control_convert_to_symbol(struct stack_back_trace_string_s *string,
												   stack_back_trace_address_t address)
{
	assert(address);

	char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
	PSYMBOL_INFO symbol_info = (PSYMBOL_INFO)buffer;

	symbol_info->SizeOfStruct = sizeof(SYMBOL_INFO);
	symbol_info->MaxNameLen = MAX_SYM_NAME;

	if (SymFromAddr(symbol_handler.process,
					(DWORD64)address,
					&symbol_handler.displacement_symbol,
					symbol_info)) {
		char *name_copy = calloc((size_t)symbol_info->NameLen + 1u, sizeof(char));

		if (NULL == name_copy) {
			LOG_DIAGNOSE("%s\r\n", "allocate new memory fail");
			return 1;
		}

		memcpy(name_copy, symbol_info->Name, symbol_info->NameLen);

		string->name_ptr = name_copy;
		string->name_len = (size_t)symbol_info->NameLen;

	#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

		printf("\t No.%d total:%d name_ptr:%s ( %lld ) \r\n",
			   frames - i, frames, symbol_info->Name, symbol_info->Address);

	#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)
	} else {
		printf("SymFromAddr error : %d \r\n", GetLastError());
	}

	return 0;
}

/**
 * @brief This function will convert the back trace struct to the line description.
 *
 * @param symbol the pointer to line description buffer
 * @param trace the pointer to the trace of stack back trace captured
 * @param frames the amount of captured
 *
 * @return NONE
 */

errno_t stack_back_trace_control_convert_to_line(struct stack_back_trace_string_s *string,
												 stack_back_trace_address_t address)
{
	assert(address);

	IMAGEHLP_LINE64 line_info = { 0 };

	line_info.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

	if (SymGetLineFromAddr64(symbol_handler.process,
							 (DWORD64)address,
							 &symbol_handler.displacement_line,
							 &line_info)) {
		size_t name_len = strlen(line_info.FileName);
		char *name_copy = calloc(name_len + 1, sizeof(char));

		if (NULL == name_copy) {
			return 1;
		}

		memcpy(name_copy, line_info.FileName, name_len);

		string->file_line = line_info.LineNumber;
		string->file_name_ptr = name_copy;
		string->file_line_len = name_len;

	#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

		printf("\t file_name_ptr: %s at line: %d \r\n",
			   line_info.FileName, line_info.LineNumber);

	#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)
	} else {
		printf("SymFromAddr error : %d \r\n", GetLastError());
	}

	return 0;
}