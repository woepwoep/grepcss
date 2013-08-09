/*
** selector.c
*/
#include "grepcss.h"

static SELECTOR_T *firstSelector = (SELECTOR_T *)0;

SELECTOR_T *findSelector(char *p_token) {
	SELECTOR_T *current;

	/* seek token */
	for (current = firstSelector; current != (SELECTOR_T *)0; current = current->next) {
		int l1 = strlen(current->name);
		int l2 = strlen(p_token);
		if (!strcmp(current->name,p_token)) {
			current->aantal++;
			break;
		}
	}
	/* return found or null */
	return current;
}

SELECTOR_T *newSelector(char *p_token) {
	SELECTOR_T *new = malloc(sizeof(SELECTOR_T));
	new->name = malloc(strlen(p_token) + 1);
	strcpy(new->name,p_token);
	new->aantal = 1;
	new->properties = (PROPERTY_T *)0;
	new->next = (SELECTOR_T *)0;
	return new;
}

SELECTOR_T *addSelector(char *p_token) {
	SELECTOR_T *current;

	/* initial */
	if (firstSelector == (SELECTOR_T *)0) {
		firstSelector = newSelector(p_token);
		return firstSelector;
	}

	current = findSelector(p_token);
	if (current != (SELECTOR_T *)0) return current;

	/* not found */
	for(current = firstSelector; current->next != (SELECTOR_T *)0; current = current->next);
	current->next = newSelector(p_token);
	return current->next;
}

SELECTOR_T *startSelector() {
	return firstSelector;
}
