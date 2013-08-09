/*
**	grepcss.h
*/
#include <stdio.h>	/* stdout */
#include <stdlib.h>	/* malloc */
#include <string.h>	/* strlen */

#define MAX_STRING_LEN 4096

typedef struct value_t {
	char *name;
	int aantal;
	struct value_t *next;
} VALUE_T;

typedef struct property_t {
	char *name;
	int aantal;
	VALUE_T *values;
	struct property_t *next;
} PROPERTY_T;

typedef struct selector_t {
	char *name;
	int aantal;
	PROPERTY_T *properties;
	struct selector_t *next;
} SELECTOR_T;

typedef struct cssfile_t {
	char *name;
	int aantal;
	SELECTOR_T *selectors;
	struct cssfile_t *next;
} CSSFILE_T;

extern SELECTOR_T *addSelector(char *), *startSelector();
extern PROPERTY_T *addProperty(SELECTOR_T *, char *);
extern void addValue(PROPERTY_T *, char *);

extern char *trimWhite(char *);

extern int printSome(SELECTOR_T *,int,char *,char *,char *);
extern int printNice(SELECTOR_T *,int);

extern int debug;
