#include <string.h>
#include <stdlib.h>

const int MAXWORD = 100;

struct label
	{
		char* name = NULL;
		int position = -1;
		
		struct label* right_label = NULL;
		struct label* left_label = NULL;
	};

typedef struct ASM_buffer
	{
		int* buffer_int;
		int buffer_count;
		//int label_buffer[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
		struct label* first_label = (struct label*)calloc(1, sizeof(struct label));
		
	} ASM_BUFFER;

#include "../read_functions/fgetword.cpp"
#include "asm_func.cpp"
#include "../headers/key_words_asm.h"

int find_key_word(char* word);
int correc_end_of_line(FILE* input);
long int size_of_file(FILE* file);


void asmm(FILE* input, ASM_BUFFER* my_buffer)
	{
		long int first_position = ftell(input);
		
		char word[MAXWORD];
		int c = 0;
		
		my_buffer->buffer_count = 0;
		
		while((c = fgetword_without_prob(word, MAXWORD, input)) != EOF)
			{
				if(type(c) == LETTER)
					{
						int number = 0;
						if((number = find_key_word(word)) == -1)
							{
								if(func_label(input, word, my_buffer) == 0)
								{
									printf("SYNTAX ERROR: %s - isn't word or label\n", word);
									break;
								}
							}
							
						//else if(func_word(input, number, my_buffer) == 0)
						else if(key_word[number].func(input, number, my_buffer) == 0)
							{
								printf("SYNTAX ERROR: %s - uncorrect operator argument\n", word);
								break;
							}
						
						/*if(correc_end_of_line(input) == 0)
							{
								printf("SYNTAX ERROR: %s uncorrect end operator", word);
								break;
							}	*/
					}
					
				/*else if(type(c) == DIGIT && word[1] == '\0')
					{
						if(func_label(input, word[0], my_buffer) == 0)
							{
								printf("SYNTAX ERROR: %s - uncorrect label", word);
								break;
							}
							
					}*/
					
				else
					{
						printf("SYNTAX ERROR: %c - uncorrect symbol", c);
						break;
					}
			}
			
			fseek(input, 0, first_position);
			
	}
	
	
int find_key_word(char* word)
	{
		int key_world_length = 0;
		
		while( strcmp(key_word[key_world_length++].word, "NULL"));
		
		for(int i = 0; i < key_world_length; i++)
			if(strcmp(key_word[i].word, word) == 0) 
				return i;
		
		return -1;
	}
	
/*int correc_end_of_line(FILE* input)
	{
		int c = 0;
		char word[MAXWORD];
		
		if(fgetword_without_prob(word, MAXWORD, input) != ';') return 0;
		
		return 1;
	}*/
	
long int size_of_file(FILE* file)
	{
		long int first_position = ftell(file);
	
		long int file_size = 0;
		
		fseek(file, 0, SEEK_END);
		
		file_size = ftell(file) - first_position;
		
		fseek(file, 0, first_position);
		
		return file_size;
	}


int main(int argc, char* argv[])
	{
		FILE* read = fopen(argv[1], "r");
	
		
		ASM_BUFFER* my_buffer = (ASM_BUFFER* )calloc(1, sizeof(ASM_BUFFER));
		
		my_buffer->buffer_int = (int* )calloc(size_of_file(read), sizeof(char));
		
		my_buffer->first_label = (struct label*)calloc(1, sizeof(struct label));
	
		asmm(read, my_buffer);
		asmm(read, my_buffer);
		
		FILE* output = fopen("out.asm", "w");
		
		fwrite(my_buffer->buffer_int, sizeof(char), my_buffer->buffer_count*sizeof(int), output);
	}