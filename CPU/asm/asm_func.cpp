#include <stdio.h>
#include <stdlib.h>

#define prototype(word)	int func_##word(FILE* input, int number, ASM_BUFFER* my_buffer)

#define func_(word) 														\
int func_##word(FILE* input, int number, ASM_BUFFER* my_buffer)				\
	{																		\
		my_buffer->buffer_int[my_buffer->buffer_count++] = number;			\
		return 1;															\
	}																		\


prototype(push);
prototype(pop);
prototype(add);
prototype(sub);
prototype(mul);
prototype(div);
prototype(out);
prototype(jmp);
int func_label(FILE* input, char* label_word, ASM_BUFFER* my_buffer);
void label_tree_upgrade(char* label_word, struct label* new_label, int position);

func_(pop)
func_(add)
func_(sub)
func_(mul)
func_(div)
func_(out)
func_(in)

int func_push(FILE* input, int number, ASM_BUFFER* my_buffer)
	{
		char word[MAXWORD];
		
		my_buffer->buffer_int[my_buffer->buffer_count++] = number;
		
		if(fgetword_without_prob(word, MAXWORD, input) != DIGIT)
			return 0;
		
		int word_num = atoi(word);
		
		my_buffer->buffer_int[my_buffer->buffer_count++] = word_num;
		
		return 1;
	}
	
int func_pushreg(FILE* input, int number, ASM_BUFFER* my_buffer)
	{
		char word[MAXWORD];
		
		my_buffer->buffer_int[my_buffer->buffer_count++] = number;
		
		if(fgetword_without_prob(word, MAXWORD, input) != LETTER)
			return 0;
		
		
		if(strcmp(word, "rax") == 0)
			{
				my_buffer->buffer_int[my_buffer->buffer_count++] = 0;
				return 1;
			}
		else if(strcmp(word, "rbx") == 0)
			{
				my_buffer->buffer_int[my_buffer->buffer_count++] = 1;
				return 1;
			}
		else if(strcmp(word, "rcx") == 0)
			{
				my_buffer->buffer_int[my_buffer->buffer_count++] = 2;
				return 1;
			}
		else if(strcmp(word, "rdx") == 0)
			{
				my_buffer->buffer_int[my_buffer->buffer_count++] = 3;
				return 1;
			}
		else
			return 0;
	}
	
int func_popreg(FILE* input, int number, ASM_BUFFER* my_buffer)
	{
		char word[MAXWORD];
		
		my_buffer->buffer_int[my_buffer->buffer_count++] = number;
		
		if(fgetword_without_prob(word, MAXWORD, input) != LETTER)
			return 0;
		
		
		if(strcmp(word, "rax") == 0)
			{
				my_buffer->buffer_int[my_buffer->buffer_count++] = 0;
				return 1;
			}
		else if(strcmp(word, "rbx") == 0)
			{
				my_buffer->buffer_int[my_buffer->buffer_count++] = 1;
				return 1;
			}
		else if(strcmp(word, "rcx") == 0)
			{
				my_buffer->buffer_int[my_buffer->buffer_count++] = 2;
				return 1;
			}
		else if(strcmp(word, "rdx") == 0)
			{
				my_buffer->buffer_int[my_buffer->buffer_count++] = 3;
				return 1;
			}
		else
			return 0;
	}
	
int func_jmp(FILE* input, int number, ASM_BUFFER* my_buffer)
	{
		char word[MAXWORD];
		
		my_buffer->buffer_int[my_buffer->buffer_count++] = number;
		
		if(fgetword_without_prob(word, MAXWORD, input) != LETTER)
			return 0;
		
		struct label* label_copy = my_buffer->first_label;
		
		while(label_copy->name != NULL)
			{
				if(strcmp(label_copy->name, word) == 0)
					{
						my_buffer->buffer_int[my_buffer->buffer_count++] = label_copy->position;
						return 1;
					}
				
				else if(strcmp(label_copy->name, word) > 0)
					label_copy = label_copy->right_label;
				
				else
					label_copy = label_copy->left_label;
			}
			
		my_buffer->buffer_int[my_buffer->buffer_count++] = -1;
		
		return 1;
	}

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
	
#undef func_(word)
#undef prototype(word)

