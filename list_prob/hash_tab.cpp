#include "list_ar.cpp"
#include <math.h>
#include <stdlib.h> 
#include <string.h>

struct hash_tab_t
	{
		list_ar_t** list_ar;
		int size;
	};
	
/**
 *
 *constructor
 *возвращает ссылку на массив списков состоящего из одного элемента
 */		
struct hash_tab_t* hash_tab_create(int size)
	{
		hash_tab_t *hash_tab = (hash_tab_t*)calloc(1, sizeof(hash_tab_t));
		
		hash_tab->list_ar = (list_ar_t**)calloc(size, sizeof(list_ar_t*));
		
		hash_tab->size = size;
		
		for(int i = 0; i < hash_tab->size; i++)
			hash_tab->list_ar[i]  = list_ar_create();
		
		return hash_tab;
	}
	
/**
 *
 *destructor
 *освобождает память хеш таблицы
 */	
void hash_tab_destroy(hash_tab_t* hash_tab)
	{
		if(hash_tab == NULL)
			return;
		
		for(int i = 0; i < hash_tab-> size; i++)
			list_ar_destroy(hash_tab->list_ar[i]);
		
		hash_tab->size = 0;
		
		free(hash_tab);
	}
	
/**
 *
 *print_hash_tab
 *печатает хеш таблицу в файл
 */	
void print_hash_tab(hash_tab_t* hash_tab, FILE* dump_file)
	{
		for(int i = 0; i < hash_tab->size; i++)
			list_print(hash_tab->list_ar[i]->first, dump_file);
	}
	
/**
 *
 *print_hash_tab_size
 *печатает размеры массивов списка таблицы в файл для каждой ячейки
 */
void print_hash_tab_size(hash_tab_t* hash_tab, FILE* dump_file)
	{
		for(int i = 0; i < hash_tab->size; i++)
			fprintf(dump_file, "%d\t\t%d\n", i, get_list_ar_size(hash_tab->list_ar[i]));
	}	
	
/**
 *
 *hash_tab_pogr
 *среднее отклонение элемента
 */
double hash_tab_pogr(hash_tab_t* hash_tab)
	{
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
 *put_data_to_tab
 *помешает данные в хеш таблицу по хеш функции
 */		
void put_data_to_tab(hash_tab_t* hash_tab, data_t data, long int (*hash_func)(data_t data))
	{
		add_first_elem(hash_tab->list_ar[abs(hash_func(data) % hash_tab->size)], data);
	}
	
/**
 *
 *hash1
 *хеш всегда возвращает 1
 */		
long int hash1(data_t data)
	{
		return 1;
	}
	
long int hash_first_symb(data_t data)
	{
		return data[0];
	}
	
long int hash_len(data_t data)
	{
		return strlen(data);
	}
	
long int hash_ascii_sum(data_t data)
	{
		long int count = 0;
		
		for(int i = 0; i < strlen(data); i++)
			count += data[i];
		
		return count;
	}
	
long int hash_ascii_sum_on_length(data_t data)
	{
		long int count = 0;
		
		for(int i = 0; i < strlen(data); i++)
			count += data[i];
		
		return count/strlen(data);
	}
	
long int hash_ascii_pn_sum(data_t data)
	{
		long int count = 0;
		
		for(int i = 0; i < strlen(data); i++)
			count += i % 2 == 0? data[i] : -data[i];
		
		return count;
	}
	
	
long int stringToHash(data_t data)
	{
		long int count = 0;
		
		for(int i = 0; i < strlen(data); i++)
			count = count*data[i] + data[i] + i;
		
		return count;
	}
	
long int hash_sdbm(data_t data)
	{
		long int count = 0;
		
		for(int i = 0; i < strlen(data); i++)
			count = data[i] + (count << 6) + (count << 16) - count;
		
		return count;
	}
	
long int hash_djb2(data_t data)
	{
		long int count = 5381;
		
		for(int i = 0; i < strlen(data); i++)
			count = data[i] + (count << 5) + count;
		
		return count;
	}
	
long int hash_adler32(data_t data)
	{
		wint_t s1 = 1;
		wint_t s2 = 0;
		
		for(int i = 0; i < strlen(data); i++)
			{
				s1 = (s1 + data[i]) % 65521;
				s2 = (s2 + s1) % 65521;
			}
			
		return (s2 << 16) | s1;
	}
	
long int hash_FAQ6(data_t data)
	{

		unsigned int hash = 0;

		for(int i = 0; i < strlen(data); i++)
			{
				hash += (unsigned char)data[i];
				hash += (hash << 10);
				hash ^= (hash >> 6);
			}
	
		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);

		return hash;

	}

long int hash_Rot13(data_t data)
	{

		unsigned int hash = 0;

		for(int i = 0; i < strlen(data); i++)
			{
				hash += (unsigned char)data[i];
				hash -= (hash << 13) | (hash >> 19);
			}

		return hash;

	}