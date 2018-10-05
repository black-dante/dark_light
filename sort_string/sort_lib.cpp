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
 *	@param[in] *str1_t comparison string
 *	@param[in] *str2_t comparison string
 *
 *	@return comparison result
 */
inline int strcmp_norms(const void *str1_t, const void *str2_t)
	{
		assert(str1_t != NULL);
		assert(str2_t != NULL);
		assert(str1_t != str2_t);
		
		register char *str1 = *(char**)str1_t;
		register char *str2 = *(char**)str2_t;
		
		do
			{
				for(; !isalpha(*str1) && *str1 != '\0'; str1++);
				for(; !isalpha(*str2) && *str2 != '\0'; str2++);
				
				if(*str1 == 0 || *str2 == 0) return *str1 - *str2;
				
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
 *	@param[in] *str1_t comparison string
 *	@param[in] *str2_t comparison string
 *
 *	@return comparison result
 */
inline int strcmp_reverse(const void *str1_t, const void *str2_t)
	{
		assert(str1_t != NULL);
		assert(str2_t != NULL);
		assert(str1_t != str2_t);
		
		register char *str1 = *(char**)str1_t;
		register char *str2 = *(char**)str2_t;
		
		str1 += strlen(str1)-1;
		str2 += strlen(str2)-1;
		
		do
			{
				for(; !isalpha(*str1) && *str1 != '\0'; str1--);
				for(; !isalpha(*str2) && *str2 != '\0'; str2--);
				
				if(*str1 == 0 || *str2 == 0) return *str1 - *str2;
				
			}
		while(*str1-- == *str2--);
		
		return *(str1+1) - *(str2+1);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------