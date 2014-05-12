#ifndef __GRAMMAR_STORE__
#define __GRAMMAR_STORE__

typedef struct __production {
	char *str;			/* The production */
	
	struct __production *next;	/* Pointer to the next production */
} Production;

typedef struct __rule {
	char *name;		/* Name of the grammar rule */
	Production *prods;	/* Pointer to the productions */
	Production *last;	/* Pointer to the last production */
	
	struct __rule *next;	/* Pointer to the next rule */
} Rule;

typedef Rule CNFG;

static Rule *head;	/* Global variable that points to the first grammar rule */
static Rule *tail;	/* Global variable that points to the last grammar rule */

/* Function declarations */
/* Grammar */
extern void init_grammar(void);
extern void print_grammar(CNFG *grammar);
extern CNFG *get_grammar(void);

/* Rules */
extern Rule *insert_rule(const char *name);

/* Productions */
extern void insert_production(Rule *rule, char *prod);

#endif
