#ifndef KEY_WORDS_CPU
#define KEY_WORDS_CPU

struct key_word_cpu
	{
		char* word;
		cpu_elem (*func)(CPU_t* my_cpu);
	};

struct key_word_cpu key_word[] =
	{
		"push", cpu_push,
		"pop",  cpu_pop,
		"pushreg", cpu_pushreg,
		"popreg", cpu_popreg,
		"add",  cpu_add,
		"sub",  cpu_sub,
		"mul",  cpu_mul,
		"div",  cpu_div,
		"out",  cpu_out,
		"in",   cpu_in,
		"jmp",  cpu_jmp,
		"NULL", NULL
	};
	
#endif