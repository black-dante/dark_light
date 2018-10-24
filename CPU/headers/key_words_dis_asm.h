#ifndef KEY_WORDS_DIS_ASM
#define KEY_WORDS_DIS_ASM

struct key_word_t
	{
		char* word;
		void (*func)(FILE* output, struct buffer* my_buffer);
	};
	
#define CMD(word) #word , func_##word,

#include "key_words.h"

#undef CMD(word)

#endif