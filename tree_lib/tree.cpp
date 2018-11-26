/*!
	\file
	\brief Файл со структурой дерева и его функциями
*/

#include <string.h>
#include "node.cpp"
#include "read_functions/fgetword.cpp"

const int FIRST_CAPASITY = 100; ///< Начальная вместимость дерева

const int CAP_INCREASE = 2; ///< Во сколько раз увеличить размер дерева
const int CAP_DECREASE = 2; ///< Во сколько раз уменьшить размер дерева

const int MAXWORDD = 100; ///< Для функции fgetword_without_prob


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Структура дерева

	Содержит\n
		имя дерева\n
		номер корня\n
		массив ссылок на свободные узлы\n
		первый свободный узел\n
		текущий размер\n
		текущую вместимость\n
		файл ошибок\n
 */
 
struct tree_t
	{
		char* name;
		
		char* diff;
		
		size_t root;
		
		node_t** nodes;
		
		size_t first_free;
		size_t size;
		size_t capasity;
		
		FILE* error_tree;
	};
//}--------------------------------------------------------------------------------------------------------------------------------------		

tree_t* tree_create(char* name, char* diff, FILE* error_tree);
void tree_destroy(tree_t** tree);
size_t flash_free_node(tree_t* tree, size_t node);
int tree_increase(tree_t* tree);
int tree_decrease(tree_t* tree);
size_t get_free_elem(tree_t* tree);
size_t add_node(tree_t* tree, data_t data, size_t left, size_t right);
void tree_visit(tree_t* tree, size_t node, void(*visit_func)(tree_t* tree, size_t node));
void tree_print(tree_t* tree, size_t node, FILE* output);
void tree_print_dot(tree_t* tree, size_t node);
size_t tree_read(tree_t* tree, char* diff, FILE* input);

#include "tree_assert.h"

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Конструктор

	\return Пустую структуру дерева
 */	
 
