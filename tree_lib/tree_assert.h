//#define DEBUGS

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Перечисление для ошибок дерева
 */
 
enum TREE_ERROR
	{
		ALWAYS_OK			= 1,
		ROOT_NULL 			= 2,
		SIZE_ERROR 			= 3,
		NULL_CENTER_ELEM 	= 4
	};
//}--------------------------------------------------------------------------------------------------------------------------------------	
	
	
//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Верификатор

	\return Код ошибки
 */	
 
TREE_ERROR tree_verifier(tree_t* tree)
	{
		if(tree == NULL) return ROOT_NULL;
		
		if(tree->size > tree->capasity || tree->size < 0 || tree->capasity < 0) return SIZE_ERROR;
		
		int size = 0;
		
		for(int i = 0; i < tree->capasity; i++)
				if(tree->nodes[i]->free == false) size++;
			
		//if(size != tree->size) return SIZE_ERROR;
		
		for(int i = 0; i < tree->capasity; i++)
				if(tree->nodes[i]->free == false && tree->nodes[i]->type == null)
					return NULL_CENTER_ELEM;
		
		return ALWAYS_OK;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------		
	
	
//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief БОЛЬШОЙ ДЕФАЙН
 */		
 
#ifdef DEBUGS																								
	#define tree_assert(tree)																												\
		switch(tree_verifier(tree))																											\
			{																																\
				case ALWAYS_OK:																												\
																																			\
					;																														\
																																			\
				break;																														\
																																			\
				case ROOT_NULL:																												\
																																			\
					printf("Tree critical error: tree pointer = NULL\n");																	\
																																			\
					printf("file = %s\nfunc = %s\nline = %d\n", __FILE__, __func__, __LINE__);												\
					printf("data = %s\ntime = %s\n\n", __DATE__, __TIME__);																	\
																																			\
					assert(0);																												\
																																			\
				break;																														\
																																			\
				case SIZE_ERROR:																											\
																																			\
					fprintf((tree)->error_tree, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __func__, __LINE__);							\
					fprintf((tree)->error_tree, "data = %s\ntime = %s\n\n", __DATE__, __TIME__);											\
																																			\
					fprintf((tree)->error_tree, "wrong tree size\n");																		\
					fprintf((tree)->error_tree, "tree size = %d, tree capasity = %d\n", (tree)->size, (tree)->capasity);					\
																																			\
					tree_print_dot((tree), (tree)->root);																					\
																																			\
					assert(0);																												\
																																			\
				break;																														\
																																			\
				case NULL_CENTER_ELEM:																										\
																																			\
					fprintf((tree)->error_tree, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __func__, __LINE__);							\
					fprintf((tree)->error_tree, "data = %s\ntime = %s\n\n", __DATE__, __TIME__);											\
																																			\
					fprintf((tree)->error_tree, "NULL center elem\n");																		\
					fprintf((tree)->error_tree, "tree size = %d, tree capasity = %d\n", (tree)->size, (tree)->capasity);					\
																																			\
					tree_print_dot((tree), (tree)->root);																					\
																																			\
					assert(0);																												\
																																			\
				break;																														\
																																			\
				default:																													\
																																			\
					fprintf((tree)->error_tree, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __func__, __LINE__);							\
					fprintf((tree)->error_tree, "data = %s\ntime = %s\n\n", __DATE__, __TIME__);											\
																																			\
					printf("Tree: unknow error\n");																							\
																																			\
					assert(0);																												\
																																			\
				break;																														\
			}
	#else 
	#define tree_assert(tree) ;
#endif
//}--------------------------------------------------------------------------------------------------------------------------------------