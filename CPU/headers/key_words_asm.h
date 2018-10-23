#ifndef KEY_WORDS_ASM
#define KEY_WORDS_ASM

struct key_word_t
	{
		char* word;
		int (*func)(FILE* input, int number, ASM_BUFFER* my_buffer);
	};

struct key_word_t key_word[] =
	{
		"push", func_push,
		"pop", func_pop,
		"pushreg", func_pushreg,
		"popreg", func_popreg,
		"add", func_add,
		"sub", func_sub,
		"mul", func_mul,
		"div", func_div,
		"out", func_out,
		"in",  func_in,
		"jmp", func_jmp,
		"NULL", NULL
	};
	
#endif