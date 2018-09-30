/**
 *	@file
 *	@brief file input and output library
 *	There are many useful functions here
 */

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *	@function size_of_file()
 *
 *	@param[in] *file_name file name
 *
 *	@return file size
 */
long int size_of_file(char* file_name)
	{
		long int file_size;
		
		FILE *input = NULL;
		input = fopen(file_name, "rb");
		
		assert(input != NULL);
		
		fseek(input, 0, SEEK_END);	
		file_size = ftell(input);
		
		assert(file_size >= 0);
		
		rewind(input);
		fclose(input);
		
		return file_size;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------	
/**
 *	@function read_file()
 *
 *	@param[in] *file_name file name
 *	@param[out] *file_size variable to write the file size
 *
 *	@return pointer to the buffer in which the file was read
 */	
char* read_file(char *file_name, long int *file_size)
	{
		long int f_size = size_of_file(file_name);
			
		FILE *input = NULL;
		input = fopen(file_name, "rb");
		
		assert(input != NULL);
			
		char* buffer = (char *)calloc(f_size+2, sizeof(char));
		
		assert(buffer != NULL);
		
		fread(buffer+1, sizeof(char), f_size, input);
		
		rewind(input);
		fclose(input);
		
		*file_size = f_size;
		return buffer;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------	
/**
 *	@function line_break()
 *	breaks the text buffer into strings and creates a string buffer
 *
 *	@param[in] *char_buffer pointer to the buffer with text
 *	@param[in] buffer_size buffer size
 *	@param[out] *num_lines variable for writing the number of rows
 *
 *	@return A pointer to the buffer in which the rows of the initial buffer are stored
 */		
char** line_break(char* char_buffer, long int buffer_size, long int* num_lines)
	{
		assert(char_buffer != NULL);
		
		if(char_buffer[buffer_size] != '\n') char_buffer[buffer_size+1] = '\n';
		
		long int n_lines = 0;
		
		for(long int i = 1; i < buffer_size + 2; i++)
				if(char_buffer[i] == '\n') n_lines++;
			
		char** line_buffer = (char **)calloc(n_lines, sizeof(char*));
		
		assert(line_buffer != NULL);
		
		long int line_pointer = 0;
		long int char_pointer = 1;
		for(long int i = 0; i < n_lines; i++)
			{
				line_buffer[line_pointer++] = &char_buffer[char_pointer];
				
				while(char_buffer[++char_pointer] != '\n');
				
				char_buffer[char_pointer++] = '\0';
			}
		
		*num_lines = n_lines;
		return line_buffer;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------	
/**
 *	@function write_file()
 *	writes text to a file
 *
 *	@param[in] **line_buffer String buffer for writing to file
 *	@param[in] n_lines Number of Rows
 *	@param[in] *file_name filename for the record
 */			
void write_file(long int n_lines, char** line_buffer, char* file_name)
	{
		assert(line_buffer != NULL);
		
		FILE *out = fopen(file_name, "w");
		
		for(int i = 0; i <n_lines; i++)
				fprintf(out, "%s\n", line_buffer[i]);
		
		fclose(out);
	}	
//}--------------------------------------------------------------------------------------------------------------------------------------	