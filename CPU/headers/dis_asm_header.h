#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * buffer struct
  *
  */
typedef double buf_type;

struct buffer
	{
		char* data;
		int count = 0;
		int len = 0;
	};
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


#include "../asm/dis_asm_func.cpp"


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * command word structure
  *
  */
struct key_word_t
	{
		char* word;
		void (*func)(FILE* output, struct buffer* my_buffer);
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