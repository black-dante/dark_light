//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *	stack assert
 *
 *	set the DEBUG flag to turn it on, reset the flag to turn it off
 *	if there is an error on the stack during operation,
 *  then an assert will output it to the error files
 *  that are in the ERRORS folder
 */	

#ifdef DEBUGS																												
	#define st_assert(stack)																										\
		switch(stack_ok(stack))																										\
			{																														\
																																	\
				case NO_ERRORS:																										\
					{																												\
						;																											\
					}																												\
				break;																												\
																																	\
				case NULL_POINTER:																									\
					{																												\
						fprintf((stack)->error_stack, "OPS st_assert %d:\n", ++(stack)->error_count);								\
						fprintf((stack)->error_stack, "WTF? pointer stack %s is NULL\n",(stack)->name);								\
						fprintf((stack)->error_stack, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __func__, __LINE__);			\
						fprintf((stack)->error_stack, "data = %s\ntime = %s\n", __DATE__, __TIME__);								\
						fprintf((stack)->error_stack, "\n\n\n\n\n");																\
						assert(0);																									\
					}																												\
				break;																												\
																																	\
				case SIZE_ERROR:																									\
					{																												\
						fprintf((stack)->error_stack, "OPS st_assert %d:\n", ++(stack)->error_count);								\
						fprintf((stack)->error_stack, "WTF? struct stack %s isn't correct\n",(stack)->name);						\
						fprintf((stack)->error_stack, "stack cap = %ld:\n stack size = %ld\n", (stack)->capasity, (stack)->size);	\
						fprintf((stack)->error_stack, "canary1 = %d canary2 = %d\n", (stack)->canary_first, (stack)->canary_last);  \
						fprintf((stack)->error_stack, "stack data ponter = %ld\n", (long int)((stack)->data));						\
						fprintf((stack)->error_stack, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __func__, __LINE__);			\
						fprintf((stack)->error_stack, "data = %s\ntime = %s\n", __DATE__, __TIME__);								\
						fprintf((stack)->error_stack, "\n\n\n\n\n");																\
						assert(0);																									\
					}																												\
				break;																												\
																																	\
				case UNCORRECT_DATA:																								\
					{																												\
						fprintf((stack)->error_stack, "OPS st_assert %d:\n", ++(stack)->error_count);								\
						fprintf((stack)->error_stack, "WTF? %s data isn't correct\n",(stack)->name);								\
						fprintf((stack)->error_stack, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __func__, __LINE__);			\
						fprintf((stack)->error_stack, "data = %s\ntime = %s\n", __DATE__, __TIME__);								\
						fprintf((stack)->error_stack, "\n\n\n\n\n");																\
																																	\
						fprintf((stack)->error_data, "OPS st_assert %d:\n", (stack)->error_count);									\
						fprintf((stack)->error_data, "WTF? %s data isn't correct\n",(stack)->name);									\
						fprintf((stack)->error_data, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __func__, __LINE__);			\
						fprintf((stack)->error_data, "data = %s\ntime = %s\n\n", __DATE__, __TIME__);								\
						stack_print_info(stack, (stack)->error_data);																\
						fprintf((stack)->error_data,  "\n\n\n\n\n");																\
						hash_sum_create(stack);																						\
						(stack)->data[0] = CANARY;																					\
						(stack)->data[(stack)->size] = CANARY;																		\
					}																												\
				break;																												\
																																	\
				default:																											\
					{																												\
						fprintf((stack)->error_stack, "OPS st_assert %d:\n", ++(stack)->error_count);								\
						fprintf((stack)->error_stack, "WTF? ERROR NUMBER ISN'T CORRECT\n");											\
						fprintf((stack)->error_stack, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __func__, __LINE__);			\
						fprintf((stack)->error_stack, "data = %s\ntime = %s\n", __DATE__, __TIME__);								\
						fprintf((stack)->error_stack, "\n\n\n\n\n");																\
						assert(0);																									\
					}																												\
				break;																												\
																																	\
			}																												
#else																														
	#define st_assert(stack) ;																								
#endif
//}--------------------------------------------------------------------------------------------------------------------------------------											//fprintf((stack)->error_stack, "canary first = %d canary last = %d\n", (stack)->canary_first, //(stack)->canary_last);\																			