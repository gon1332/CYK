#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GrammarStore.h"
#include "ErrorChecks.h"
#include "strdup.h"

/* Function implementations */
/*
                                            tail
                                             |
   head -> [RULE_1] -> [RULE_2] -> ... -> [RULE_n] -> NULL
          /   |       /   |                  .
         / {PROD_1}  / {PROD_1}              .
        |     |     |     |                  .
        +->{PROD_2} |  {PROD_2}             NULL
              |     |     |
             NULL   +->{PROD_3}
                          |
                         NULL
*/

void init_grammar(void)
{
	head = NULL;
	tail = head;
}

void print_grammar(CNFG *grammar)
{
	Rule *rcurr;
	Production *pcurr;

	for (rcurr = grammar; rcurr; rcurr = rcurr->next) {
		printf("[%s]   \t->\t", rcurr->name);
		for (pcurr = rcurr->prods; pcurr; pcurr = pcurr->next) {
			printf("{ %s } ", pcurr->str);
		}
		puts("");
	}
}

CNFG *get_grammar(void)
{
	return(head);
}

Rule *insert_rule(const char *name)
{
	Rule *new_rule;

	SafeCall( new_rule = malloc(sizeof(Rule)) );

	SafeCall( new_rule->name = strdup(name) );
	new_rule->prods = NULL;
	new_rule->last  = NULL;
	new_rule->next  = NULL;

	if (!head)
		head = new_rule;
	else
		tail->next = new_rule;

	tail = new_rule;

	return(new_rule);
}

Rule *search_rule(const char *name)
{
    if (!head)
        return NULL;

    Rule *curr;
    for (curr = head; curr; curr = curr->next)
        if (!strcmp(curr->name, name))
            return curr;
    return NULL;
}

void insert_production(Rule *rule, const char *prod)
{
	Production *new_prod;

	SafeCall( new_prod = malloc(sizeof(Production)) );

	SafeCall( new_prod->str = strdup(prod) );

	if (rule->last)
		rule->last->next = new_prod;
	else {
		rule->prods = new_prod;
		rule->last = new_prod;
	}
	new_prod->next = NULL;
	rule->last = new_prod;
}

Production *search_production(Rule *rule, const char *prod)
{
    if (!rule)
        return NULL;
    Production *curr;
    for (curr = rule->prods; curr; curr = curr->next)
        if (!strcmp(curr->str, prod))
            return curr;
    return NULL;
}

char *match_production(const char *prod)
{
    if (!head)
        return NULL;

    char nonterminals[10] = {0};
    Rule *curr;
    int i = 0;
    for (curr = head; curr; curr = curr->next) {
        Production *query;
        if ((query = search_production(curr, prod))) {
            if (i > 9)
                printf("***Match Production: Need for more space - "
                       "Too many Rules.");
            nonterminals[i] = (curr->name)[0];
            i++;
        }
    }
    if (!i)
        return 0;
    return strdup(nonterminals);
}
