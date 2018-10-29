#include "../headers/dis_asm_header.h"


long int size_of_file(FILE* file);
buf_type* read_asm_file_and_create_buffer(FILE* input, int* buffer_len);


//{--------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
	{
		FILE* input = fopen(argv[1], "r");
		FILE* output = fopen("dis_out.txt", "w");
		
		int len = 0;
		
		struct buffer* my_buffer = (struct buffer*)calloc(1, sizeof(struct buffer));
		my_buffer->data = read_asm_file_and_create_buffer(input, &(my_buffer->len));
		
		while(my_buffer->count < my_buffer->len)
				key_word[(int)(my_buffer->data[my_buffer->count])].func(output, my_buffer);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------	
buf_type* read_asm_file_and_create_buffer(FILE* input, int* buffer_len)
	{
		assert(input != NULL);
		assert(buffer_len != NULL);
		
		int file_len = size_of_file(input);
		
		buf_type* buffer =(buf_type *)calloc(file_len, sizeof(char));
		assert(buffer != NULL);
		
		int count = fread(buffer, sizeof(char), file_len, input);
		
		*buffer_len = count / sizeof(buf_type);
		
		return buffer;
		
	}
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------	
long int size_of_file(FILE* file)
	{	
		assert(file != NULL);
		
		fseek(file, 0, SEEK_END);
		
		long int file_size = ftell(file);
		
		fseek(file, 0, SEEK_SET);
		
		return file_size;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------