tree_t* tree_create(char* name, char* diff, FILE* error_tree)
	{
		tree_t* tree = (tree_t*) calloc(1, sizeof(tree_t));
		
		tree->nodes = (node_t**)calloc(FIRST_CAPASITY, sizeof(node_t*));

		for(int i = 0; i < FIRST_CAPASITY; i++)
			tree->nodes[i] = node_create();
		
		tree->name = strdup(name);
		tree->diff = strdup(diff);
		
		tree->root = NULL_NODE;
		
		tree->first_free = 0;
		tree->size = 0;
		tree->capasity = FIRST_CAPASITY;
		
		tree->error_tree = error_tree;
		
		flash_free_node(tree, 0);
		
		return tree;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------	


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Деструктор

	Обнуляет все переменные дерева и освобождает память
	\param [in] tree Двойной указатель на дерево
 */		
 	
void tree_destroy(tree_t** tree)
	{
		assert(tree != NULL);
		
		if(*tree == NULL) return;
		
		(*tree)->root = NULL_NODE;
		
		for(int i = 0; i < FIRST_CAPASITY; i++)
				node_destroy(&(*tree)->nodes[i]);
			
		free((*tree)->nodes);
		
		(*tree)->name = NULL;
		
		(*tree)->first_free = 0;
		(*tree)->size = 0;
		(*tree)->capasity = 0;
		
		fclose((*tree)->error_tree);
		
		free(*tree);
		
		*tree = NULL;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Связывание свободных узлов для быстрого поиска

	\param [in] tree указатель на дерево
	\param [in] node номер узла с которого нужно связать свободные
 */	
 
size_t flash_free_node(tree_t* tree, size_t node)////Прошить все узлы дерева односвязным списком начиная с какого то узла node
	{
		assert(tree != NULL);
		assert(node < tree->capasity);
		
		tree->first_free = NULL_NODE;
		printf("\nlol\n");
		for(size_t i = tree->capasity - 1; i > node ; i--)
			if(tree->nodes[i]->free == true)
				{
					tree->first_free = i;
					break;
				}
		printf("\nlol\n");		
		if(tree->first_free == NULL_NODE)
			{
				printf("Don't have free elems\n");
				return NULL_NODE; //свободных элементов нет
			}
		printf("\nlol\n");
		size_t first = tree->first_free;
		
		for(size_t i = first - 1; i > node; i--)
			if(tree->nodes[i]->free == true)
				{
					if(i % 10000 == 0)
					printf("\%ld\n", i);
					tree->nodes[i]->left = tree->first_free;
					tree->first_free = i;
				}//связь односвязного списка по левому сыну
		printf("\nlol\n");
	}
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Очищает дерево

	\param [in] tree указатель на дерево
 */	
 
void tree_clear(tree_t* tree)
	{
		tree->root = NULL_NODE;
		
		for(int i = 0; i < tree->capasity; i++)
			tree->nodes[i]->free = true;
		
		tree->first_free = 0;
		tree->size = 0;		
		
		flash_free_node(tree, 0);	
	}
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Увеличение размера дерева

	Увеличивает дерево в кол во раз заданное переменной CAP_INCREASE
	\param [in] tree указатель на дерево
	\return true - если все ок\n
			false - если ошибка
 */	
 
int tree_increase(tree_t* tree)
	{
		assert(tree != NULL);
		
		printf("HELLO\n");
		
		size_t new_capasity = tree->capasity * CAP_INCREASE;
		
		tree->nodes =(node_t**)realloc(tree->nodes, new_capasity * sizeof(node_t*));
		
		for(size_t i = tree->capasity; i < new_capasity; i++)
				tree->nodes[i] = node_create();
		
		if(tree->nodes != NULL)
			{
				tree->capasity *= CAP_INCREASE;
				flash_free_node(tree, tree->capasity / CAP_INCREASE);
				return true;
			}
		
		printf("Не могу выделить память\n");
		return false;
	}	
//}--------------------------------------------------------------------------------------------------------------------------------------	


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Уменьшение размера дерева

	Уменьшает дерево в кол во раз заданное переменной CAP_DECREASE
	\param [in] tree указатель на дерево
	\return true - если все ок\n
			false - если ошибка
 */	
 
int tree_decrease(tree_t* tree)
	{
		assert(tree != NULL);
		
		size_t new_capasity = tree->capasity / CAP_DECREASE;
		
		tree->nodes =(node_t**)realloc(tree->nodes, new_capasity * sizeof(node_t*));
		
		if(tree->nodes != NULL)
			{
				tree->capasity /= CAP_DECREASE;
				flash_free_node(tree, 0);
				return true;
			}
			
		return false;
	}	
//}--------------------------------------------------------------------------------------------------------------------------------------	


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief дает свободный элемент

	\param [in] tree указатель на дерево
 */	
 
size_t get_free_elem(tree_t* tree)
	{
		assert(tree != NULL);
		
		if(tree->first_free == NULL_NODE)
			tree_increase(tree);
		
		
		size_t free_elem = tree->first_free;
		
		tree->first_free = tree->nodes[tree->first_free]->left;
		
		assert(free_elem != NULL_NODE);
		return free_elem;
		
	}
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Добавляет узел в дерево

	\param [in] tree указатель на дерево
	\param [in] data данные для нового узла
	\param [in] left левый сын
	\param [in] right правый сын
	
	\return номер узла дерева
 */
	
size_t add_node(tree_t* tree, data_t data, size_t left, size_t right)
	{
		tree_assert(tree);
		
		size_t node_n = get_free_elem(tree);
		
		if(tree->size == 0) tree->root = node_n;
		
		tree->nodes[node_n]->data = data;
		tree->nodes[node_n]->left = left;
		tree->nodes[node_n]->right = right;
		tree->nodes[node_n]->free = false;
		
		switch(data[0])
			{
				case '*':
					tree->nodes[node_n]->type = oper;
				break;
				
				case '+':
					tree->nodes[node_n]->type = oper;
				break;
				
				case '-':
					tree->nodes[node_n]->type = oper;
				break;
				
				case '/':
					tree->nodes[node_n]->type = oper;
				break;
				
				default:
					if(data[0] >= '0' && data[0] <= '9')
						tree->nodes[node_n]->type = digit;
					
					else if((data[0] >= 'a' && data[0] <= 'z' || data[0] >= 'A' && data[0] <= 'Z' || data[0] == '_'))
							if(strcmp(data, tree->diff) == 0)
								tree->nodes[node_n]->type = var;
							else
								tree->nodes[node_n]->type = digit;
							
					else tree->nodes[node_n]->type = null;
				break;
			}
		
		tree->size++;
		
		tree_assert(tree);
		
		return node_n;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Меняет данные узла

	\param [in] tree указатель на дерево
	\param [in] node_n указатель на узел
	\param [in] data данные для узла
 */
	
void change_node_data(tree_t* tree, size_t node_n, data_t data)
	{
		tree_assert(tree);
		
		tree->nodes[node_n]->data = data;
		
		switch(data[0])
			{
				case '*':
					tree->nodes[node_n]->type = oper;
				break;
				
				case '+':
					tree->nodes[node_n]->type = oper;
				break;
				
				case '-':
					tree->nodes[node_n]->type = oper;
				break;
				
				case '/':
					tree->nodes[node_n]->type = oper;
				break;
				
				default:
					if(data[0] >= '0' && data[0] <= '9')
						tree->nodes[node_n]->type = digit;
					
					else if((data[0] >= 'a' && data[0] <= 'z' || data[0] >= 'A' && data[0] <= 'Z' || data[0] == '_'))
							if(strcmp(data, tree->diff) == 0)
								tree->nodes[node_n]->type = var;
							else
								tree->nodes[node_n]->type = digit;
							
					else tree->nodes[node_n]->type = null;
				break;
			}
		
		tree_assert(tree);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Рекурсивная функция, проходит по всем узлам дерева

	\param [in] tree указатель на дерево
	\param [in] node номер узла в дереве
	\param [in] visit_func указатель на функцию, для которой делается обход
 */
 
void tree_visit(tree_t* tree, size_t node, void(*visit_func)(tree_t* tree, size_t node))
	{
		assert(tree != NULL);
		
		if(node == NULL_NODE) return;
		
		tree_visit(tree, (tree->nodes[node])->left, visit_func);
		
		visit_func(tree, node);
		
		tree_visit(tree, (tree->nodes[node])->right, visit_func);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Рекурсивная функция печати дерева

	\param [in] tree указатель на дерево
	\param [in] node номер узла с которого начнется распечатка
	\param [in] output файл для записи
 */
 
void tree_print_rec(tree_t* tree, size_t node, FILE* output);
 
 
void tree_print(tree_t* tree, size_t node)
	{
		char* filename1 = (char* )calloc(MAXWORDD, sizeof(char));
		
		strcpy(filename1, tree->name);
		strcat(filename1, ".txt");
		
		FILE* output = fopen(filename1, "w");
		
		tree_print_rec(tree, node, output);
		
		fclose(output);
	} 
 
 
void tree_print_rec(tree_t* tree, size_t node, FILE* output)
	{
		if(node == NULL_NODE) return;
		
		static int i = 1;
		
		i++;
		
		/*for(int j = 0; j < i*4 - 4; j++)
			fprintf(output, " ");*/
		
		if(i != 2) fprintf(output, "(");
		
		tree_print_rec(tree, tree->nodes[node]->left, output);
		
		fprintf(output, "%s", tree->nodes[node]->data);
		
		tree_print_rec(tree, tree->nodes[node]->right, output);
		
		/*for(int j = 0; j < i*4 - 4; j++)
			fprintf(output, " ");*/
		
		if(i != 2) fprintf(output, ")");
		
		i--;
		
	}
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Рекурсивная функция печати дерева в латех

	\param [in] tree указатель на дерево
	\param [in] node номер узла с которого начнется распечатка
 */
 
 
void tree_print_lat_rec(tree_t* tree, size_t node, FILE* output);
 
void tree_print_latex(tree_t* tree, size_t node)
	{
		char* filename1 = (char* )calloc(MAXWORDD, sizeof(char));
		
		strcpy(filename1, tree->name);
		strcat(filename1, ".tex");
		
		char* filename2 = (char* )calloc(MAXWORDD, sizeof(char));
		
		strcpy(filename2, "pdflatex ");
		strcat(filename2, filename1);
		
		FILE* output = fopen(filename1, "w");
		
		//Печать заголовка файла;
		
		fprintf(output,\
		"\
		\\documentclass[a4paper,12pt]{article}\n\
		\\usepackage{graphicx}\n\
		\\usepackage[T2A]{fontenc}\n\
		\\usepackage[utf8]{inputenc}\n\
		\\usepackage[english,russian]{babel}\n\
		\\pagestyle{plain}\n\
		\\usepackage{wrapfig}\n\
		\\usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools}\n\
		\\usepackage{wasysym}\n\
		\\begin{document}\n\
		");
		
		fprintf(output, "$");
		tree_print_lat_rec(tree, node, output);
		fprintf(output, "$\n");
		
		fprintf(output, "\\end{document}");
		
		fclose(output);
		
		//system(filename2);
		
	} 

	
void tree_print_lat_rec(tree_t* tree, size_t node, FILE* output)
	{
		static int count = 0;
		
		//printf("count = %d\n", count);
		
		count++;
		
		if(node == NULL_NODE) return;
		
		switch(tree->nodes[node]->type)
			{
				case null:
					fprintf(output, "0");
				break;
				
				case digit:
					fprintf(output, "%s", tree->nodes[node]->data);
				break;
				
				case var:
					fprintf(output, "%s", tree->nodes[node]->data);
				break;
				
				case oper:
					switch(tree->nodes[node]->data[0])
						{
							case '+':
							
								fprintf(output, " ( ");
								
								if(count > 5)
								{
									count = 0;
									fprintf(output, "\\\\\n");
								}
								
								tree_print_lat_rec(tree, tree->nodes[node]->left, output);
								fprintf(output, " + ");
								tree_print_lat_rec(tree, tree->nodes[node]->right, output);
								fprintf(output, " ) ");
								
								if(count > 5)
								{
									count = 0;
									fprintf(output, "\\\\\n");
								}
							break;
							
							case '-':
							
								fprintf(output, " ( ");
								
								if(count > 5)
								{
									count = 0;
									fprintf(output, "\\\\\n");
								}
								
								tree_print_lat_rec(tree, tree->nodes[node]->left, output);
								fprintf(output, " - ");
								tree_print_lat_rec(tree, tree->nodes[node]->right, output);
								fprintf(output, " ) ");
								
								if(count > 5)
								{
									count = 0;
									fprintf(output, "\\\\\n");
								}
							break;
							
							case '*':
							
								tree_print_lat_rec(tree, tree->nodes[node]->left, output);
								fprintf(output, " * ");
								tree_print_lat_rec(tree, tree->nodes[node]->right, output);
								
								if(count > 5)
								{
									count = 0;
									fprintf(output, "\\\\\n");
								}
							break;
							
							case '/':
								tree_print_lat_rec(tree, tree->nodes[node]->left, output);
								fprintf(output, " / ");
								tree_print_lat_rec(tree, tree->nodes[node]->right, output);
								
								if(count > 5)
								{
									count = 0;
									fprintf(output, "\\\\\n");
								}

							break;
						}
				break;
			}
	}

//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Рекурсивная функция печати дерева в дот

	\param [in] tree указатель на дерево
	\param [in] node номер узла с которого начнется распечатка
 */
 
void tree_print_d(tree_t* tree, size_t node, FILE* output); 
 
 
void tree_print_dot(tree_t* tree, size_t node)
	{
		char* filename1 = (char* )calloc(MAXWORDD, sizeof(char));
		
		strcpy(filename1, tree->name);
		strcat(filename1, ".gv");
		
		char* filename2 = (char* )calloc(MAXWORDD, sizeof(char));
		
		strcpy(filename2, tree->name);
		strcat(filename2, ".jpg");
		
		char* sysdot = (char* )calloc(MAXWORDD, sizeof(char));
		
		strcpy(sysdot, "dot -Tjpg -o ");
		strcat(sysdot, filename2);
		strcat(sysdot, " ");
		strcat(sysdot, filename1);
		
		FILE* output = fopen(filename1, "w");
		
		fprintf(output, "digraph G\n{\n");
		
		tree_print_d(tree, tree->root, output);
		
		fprintf(output, "}");
		
		fclose(output);
		
		system(sysdot);
	}
 
void tree_print_d(tree_t* tree, size_t node, FILE* output)
	{
		if(node == NULL_NODE) return;
		
		tree_print_d(tree, tree->nodes[node]->left, output);
		
		switch(tree->nodes[node]->type)
			{
				case null:
					fprintf(output, "\"%d: %s\" [color = red];\n", node, tree->nodes[node]->data);
				break;
				
				case digit:
					fprintf(output, "\"%d: %s\" [color = green];\n", node, tree->nodes[node]->data);
				break;
				
				case oper:
					fprintf(output, "\"%d: %s\" [color = yellow];\n", node, tree->nodes[node]->data);
				break;
				
				case var:
					fprintf(output, "\"%d: %s\" [color = blue];\n", node, tree->nodes[node]->data);
				break;
			}
		
		if(tree->nodes[node]->left != NULL_NODE)
			fprintf(output, "\"%d: %s\" -> \"%d: %s\";\n", node, tree->nodes[node]->data, tree->nodes[node]->left, tree->nodes[tree->nodes[node]->left]->data);
		
		if(tree->nodes[node]->right != NULL_NODE)
			fprintf(output, "\"%d: %s\" -> \"%d: %s\";\n", node, tree->nodes[node]->data, tree->nodes[node]->right, tree->nodes[tree->nodes[node]->right]->data);
		
		tree_print_d(tree, tree->nodes[node]->right, output);
		
	}
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Рекурсивная функция чтения дерева

	\param [in] tree указатель на дерево
	\param [in] input файл для чтения
	
	\return узел созданный
 */
 
size_t tree_read(tree_t* tree, FILE* input)
	{
		size_t node = add_node(tree, "+", NULL_NODE, NULL_NODE);
		
		char word[MAXWORDD];
		char symb = fgetword_without_prob(word, MAXWORDD, input);
		
		if(symb == '(')
			{
				tree->nodes[node]->left = tree_read(tree, input);
				symb = fgetword_without_prob(word, MAXWORDD, input);
			}
			
		//tree->nodes[node]->data = strdup(word);
		change_node_data(tree, node, strdup(word));
		
		symb = fgetword_without_prob(word, MAXWORDD, input);
		
		if(symb == '(')
			{
				tree->nodes[node]->right = tree_read(tree, input);
				symb = fgetword_without_prob(word, MAXWORDD, input);
			}
		
		return node;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

