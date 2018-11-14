#include "../headers/CPU_header.h"
#include <assert.h>


void CPU_create(CPU_t** my_cpu, FILE* _asm_);
void CPU_destroy(CPU_t** my_cpu);
char* read_asm_file_to_buffer(FILE* input, int* buffer_len);
long int size_of_file(FILE* file);
void cpu_start_command(CPU_t* my_cpu);


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * constructor and destructor for the buffer
  */
#define reg(reg_name) (*my_cpu)->reg_name = 0;
#define flag(flag_name) (*my_cpu)->flag_name = 0;
	
void CPU_create(CPU_t** my_cpu, FILE* _asm_)
	{
		assert(_asm_ != NULL);
		assert(my_cpu != NULL);
		
		*my_cpu = (CPU_t*)calloc(1, sizeof(CPU_t));
		assert(*my_cpu != NULL);
		
		#define REGISTERS_CPU
		#include "../headers/CPU_struct.h"
		#undef REGISTERS_CPU
		reg(sys_reg)
		
		#define FLAGS_CPU
		#include "../headers/CPU_struct.h"
		#undef FLAGS_CPU
		
		(*my_cpu)->command_buf = read_asm_file_to_buffer(_asm_, &(*my_cpu)->max_count);
		assert((*my_cpu)->command_buf != NULL);
		
		(*my_cpu)->RAM = (cpu_elem*)calloc(RAM_SIZE, sizeof(cpu_elem));
		assert((*my_cpu)->RAM != NULL);
		
		(*my_cpu)->counter = 0;
		
		(*my_cpu)->error_CPU = fopen("ERRORS/cpu_error.txt","w");
		(*my_cpu)->error_data = fopen("ERRORS/data_error.txt","w");
		
		stack_create(&((*my_cpu)->stack), "cpu_stack", (*my_cpu)->error_CPU, (*my_cpu)->error_data);
		stack_create(&((*my_cpu)->command_pointer), "cpu_command_pointer", (*my_cpu)->error_CPU, (*my_cpu)->error_data);
	}

	
void CPU_destroy(CPU_t** my_cpu)
	{
		assert(my_cpu != NULL);
		
		if(!(*my_cpu)) return;
		
		free((*my_cpu)->command_buf);
		(*my_cpu)->command_buf = NULL;
		
		free((*my_cpu)->RAM);
		(*my_cpu)->RAM = NULL;
		
		#define REGISTERS_CPU
		#include "../headers/CPU_struct.h"
		#undef REGISTERS_CPU
		reg(sys_reg)
		
		#define FLAGS_CPU
		#include "../headers/CPU_struct.h"
		#undef FLAGS_CPU
		
		(*my_cpu)->counter = 0;
		
		fclose((*my_cpu)->error_CPU);
	 	fclose((*my_cpu)->error_data);
		
		stack_destroy(&((*my_cpu)->stack));
		stack_destroy(&((*my_cpu)->command_pointer));
		
		*my_cpu = NULL;
	}

	
#undef flag(flag_name)	
#undef reg(reg_name)
//}--------------------------------------------------------------------------------------------------------------------------------------
	
	
//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * @function read_asm_file_to_buffer()
  *
  * @param[in] input file
  * @param[in] buffer_len pointer to variable storing buffer length
  *
  * @return buffer
  */	
char* read_asm_file_to_buffer(FILE* input, int* buffer_len)
	{
		assert(input != NULL);
		assert(buffer_len != NULL);
		
		int file_len = size_of_file(input);
		
		char* buffer =(char *)calloc(file_len, sizeof(char));
		assert(buffer != NULL);
		
		int count = fread(buffer, sizeof(char), size_of_file(input), input);
		
		*buffer_len = count;
		
		return buffer;
	}
//{--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * @function size_of_file()
  *
  * @param[in] file
  *
  * @return file size
  */
long int size_of_file(FILE* file)
	{
		assert(file != NULL);
		
		long int first_position = ftell(file);
	
		long int file_size = 0;
		
		fseek(file, 0, SEEK_END);
		
		file_size = ftell(file) - first_position;
		
		fseek(file, 0, first_position);
		
		return file_size;
	}
//{--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * @function cpu_start_command()
  *
  * @param[in] my_cpu
  */
void cpu_start_command(CPU_t* my_cpu)
	{
		while(my_cpu->counter < my_cpu->max_count)
			{
				key_word[(int)(my_cpu->command_buf[my_cpu->counter])].func(my_cpu);
			}
	}
//{--------------------------------------------------------------------------------------------------------------------------------------