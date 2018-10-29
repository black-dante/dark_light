#include <string.h>
#include <stdlib.h>

#include "../read_functions/fgetword.cpp"

const int MAXWORD = 100;


//{--------------------------------------------------------------------------------------------------------------------------------------
struct label
	{
		char* name = NULL;
		int position = -1;
		
		struct label* right_label = NULL;
		struct label* left_label = NULL;
	};

typedef double buf_type;	
	
typedef struct ASM_buffer
	{
		buf_type* data;
		int buffer_count;
		struct label* first_label = (struct label*)calloc(1, sizeof(struct label));
		
	} ASM_BUFFER;
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



//{--------------------------------------------------------------------------------------------------------------------------------------	
#define CMD(word) word##_number,

enum command_number
	{
		#define COMMANDS_CPU
		#include "../headers/CPU_struct.h"
		#undef COMMANDS_CPU
		
		null_number
	};
	
#undef CMD(word) 
//}--------------------------------------------------------------------------------------------------------------------------------------

#include "../asm/asm_func.cpp"

	
//{--------------------------------------------------------------------------------------------------------------------------------------	
struct key_word_t
	{
		char* word;
		int (*func)(FILE* input, int number, ASM_BUFFER* my_buffer);
	};
	
#define CMD(word) #word , func_##word,

struct key_word_t key_word[] =
	{
		#define COMMANDS_CPU
		#include "../headers/CPU_struct.h"
		#undef COMMANDS_CPU
		"NULL", NULL
	};
	
#undef CMD(word)
//}--------------------------------------------------------------------------------------------------------------------------------------
