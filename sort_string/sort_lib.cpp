/**
 *	@file
 *	@brief File with comparators
 */
 
#include <string.h>
#include <ctype.h>

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *	@function strcmp_norm()
 *	Compares the lines lexicographically from the beginning
 *
 *	@param[in] *str1_t comparison struct string
 *	@param[in] *str2_t comparison struct string
 *
 *	@return comparison result
 */
inline int strcmp_norms(const void *str1_t, const void *str2_t)
	{
		//assert(str1_t != NULL);
		//assert(str2_t != NULL);
		//assert(str1_t != str2_t);

		struct line* str1_s = *(struct line**)str1_t;
		struct line* str2_s = *(struct line**)str2_t;
		
		register char *str1 = str1_s->line_p;
		register char *str2 = str2_s->line_p;
		
		do
			{
				for(; !isalpha(*str1) && *str1 != '\n'; str1++);
				for(; !isalpha(*str2) && *str2 != '\n'; str2++);
				
				if(*str1 == '\n' || *str2 == '\n') return *str1 - *str2;
				
			}
		while(*str1++ == *str2++);
		
		return *(str1-1) - *(str2-1);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------	
/**
 *	@function strcmp_reverse()
 *	Compares the lines lexicographically from the end
 *
 *	@param[in] *str1_t comparison struct string
 *	@param[in] *str2_t comparison struct string
 *
 *	@return comparison result
 */
inline int strcmp_reverse(const void *str1_t, const void *str2_t)
	{
		//assert(str1_t != NULL);
		//assert(str2_t != NULL);
		//assert(str1_t != str2_t);
		
		struct line* str1_s = *(struct line**)str1_t;
		struct line* str2_s = *(struct line**)str2_t;
		
		register char *str1 = str1_s->line_p + str1_s->line_len - 2;
		register char *str2 = str2_s->line_p + str2_s->line_len - 2;
		
		do
			{
				for(; !isalpha(*str1) && *str1 != '\n'; str1--);
				for(; !isalpha(*str2) && *str2 != '\n'; str2--);
				
				if(*str1 == '\n' || *str2 == '\n') return *str1 - *str2;
				
			}
		while(*str1-- == *str2--);
		
		return *(str1+1) - *(str2+1);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------