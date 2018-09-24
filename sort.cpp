/*!
\file
\brief Здесь собраны функции для сортировки строк
*/

#include <string.h>
/*!
Сортировка строк по методу Шелла
\param[in] line_pointer[] массив строк для сортировки
\param[in] n количество элементов в массиве
\param[in] comp() функция для сортировки определенным способом
\param[in] exch() функция для обмена строк определенным способом
\return 
*/
void shell_sort(char *line_pointer[],int n, int (*comp)(char *s, char *t), void (*exch)(char *px[], char *py[]))
{
	int gap = 0, i = 0, j = 0;
	for(gap = n/2; gap > 0; gap/=2)
		for(i = gap; i < n; i++)
			for(j = i - gap; j >= 0; j -= gap)
			{
				if((*comp) (line_pointer[j], line_pointer[j + gap]) <= 0)
					break;
				(*exch) (&line_pointer[j], &line_pointer[j + gap]);
			}
}

/*!
Функция обмена строк
\param[in] str1[] строка для обмена
\param[in] str2[] строка для обмена
*/
void _swap(char *str1[], char *str2[])
{
	char *temp;
	char *str_copy = *str1;
	*str1 = *str2;
	*str2 = str_copy;
}

/*!
Сравнивает строки лексикографически с начала
\param[in] str1[] строка для сравнения
\param[in] str2[] строка для сравнения
\return результат сравнения
*/
int strcmp_norm(const char *str1,const char *str2)
{
	for (; *str1 == *str2; str1++, str2++)
		if (*str1 == '\0') return(0);
	return(*str1 - *str2);
}

/*!
Сравнивает строки лексикографически с конца
\param[in] str1[] строка для сравнения
\param[in] str2[] строка для сравнения
\return результат сравнения
*/
int strcmp_reverse(char *str1, char *str2)
{
	int str1_len = strlen(str1);
	int str2_len = strlen(str2);
	
	char *str1_end = str1 + str1_len-1;
	char *str2_end = str2 + str2_len-1;
	
	if(*str1_end == '\n') str1_end--;
	if(*str2_end == '\n') str2_end--;
	
	for (; *str1_end == *str2_end; str1_end--, str2_end--)
		if (str1_end == str1 || str2_end == str2) return(str1_len - str2_len);
	
	return(*str1_end - *str2_end);
}


