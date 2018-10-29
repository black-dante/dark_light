#include "../CPU/stack.cpp"

//{--------------------------------------------------------------------------------------------------------------------------------------
const int RAM_SIZE = 1024;

typedef double cpu_elem;

#define reg(reg_name) cpu_elem reg_name;
#define flag(flag_name) int flag_name;

typedef struct CPU 
	{
		STACK* stack;
		
		STACK* command_pointer;
		
		reg(sys_reg)
		
		#define REGISTERS_CPU
		#include "../headers/CPU_struct.h"
		#undef REGISTERS_CPU
		
		#define FLAGS_CPU
		#include "../headers/CPU_struct.h"
		#undef FLAGS_CPU
		
		cpu_elem* command_buf;
		
		cpu_elem* RAM;
		
		int counter;
		int max_count;
		
		FILE* error_CPU;
		FILE* error_data;
	} CPU_t;

#undef flag(flag_name)
#undef reg(reg_name)
//}--------------------------------------------------------------------------------------------------------------------------------------
	
	
//{--------------------------------------------------------------------------------------------------------------------------------------
enum write_command
	{
		default_write = 0,
		write_to_ram = 1
	};
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------	
#define reg(register_name) register_name,

enum _registers
	{
		sys_reg = 2,
		#define REGISTERS_CPU
		#include "../headers/CPU_struct.h"
		#undef REGISTERS_CPU
		sys_reg0
	};
	
#undef reg(register_name)
//}--------------------------------------------------------------------------------------------------------------------------------------
	
	
#include "../CPU/CPU_func.cpp"


//{--------------------------------------------------------------------------------------------------------------------------------------	
struct key_word_t
	{
		char* word;
		cpu_elem (*func)(CPU_t* my_cpu);
	};
	
#define CMD(word) #word , cpu_##word,

struct key_word_t key_word[] =
	{
		#define COMMANDS_CPU
		#include "../headers/CPU_struct.h"
		#undef COMMANDS_CPU
		"NULL", NULL
	};
	
#undef CMD(word)
//}--------------------------------------------------------------------------------------------------------------------------------------