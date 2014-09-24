/**********************#############################***************************
 *                      CYK Parser for CNF Grammars                           *
 *                      ###########################                           *
 * Ioannidis Christos, hrioan@inf.uth.gr                                      *
 * Konstadelias Ioannis, konstadel@inf.uth.gr                                 *
 * University of Thessaly, 2014                                               *
 *										                                      *
 * This program parses an input string using the CYK parser for CNF grammars. *
 * The parser is implemented with the dynamic programming method.		      *
 *****************************************************************************/
#include <libxml/xmlreader.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/ErrorChecks.h"
#include "include/GrammarStore.h"
#include "include/strdup.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Parse XML file including CNF grammar.
 * --
 *  The storage of the grammar in main memory is done in one pass during the
 *  parsing.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* STATES: Is the current node a Left-Hand side or a Right-Hand side? */
#define xHS -1
#define LHS 0
#define RHS 1

/* TRIVIAL BOOLEAN FLAGS: For printCNF, is it time to print an arrow? */
#define YES 1
#define NO  0

/* STATE variables used for parsing */
int handside_of_operand = xHS;
int place_arrow = NO;

/* XML PARSING FUNCTIONS */
/* Current Rule */
Rule *rule;
/* Store the CNF grammar during parsing for. Also print under debugging. */
// #define DEBUG
void storeCNF(int type, xmlChar *name, xmlChar *value);
/* Process an XML node. */
void processNode(xmlTextReaderPtr reader);
/* Walk down the XML tree and read it. */
CNFG *streamFile(char *filename);


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Parse input string with CYK (aka CKY) algorithm.
 * --
 *  Array M[][] is a string container.
 *  I use strings in order to simulate sets data type.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int parseCYK(char string[], CNFG *grammar)
{
    /* Initialize M to a zero-indexed, two dimensional array of empty sets. */
    int len = strlen(string);
    char *M[len][len];
    for (int i = 0; i < len; i ++)
        for (int j = 0; j < len; j++)
            M[i][j] = 0;

    /*  */
    for (int i = 0; i < len; i++) {
        /* Convert a character to string. */
        char prod[5] = {0};
        sprintf(prod, "%c", string[i]);
        /* Fill the first row of sets. */
        char *temp = match_production(prod);
        if (temp == 0) {
            printf("CYK: Input string contains unknown terminal symbol "
                   "`%c\'\n", string[i]);
            return 0;
        } else {
            M[i][i] = temp;
        }
    }

    putchar('\n');
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            fflush(stdout);
            if (M[i][j] != 0)
                printf("%s   ", M[i][j]);
            else
                printf("    ");
        }
        putchar('\n');
    }

    /* every substring length */
    for (int l = 1; l < len; l++) {
        /* every starting location for a substring of length l */
        for (int r = 0; r < len - l; r++) {
            /* every split of the substring at string[r : r + l] */
            for (int t = 0; t < l; t++) {
                // DO STUF IN HERE
            }
        }
    }

    return 1;
}


int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "--info-----\n");
		fprintf(stderr, "#\tCYK parser usage: %s <xml_file.jff>\n", argv[0]);
		fprintf(stderr, "--warning--\n");
		fprintf(stderr, "#\tThe grammar in the input file must be in Chomsky");
		fprintf(stderr, "Normal Form.\n#\tIf not, the parser will not complain");
		fprintf(stderr, ". The execution will not\n#\tstop. The result will be");
		fprintf(stderr, " more than 99.1%% logically incorrect.\n");
		return 1;
	}

    CNFG *grammar = streamFile(argv[1]);
    fputs("Grammar loaded...\n", stdout);
    print_grammar(grammar);

    char in_string[100] = {0};
    fprintf(stdout, "Enter the input string: ");
    scanf("%99s", in_string);

    parseCYK(in_string, grammar);

    return 0;
}


void storeCNF(int type, xmlChar *name, xmlChar *value)
{
    // If Node is start of an element:
    if (1 == type) {
        // If element is <left>:
        if (xmlStrEqual(name, xmlCharStrndup("left", 4)))
            handside_of_operand = LHS;
        // If element is <right>:
        else if (xmlStrEqual(name, xmlCharStrndup("right", 5)))
            handside_of_operand = RHS;
    }
    // If Node is text:
    else if (3 == type) {
        if (handside_of_operand == LHS) {
#ifdef DEBUG
            printf("%s", value);
#endif
            rule = search_rule((char *)value);  // a hack-cast
            if (!rule)
                rule = insert_rule((char *)value);  // a hack-cast
            place_arrow = YES;
        } else if (handside_of_operand == RHS) {
#ifdef DEBUG
            printf("%s\n", value);
#endif
            insert_production(rule, (char *)value); // a hack-cast
        }
    }

#ifdef DEBUG
    if (place_arrow == YES && handside_of_operand == LHS) {
        printf("  ->  ");
        place_arrow = NO;
    }
#endif
}

void processNode(xmlTextReaderPtr reader)
{
    /* handling of a node in the tree */
    xmlChar *name, *value;
    int type;

    name = xmlTextReaderName(reader);
    if (name == NULL)
        name = xmlStrdup(BAD_CAST "--");
    value = xmlTextReaderValue(reader);

    type = xmlTextReaderNodeType(reader);

    storeCNF(type, name, value);

    xmlFree(name);
    if (value)
        xmlFree(value);
}

CNFG *streamFile(char *filename)
{
    xmlTextReaderPtr reader;
    int ret;

    /* Initialize grammar store. */
    init_grammar();

    reader = xmlNewTextReaderFilename(filename);
    if (reader != NULL) {
        ret = xmlTextReaderRead(reader);
        while (ret == 1) {
            processNode(reader);
            ret = xmlTextReaderRead(reader);
        }
        xmlFreeTextReader(reader);
        if (ret != 0) {
            printf("%s : failed to parse\n", filename);
        }
    } else {
        printf("Unable to open %s\n", filename);
        exit(1);
    }

    return get_grammar();
}
