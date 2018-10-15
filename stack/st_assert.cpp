//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *	stack assert
 *
 *	set the DEBUG flag to turn it on, reset the flag to turn it off
 *	if there is an error on the stack during operation,
 *  then an assert will output it to the error files
 *  that are in the ERRORS folder
 */	

#define DEBUGS

#ifdef DEBUGS																												
	#define st_assert(stack)																								\
		switch(stack_ok(stack))																								\
			{																												\
																															\
				case 0:																										\
					{																										\
						;																									\
					}																										\
				break;																										\
																															\
				case 1:																										\
					{																										\
						fprintf(error_stack, "OPS st_assert %d:\n", ++ERROR_COUNT);											\
						fprintf(error_stack, "WTF? pointer stack %s is NULL\n",#stack);										\
						fprintf(error_stack, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __FUNCSIG__, __LINE__);			\
						fprintf(error_stack, "data = %s\ntime = %s\n", __DATE__, __TIME__);									\
						fprintf(error_stack, "\n\n\n\n\n");																	\
						assert(0);																							\
					}																										\
				break;																										\
																															\
				case 2:																										\
					{																										\
						fprintf(error_stack, "OPS st_assert %d:\n", ++ERROR_COUNT);											\
						fprintf(error_stack, "WTF? struct stack %s isn't correct\n",#stack);								\
						fprintf(error_stack, "stack cap = %ld:\n stack size = %ld\n", (stack)->capasity, (stack)->size);	\
						fprintf(error_stack, "stack data ponter = %ld\n", (long int)((stack)->data));						\
						fprintf(error_stack, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __FUNCSIG__, __LINE__);			\
						fprintf(error_stack, "data = %s\ntime = %s\n", __DATE__, __TIME__);									\
						fprintf(error_stack, "\n\n\n\n\n");																	\
						assert(0);																							\
					}																										\
				break;																										\
																															\
				case 3:																										\
					{																										\
						fprintf(error_stack, "OPS st_assert %d:\n", ++ERROR_COUNT);											\
						fprintf(error_stack, "WTF? %s data isn't correct\n",#stack);										\
						fprintf(error_stack, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __FUNCSIG__, __LINE__);			\
						fprintf(error_stack, "data = %s\ntime = %s\n", __DATE__, __TIME__);									\
						fprintf(error_stack, "\n\n\n\n\n");																	\
																															\
						fprintf(error_data, "OPS st_assert %d:\n", ERROR_COUNT);											\
						fprintf(error_data, "WTF? %s data isn't correct\n",#stack);											\
						fprintf(error_data, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __FUNCSIG__, __LINE__);			\
						fprintf(error_data, "data = %s\ntime = %s\n\n", __DATE__, __TIME__);								\
						stack_print_info(stack, error_data);																\
						fprintf(error_data,  "\n\n\n\n\n");																	\
						hash_sum_create(stack);																				\
						(stack)->data[0] = CANARY;																			\
						(stack)->data[(stack)->size] = CANARY;																\
					}																										\
				break;																										\
																															\
				default:																									\
					{																										\
						fprintf(error_stack, "OPS st_assert %d:\n", ++ERROR_COUNT);											\
						fprintf(error_stack, "WTF? ERROR NUMBER ISN'T CORRECT\n");											\
						fprintf(error_stack, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __FUNCSIG__, __LINE__);			\
						fprintf(error_stack, "data = %s\ntime = %s\n", __DATE__, __TIME__);									\
						fprintf(error_stack, "\n\n\n\n\n");																	\
						assert(0);																							\
					}																										\
				break;																										\
																															\
			}																												
#else																														
	#define st_assert(stack) ;																								
#endif
//}--------------------------------------------------------------------------------------------------------------------------------------																														