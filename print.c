/*
** print.c
*/
#include "grepcss.h"

printSome(SELECTOR_T *p_selectorstart, int p_count, char *p_selector, char *p_property, char *p_value) {
	SELECTOR_T *lptr;
	PROPERTY_T *pptr;
	VALUE_T *vptr;
	for (lptr = p_selectorstart; lptr != (SELECTOR_T *)0; lptr = lptr->next) {
		if (*p_selector && strcmp(p_selector,lptr->name)) continue;
		for (pptr = lptr->properties; pptr != (PROPERTY_T *)0; pptr = pptr->next) {
			if (*p_property && strcmp(p_property,pptr->name)) continue;
			for (vptr = pptr->values; vptr != (VALUE_T *)0; vptr = vptr->next) {
				if (*p_value && strcmp(p_value,vptr->name)) continue;
				fprintf(stdout,"%s { %s: %s; }",lptr->name,pptr->name,vptr->name);
				if (p_count) {
					fprintf(stdout," /*aantal=%d*/",pptr->aantal);
				}
				fprintf(stdout,"\n");
			}
		}
	}
}

printNice(SELECTOR_T *p_selectorstart, int p_count) {
	SELECTOR_T *lptr;
	PROPERTY_T *pptr;
	VALUE_T *vptr;
	for (lptr = p_selectorstart; lptr != (SELECTOR_T *)0; lptr = lptr->next) {
		if (lptr->properties == (PROPERTY_T *)0) continue;
		fprintf(stdout,"\n%s {\n",lptr->name);
		for (pptr = lptr->properties; pptr != (PROPERTY_T *)0; pptr = pptr->next) {
			for (vptr = pptr->values; vptr != (VALUE_T *)0; vptr = vptr->next) {
				fprintf(stdout,"\t%s: %s;",pptr->name,vptr->name);
				if (p_count) {
					fprintf(stdout," /*aantal=%d*/",pptr->aantal);
				}
				fprintf(stdout,"\n");
			}
		}
		fprintf(stdout,"}\n");
	}
}
