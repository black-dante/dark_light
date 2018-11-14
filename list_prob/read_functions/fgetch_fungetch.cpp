#include <stdio.h>

#define BUFSIZE 100

static char buf[BUFSIZE];
static int bufp = 0;

int fgetch(FILE *fp);
void fungetch(int c);

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 * @function fgetch()
 *
 * @param[in] file read file like getch() function
 */
int fgetch(FILE *file)
	{
		return((bufp > 0) ? buf[--bufp] : getc(file));
	}
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 * @function fgetch()
 *
 * @param[in] symbol ungetch symbol to buffer
 */
void fungetch(int symbol)
	{
		if (bufp > BUFSIZE)
			printf("UNGETCH, TOO MANY CHARACTERS");
		else
			buf[bufp++] = symbol;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------