/*!
	\file
	\brief Файл со структурой узла и его функциями
*/

#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


typedef char* data_t; ///< Тип информации в дереве

const size_t NULL_NODE = -1; ///< Нулевой узел


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Перечисление для типа data в узле
 */
 
enum data_e
	{
		null = 0,	//красный
		digit = 1,	//зеленый
		oper = 2,	//желтый
		var = 3		//голубой
	};
//}--------------------------------------------------------------------------------------------------------------------------------------	

	
//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Структура узла дерева

	Содержит\n
		дату\n
		ссылку на левого сына\n
		ссылку на правого сына\n
		указание на то свободен ли узел\n
 */

struct node_t
	{
		data_e type;
		data_t data;
		
		size_t left;
		size_t right;
		
		size_t free;
	};
//}--------------------------------------------------------------------------------------------------------------------------------------		


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Конструктор

	\return Пустую структуру узла
 */	
 
node_t* node_create()
	{
		node_t* node = (node_t*) calloc(1, sizeof(node_t));
		
		node->type = null;
		node->data = NULL;
		
		node->left = NULL_NODE;
		node->right = NULL_NODE;
		
		node->free = true;
		
		return node;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------		


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
	\brief Деструктор

	Обнуляет все переменные узла и освобождает память
	\param [in] node Двойной указатель на узел
 */		
 
void node_destroy(node_t** node)
	{
		assert(node != NULL);
		
		if(*node == NULL) return;
		
		(*node)->type = null;
		(*node)->data = NULL;
		
		(*node)->left = NULL_NODE;
		(*node)->right = NULL_NODE;
		
		(*node)->free = true;
		
		free(*node);
		
		*node = NULL;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------		