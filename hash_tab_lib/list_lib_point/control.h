//{--------------------------------------------------------------------------------------------------------------------------------------		
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Приветствую уважаемый пользователь, спасибо что юзаете мои списки))
//
//	Вы зашли в файл управления списком
//
//	Перед использованием настройте все данные как нужно вам
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 *	Элемент структуры список
 *
 *	struct list_t
 *		{
 *			data_t field;  -- поле данных
 *			struct list_t *next; 	-- указатель на следующий элемент
 *			struct list_t *prev; 	-- указатель на предыдущий элемент
 *		};
 */

/**
 *	Структура нескольких элементов списка
 *
 *	struct list_ar_t
 *		{
 *			list_t* first; -- указатель на первый элемент
 *			list_t* last;  -- указатель на последний элемент
 *
 *			size_t size;   -- размер всей структуры
 *
 *			FILE* error_list; -- файл для вывода ошибок(Пожалуйста не ошибайтесь много)
 *		};
 */

/**
 *
 *	введите тип значения который будет в списке
 *	
 *	пример typedef char* data_t;
 */
#ifdef LIST_TYPE

typedef char* data_t;

#endif


/**
 *
 *	введите каким образом печатать полную информацию об элементе списка
 *	
 *	пример fprintf(data_file, "list field = %s\n", list->field);
 */
#ifdef LIST_FULL_INFO

fprintf(data_file, "list field = %s\n", list->field);

#endif


/**
 *
 *	введите каким образом печатать короткую информацию об элементе списка
 *	
 *	пример fprintf(data_file, "%s->", list->field);
 */
#ifdef LIST_SHORT_INFO

fprintf(data_file, "%s->", list->field);

#endif


/**
 *
 *	Введите каким образом искать элемент вашего списка
 *	
 *	if(list->field == field) return list;
 */
#ifdef FIND_LIST_ELEM

if(list->field == field) return list;

#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	ПОСЛЕ НАСТРОЙКИ ВАМ ДОСТУПНЫ СЛЕДУЮЩИЕ ФУНКЦИИ
//
//
//	ДЛЯ ОДНОГО ЭЛЕМЕТНА СПИСКА
//
//	struct list_t* list_create(data_t field) - конструктор
//	void list_destroy(list_t** list) - деструктор !!принимает двойной указатель на структуру
//
//	void list_full_info(list_t* list, FILE* data_file) - напечатать полную информацию о элементе в файл
//	void list_short_info(list_t* list, FILE* data_file) - напечатать короткую информацию об элементе в файл
//	void root_full_info(list_t* list, FILE* data_file) - напечатать полную информацию о корне в файл
//	void root_short_info(list_t* list, FILE* data_file) - напечатать краткую информацию о корне в файл
//
//	void add_next_elem(list_t *list, list_t *add_list) - добавляет следующий элемент add_list в list
//	void add_prev_elem(list_t *list, list_t *add_list) - добавляет предыдущий элемент add_list в list
//
//	void delete_elem(list_t *list) - удаляет элемент list из списка
//	void change_elem(list_t *list1, list_t *list2) - меняет два элемента в списке местами
//
//
//	ДЛЯ НЕСКОЛЬКИХ ЭЛЕМЕНТОВ СПИСКА
//
//	struct list_ar_t* list_ar_create(FILE* error_list) - конструктор, принимает файл с ошибками
//	void delete_all_elem(list_ar_t* list_ar) - удаляет все элементы
//	void list_ar_destroy(list_ar_t** list_ar) - освобождает память списка !!принимает двойной указатель на структуру
//
//	void add_elem_with_zero_size(list_ar_t* list_ar, data_t field) - функция нужна на случай добавления самого первого элемента
//	void add_next_elem(list_ar_t* list_ar, list_t* point, data_t field) - добавляет элемент в массив списков за point
//	void add_prev_elem(list_ar_t* list_ar, list_t* point, data_t field) - добавляет элемент в массив списков перед point
//	void add_first_elem(list_ar_t* list_ar, data_t field) - добавляет элемент в массив списков в начало
//	void add_last_elem(list_ar_t* list_ar, data_t field) - добавляет элемент в массив списков в конец
//
//	struct list_t* get_next_elem(list_t* point) - дает указатель на следующий элемент за point
//	struct list_t* get_prev_elem(list_t* point) - дает указатель на предыдущий элемент перед point
//	struct list_t* get_first_elem(list_ar_t* list_ar) - дает указатель на первый элемент в массиве списков
//	struct list_t* get_last_elem(list_ar_t* list_ar) - дает указатель на последний элемент в массиве списков
//
//	void delete_elem(list_ar_t* list_ar, list_t *list) - удаляет элемент list из массива list_ar
//	struct list_t* find_elem(list_ar_t* list_ar, data_t field) - находит элемент по его значению
//	size_t get_list_ar_size(list_ar_t* list_ar) - выдает размер списка
//
//	void list_ar_header(list_ar_t* list_ar, FILE* data) - печатает заголовок листа
//	void list_ar_full_info(list_ar_t* list_ar, FILE* data) - печатает полную информацию о массиве cписков
//	void list_ar_short_info(list_ar_t* list_ar, FILE* data) -печатает краткую информацию о массиве cписков
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//}--------------------------------------------------------------------------------------------------------------------------------------	