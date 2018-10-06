/**
 *	@file
 *	@brief Main program
 *	Here begins the work of the program
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <assert.h>
#include <io.h>
#include <errno.h>
#include <time.h>

#include "r_wr_line_lib.cpp"
#include "sort_lib.cpp"

//{--------------------------------------------------------------------------------------------------------------------------------------	
/**
 *	@function main()
 *	Main Function
 *
 *	Enter the filename in the command-line options\n
 * 	If everything goes smoothly, the function will create the following files\n
 * 	1)file where all lines are sorted lexicographically from the beginning\n
 * 	1)file where all rows are sorted lexicographically from the end\n
 *	3)original file\n
 * 	In the event of an error, the assert
 */
int main(int argc, char* argv[])
	{
		assert(argv[1] != NULL);
		
		clock_t begin = clock();
		
		int file_input = open(argv[1], O_RDONLY | O_BINARY);
		assert(file_input >= 0);
		int file_output = open("Output/out.txt", O_WRONLY | O_CREAT);
		assert(file_output >= 0);
		
		long int n_chars = 0;
		char* char_buffer = NULL;
		long int n_lines = 0;
		struct line** line_buffer = NULL;

		read_file_and_create_char_and_line_buffers(file_input, &line_buffer, &char_buffer, &n_lines, &n_chars);
		
		printf("chars = %ld lines = %ld\n", n_chars, n_lines);
		
		qsort(line_buffer, n_lines, sizeof(struct line*), strcmp_norms);
		char* new_char_buffer = line_buffer_to_char_buffer(n_lines, line_buffer, n_chars);
		write(file_output, new_char_buffer, n_chars);
		
		qsort(line_buffer, n_lines, sizeof(struct line*), strcmp_reverse);
		new_char_buffer = line_buffer_to_char_buffer(n_lines, line_buffer, n_chars);
		write(file_output, new_char_buffer, n_chars);
		
		write(file_output, char_buffer + 1, n_chars);
		
		clock_t end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("end time = %lf \n", time_spent);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------