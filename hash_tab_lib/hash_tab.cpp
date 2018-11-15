#include "list_lib_point//list_ar.cpp"
#include <math.h>
#include <stdlib.h> 
#include <string.h>
#include <assert.h>

//1000 ячеек

struct hash_tab_t
	{
		list_ar_t** list_ar;
		
		int size;
		
		long int (*hash_func)(data_t data);
		
		FILE* file_error;
	};
	
//{--------------------------------------------------------------------------------------------------------------------------------------		
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Конструктор и деструктор
//
//	struct hash_tab_t* hash_tab_create(int size, long int (*hash_func)(data_t data), FILE* file_error)
//	void hash_tab_destroy(hash_tab_t** hash_tab)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
/**
 *
 *	constructor
 *	возвращает ссылку на хеш таблицу
 */		
struct hash_tab_t* hash_tab_create(int size, long int (*hash_func)(data_t data), FILE* file_error)
	{
		assert(file_error != NULL);
		
		hash_tab_t *hash_tab = (hash_tab_t*)calloc(1, sizeof(hash_tab_t));
		
		hash_tab->list_ar = (list_ar_t**)calloc(size, sizeof(list_ar_t*));
		
		hash_tab->size = size;
		
		hash_tab->hash_func = hash_func;
		
		for(int i = 0; i < hash_tab->size; i++)
			hash_tab->list_ar[i]  = list_ar_create(file_error);
		
		hash_tab->file_error = file_error;
		
		return hash_tab;
	}

	
/**
 *
 *	destructor
 *	освобождает память хеш таблицы
 */	
void hash_tab_destroy(hash_tab_t** hash_tab)
	{
		assert(hash_tab != NULL);
		
		if((*hash_tab) == NULL)
			return;
		
		for(int i = 0; i < (*hash_tab)-> size; i++)
			list_ar_destroy(&((*hash_tab)->list_ar[i]));
		
		(*hash_tab)->size = 0;
		
		(*hash_tab)->hash_func = NULL;
		
		fclose((*hash_tab)->file_error);
		
		free(hash_tab);
		
		(*hash_tab) = NULL;
	}
	
	
//}--------------------------------------------------------------------------------------------------------------------------------------	


//{--------------------------------------------------------------------------------------------------------------------------------------		
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Функции хеш таблицы
//
//	void print_hash_tab(hash_tab_t* hash_tab, FILE* dump_file)
//	void print_hash_tab_size(hash_tab_t* hash_tab, FILE* dump_file)
//	double hash_tab_pogr(hash_tab_t* hash_tab)
//	void put_data_to_tab(hash_tab_t* hash_tab, data_t data)
//	struct list_t* find_elem_in_tab(hash_tab_t* hash_tab, data_t data_find)
//	void hash_tab_delete_elem(hash_tab_t* hash_tab, list_t *list)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	


/**
 *
 *	print_hash_tab
 *	печатает хеш таблицу в файл
 */	
void print_hash_tab(hash_tab_t* hash_tab, FILE* dump_file)
	{
		assert(hash_tab != NULL);
		
		for(int i = 0; i < hash_tab->size; i++)
			list_ar_short_info(hash_tab->list_ar[i], dump_file);
	}
	
	
/**
 *
 *	print_hash_tab_size
 *	печатает размеры массивов списка таблицы в файл для каждой ячейки
 */
void print_hash_tab_size(hash_tab_t* hash_tab, FILE* dump_file)
	{
		assert(hash_tab != NULL);
		
		for(int i = 0; i < hash_tab->size; i++)
			fprintf(dump_file, "%d\t\t%d\n", i, get_list_ar_size(hash_tab->list_ar[i]));
	}	
	
	
/**
 *
 *	hash_tab_pogr
 *	среднее отклонение элемента
 */
double hash_tab_pogr(hash_tab_t* hash_tab)
	{
		assert(hash_tab != NULL);
		
		long double tab_size_aver = 0;
		
		for(int i = 0; i < hash_tab->size; i++)
			tab_size_aver += get_list_ar_size(hash_tab->list_ar[i]);
		
		tab_size_aver = tab_size_aver / hash_tab->size;
		
		double tab_pogr = 0;
		
		for(int i = 0; i < hash_tab->size; i++)
			{
				double pogr_copy = (get_list_ar_size(hash_tab->list_ar[i]) - tab_size_aver);
				
				pogr_copy *= pogr_copy;
				
				tab_pogr += pogr_copy ;
			}
			
		return sqrt(tab_pogr / hash_tab->size);
	}	

	
/**
 *
 *	put_data_to_tab
 *	помешает данные в хеш таблицу по хеш функции
 */		
void put_data_to_tab(hash_tab_t* hash_tab, data_t data)
	{
		assert(hash_tab != NULL);
		
		add_first_elem(hash_tab->list_ar[abs(hash_tab->hash_func(data) % hash_tab->size)], data);
	}

	
/**
 *
 *	find_elem_in_tab
 *	находит элемент в хеш таблице
 */		
struct list_t* find_elem_in_tab(hash_tab_t* hash_tab, data_t data_find)
	{
		assert(hash_tab != NULL);
		
		return find_elem(hash_tab->list_ar[abs(hash_tab->hash_func(data_find) % hash_tab->size)], data_find);
	}

	
/**
 *
 *	hash_tab_delete_elem
 *	удаляет элемент в хеш таблице
 */		
void hash_tab_delete_elem(hash_tab_t* hash_tab, list_t *list)
	{
		assert(hash_tab != NULL);
		assert(list != NULL);
		
		delete_elem(hash_tab->list_ar[abs(hash_tab->hash_func(list->field) % hash_tab->size)], list);
	}	
	
	
//}--------------------------------------------------------------------------------------------------------------------------------------	