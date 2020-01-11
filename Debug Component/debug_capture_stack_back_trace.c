/*
************************************************************************************************************************
*                                  DEBUG COMPONENT OF CAPATURE STACK BACK TRACE FUNCTIONS
*
* File    : DEBUG_CAPATURE_STACK_BACK_TRACE.C
* By      : lqq
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

#include "debug_capture_stack_back_trace.h"

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
 * @brief This function will initialize the capture stack back trace struct.
 *
 * @param structure the pointer to the capture stack back trace struct
 * @param count the amount of type stack situation
 *
 * @return NONE
 */

void debug_capture_stack_back_trace_init(struct capture_stack_back_trace_t **structure,
										 DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE count)
{
	struct capture_stack_back_trace_t
		*strcuture_allocated = (struct capture_stack_back_trace_t *)calloc(1,
																		   sizeof(struct capture_stack_back_trace_t));

	back_trace_t
		*trace_allocated = (back_trace_t *)calloc(count,
												  sizeof(back_trace_t));

	back_trace_hash_t
		*hash_allocated = (back_trace_hash_t *)calloc(count, sizeof(back_trace_hash_t));

	DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE *count_allocated =
		(DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE *)calloc(count,
															   sizeof(DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE));

	back_trace_symbol_t
		*symbol_ptr = (back_trace_symbol_t *)calloc(1, sizeof(back_trace_symbol_t));

	back_trace_line_t
		*line_ptr = (back_trace_line_t *)calloc(1, sizeof(back_trace_line_t));

	back_trace_symbol_t
		symbol_allocated = (back_trace_symbol_t)calloc(count,
													   sizeof(SYMBOL_INFO) *
													   DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH);

	back_trace_line_t
		line_allocated = (back_trace_line_t)calloc(count,
												   sizeof(IMAGEHLP_LINE64) *
												   DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH);

	printf("hash:%p symbol:%p line:%p capture stack back trace.init:block \r\n",
		   hash_allocated, symbol_allocated, line_allocated);

	if (NULL == strcuture_allocated ||
		NULL == trace_allocated ||
		NULL == hash_allocated ||
		NULL == count_allocated ||
		NULL == symbol_allocated ||
		NULL == symbol_ptr ||
		NULL == line_ptr ||
		NULL == line_allocated) {
		return;
	}

	strcuture_allocated->max_type_count = count;
	strcuture_allocated->type_count = 0u;
	strcuture_allocated->back_trace_count = count_allocated;
	strcuture_allocated->back_trace = trace_allocated;
	strcuture_allocated->back_trace_hash = hash_allocated;
	strcuture_allocated->back_trace_symbol = symbol_ptr;
	strcuture_allocated->back_trace_line = line_ptr;
	*strcuture_allocated->back_trace_symbol = symbol_allocated;
	*strcuture_allocated->back_trace_line = line_allocated;

	*structure = strcuture_allocated;

	printf("hash:%p symbol:%p line:%p capture stack back trace.init \r\n",
		(*structure)->back_trace_hash, *(*structure)->back_trace_symbol, *(*structure)->back_trace_line);
}

/**
 * @brief This function will destroy the capture stack back trace struct.
 *
 * @param structure the pointer to the capture stack back trace struct
 *
 * @return NONE
 */

void debug_capture_stack_back_trace_destroy(struct capture_stack_back_trace_t **strcuture)
{
	assert(strcuture);

	#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	free((*strcuture)->back_trace);
	free((*strcuture)->back_trace_hash);
	free((*strcuture)->back_trace_count);
	free(*(*strcuture)->back_trace_symbol);
	free(*(*strcuture)->back_trace_line);
	free((*strcuture)->back_trace_symbol);
	free((*strcuture)->back_trace_line);

	(*strcuture)->type_count = 0u;

	free((*strcuture));
}

/**
 * @brief This function will back trace the stack.
 *
 * @param structure the pointer to the capture stack back trace struct
 * @param frames_to_skip the amount of stack the capture back trace will skip
 * @param frames_to_capture the amount of stack the capture back trace will capture
 *
 * @return NONE
 */

void debug_capture_stack_back_trace(struct capture_stack_back_trace_t *stack_back_trace,
									DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE frames_to_skip,
									DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE frames_to_capture)
{
	back_trace_t backTrace = { 0 };
	ULONG backTraceHash = 0;

	const USHORT nFrame = CaptureStackBackTrace(
		frames_to_skip
		, frames_to_capture
		, backTrace
		, &backTraceHash
	);

	#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	printf("hash : %d \r\n", backTraceHash);

	#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	for (size_t cnt = 0; cnt < stack_back_trace->type_count; cnt++) {
		if ((ULONG)&stack_back_trace->back_trace_hash[cnt] == backTraceHash) {
			stack_back_trace->back_trace_count[cnt] += 1;

			return;
		}
	}

	memcpy((void *)((size_t)stack_back_trace->back_trace + stack_back_trace->type_count * sizeof(back_trace_t)),
		(void *)backTrace, sizeof(back_trace_t));

	memcpy((void *)((size_t)stack_back_trace->back_trace_hash + stack_back_trace->type_count * sizeof(ULONG)),
		(void *)&backTraceHash, sizeof(ULONG));

	stack_back_trace->back_trace_count[stack_back_trace->type_count] += 1;

	stack_back_trace->type_count++;
}

