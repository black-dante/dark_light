#ifndef KEY_WORDS_ASM
#define KEY_WORDS_ASM

struct key_word_t
	{
		char* word;
		int (*func)(FILE* input, int number, ASM_BUFFER* my_buffer);
	};
	
#define CMD(word) #word , func_##word,

#include "key_words.h"

#undef CMD(word)
		
#endif