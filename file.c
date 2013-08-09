/*
** file.c
*/
#include "grepcss.h"

processFile(char *p_filename, FILE *fp) {

	char this_c;
	char next_c;
	char last_c;

	int toestand = 0;
	while((this_c = fgetc(fp)) != EOF) {
		next_c = fgetc(fp);
		ungetc(next_c, fp);
		toestand = processChar(p_filename, toestand, last_c, this_c, next_c);
		last_c = this_c;
	}
}
