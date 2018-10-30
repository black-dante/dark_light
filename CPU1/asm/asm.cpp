#include "../headers/asm_header.h"
#include <assert.h>

int find_key_word(char* word);
int correc_end_of_line(FILE* input);
long int size_of_file(FILE* file);
ASM_BUFFER* create_asm_buffer(FILE* read);
int line_number(FILE* input);
void print_line(FILE* input, int line_number);


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * @function asmm()
  * reads the file and writes the byte code to the buffer.
  * Called twice due to a label.
  *
  * @param[in] input file to read
  * @param[in] my_buffer pointer to buffer data structure
  */
void asmm(FILE* input, ASM_BUFFER* my_buffer)
	{
		assert(input != NULL);
		assert(my_buffer != NULL);
		
		long int first_position = ftell(input);
		
		char word[MAXWORD + 1];
		int symbol = 0;
		
		my_buffer->buffer_count = 0;
		
		while((symbol = fgetword_without_prob(word, MAXWORD, input)) != EOF)
			{
				if(type(symbol) == LETTER)
					{
						int number = 0;
						if((number = find_key_word(word)) == -1)
							{
								
								if(func_label(input, word, my_buffer) == false)
								{
									printf("\nSYNTAX ERROR: %s - isn't word or label\n", word);
									printf("\nLine number = %d\n", line_number(input));
									print_line(input, line_number(input));
									break;
								}
							}
							
						else if(key_word[number].func(input, number, my_buffer) == false)
							{
								printf("\nSYNTAX ERROR: %s - uncorrect operator argument\n", word);
								printf("\nLine number = %d\n", line_number(input));
								print_line(input, line_number(input));
								break;
							}
						
					}
					
				else
					{
						printf("\nSYNTAX ERROR: %c - uncorrect symbol\n", symbol);
						printf("\nLine number = %d\n", line_number(input));
						print_line(input, line_number(input));
						break;
					}
			}
			
			fseek(input, 0, first_position);
			
	}
//}--------------------------------------------------------------------------------------------------------------------------------------	


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * @function find_key_word()
  *
  * @param[in] word search word
  *
  * @return word number
  */	
int find_key_word(char* word)
	{
		assert(word != NULL);
		
		int key_world_length = 0;
		
		while( strcmp(key_word[key_world_length++].word, "NULL"));
		
		for(int i = 0; i < key_world_length; i++)
			if(strcmp(key_word[i].word, word) == 0) 
				return i;
		
		return -1;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------
	
//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * @function size_of_file()
  *
  * @param[in] file
  
  * @return file size
  */	
long int size_of_file(FILE* file)
	{	
		assert(file != NULL);
	
		fseek(file, 0, SEEK_END);
		
		long int file_size = ftell(file);
		
		fseek(file, 0, SEEK_SET);
		
		return file_size;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * @function create_asm_buffer()
  *
  * @param[in] file
  *
  * @return asm_buffer
  */
ASM_BUFFER* create_asm_buffer(FILE* read)
	{
		assert(read != NULL);
		
		ASM_BUFFER* my_buffer = (ASM_BUFFER* )calloc(1, sizeof(ASM_BUFFER));
		
		my_buffer->data = (char* )calloc(size_of_file(read)*sizeof(buf_type), sizeof(char));
		
		my_buffer->first_label = (struct label*)calloc(1, sizeof(struct label));
		
		return my_buffer;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * @function line_number()
  *
  * @param[in] file
  *
  * @return line_number
  */
int line_number(FILE* input)
	{
		assert(input != NULL);
		
		int max_count = ftell(input);
		
		fseek(input, 0, SEEK_SET);
		int n_counter = 0;
		int symbol = 0;
		
		for(int i = 0; i < max_count; i++)
			{
				symbol = fgetch(input);
				if(symbol == '\n')
					n_counter++;
			}
			
		fseek(input, 0, max_count);
			
		return n_counter;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * @function print_line()
  *
  * @param[in] file
  * @param[in] line_number
  */
void print_line(FILE* input, int line_number)
	{
		assert(input != NULL);
		
		printf("\n");
		
		int max_count = ftell(input);
		
		fseek(input, 0, SEEK_SET);
		int n_counter = 0;
		int symbol = 0;
		
		for(int i = 0; i < max_count; i++)
			{
				symbol = fgetch(input);
				
				if(symbol == '\n')
					n_counter++;
				
				if (n_counter == line_number)
					{
						fungetch(symbol);
						break;
					}
			}
		
		while((symbol = fgetch(input)) != '\n' && symbol != EOF)
			putchar(symbol);
		
		printf("\n");
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * @function main()
  *
  * @param[in] argc
  * @param[in] *argv[]
  */
int main(int argc, char* argv[])
	{
		FILE* read = fopen(argv[1], "rb");
	
		ASM_BUFFER* my_buffer = create_asm_buffer(read);
	
		asmm(read, my_buffer);
		asmm(read, my_buffer);
		
		FILE* output = fopen("out.asm", "wb");
		
		fwrite(my_buffer->data, sizeof(char), my_buffer->buffer_count, output);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------