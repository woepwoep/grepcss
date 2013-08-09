/*
**	name:	printcss
**	author:	Ronald Wopereis
**	date:	wo dec 14 09:10:44 CET 2011
**	goal:	to print (parts of) a css file
**
**	usage:	printcss [-s selector] [-p property] [-v value] filename.css [...css]
**		if [filename.css] is not provided, stdin is used
*/

#include <unistd.h>

#include "grepcss.h"

int debug = 0;

int main(int argc, char *argv[]) {
	int opt;
	SELECTOR_T *selectorstart;

	int beautify;
	int count;
	char selector[MAX_STRING_LEN];
	char property[MAX_STRING_LEN];
	char value[MAX_STRING_LEN];

	beautify = 0;
	count = 0;
	debug = 0;
	selector[0] = '\0';
	property[0] = '\0';
	value[0] = '\0';

	while ((opt = getopt(argc, argv, "bcdp:s:tv:")) != -1) {
		switch (opt) {
		case 'b':
			beautify=1;
			break;
		case 'c':
			count=1;
			break;
		case 'd':
			debug=1;
			break;
		case 'p':
			strcpy(property, optarg);
			break;
		case 's':
			strcpy(selector, optarg);
			break;
		case 't':
			fprintf(stderr,"Translate functie\n");
			break;
		case 'v':
			strcpy(value, optarg);
			break;
		default:
			usage(argv[0]);
			break;
		}
	}

	if (beautify && (*selector || *property || *value)) {
		usage(argv[0]);
	}

	if (optind == argc) {
		processFile("stdin", stdin);
	} else while (optind < argc) {
		FILE *fp;
		char *filename = argv[optind];
		fp = fopen(filename,"r");;
		if (fp == NULL) {
			perror(filename);
		} else {
			processFile(filename, fp);
			fclose(fp);
		}
		optind++;
	}
	selectorstart = startSelector();
	if (beautify) {
		printNice(selectorstart,count);
	} else {
		printSome(selectorstart,count,selector,property,value);
	}
	exit(0);
}

usage(char *p_program) {
	fprintf(stderr, "Usage: %s [-c] [-s selector] [-p property] [-v value] cssfile(s)\n", p_program);
	fprintf(stderr, "   or: %s [-b] [-c] cssfile(s)\n", p_program);
	exit(EXIT_FAILURE);
}