void debug_capture_stack_back_trace_to_symbol(struct capture_stack_back_trace_t *back_trace,
											  DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE frames_to_skip,
											  DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE frames_to_capture)
{
	HANDLE process = GetCurrentProcess();

	SymInitialize(process, NULL, TRUE);

	back_trace_t back_trace_tmp = { 0 };
	ULONG back_trace_hash_tmp = 0;
	SYMBOL_INFO back_trace_symbol_tmp[64] = { 0 };
	IMAGEHLP_LINE64 back_trace_line_tmp[64] = { 0 };

	const USHORT frames = CaptureStackBackTrace(
		frames_to_skip
		, frames_to_capture
		, back_trace_tmp
		, &back_trace_hash_tmp
	) - 7;									/* the stack of main() is start from the level 7 */

	for (USHORT i = 0; i < frames; ++i) {
		DWORD64 back_trace_address = (DWORD64)back_trace_tmp[i];
		DWORD64 displacementSym = 0;
		DWORD displacementLine = 0;

		back_trace_symbol_tmp[i].SizeOfStruct = sizeof(SYMBOL_INFO);
		back_trace_symbol_tmp[i].MaxNameLen = MAX_SYM_NAME;

		back_trace_line_tmp[i].SizeOfStruct = sizeof(IMAGEHLP_LINE64);

		if (SymFromAddr(process, back_trace_address, &displacementSym, &back_trace_symbol_tmp[i])
			&& SymGetLineFromAddr64(process, back_trace_address, &displacementLine, &back_trace_line_tmp[i])) {
			#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

			printf("\t name:%s ( %lld ) at %s : %d \r\n",
				   back_trace_symbol_tmp[i].Name, 
				   back_trace_symbol_tmp[i].Address, 
				   back_trace_line_tmp[i].FileName, 
				   back_trace_line_tmp[i].LineNumber);

			#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)
		} else {
			printf("SymFromAddr error : %d \r\n", GetLastError());
		}
	}

	for (size_t cnt = 0; cnt < back_trace->type_count; cnt++) {
		back_trace_hash_t
			hash = *(back_trace->back_trace_hash + cnt);
		back_trace_line_t
			line = (back_trace_line_t)((size_t)*back_trace->back_trace_line +
									   cnt * sizeof(IMAGEHLP_LINE64) *
									   DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH);

		if (hash == back_trace_hash_tmp &&
			line->LineNumber == back_trace_line_tmp[0].LineNumber) {
			back_trace->back_trace_count[cnt] += 1;

			return;
		}
	}

	memcpy((void *)(back_trace->back_trace_hash + back_trace->type_count),
		(void *)&back_trace_hash_tmp, sizeof(back_trace_hash_t));

	memcpy((void *)((size_t)*back_trace->back_trace_symbol +
					back_trace->type_count * sizeof(SYMBOL_INFO) * DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH),
					(void *)back_trace_symbol_tmp, sizeof(SYMBOL_INFO) * DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH);

	memcpy((void *)((size_t)*back_trace->back_trace_line +
					back_trace->type_count * sizeof(IMAGEHLP_LINE64) * DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH),
					(void *)back_trace_line_tmp, sizeof(IMAGEHLP_LINE64) * DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH);

	back_trace->back_trace_count[back_trace->type_count] += 1;

	back_trace->type_count++;
}

/*
string TraceStack()
{
	static const int MAX_STACK_FRAMES = 5;

	void *pStack[MAX_STACK_FRAMES];

	HANDLE process = GetCurrentProcess();
	SymInitialize(process, NULL, TRUE);
	WORD frames = CaptureStackBackTrace(0, MAX_STACK_FRAMES, pStack, NULL);

	for (WORD i = 0; i < frames; ++i) {
		DWORD64 address = (DWORD64)(pStack[i]);

		DWORD64 displacementSym = 0;
		char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
		PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;
		pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		pSymbol->MaxNameLen = MAX_SYM_NAME;

		DWORD displacementLine = 0;
		IMAGEHLP_LINE64 line;
		//SymSetOptions(SYMOPT_LOAD_LINES);
		line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

		if (SymFromAddr(process, address, &displacementSym, pSymbol)
			&& SymGetLineFromAddr64(process, address, &displacementLine, &line)) {
			oss << "\t" << pSymbol->Name << " at " << line.FileName << ":" << line.LineNumber << "(0x" << std::hex << pSymbol->Address << std::dec << ")" << std::endl;
		} else {
			oss << "\terror: " << GetLastError() << std::endl;
		}
	}
	return oss.str();
}
*/