#include "stack.cpp"

const int RAM_SIZE = 1024;

typedef int cpu_elem;

typedef struct CPU 
	{
		STACK* stack;
		
		cpu_elem rax;
		cpu_elem rbx;
		cpu_elem rcx;
		cpu_elem rdx;
		
		cpu_elem* command_buf;
		
		cpu_elem* RAM;
		
		int counter;
		int max_ram;
		
		FILE* error_CPU;
		FILE* error_data;
	} CPU_t;
	
#include "CPU_func.cpp"
#include "../headers/key_words_cpu.h"	

	
void CPU_create(CPU_t** my_cpu, FILE* _asm_);
void CPU_destroy(CPU_t** my_cpu);
cpu_elem* read_asm_file_to_buffer(FILE* input, int* buffer_len);
long int size_of_file(FILE* file);
void cpu_start_command(CPU_t* my_cpu);

	
void CPU_create(CPU_t** my_cpu, FILE* _asm_)
	{
		assert(my_cpu != NULL);
		
		*my_cpu = (CPU_t*)calloc(1, sizeof(CPU_t));
		assert(*my_cpu != NULL);
		
		(*my_cpu)->rax = 0;
		(*my_cpu)->rbx = 0;
		(*my_cpu)->rcx = 0;
		(*my_cpu)->rdx = 0;
		
		(*my_cpu)->command_buf = read_asm_file_to_buffer(_asm_, &(*my_cpu)->max_ram);
		assert((*my_cpu)->command_buf != NULL);
		
		(*my_cpu)->RAM = (cpu_elem*)calloc(RAM_SIZE, sizeof(cpu_elem));
		assert((*my_cpu)->RAM != NULL);
		
		(*my_cpu)->counter = 0;
		
		(*my_cpu)->error_CPU = fopen("ERRORS/cpu_error.txt","w");
		(*my_cpu)->error_data = fopen("ERRORS/data_error.txt","w");
		
		stack_create(&((*my_cpu)->stack), "cpu_stack", (*my_cpu)->error_CPU, (*my_cpu)->error_data);
	}
	
void CPU_destroy(CPU_t** my_cpu)
	{
		assert(my_cpu != NULL);
		
		if(!(*my_cpu)) return;
		
		free((*my_cpu)->command_buf);
		(*my_cpu)->command_buf = NULL;
		
		free((*my_cpu)->RAM);
		(*my_cpu)->RAM = NULL;
		
		(*my_cpu)->rax = 0;
		(*my_cpu)->rbx = 0;
		(*my_cpu)->rcx = 0;
		(*my_cpu)->rdx = 0;
		
		(*my_cpu)->counter = 0;
		
		fclose((*my_cpu)->error_CPU);
	 	fclose((*my_cpu)->error_data);
		
		stack_destroy(&((*my_cpu)->stack));
		
		*my_cpu = NULL;
	}
	
cpu_elem* read_asm_file_to_buffer(FILE* input, int* buffer_len)
	{
		int file_len = size_of_file(input);
		
		cpu_elem* buffer =(cpu_elem *)calloc(file_len, sizeof(char));
		assert(buffer != NULL);
		
		int count = fread(buffer, sizeof(char), size_of_file(input), input);
		
		*buffer_len = count / sizeof(cpu_elem);
		
		return buffer;
	}

long int size_of_file(FILE* file)
	{
		long int first_position = ftell(file);
	
		long int file_size = 0;
		
		fseek(file, 0, SEEK_END);
		
		file_size = ftell(file) - first_position;
		
		fseek(file, 0, first_position);
		
		return file_size;
	}
	
void cpu_start_command(CPU_t* my_cpu)
	{
		printf("Ok\n");
		while(my_cpu->counter < my_cpu->max_ram)
			{
				key_word[my_cpu->command_buf[my_cpu->counter]].func(my_cpu);
			}
	}