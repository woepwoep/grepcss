/*
** value.c
*/
#include "grepcss.h"

VALUE_T *newValue(char *p_token) {
	VALUE_T *new = malloc(sizeof(VALUE_T));
	new->name = malloc(strlen(p_token) + 1);
	strcpy(new->name,p_token);
	new->aantal = 1;
	new->next = (VALUE_T *)0;
	return new;
}

void addValue(PROPERTY_T *p_property, char *p_token) {
	VALUE_T *current;

	if (p_property->values == (VALUE_T *)0) {

		/* initial */
		p_property->values = newValue(p_token);

	} else { 

		/* new value */
		for(current = p_property->values; current->next != (VALUE_T *)0; current = current->next);
		current->next = newValue(p_token);
	}
}
