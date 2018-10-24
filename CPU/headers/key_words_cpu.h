#ifndef KEY_WORDS_CPU
#define KEY_WORDS_CPU

struct key_word_t
	{
		char* word;
		cpu_elem (*func)(CPU_t* my_cpu);
	};
	
#define CMD(word) #word , cpu_##word,

#include "key_words.h"

#undef CMD(word)
	
#endif