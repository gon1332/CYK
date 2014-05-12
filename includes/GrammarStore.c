#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GrammarStore.h"
#include "ErrorChecks.h"

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

extern void init_grammar(void)
{
	head = NULL;
	tail = head;
}

extern void print_grammar(CNFG *grammar)
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

extern CNFG *get_grammar(void)
{
	return(head);
}

extern Rule *insert_rule(const char *name)
{
	Rule *new_rule;

	SafeCall( new_rule = malloc(sizeof(Rule)) );

	SafeCall( new_rule->name = strdup(name) );
	new_rule->prods = NULL;
	new_rule->last = NULL;
	new_rule->next = NULL;

	if (!head)
		head = new_rule;
	else
		tail->next = new_rule;
	
	tail = new_rule;

	return(new_rule);
}

extern void insert_production(Rule *rule, char *prod)
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


/*/* int list_is_empty(void)*/
/* * */
/* * Checks if the list is empty. If it is returns 1, otherwise 0.*/
/* */
/*int list_is_empty(void){*/
/*	if(root->next == root && root->prev == root)*/
/*		return(1);*/
/*	return(0);*/
/*}*/

/*/* void print_list(void)*/
/* * */
/* * Prints the list.*/
/* */
/*void print_list(void){*/
/*	env_T *curr;*/
/*	*/
/*	for(curr = root->next; curr != root; curr = curr->next)*/
/*		printf("%s=%s\n", curr->name, curr->value);*/
/*}*/
