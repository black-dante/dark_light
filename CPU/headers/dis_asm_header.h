#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

//{--------------------------------------------------------------------------------------------------------------------------------------
typedef double buf_type;

struct buffer
	{
		buf_type* data;
		int count = 0;
		int len = 0;
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


#include "../asm/dis_asm_func.cpp"


//{--------------------------------------------------------------------------------------------------------------------------------------
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