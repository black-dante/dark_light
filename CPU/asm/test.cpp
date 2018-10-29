#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

typedef double buf_type;

long int size_of_file(FILE* file);
buf_type* read_asm_file_and_create_buffer(FILE* input, int* buffer_len);

int main(int argc, char* argv[])
	{
		FILE* input = fopen(argv[1], "r");
		
		int len = 0;
		
		buf_type* buffer = read_asm_file_and_create_buffer(input, &len);
		
		for(int i = 0; i < len; i++)
			printf("%lf\n", buffer[i]);
		
	}
	
buf_type* read_asm_file_and_create_buffer(FILE* input, int* buffer_len)
	{
		int file_len = size_of_file(input);
		
		buf_type* buffer =(buf_type *)calloc(file_len, sizeof(char));
		assert(buffer != NULL);
		
		int count = fread(buffer, sizeof(char), size_of_file(input), input);
		
		*buffer_len = count / sizeof(buf_type);
		
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