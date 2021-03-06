#include <stdio.h>

#include "fgetch_fungetch.cpp"

const int LETTER = 'A';
const int DIGIT  = '0';

int type(int symbol);
int fgetword(char *w , int lim, FILE *fp);
void fungetword(char *word);
int fgetword_without_prob(char *w , int lim, FILE *fp);

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 * @function type()
 *
 * @param[in] symbol 
 *
 * return LETTER if symbol is LETTER
 *        DIGIT if symbol is DIGIT
 *        symbol if symbol isn't LETTER and DIGIT
 */
int type(int symbol)
{
	if (symbol >= 'A' && symbol <= 'Z' || symbol >= 'a' && symbol <= 'z' || symbol == '_')
		return (LETTER);
	else if (symbol >= '0' && symbol <= '9')
		return (DIGIT);
	else return(symbol);
}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 * @function fgetword()
 *
 * @param[in] word  pointer where characters will be written
 * @param[in] limit maximum number of characters in a word
 * @param[in] file read file
 * 
 * return LETTER if symbol is LETTER
 *        DIGIT if symbol is DIGIT
 *        symbol if symbol isn't LETTER and DIGIT
 */
int fgetword(char *word , int limit, FILE *file)
{
	int symbol, type_symb;
	if (type(symbol = *word++ = fgetch(file)) != LETTER && type(symbol) != DIGIT)
		{
			*word = '\0';
		
			return(symbol);//возврат символа
		}
		
	if(type(symbol) == LETTER)
	while (--limit > 0)
	{
		type_symb = type(symbol = *word++ = fgetch(file));
		
		if (type_symb != LETTER && type_symb != DIGIT)
			{
				fungetch(symbol);
			
				*(word - 1) = '\0';
			
				return(LETTER);//возврат слова
			}
	}
	
	if(type(symbol) == DIGIT || symbol == '-')
	{
	int tochka_count = 0;
		
	while (--limit > 0)
		{
			type_symb = type(symbol = *word++ = fgetch(file));
			
			if (type_symb != DIGIT)
				{
					if(type_symb == '.' && tochka_count == 0)
						{
							tochka_count++;
						}
					else
						{
							fungetch(symbol);
			
							*(word - 1) = '\0';
			
							return(DIGIT);//возврат числа
						}
				}
		}
	}
	
	return type(*word) == LETTER ? LETTER: DIGIT;
}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 * @function fungetword()
 *
 * @param[in] word to return to read stream
 *
 */
void fungetword(char *word)
	{
		int limit = 0;
		while(word[limit++] != '\0');
		
		limit-=2;
		
		do
			fungetch(word[limit]);
		while(limit-- != 0);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 * @function fgetword_without_prob()
 * function like fgetword, but without space yab and enter
 *
 * @param[in] word  pointer where characters will be written
 * @param[in] limit maximum number of characters in a word
 * @param[in] file read file
 * 
 * return LETTER if symbol is LETTER
 *        DIGIT if symbol is DIGIT
 *        symbol if symbol isn't LETTER and DIGIT
 */
int fgetword_without_prob(char *word , int limit, FILE *file)
	{
		int symbol = 0;
		
		while((symbol = fgetword(word, limit, file)) == ' ' || symbol == '\t' || symbol == '\n' || symbol == ';' || symbol == '\r')
			{
				if(symbol == ';')
					while((symbol = fgetword(word, limit, file)) != '\n' && symbol != EOF);
			}
		
		return symbol;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------
