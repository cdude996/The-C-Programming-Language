/* 
 * Exercise 5-11. Modify the program and detab (written in exercises in Chapter
 * 1) to accept a list of tab stops as arguments. Use the default tab setting
 * if there are no arguments.
 * By Faisal Saadatmad
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 1000
#define MAXARG  1000                  /* max number of tabstop arguments */
#define N       4                   /* default tabstop for every n columns */

/* functions declarations */
int getLine(char *s, int lim);
void detabList(char *line, char *modLine, int *list, int listSzie);

/* getLine: get line into s, return length of s -- pointer version */
int getLine(char *s, int lim)
{
	int c, len;

	len = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
		*s++ = c;
		++len;
	}
	if ( c == '\n') {
		*s++ = c;
		++len;
	}
	*s = '\0';
	return len;
}

/* detabList function: replaces tabs with the proper number of blanks; reads from
 * line, writes to modLine. Uses default tabstop (every N column) if no list.
 * is supplied */
void detabList(char *line, char *modLine, int *list, int listSzie)
{
	int toNextTabStop;              /* number of spaces to the next tabstop */
	int column;                     /* current column number/location */

	column = 0;
	while (*line) {
		if (*line == '\t') {
			if (listSzie > 0) {
				while (column >= *list && listSzie > 0) {
					++list;
					--listSzie;
				}
				toNextTabStop = *list - column;
			} else
				toNextTabStop = N - (column % N); /* default tabstop setting */
			while (toNextTabStop-- > 0) {
				*modLine++ = ' ';
				++column;
			}
		} else {
			*modLine++ = *line;
			++column;
		}
		++line;
	}
	*modLine = '\0';
}

/* isDigitStr: check if string is made of positive integers characters. Return
 * 1 if true; 0 if false */
int isDigitStr(char *s[])
{
	int i;

		for (i = 0; (*s)[i]; ++i)   /* ommitted '\0', since s is a pointer */
			if (!isdigit((*s)[i]))
				return 0;
	return 1;
}

int main(int argc, char *argv[])
{
	char line[MAXLINE];             /* currently read line */
	char modLine[MAXLINE];          /* modified line */
	static int tabStopList[MAXARG]; /* list of tab stops (column numbers) */
	int argNum = 0;                 /* number of command-line arguments */ 
	int c;                          /* current read character */
	int list;                       /* flag variable to signal "-l" option */
	int *pTablist;                  /* pointer to tabStopList */

	argNum = argc - 1;              /* record number of cli arguments;
									   exclude program name (*argv)  */
	while (--argc > 0 && (*++argv)[0] == '-') {   /* parse options */
		while ((c = *++argv[0]))    /* cycle through columns */
			switch (c) {
			case 'l':
				list = 1;
				break;
			default:
				printf("detab: illegal option %c\n", c);
				argc = -1;
				break;
			}
	}

	if (list) {
		pTablist = tabStopList;
		--argNum;                               /* exclude "-l" */
		while (argc > 0) 
			if (isDigitStr(argv)) {             /* error check */
				*pTablist++ = atoi(*argv++);    /* store tabstops list */
				--argc;
			} else {
				printf("error: invalid tab Stop %s\n", *argv);
				argc = -1;
			}
	}

	if (argc < 0)
		return -1;

	while (getLine(line, MAXLINE) > 0) {
		detabList(line, modLine, tabStopList, argNum);
		printf("%s", modLine);
	}
	return 0;
}