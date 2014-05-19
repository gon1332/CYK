/**********************#############################*****************************
 *			CYK Parser for CNF Grammars				*
 *			###########################				*
 * Ioannidis Christos, hrioan@inf.uth.gr					*
 * Konstadelias Ioannis, konstadel@inf.uth.gr					*
 * University of Thessaly, 2014							*
 *										*
 * This program parses an input string using the CYK parser for CNF grammars.	*
 * The parser is implemented with the dynamic programming method.		*
 ********************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/ErrorChecks.h"
#include "include/GrammarStore.h"

#define RuleReader		/* Rule Reader */
#define ProductionReader	/* Production Reader*/

#define MAX_IN_CHARS 100	/* Without including NULL */
char *input_str = NULL;

/*
 * void CYK(CNFG *grammar)
 */
void CYK(CNFG *grammar)
{
	// Code goes here
}

/*
 * void scan (FILE *input)
 *
 * Scans the input file line by line and parses each line recognizing the left-hand
 * sides (LHS) and right-hand sides (RHS) of the grammar rules. It also constructs
 * and returns the pointer to the grammar in the main memory for further use.
 */
CNFG *scan (FILE *input);

/*
 * Main Program
 * - Reads the grammar from the file
 * - Run CYK on it
 */
int main (int argc, char **argv)
{
	FILE *f_in;
	CNFG *grammar;

	if (2 != argc) {
		fprintf(stderr, "--info-----\n");
		fprintf(stderr, "#\tCYK parser usage: %s <input_file.cnf>\n", argv[0]);
		fprintf(stderr, "--warning--\n");
		fprintf(stderr, "#\tThe grammar in the input file must be in Chomsky");
		fprintf(stderr, "Normal Form.\n#\tIf not, the parser will not complain");
		fprintf(stderr, ". The execution will not\n#\tstop. The result will be");
		fprintf(stderr, " more than 99.1%% logically incorrect.\n");
		return(1);
	}
	
	SafeCall( f_in = fopen(argv[1], "r") );

	grammar = scan(f_in);
	print_grammar(grammar);

	/* Remove when CYK is implemented
	CYK(grammar);
	*/

	fclose(f_in);

	return(0);
}


CNFG *scan (FILE *input)
{
	char line[100] = {0};
	char str_in = 0;	/* checks if an input string is given */
	
	init_grammar();
	
	while (fgets(line, 99, input)) {
		/* Check if it's time to parse the input string */
		int i;
		for (i = 0; ' ' == line[i]; i++)	/* space sucker */
			;
		if ('\\' == line[i] && '&' == line[i + 1]) {
			str_in = 1;
			break;
		}

		/* Scan 'n Parse the CNF Grammar */
		int lpos = 0;
		Rule *rule;
		
		RuleReader {
			char buffer[20] = {0};
			int i, j;
			for (i = 0; ' ' == line[i]; i++)	/* space sucker */
				;
			for (j = 0 ; ':' != line[i]; i++, j++)
				if (' ' == line[i])
					continue;
				else
					buffer[j] = line[i];
			buffer[j] = '\0';

			lpos = i;
			rule = insert_rule(buffer);
		}

		ProductionReader {
			char buffer[30] = {0};
			int i, j;
			for (i = lpos + 1; ' ' == line[i]; i++)	/* space sucker */
				;
			for (j = 0; line[i]; i++) {
				for (; ' ' == line[i]; i++)	/* space sucker */
					;
				if (('|' == line[i]) || (';' == line[i])) {
					buffer[j] = '\0';
					insert_production(rule, buffer);
					memset(buffer, '\0', j);
					j = 0;
					continue;
				} else {
					buffer[j++] = line[i];
				}
			}
		}
	}

	if (str_in) {
		/* Accept an input of maximum MAX_IN_CHARS characters */
		SafeCall( input_str = malloc(MAX_IN_CHARS + 1) );
		if (!fgets(line, MAX_IN_CHARS, input)) {
			fprintf(stderr, "Syntax error: Missing input string.\n");
			exit(1);
		}
		strncpy(input_str, line, MAX_IN_CHARS);
		strncat(input_str, "\0", 1);
	} else {
		fprintf(stderr, "Syntax error: Missing \\& symbol.\n");
		exit(1);
	}
	
	
	return(get_grammar());
}
