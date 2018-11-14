#include "list.cpp"

/**
 *
 *	структура массива списков
 */	

struct list_ar_t
	{
		list_t* first;
		list_t* last;
		
		size_t size;
		
		FILE* error_list;

	};

	
size_t get_list_ar_size(list_ar_t* list_ar);
void list_ar_header(list_ar_t* list_ar, FILE* data);
void list_ar_full_info(list_ar_t* list_ar, FILE* data);
void list_ar_short_info(list_ar_t* list_ar, FILE* data);
		
#include "list_assert.h"
	
//{--------------------------------------------------------------------------------------------------------------------------------------		
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Конструктор и Деструктор
//
//	list_ar_create()
//	delete_all_elem()
//	list_ar_destroy()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 *
 *	constructor
 *	возвращает ссылку на массив списков состоящего из одного элемента
 */		
struct list_ar_t* list_ar_create(FILE* error_list)
	{
		list_ar_t *list_ar = (list_ar_t*)calloc(1, sizeof(list_ar_t));
		
		list_ar->first = list_ar->last = list_create(0);
		
		list_ar->size = 0;
		
		//#ifdef DEBUGS
		list_ar->error_list = error_list;
		//#endif
		
		return list_ar;
	}
	
	
/**
 *
 *	delete_all_elem
 *	Удаляет все элементы
 */	
void delete_all_elem(list_ar_t* list_ar)
	{
		list_t* free_point = list_ar->first;
		
		while(free_point != list_ar->last)
			{
				free_point = list_ar->first->next;
				free(list_ar->first);
				list_ar->first = free_point;
			}
			
		list_ar->size = 0;
	}

	
/**
 *
 *	destructor
 *	освобождает память массива списков
 */	
void list_ar_destroy(list_ar_t** list_ar)
	{
		assert(list_ar != NULL);
		
		if((*list_ar) == NULL)
			return;
		
		delete_all_elem(*list_ar);
		
		(*list_ar)->first = (*list_ar)->last = NULL;
		
		(*list_ar)->size = 0;
		
		#ifdef DEBUGS
		fclose((*list_ar)->error_list);
		#endif
		
		free(list_ar);
		
		*list_ar = NULL;
	}
	
	
//}--------------------------------------------------------------------------------------------------------------------------------------	

//{--------------------------------------------------------------------------------------------------------------------------------------		
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Функции изменения, поиска элементов и пр.
//
//	add_elem_with_zero_size()
//	add_next_elem()
//	add_prev_elem()
//	add_first_elem()
//	add_last_elem()
//	get_next_elem()
//	get_prev_elem()
//	get_first_elem()
//	get_last_elem()
//	delete_elem()
//	find_elem()
//	get_list_ar_size()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
/**
 *
 *	add_elem_with_zero_size
 *	функция нужна на случай добавления самого первого элемента
 */		
void add_elem_with_zero_size(list_ar_t* list_ar, data_t field)
	{
		ls_assert(list_ar);
		
		assert(list_ar != NULL);
		
		list_ar->first->field = field;
		list_ar->size++;
		
		ls_assert(list_ar);
	}

	
	
/**
 *
 *	add_next_elem
 *	добавляет элемент в массив списков за point
 */	
void add_next_elem(list_ar_t* list_ar, list_t* point, data_t field)
	{
		ls_assert(list_ar);
		
		if(list_ar->size == 0)
			{
				add_elem_with_zero_size(list_ar, field);
				return;
			}
		
		add_next_elem(point, list_create(field));
		
		list_ar->size++;
		
		if(point == list_ar->last)
			list_ar->last = point->next;
		
		ls_assert(list_ar);
	}

	
/**
 *
 *	add_prev_elem
 *	добавляет элемент в массив списков перед point
 */		
void add_prev_elem(list_ar_t* list_ar, list_t* point, data_t field)
	{
		ls_assert(list_ar);
		
		assert(list_ar != NULL);
		
		if(list_ar->size == 0)
			{
				add_elem_with_zero_size(list_ar, field);
				return;
			}
		
		add_prev_elem(point, list_create(field));
		
		list_ar->size++;
		
		if(point == list_ar->first)
			list_ar->first = point->next;
		
		ls_assert(list_ar);
	}

	
/**
 *
 *	add_first_elem
 *	добавляет элемент в массив списков в начало
 */		
