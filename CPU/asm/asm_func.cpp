#include <stdio.h>
#include <stdlib.h>

//{--------------------------------------------------------------------------------------------------------------------------------------
#define CMD(word) int func_##word(FILE* input, int number, ASM_BUFFER* my_buffer);
	
#define COMMANDS_CPU
#include "../headers/CPU_struct.h"
#undef COMMANDS_CPU
int func_label(FILE* input, char* label_word, ASM_BUFFER* my_buffer);
void label_tree_upgrade(char* label_word, struct label* new_label, int position);

#undef CMD(word)
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
#define func_(word) 														\
int func_##word(FILE* input, int number, ASM_BUFFER* my_buffer)				\
	{																		\
		my_buffer->data[my_buffer->buffer_count++] = number;				\
		return 1;															\
	}
	
func_(add)
func_(sub)
func_(mul)
func_(div)
func_(out)
func_(in)
func_(ret)
func_(sqrt)
func_(sin)
func_(cos)
func_(end)

#undef func_(word)
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
#define reg(reg_name) 														\
if(strcmp(word, #reg_name) == 0) 											\
	{																		\
		my_buffer->data[my_buffer->buffer_count++] = reg_name;				\
		return 1;															\
	}																		\	

	
#define command_conversion 													\
my_buffer->buffer_count--;													\
func_push(input, push_number, my_buffer);									\
																			\
while(1)																	\
	{																		\
		char word_znak[MAXWORD];											\
		int symbol = fgetword_without_prob(word_znak, MAXWORD, input);		\
																			\
		if(symbol == 'EOF') return 0;										\
																			\
		if(symbol == ']') break;											\
																			\
		func_push(input,  push_number, my_buffer);							\
																			\
		if(symbol == '+') 													\
			func_add(input, add_number, my_buffer);							\
		else if (symbol == '-')												\
			func_sub(input, sub_number, my_buffer);							\
		else																\
			return 0;														\
																			\
	}																		\
	

int func_push(FILE* input, int number, ASM_BUFFER* my_buffer)
	{
		char word[MAXWORD];
		
		my_buffer->data[my_buffer->buffer_count++] = number;
		
		if(fgetword_without_prob(word, MAXWORD, input) != DIGIT)
			{
				if(strcmp(word, "[") == 0)
					{
						command_conversion
							
						my_buffer->data[my_buffer->buffer_count++] = pop_number;// номер команды pop
						my_buffer->data[my_buffer->buffer_count++] = sys_reg;//номер системного регистра
						my_buffer->data[my_buffer->buffer_count++] = push_number;//номер команды пуш
						my_buffer->data[my_buffer->buffer_count++] = write_to_ram;//команда push [sys_reg]
						
						return 1;
						
					}
				
				#define REGISTERS_CPU
				#include "../headers/CPU_struct.h"
				#undef REGISTERS_CPU
				reg(sys_reg)
				
				printf("push_error");
				return 0;
			}
		
		my_buffer->data[my_buffer->buffer_count++] = default_write;//аргумент число
		
		buf_type word_num = atof(word);
		
		my_buffer->data[my_buffer->buffer_count++] = word_num;
		
		return 1;
	}
	
int func_pop(FILE* input, int number, ASM_BUFFER* my_buffer)
	{
		char word[MAXWORD];
		my_buffer->data[my_buffer->buffer_count++] = number;
		
		if(fgetword_without_prob(word, MAXWORD, input) != LETTER)
			{
				if(strcmp(word, "[") == 0)
					{
						command_conversion
							
						my_buffer->data[my_buffer->buffer_count++] = pop_number;// номер команды pop
						my_buffer->data[my_buffer->buffer_count++] = sys_reg;//номер системного регистра
						my_buffer->data[my_buffer->buffer_count++] = pop_number;//номер команды pop
						my_buffer->data[my_buffer->buffer_count++] = write_to_ram;//команда pop [sys_reg]
						
						return 1;
					}
					
				printf("pop_error");
				return 0;
			}
		
		#define REGISTERS_CPU
		#include "../headers/CPU_struct.h"
		#undef REGISTERS_CPU
		reg(sys_reg)
		
		fungetword(word);
		
		my_buffer->data[my_buffer->buffer_count++] = default_write;//нет регистра
		
		return 1;
		
	}

#undef command_conversion()
#undef reg(reg_name)
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------	
#define jump_command(jump_name)																	\
int func_##jump_name(FILE* input, int number, ASM_BUFFER* my_buffer)							\
	{																							\
		char word[MAXWORD];																		\
																								\
		my_buffer->data[my_buffer->buffer_count++] = number;									\
																								\
		if(fgetword_without_prob(word, MAXWORD, input) != LETTER)								\
			{																					\
				printf("%s error", #jump_name);													\
				return 0;																		\
			}																					\
																								\
		struct label* label_copy = my_buffer->first_label;										\
																								\
		while(label_copy->name != NULL)															\
			{																					\
				if(strcmp(label_copy->name, word) == 0)											\
					{																			\
						my_buffer->data[my_buffer->buffer_count++] = label_copy->position;		\
						return 1;																\
					}																			\
																								\
				else if(strcmp(label_copy->name, word) > 0)										\
					label_copy = label_copy->right_label;										\
																								\
				else																			\
					label_copy = label_copy->left_label;										\
			}																					\
																								\
		my_buffer->data[my_buffer->buffer_count++] = -1;										\
																								\
		return 1;																				\
	}																							\

	
jump_command(jmp)
jump_command(call)
jump_command(je)
jump_command(jne)
jump_command(ja)
jump_command(jae)
jump_command(jb)
jump_command(jbe)
	
#undef jump_command(jump_name)
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
#define reg(reg_name) 														\
if(strcmp(word, #reg_name) == 0) 											\
	{																		\
		my_buffer->data[my_buffer->buffer_count++] = reg_name;				\
	}																		\

	
int func_cmp(FILE* input, int number, ASM_BUFFER* my_buffer)
	{
		char word[MAXWORD];
		printf("Hey");
		
		my_buffer->data[my_buffer->buffer_count++] = number;
		
		int symbol = fgetword_without_prob(word, MAXWORD, input);
		
		switch(symbol)																
			{																
				case DIGIT:													
	
				my_buffer->data[my_buffer->buffer_count++] = 0;				
				my_buffer->data[my_buffer->buffer_count++] = atof(word);	

				break;														

				case LETTER:												
	
				#define REGISTERS_CPU										
				#include "../headers/CPU_struct.h"							
				#undef REGISTERS_CPU										
				reg(sys_reg)											

				break;														

				default:		
				printf("CMP error");
				return 0;													
				break;														
			}			
			
		symbol = fgetword_without_prob(word, MAXWORD, input);
		
		switch(symbol)																
			{																
				case DIGIT:													

				my_buffer->data[my_buffer->buffer_count++] = 0;			
				my_buffer->data[my_buffer->buffer_count++] = atof(word);	

				break;														

				case LETTER:												

				#define REGISTERS_CPU										
				#include "../headers/CPU_struct.h"							
				#undef REGISTERS_CPU										
				reg(sys_reg)												

				break;														

				default:
				printf("CMP error");				
				return 0;													
				break;														
			}			
			
		return 1;
	}
	
#undef reg(reg_name)
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------	
int func_label(FILE* input, char* label_word, ASM_BUFFER* my_buffer)
	{
		char word[MAXWORD];
		
		if(fgetword(word, MAXWORD, input) != ':')
			return 0;
		
		label_tree_upgrade(label_word, my_buffer->first_label, my_buffer->buffer_count);
		
		return 1;
	}
	
void label_tree_upgrade(char* label_word, struct label* new_label, int position)
	{
		if(new_label->name == NULL)
			{
				new_label->name = (char*)calloc(strlen(label_word), sizeof(char));
				strcpy(new_label->name, label_word);
				new_label->position = position;
				
				new_label->right_label = (struct label*)calloc(1, sizeof(struct label));
				new_label->left_label = (struct label*)calloc(1, sizeof(struct label));
				return;
			}
			
		else if(strcmp(new_label->name, label_word) == 0)
			{
				new_label->position = position;
				return;
			}
			
		else if(strcmp(new_label->name, label_word) > 0)
			label_tree_upgrade(label_word, new_label->right_label, position);
		
		else
			label_tree_upgrade(label_word, new_label->left_label, position);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------
