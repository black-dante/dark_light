/*!
\file
\brief Главная функция
Здесь начинает работать вся програма
*/

#include "sort_string.h"
#include <limits.h>

/*!
Максимальное количество строк
*/
const int LINESK = SHRT_MAX;

int main()
{
	FILE *file_out = fopen("Output/out.txt", "w");
	
    char *line_pointer[LINESK];
	int nlines = readlines_(line_pointer, LINESK);
	
	if (nlines >= 0)
	{
        shell_sort(line_pointer, nlines, strcmp_reverse, _swap);
		writelines_(file_out, line_pointer, nlines);
		
	}
	else printf("ERROR\n");
}
