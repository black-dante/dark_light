#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//}

//{-------------------------------------------------------------------------------------------------------------------

//! вводит одну строку																						
int getline_(char *str, int char_limit);

//! вводит строки и сохраняет их в масиве указателей
int readlines_(char *line_pointer[], int maxlines);

//! печатает массив указаелей строк line_pointer
void writelines_(FILE *out_file, char *line_pointer[], int nlines);

//! сортирует массив указателей строк 
void shell_sort(char *line_pointer[],int n, int (*comp)(char *str1, char *str2), void (*exch)(char *str1[], char *str2[]));

//! обмен строками
void swap_( char *str1[], char *str2[]);

//! сравнение строк лексикографически с начала
int strcmp_norm(char *str1, char *str2);

//! сравнение строк лексикографически с конца
int strcmp_reverse(char *str1, char *str2);

//}-------------------------------------------------------------------------------------------------------------------

#include "read_write_lines.cpp"
#include "sort.cpp"
