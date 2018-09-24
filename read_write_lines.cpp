/*!
\file
\brief Здесь собраны функции для ввода и вывода строк
*/

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "memory_manager.cpp"

/*!
Максимальное количество символов в строке
*/
const int MAXCHAR = SHRT_MAX;

/*!
Считывает строку с ввода и записывает ее в массив с адреса str
\param[in] char_limit Максимальное количество символов в строке, если строка не вмещается, произойдет обрезание
\param[out] str строка для заполнения символами
\return  Количество символов введенных в str не считая символа конца строки
*/
int getline_(char *str, int char_limit)
{
	int symbol = 0;
	int i = 0;
	
	for (i = 0; i < char_limit - 2 && (symbol = getchar()) != EOF && symbol != '\n'; i++)
			str[i] = symbol;
		
	 if(i != 0 || symbol == '\n') str[i++] = '\n';
		str[i] = '\0';
	
		return(i);
}

/*!
Считывает строки с ввода пока не кончится файл, либо не кончится место в массиве указателей
\param[in] maxlines Максимальное количество введенных строк 
\param[out] line_pointer Массив указателей для хранения строк
\return Количество введенных строк
*/
int readlines_(char *line_pointer[], int maxlines)
{
	int len = 0, nlines = 0;
	char *poiner = NULL, line[MAXCHAR] = "";
	while ((len = getline_(line, MAXCHAR)) > 0)
	{
		if (nlines >= maxlines)
		{ 
			printf("Readlines: nlines >= maxlines!!!\n");
			break;
		}
		else if ((poiner = alloc(len + 1)) == 0)
		{			
			printf("Readlines: alloc bufer is full\n");
			break;
		}	
		else if(line[0] != '\n')
		{
			strcpy(poiner, line);
			line_pointer[nlines++] = poiner;
		}
	}
	return(nlines);
}

/*!
Выводит строки из массива указателей строк в файл
\param [in] nlines Количество выводимых строк
\param [in] file_out Файл в который все выведется
\param [in] line_pointer[] Массив указателей на строки 
*/
void writelines_(FILE *file_out,char *line_pointer[], int nlines)
{
	for (int i = 0; i < nlines; i++)
		fprintf(file_out, "%s", line_pointer[i]);
}
