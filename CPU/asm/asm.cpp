#include "../headers/asm_header.h"

int find_key_word(char* word);
int correc_end_of_line(FILE* input);
long int size_of_file(FILE* file);
ASM_BUFFER* create_asm_buffer(FILE* read);
int line_number(FILE* input);


//{--------------------------------------------------------------------------------------------------------------------------------------
void asmm(FILE* input, ASM_BUFFER* my_buffer)
	{
		long int first_position = ftell(input);
		
		char word[MAXWORD];
		int symbol = 0;
		
		my_buffer->buffer_count = 0;
		
		while((symbol = fgetword_without_prob(word, MAXWORD, input)) != EOF)
			{
				if(type(symbol) == LETTER)
					{
						int number = 0;
						if((number = find_key_word(word)) == -1)
							{
								if(func_label(input, word, my_buffer) == 0)
								{
									printf("SYNTAX ERROR: %s - isn't word or label\n", word);
									printf("\nLine number = %d\n", line_number(input));
									break;
								}
							}
							
						else if(key_word[number].func(input, number, my_buffer) == 0)
							{
								printf("\nSYNTAX ERROR: %s - uncorrect operator argument\n", word);
								printf("\nLine number = %d\n", line_number(input));
								break;
							}
						
					}
					
				else
					{
						printf("\nSYNTAX ERROR: %c - uncorrect symbol\n", symbol);
						printf("\nLine number = %d\n", line_number(input));
						break;
					}
			}
			
			fseek(input, 0, first_position);
			
	}
//}--------------------------------------------------------------------------------------------------------------------------------------	


//{--------------------------------------------------------------------------------------------------------------------------------------	
int find_key_word(char* word)
	{
		int key_world_length = 0;
		
		while( strcmp(key_word[key_world_length++].word, "NULL"));
		
		for(int i = 0; i < key_world_length; i++)
			if(strcmp(key_word[i].word, word) == 0) 
				return i;
		
		return -1;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------
	
//{--------------------------------------------------------------------------------------------------------------------------------------
long int size_of_file(FILE* file)
	{	
		fseek(file, 0, SEEK_END);
		
		long int file_size = ftell(file);
		
		fseek(file, 0, SEEK_SET);
		
		return file_size;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
ASM_BUFFER* create_asm_buffer(FILE* read)
	{
		ASM_BUFFER* my_buffer = (ASM_BUFFER* )calloc(1, sizeof(ASM_BUFFER));
		
		my_buffer->data = (buf_type* )calloc(size_of_file(read)*sizeof(buf_type), sizeof(char));
		
		my_buffer->first_label = (struct label*)calloc(1, sizeof(struct label));
		
		return my_buffer;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
int line_number(FILE* input)
	{
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
			
		return n_counter;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
	{
		FILE* read = fopen(argv[1], "r");
	
		ASM_BUFFER* my_buffer = create_asm_buffer(read);
	
		asmm(read, my_buffer);
		asmm(read, my_buffer);
		
		FILE* output = fopen("out.asm", "w");
		
		fwrite(my_buffer->data, sizeof(char), my_buffer->buffer_count*sizeof(buf_type), output);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------