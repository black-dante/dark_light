/**
 *	@file
 *	@brief Main program
 *	Here begins the work of the program
 */

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "sort_lib.cpp"
#include "r_wr_file_lib.cpp"

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
		
		long int file_size = 0;
		
		char* char_buffer = read_file(argv[1], &file_size);
		assert(char_buffer != NULL);
		
		long int n_lines = 0;
		
		char** line_buffer = line_break(char_buffer, file_size, &n_lines);
		assert(line_buffer != NULL);
		
		char** line_buffer_copy = (char **)calloc(n_lines, sizeof(char*));
		assert(line_buffer_copy != NULL);
		for(int i = 0; i < n_lines; i++)
			line_buffer_copy[i] = line_buffer[i];
		
		qsort(line_buffer, n_lines, sizeof(char *), strcmp_norms);
		write_file(n_lines, line_buffer, "Output/out_nach.txt");
		
		qsort(line_buffer, n_lines, sizeof(char *), strcmp_reverse);
		write_file(n_lines, line_buffer, "Output/out_kon.txt");
		
		write_file(n_lines, line_buffer, "Output/out_norm.txt");
		
		clock_t end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("end time = %lf \n", time_spent);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------