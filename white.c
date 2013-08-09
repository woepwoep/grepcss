/*
**	white.c
*/
#include "grepcss.h"

/* rtrim trailing whitespace */
char *rtrim(char *p_ptr) {
	char *ptr = p_ptr;
	int len = strlen(p_ptr);

	for (ptr = &p_ptr[len-1]; *ptr && white(*ptr); ptr--) {
		*ptr = '\0';
	}

	/* return the original pointer */
	ptr = p_ptr;
	return p_ptr;

}
/* ltrim starting whitespace */
char *ltrim(char *p_ptr) {
	char *ptr = p_ptr;

	/* find pointer beyond leading white space */
	for (ptr = p_ptr; *ptr && white(*ptr); ptr++);

	/* return this pointer */
	return ptr;
}
/* trim function */
char *trimWhite(char *p_ptr) {
	char *ptr = p_ptr;

	ptr = rtrim(ptr);
	ptr = ltrim(ptr);

	return ptr;
}

white(int p_char) {
	int retval = 0;
	switch(p_char) {
	default: 
		retval = 0;
		break;
	case '\n': 
	case '\r': 
	case '\t': 
	case ' ': 
		retval = 1;
		break;
	}
	return retval;
}
