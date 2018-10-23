#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

long int size_of_file(FILE* file);
int* read_asm_file_and_create_buffer(FILE* input, int* buffer_len);

int main(int argc, char* argv[])
	{
		FILE* input = fopen(argv[1], "r");
		
		int len = 0;
		
		int* buffer = read_asm_file_and_create_buffer(input, &len);
		
		for(int i = 0; i < len; i++)
			printf("%d\n", buffer[i]);
		
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