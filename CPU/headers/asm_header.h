#include <string.h>
#include <stdlib.h>

#include "../read_functions/fgetword.cpp"

const int MAXWORD = 300;


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * label struct
  *
  */
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
		char* data;
		int buffer_count;
		struct label* first_label = (struct label*)calloc(1, sizeof(struct label));
		
	} ASM_BUFFER;
//}--------------------------------------------------------------------------------------------------------------------------------------
	
	
//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * command enum
  *
  */
enum write_command
	{
		default_write = 0,
		write_to_ram = 1
	};
//}--------------------------------------------------------------------------------------------------------------------------------------

	
//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * registers enum
  *
  */	
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
/**
  * command number
  *
  */	
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
/**
  * command word structure
  *
  */	
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
