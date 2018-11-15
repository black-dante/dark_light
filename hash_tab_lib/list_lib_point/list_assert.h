//{--------------------------------------------------------------------------------------------------------------------------------------		
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Для дебаг режима. Чтобы список работал быстрее уберите флаг DEBUGS
//
//	enum LIST_ERROR
//	LIST_ERROR list_ok()
//	Большой Дефайн
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define DEBUGS


enum LIST_ERROR
	{
		ALWAYS_OK = 1,
		SIZE_ERROR = 2,
		CYCLE_ERROR = 3,
		NULL_LAST_FIRST_ERROR = 4,
		NULL_CENTER_ELEM = 5,
		HEAD_NULL = 6
	};

	
/**
 *
 *	list_ok
 *	верификатор
 */	
LIST_ERROR list_ok(list_ar_t* list_ar)
	{
		if(list_ar == NULL)
			return HEAD_NULL;

		if(list_ar->first == NULL || list_ar->last == NULL)
			return NULL_LAST_FIRST_ERROR;

		if(list_ar->size == 0) 
			return ALWAYS_OK;
		else if(list_ar->size < 0)
			return SIZE_ERROR;
		
		list_t** list_mass = (list_t**)calloc(get_list_ar_size(list_ar), sizeof(list_t*));
		list_t* list = list_ar->first;
		
		for(int i = 0; i < get_list_ar_size(list_ar); i++)
			{
				for(int j = 0; j < i; j++)
					if(list_mass[j] == list) 
						return CYCLE_ERROR;
				
				if(list == NULL) 
					return NULL_CENTER_ELEM;
				
				list_mass[i] = list;
				
				list = list->next;
			}
			
		if(list_mass[get_list_ar_size(list_ar) - 1] != list_ar->last)
			return SIZE_ERROR;
		
		return ALWAYS_OK;
	}
	
	


#ifdef DEBUGS																								
	#define ls_assert(list_ar)																												\
		switch(list_ok(list_ar))																											\
			{																																\
				case HEAD_NULL:																												\
					{																														\
																																			\
						printf("List critical error: list_ar pointer = NULL\n");															\
																																			\
						printf("file = %s\nfunc = %s\nline = %d\n", __FILE__, __func__, __LINE__);											\
						printf("data = %s\ntime = %s\n\n", __DATE__, __TIME__);																\
																																			\
						assert(0);																											\
					}																														\
				break;																														\
																																			\
				case NULL_LAST_FIRST_ERROR:																									\
					{																														\
						fprintf((list_ar)->error_list, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __func__, __LINE__);					\
						fprintf((list_ar)->error_list, "data = %s\ntime = %s\n\n", __DATE__, __TIME__);										\
																																			\
						fprintf((list_ar)->error_list, "zero first or last element\n");														\
						list_ar_header(list_ar, (list_ar)->error_list);																		\
						assert(0);																											\
					}																														\
				break;																														\
																																			\
				case SIZE_ERROR:																											\
					{																														\
						fprintf((list_ar)->error_list, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __func__, __LINE__);					\
						fprintf((list_ar)->error_list, "data = %s\ntime = %s\n\n", __DATE__, __TIME__);										\
																																			\
						fprintf((list_ar)->error_list, "wrong list size\n");																\
						list_ar_header(list_ar, (list_ar)->error_list);																		\
						assert(0);																											\
					}																														\
				break;																														\
																																			\
				case CYCLE_ERROR:																											\
					{																														\
						fprintf((list_ar)->error_list, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __func__, __LINE__);					\
						fprintf((list_ar)->error_list, "data = %s\ntime = %s\n\n", __DATE__, __TIME__);										\
																																			\
						fprintf((list_ar)->error_list, "middle looping list");																\
																																			\
						list_ar_header(list_ar, (list_ar)->error_list);																		\
																																			\
						list_t* list1 = (list_ar)->first;																					\
																																			\
						fprintf((list_ar)->error_list, "\n\nlist elements:\n\n\n");															\
																																			\
						for(int i = 0; i < get_list_ar_size(list_ar); i++)																	\
							{																												\
								if(list1 != NULL) 																							\
									list_full_info(list1, (list_ar)->error_list);															\
								else																										\
									fprintf((list_ar)->error_list, "NULL\n");																\
																																			\
								list1 = list1->next;																						\
							}																												\
						assert(0);																											\
					}																														\
				break;																														\
																																			\
				case NULL_CENTER_ELEM: 																										\
					{																														\
						fprintf((list_ar)->error_list, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __func__, __LINE__);					\
						fprintf((list_ar)->error_list, "data = %s\ntime = %s\n\n", __DATE__, __TIME__);										\
																																			\
						fprintf((list_ar)->error_list, "null_center_elem\n");																\
																																			\
						list_ar_header((list_ar), (list_ar)->error_list);																	\
																																			\
						fprintf((list_ar)->error_list, "\n\nlist elements:\n\n\n");															\
																																			\
						root_full_info((list_ar)->first, (list_ar)->error_list);															\
						assert(0);																											\
					}																														\
				break;																														\
																																			\
				case ALWAYS_OK:																												\
					{																														\
						;																													\
					}																														\
				break;																														\
																																			\
				default:																													\
					{																														\
						fprintf((list_ar)->error_list, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __func__, __LINE__);					\
						fprintf((list_ar)->error_list, "data = %s\ntime = %s\n\n", __DATE__, __TIME__);										\
																																			\
						printf("List: unknow error\n");																						\
						assert(0);																											\
					}																														\
				break;																														\
			}
#else 
	#define ls_assert(list_ar) ;
#endif


//}--------------------------------------------------------------------------------------------------------------------------------------	