/**
 *	@file
 *	@brief file input and output library
 *	There are many useful functions here
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <io.h>

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *	@function size_of_file()
 *
 *	@param[in] file_dis file descriptor
 *
 *	@return file size
 */
long int size_of_file(int  file_dis)
	{
		assert(file_dis > 2);
		
		long int file_size = 0;
		
		lseek(file_dis, 0, SEEK_END);
		
		assert(errno != EBADF);
		assert(errno != EINVAL);
		
		file_size = tell(file_dis);
		
		assert(errno != EBADF);
		
		lseek(file_dis, 0, SEEK_SET);
		
		assert(errno != EBADF);
		assert(errno != EINVAL);
		
		assert(file_size >= 0);
		
		return file_size;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------	

//{--------------------------------------------------------------------------------------------------------------------------------------	
/**
 *	@function read_file()
 *
 *	@param[in] file_dis file descriptor
 *	@param[out] *file_size variable to write the file size
 *
 *	@return pointer to the buffer in which the file was read
 */	
char* read_file(int  file_dis, long int *file_size)
	{
		assert(file_dis > 2);
		
		*file_size = size_of_file(file_dis);
			
		char* buffer = (char *)calloc(*file_size+2, sizeof(char));
		
		assert(buffer != NULL);
		
		read(file_dis, buffer+1, *file_size);
		
		assert(errno != EACCES);
		assert(errno != EBADF);
		
		lseek(file_dis, 0, SEEK_SET);
		
		assert(errno != EBADF);
		assert(errno != EINVAL);
		
		return buffer;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------	
/**
 *	@function char_buffer_to_line_buffer()
 *	breaks the text buffer into strings and creates a string buffer
 *
 *	@param[in] *char_buffer pointer to the buffer with text
 *	@param[in] buffer_size buffer size
 *	@param[out] *num_lines variable for writing the number of rows
 *
 *	@return A pointer to the buffer in which the rows of the initial buffer are stored
 */		
char** char_buffer_to_line_buffer(char* char_buffer, long int buffer_size, long int* num_lines)
	{
		assert(buffer_size >= 0);
		assert(num_lines != NULL);
		assert(char_buffer != NULL);
		
		if(char_buffer[buffer_size] != '\n') char_buffer[buffer_size+1] = '\n';
		
		long int n_lines = 0;
	
		for(char* pointer = char_buffer + 1; (pointer = strchr(pointer, '\n' )) != NULL; pointer++)
				n_lines++;
		
		
		char** line_buffer = (char **)calloc(n_lines, sizeof(char*));
		
		assert(line_buffer != NULL);
		
		long int line_pointer = 0;
		
		
		for(char* pointer = char_buffer+1; line_pointer < n_lines;)
			{
				line_buffer[line_pointer++] = pointer;
				pointer = strchr(pointer, '\n' );
				*pointer = '\0';
				pointer++;
			}
		
		*num_lines = n_lines;
		return line_buffer;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *	@function copy_line_buffer()
 *
 *	@param[in] line_buffer pointer is being copied buffer
 *	@param[in] n_lines number of lines in the buffer
 *
 *	@return pointer to copied buffer
 */	
char**	copy_line_buffer(char** line_buffer, long int n_lines)
	{
		assert(line_buffer != NULL);
		assert(n_lines >= 0);
		
		char** line_buffer_copy = (char **)calloc(n_lines, sizeof(char*));
		
		assert(line_buffer_copy != NULL);
		
		for(int i = 0; i < n_lines; i++)
			line_buffer_copy[i] = line_buffer[i];
	
		return line_buffer_copy;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------	
/**
 *	@function write_file()
 *	writes text to a file
 *
 *	@param[in] **line_buffer String buffer for writing to file
 *	@param[in] n_lines number of lines
 *	@param[in] *output file structure for output
 */			
void write_file(FILE* output, long int n_lines, char** line_buffer)
	{
		assert(line_buffer != NULL);
		assert(output != NULL);
		assert(n_lines >= 0);
	
		for(int i = 0; i <n_lines; i++)
				fprintf(output, "%s\n", line_buffer[i]);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------	
/**
 *	@function read_file_and_create_char_and_line_buffers()
 *	read the name of the function
 *
 *	@param[in]  file_dis file descriptor
 *	@param[out] ***line_buffer pointer of buffer for strings
 *	@param[out] n_lines number of lines
 *	@param[out] **char_buffer pointer to the character buffer
 *	@param[out] n_chars number of characters
 */			
void read_file_and_create_char_and_line_buffers(int  file_dis, char*** line_buffer, char** char_buffer, long int* n_lines, long int* n_chars)
	{
		assert(file_dis > 2);
		
		*char_buffer = read_file(file_dis, n_chars);
		
		*line_buffer = char_buffer_to_line_buffer(*char_buffer, *n_chars, n_lines);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

	