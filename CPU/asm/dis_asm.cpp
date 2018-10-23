#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

struct buffer
	{
		int* data;
		int count = 0;
		int len = 0;
	};

#include "dis_asm_func.cpp"
#include "../headers/key_words_dis_asm.h"

long int size_of_file(FILE* file);
int* read_asm_file_and_create_buffer(FILE* input, int* buffer_len);

int main(int argc, char* argv[])
	{
		FILE* input = fopen(argv[1], "r");
		FILE* output = fopen("dis_out.txt", "w");
		
		int len = 0;
		
		struct buffer* my_buffer = (struct buffer*)calloc(1, sizeof(struct buffer));
		my_buffer->data = read_asm_file_and_create_buffer(input, &(my_buffer->len));
		
		while(my_buffer->count < my_buffer->len)
				key_word[my_buffer->data[my_buffer->count]].func(output, my_buffer);
	}
	
int* read_asm_file_and_create_buffer(FILE* input, int* buffer_len)
	{
		int file_len = size_of_file(input);
		
		int* buffer =(int *)calloc(file_len, sizeof(char));
		assert(buffer != NULL);
		
		int count = fread(buffer, sizeof(char), size_of_file(input), input);
		
		*buffer_len = count / sizeof(int);
		
		return buffer;
		
	}
	
long int size_of_file(FILE* file)
	{
		long int first_position = ftell(file);
	
		long int file_size = 0;
		
		fseek(file, 0, SEEK_END);
		
		file_size = ftell(file) - first_position;
		
		fseek(file, 0, first_position);
		
		return file_size;
	}