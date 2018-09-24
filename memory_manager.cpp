/*!
\file
\brief Я менеджер памяти

Если тебе нужна память, то обращайся ко мне
*/

/*!
Размер памяти менеджера
*/
const int ALLOCSIZE = 10000000;

static char allocbuf[ALLOCSIZE];
static char *alloc_pointer = allocbuf;

char *alloc(int n);
void free(char *pointer);

/*!
Выделяет область памяти в количестве n байт и возвращает указатель типа char на первый байт 
\param[in] n Количество нужных байт
\return  Указатель на первый байт памяти
*/
char *alloc(int n)
{
	if (alloc_pointer + n <= allocbuf + ALLOCSIZE)
	{
		alloc_pointer += n;
		return(alloc_pointer - n);
	}
	else return(0);

}

/*!
Освобождает память с введеного адреса
\param[in] pointer Адрес с которого нужно освободить память
*/
void free(char *pointer)
{
	if (pointer >= allocbuf && pointer <= allocbuf + ALLOCSIZE)
			alloc_pointer = pointer;
}
