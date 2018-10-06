#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <io.h>

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 * single line structure
 *
 */
struct line
	{
		char* line_p;
		long int line_len;
	};
//}--------------------------------------------------------------------------------------------------------------------------------------

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
		assert(file_dis > 0);
		
		long int file_size = 0;
		
		lseek(file_dis, 0, SEEK_END);
		
		assert(errno != EBADF);
		assert(errno != EINVAL);
		errno = 0;
		
		file_size = tell(file_dis);
		
		assert(errno != EBADF);
		errno = 0;
		
		lseek(file_dis, 0, SEEK_SET);
		
		assert(errno != EBADF);
		assert(errno != EINVAL);
		errno = 0;
		
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
		assert(file_dis > 0);
		
		*file_size = size_of_file(file_dis);
			
		char* buffer = (char *)calloc(*file_size+2, sizeof(char));
		
		assert(buffer != NULL);
		
		read(file_dis, buffer+1, *file_size);
		
		assert(errno != EACCES);
		assert(errno != EBADF);
		errno = 0;
		
		lseek(file_dis, 0, SEEK_SET);
		
		assert(errno != EBADF);
		assert(errno != EINVAL);
		errno = 0;
		
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
 *	@return pointer to an array of pointers to line structures
 */		
struct line** char_buffer_to_line_buffer(char* char_buffer, long int buffer_size, long int* num_lines)
	{
		assert(buffer_size >= 0);
		assert(num_lines != NULL);
		assert(char_buffer != NULL);
		
		if(char_buffer[buffer_size] != '\n') char_buffer[buffer_size+1] = '\n';
		char_buffer[0] = '\n';
		
		long int n_lines = 0;
	
		for(char* pointer = char_buffer + 1; (pointer = strchr(pointer, '\n' )) != NULL; pointer++)
				n_lines++;
		
		
		struct line** line_buffer = (struct line**)calloc(n_lines, sizeof(struct line*));
		for(long int i = 0; i < n_lines; i++)
			line_buffer[i] = (struct line*)calloc(1, sizeof(struct line));
		
		assert(line_buffer != NULL);
		
		long int line_pointer = 0;
		
		for(char* pointer = char_buffer + 1; line_pointer < n_lines; pointer++)
			{
				line_buffer[line_pointer]->line_p = pointer;
				line_buffer[line_pointer]->line_len = (pointer = strchr(pointer, '\n')) - line_buffer[line_pointer++]->line_p + 1;
			}
		
		*num_lines = n_lines;
		return line_buffer;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------	
/**
 *	@function read_file_and_create_char_and_line_buffers()
 *	read the name of the function
 *
 *	@param[in]  file_dis file descriptor
 *	@param[out] ***line_buffer pointer to pointer to an array of pointers to line structures
 *	@param[out] n_lines number of lines
 *	@param[out] **char_buffer pointer to the character buffer
 *	@param[out] n_chars number of characters
 */			
void read_file_and_create_char_and_line_buffers(int  file_dis, struct line*** line_buffer, char** char_buffer, long int* n_lines, long int* n_chars)
	{
		assert(file_dis > 0);
		
		*char_buffer = read_file(file_dis, n_chars);
		
		*line_buffer = char_buffer_to_line_buffer(*char_buffer, *n_chars, n_lines);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------
	
//{--------------------------------------------------------------------------------------------------------------------------------------	
/**
 *	@function read_file_and_create_char_and_line_buffers()
 *
 *  @param[in] n_lines number of lines
 *  @param[in] **line_buffer pointer to an array of pointers to line structures
 *  @param[in] n_chars number of characters
 *
 *  @return copied line buffer
 */
char* line_buffer_to_char_buffer(long int n_lines, struct line** line_buffer, long int n_chars)
	{
		assert(n_lines >= 0);
		assert(line_buffer != NULL);
		assert(n_chars >= 0);
		
		char* char_buffer = (char *)calloc(n_chars, sizeof(char));
		assert(char_buffer != NULL);
		
		long int char_count = 0;
		for(long int i = 0; i < n_lines; i++)
			for(long int j = 0; j < line_buffer[i]->line_len; j++)
				char_buffer[char_count++] = line_buffer[i]->line_p[j];
			
		return char_buffer;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------
