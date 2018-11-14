#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef int data_t;

struct list_t
	{
		data_t field; 					// поле данных
		struct list_t *next; 		// указатель на следующий элемент
		struct list_t *prev; 		// указатель на предыдущий элемент
	};


/**
 *
 *constructor
 *возвращает ссылку на список с нулевыми указателями и заполненным полем данных
 */	
struct list_t* list_create(data_t field)
	{
		list_t *list = (list_t*)calloc(1, sizeof(list_t));
		assert(list != NULL);
		
		list->field = field;
		
		list->next = NULL;
		list->prev = NULL;
		
		return(list);
	}
	

/**
 *
 *destructor
 *освобождает память списка
 */	
void list_destroy(list_t* list)
	{
		if(list == NULL)
			return;
		
		list->field = 0;
		list->next = NULL;
		list->prev = NULL;
		
		free(list);
	}
	
	
/**
 *
 *info
 *напечатать лист в файл
 */
void list_info(list_t* list, FILE* data_file)
	{
		assert(list != NULL);
		assert(data_file != NULL);
		
		fprintf(data_file, "list address = %d\n", list);
		fprintf(data_file, "list field = %d\n", list->field);//!!!!
		fprintf(data_file, "list next = %d\n", list->next);
		fprintf(data_file, "list prev = %d\n", list->prev);
		fprintf(data_file, "\n\n\n");
	}

	
/**
 *
 *add_next_elem
 *добавляет следующий элемент add_list в list
 */	
void add_next_elem(list_t *list, list_t *add_list)
	{
		assert(list != NULL);
		assert(add_list != NULL);
		
		add_list->prev = list;
		add_list->next = list->next;
		
		list->next = add_list;
		
		if(add_list->next != 0)
			add_list->next->prev = add_list;
	}
	
	
/**
 *
 *add_prev_elem
 *добавляет предыдущий элемент add_list в list
 */	
void add_prev_elem(list_t *list, list_t *add_list)
	{
		assert(list != NULL);
		assert(add_list != NULL);
		
		add_list->next = list;
		add_list->prev = list->prev;
		
		list->prev = add_list;
		
		if(add_list->prev != 0)
			add_list->prev->next = add_list;
	}

/**
 *
 *delete_elem
 *удаляет элемент list из списка
 */		
void delete_elem(list_t *list)
	{
		assert(list != NULL);
	
		if (list->prev != NULL)
			list->prev->next = list->next; // переставляем указатель
		if (list->next != NULL)
			list->next->prev = list->prev; // переставляем указатель

		free(list); // освобождаем память удаляемого элемента
	}

	
/**
 *
 *list_print
 *печатает список с текущего элемента
 */
void list_print(list_t *list, FILE* data_file)
	{
		assert(list != NULL);
		
		list_t* point = list;
		
		while(point != NULL)
			{
				fprintf(data_file, "%d->", point->field);///!!!!!!
				
				point = point->next;
			}
			
		fprintf(data_file, "NULL\n\n\n");
	}

/**
 *
 *change_elem
 *меняет два элемента в списке местами
 */	
void change_elem(list_t *list1, list_t *list2)
	{
		data_t field = list1->field;
		
		list1->field = list2->field;
		list2->field = field;
	}

int main()
	{
		list_t* list1 = list_create(7);
		list_t* list2 = list_create(9);
		list_t* list3 = list_create(8);
		
		add_next_elem(list1, list2);
		add_next_elem(list1, list3);
		
		FILE* dump_file = fopen("dump.txt", "w");
		
		list_info(list1, dump_file);
		list_info(list2, dump_file);
		list_info(list3, dump_file);
		
		list_print(list1, dump_file);
		
		delete_elem(list3);
		
		list_info(list1, dump_file);
		list_info(list2, dump_file);
		
		list_print(list1, dump_file);
		
		change_elem(list1, list2);
		
		list_print(list1, dump_file);

		list_destroy(list1);
		list_destroy(list2);
		list_destroy(list3);
		
		fclose(dump_file);
	}