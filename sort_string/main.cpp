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
		assert(file_input != -1);
		
		long int n_chars = 0;
		char* char_buffer = NULL;
		long int n_lines = 0;
		char** line_buffer = NULL;
		
		read_file_and_create_char_and_line_buffers(file_input, &line_buffer, &char_buffer, &n_lines, &n_chars);
		
		char** line_buffer_copy = copy_line_buffer(line_buffer, n_lines);
		
		printf("chars = %ld lines = %ld\n", n_chars, n_lines);
		
		FILE* out_nach = fopen("Output/out_nach.txt","w");
		FILE* out_kon = fopen("Output/out_kon.txt","w");
		FILE* out_norm = fopen("Output/out_norm.txt","w");
		
		qsort(line_buffer, n_lines, sizeof(char *), strcmp_norms);
		write_file(out_nach, n_lines, line_buffer);
		
		qsort(line_buffer, n_lines, sizeof(char *), strcmp_reverse);
		write_file(out_kon, n_lines, line_buffer);
		
		write_file(out_norm, n_lines, line_buffer_copy);
		
		fclose(out_nach);
		fclose(out_kon);
		fclose(out_norm);
		
		clock_t end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("end time = %lf \n", time_spent);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------