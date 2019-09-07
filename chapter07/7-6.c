/*
 * Exercise 7-6. Write a program to compare two file, printing the first line
 * where they differ.
 *
 * By Faisal Saadatmand
 */

#define MAXFILES  3
#define MAXLEN    1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *file[MAXFILES];                  /* array to store files */
	char *prog = argv[0];                  /* program name for errors */
	char *f1name = argv[1];                /* file 1 name for printing line */
	char *f2name = argv[2];                /* file 2 name for printing line */
	char f1line[MAXLEN], f2line[MAXLEN];   /* currently read line */
	int  f1ln, f2ln;                       /* currently read line number */
	int i;
	
	/* check cli argument */
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <file1> <file2>\n", prog);
		exit(EXIT_FAILURE);
	}

	/* open files */
	for (i = 1; --argc > 0; ++i)           /* skip file[0] for readability */
		if (!(file[i] = fopen(*++argv, "r"))) {
			fprintf(stderr, "%s: can't open %s\n", prog, *argv);
			exit(EXIT_FAILURE);
		}

	f1ln = f2ln = 0;
	while (!feof(file[1]) && !feof(file[2])) { 
		if (fgets(f1line, MAXLEN, file[1]))
			f1ln++;                        /* count successfully read lines */
		if (fgets(f2line, MAXLEN, file[2]))
			f2ln++;                        /* count successfully read lines */
		if (f1ln > f2ln)                   /* file 1 is longer */
			fprintf(stdout, "\n%s: %i: %s", f1name, f1ln, f1line);
		else if (f1ln < f2ln)              /* file 2 is longer */
			fprintf(stdout, "\n%s: %i: %s", f2name, f2ln, f2line);
		else if (strcmp(f1line, f2line)) {
			fprintf(stdout, "\n%s: %i: %s", f1name, f1ln, f1line);
			fprintf(stdout, "\n%s: %i: %s", f2name, f2ln, f2line);
		}
	}

	fclose(file[1]);
	fclose(file[2]);

	exit(EXIT_SUCCESS);
}