void add_first_elem(list_ar_t* list_ar, data_t field)
	{
		ls_assert(list_ar);
		
		assert(list_ar != NULL);
		
		if(list_ar->size == 0)
			{
				add_elem_with_zero_size(list_ar, field);
				return;
			}
		
		add_prev_elem(list_ar->first, list_create(field));
		
		list_ar->size++;
		
		list_ar->first = list_ar->first->prev;
		
		ls_assert(list_ar);
	}

	
/**
 *
 *	add_last_elem
 *	добавляет элемент в массив списков в конец
 */	
void add_last_elem(list_ar_t* list_ar, data_t field)
	{
		ls_assert(list_ar);
		
		assert(list_ar != NULL);
		
		if(list_ar->size == 0)
			{
				add_elem_with_zero_size(list_ar, field);
				return;
			}
		
		add_next_elem(list_ar->last, list_create(field));
		
		list_ar->size++;
		
		list_ar->last = list_ar->last->next;
		
		ls_assert(list_ar);
	}

	
/**
 *
 *	get_next_elem
 *	дает указатель на следующий элемент за point
 */	
struct list_t* get_next_elem(list_t* point)
	{
		assert(point != NULL);
		
		return point->next;
	}

	
/**
 *
 *	get_prev_elem
 *	дает указатель на предыдущий элемент перед point
 */	
struct list_t* get_prev_elem(list_t* point)
	{
		assert(point != NULL);
		
		return point->prev;
	}

	
/**
 *
 *	get_first_elem
 *	дает указатель на первый элемент в массиве списков
 */	
struct list_t* get_first_elem(list_ar_t* list_ar)
	{
		ls_assert(list_ar);
		
		return list_ar->first;
		
		ls_assert(list_ar);
	}

	
/**
 *
 *	get_last_elem
 *	дает указатель на последний элемент в массиве списков
 */	
struct list_t* get_last_elem(list_ar_t* list_ar)
	{
		ls_assert(list_ar);
		
		return list_ar->last;
		
		ls_assert(list_ar);
	}

	
/**
 *
 *	delete_elem
 *	удаляет элемент list из массива list_ar
 */	
void delete_elem(list_ar_t* list_ar, list_t *list)
	{
		ls_assert(list_ar);
		
		assert(list != NULL);
		
		if(list_ar->size == 0) return;
		
		delete_elem(list);
		list_ar->size--;
		
		ls_assert(list_ar);
	}

	
/**
 *
 *	find_elem
 *	Находит элемент по его значению
 */
struct list_t* find_elem(list_ar_t* list_ar, data_t field)
	{
		ls_assert(list_ar);
		
		list_t* list = list_ar->first;
		
		while(list != NULL)
			{
				#define FIND_LIST_ELEM
				#include "control.h"
				#undef FIND_LIST_ELEM
					
				list = list->next;
			}
			
		return NULL;
	}

	
/**
 *
 *	get_list_ar_size
 *	выдает размер списка
 */	
size_t get_list_ar_size(list_ar_t* list_ar)
	{
		return list_ar->size;
	}

//}--------------------------------------------------------------------------------------------------------------------------------------	

//{--------------------------------------------------------------------------------------------------------------------------------------		
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Функции ввода-вывода
//
//	list_ar_header()
//	list_ar_full_info()
//	list_ar_short_info()
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
/**
 *
 *	list_ar_header
 *	печатает заголовок листа
 */	
void list_ar_header(list_ar_t* list_ar, FILE* data)
	{
		fprintf(data, "list size = %ld\n", get_list_ar_size(list_ar));
		fprintf(data, "list first pointer = %ld\n", (int) list_ar->first);
		fprintf(data, "list last pointer = %ld\n", (int) list_ar->last);
	}
	
	
/**
 *
 *	list_ar_full_info
 *	печатает полную информацию о массиве cписков
 */		
void list_ar_full_info(list_ar_t* list_ar, FILE* data)
	{
		list_ar_header(list_ar, data);
		root_full_info(list_ar->first, data);
	}
	
/**
 *
 *	list_ar_short_info
 *	печатает краткую информацию о массиве cписков
 */		
void list_ar_short_info(list_ar_t* list_ar, FILE* data)
	{
		list_ar_header(list_ar, data);
		root_short_info(list_ar->first, data);
	}
	
//}--------------------------------------------------------------------------------------------------------------------------------------	


