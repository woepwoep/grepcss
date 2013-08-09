/*
** property.c
*/
#include "grepcss.h"

PROPERTY_T *newProperty(char *p_token) {
	PROPERTY_T *new = malloc(sizeof(PROPERTY_T));
	new->name = malloc(strlen(p_token) + 1);
	strcpy(new->name,p_token);
	new->aantal = 1;
	new->values = (VALUE_T *)0;
	new->next = (PROPERTY_T *)0;
	return new;
}

PROPERTY_T *findProperty(SELECTOR_T *p_selector, char *p_token) {
	PROPERTY_T *current;
	
	/* seek p_token */
	for (current = p_selector->properties; current != (PROPERTY_T *)0; current = current->next) {
		if (!strcmp(current->name,p_token)) {
			current->aantal++;
			break;
		}
	}
	return current;
}

PROPERTY_T *addProperty(SELECTOR_T *p_selector, char *p_token) {
	PROPERTY_T *current;

	/* initial */
	if (p_selector->properties == (PROPERTY_T *)0) {
		p_selector->properties = newProperty(p_token);
		return p_selector->properties;
	}

	current = findProperty(p_selector, p_token);
	if (current != (PROPERTY_T *)0) {
		return current;
	}

	/* not found */
	for(current = p_selector->properties; current->next != (PROPERTY_T *)0; current = current->next);
	current->next = newProperty(p_token);
	return current->next;
}
