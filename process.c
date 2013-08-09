/*
**	process.c
*/
#include "grepcss.h"

static SELECTOR_T *selectorList[100];
static char currentPropertyName[MAX_STRING_LEN];

static int nSelectors = 0;

int add2SelectorList(char *p_token) {
	if (nSelectors > 99) {
		fprintf(stderr,"Max limit reached 100 for selectorList\n");
		exit(2);
	}
	if (*p_token) {
		selectorList[nSelectors++] = addSelector(p_token);
	}
}
int resetSelectorList() {
	nSelectors = 0;
}

#define SELECTOR 0
#define PROPERTY 1
#define VALUE 2

#define AT 10
#define IMPORT 11
#define FILENAME 12
#define ATDONE 13

static char tokenArea[MAX_STRING_LEN];
static char *tokenPtr = tokenArea;
static int insideComment = 0;	/* 0=false, 1=true */
static int insideAt = 0;	/* 0=false, 1=true */

static SELECTOR_T *currentselector = (SELECTOR_T *)0;
static PROPERTY_T *currentproperty = (PROPERTY_T *)0;
static VALUE_T *currentvalue = (VALUE_T *)0;

int processChar(char *p_filename, int p_toestand, int p_lastchar, int p_thischar, int p_nextchar) {

	int toestand = p_toestand;

	/* entering comment area */
	if (p_thischar == '/' && p_nextchar == '*') {
		insideComment = 1;
	}
	if (!insideComment && p_thischar == '@') {
		insideAt = 1;
		toestand = AT;
	}
	/* if inside at area and not inside comment area */
	if (insideAt && !insideComment) {
		switch(p_thischar) {
		default:	/* token not ready yet */
			*tokenPtr++ = p_thischar;
			break;
		case ' ':
			*tokenPtr = '\0';
			tokenPtr = trimWhite(tokenArea);
			if (strcmp(tokenPtr,"@import") == 0) {
				tokenPtr = tokenArea;
				toestand = IMPORT;
			}
			break;
		case '"':	/* filename @import */
			switch (toestand) {
			default:
				fprintf(stderr,"atQuote: Unknown toestand %d near %c%c%c in file %s\n",toestand,p_lastchar,p_thischar,p_nextchar,p_filename);
				exit(1);
			case IMPORT:	/* start of filename */
				*tokenPtr = '\0';
				tokenPtr = trimWhite(tokenArea);
				tokenPtr = tokenArea;
				toestand = FILENAME;
				break;
			case FILENAME:	/* end of filename */
				*tokenPtr = '\0';
				tokenPtr = trimWhite(tokenArea);
				fprintf(stderr,"Found FILENAME=%s\n",tokenPtr);
				tokenPtr = tokenArea;
				toestand = ATDONE;
				break;
			}
			break;
		case ';':
			switch (toestand) {
			default:
				fprintf(stderr,"atSemiColon: Unknown toestand %d near %c%c%c in file %s\n",toestand,p_lastchar,p_thischar,p_nextchar,p_filename);
				exit(1);
			case ATDONE:
				*tokenPtr = '\0';
				tokenPtr = trimWhite(tokenArea);
				tokenPtr = tokenArea;
				break;
			}
			break;
		}
	}

	/* if not inside comment or at area */
	if (!insideComment && !insideAt) {
		switch(p_thischar) {
		default:	/* token not ready yet */
			*tokenPtr++ = p_thischar;
			break;
		case ',':	/* next selector or next value */
			switch (toestand) {
			default:
				fprintf(stderr,"Comma Unknown toestand %d near %c%c%c in file %s\n",toestand,p_lastchar,p_thischar,p_nextchar,p_filename);
				exit(1);
			case SELECTOR:
				*tokenPtr = '\0';
				tokenPtr = trimWhite(tokenArea);
				add2SelectorList(tokenPtr);
				tokenPtr = tokenArea;
				break;
			case VALUE:
				*tokenPtr++ = p_thischar;
				break;
			} 
			break;
		case '{':	/* selector done, property starts here */
			switch(toestand) {
			default:
				fprintf(stderr,"AccoladeOpen Unknown toestand %d near %c%c%c in file %s\n",toestand,p_lastchar,p_thischar,p_nextchar,p_filename);
				exit(1);
			case SELECTOR:
				*tokenPtr = '\0';
				tokenPtr = trimWhite(tokenArea);
				add2SelectorList(tokenPtr);
				tokenPtr = tokenArea;
				toestand = PROPERTY;
				break;
			}
			break;
		case ':':	/* colon can occur in selector. if not then property done, value starts here */
			switch(toestand) {
			default:
				fprintf(stderr,"Colon Unknown toestand %d near %c%c%c in file %s\n",toestand,p_lastchar,p_thischar,p_nextchar,p_filename);
				exit(1);
			case SELECTOR:
				*tokenPtr++ = p_thischar;
				break;
			case PROPERTY:
				*tokenPtr = '\0';
				tokenPtr = trimWhite(tokenArea);
				strcpy(currentPropertyName, tokenPtr);
				tokenPtr = tokenArea;
				toestand = VALUE;
				break;
			}
			break;
		case ';':	/* values done */
			switch(toestand) {
			default:
				fprintf(stderr,"SemiColon Unknown toestand %d near %c%c%c in file %s\n",toestand,p_lastchar,p_thischar,p_nextchar,p_filename);
				exit(1);
			case VALUE:
				*tokenPtr = '\0';
				tokenPtr = trimWhite(tokenArea);
				if (*tokenPtr) {
					int i;
					for (i = 0; i < nSelectors; i++) {
						addValue(addProperty(selectorList[i],currentPropertyName),tokenPtr);
					}
				}
				tokenPtr = tokenArea;
				toestand = PROPERTY;
				break;
			}
			break;
		case '}':	/* selectors done */
			switch(toestand) {
			default:
				fprintf(stderr,"AccoladeClose Unknown toestand %d near %c%c%c in file %s\n",toestand,p_lastchar,p_thischar,p_nextchar,p_filename);
				exit(1);
			case VALUE:
/*fprintf(stderr,"%s: Syntax error found ... missing ;\n",p_filename);*/
{ /* repair */
	/* thischar should have been a semicolon but it is a closing accolade - pretend it's there */
	processChar(p_filename, p_toestand, p_lastchar, ';', p_thischar);
} /* done repair */
				toestand = PROPERTY;	/* fall through */
			case PROPERTY:
				*tokenPtr = '\0';
				tokenPtr = trimWhite(tokenArea);
				if (*tokenPtr) {
					int i;
					for (i = 0; i < nSelectors; i++) {
						addValue(addProperty(selectorList[i],currentPropertyName),tokenPtr);
					}
				}
				tokenPtr = tokenArea;
				resetSelectorList();
				toestand = SELECTOR;
				break;
			}
			break;
		}
	}

	/* exiting comment area */
	if (insideComment && p_lastchar == '*' && p_thischar == '/') {
		insideComment = 0;
	} 
	/* exiting at area */
	if (!insideComment && insideAt && toestand == ATDONE && p_lastchar == ';') {
		insideAt = 0;
		toestand = SELECTOR;
	}

	/* return nieuwe toestand */
	return toestand;
}

