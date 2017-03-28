#include "suivants.h"
#include "premiers.h"
#include "analyseur_lexical.h"
#include "analyseur_syntaxique.h"
#include "symboles.h"
#include "affiche_arbre_abstrait.h"
#include "analyseur_semantique.h"
#include "tabsymboles.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG_ABSTR 0

char yytext[100];
FILE *yyin = NULL;
int analyseLex = 0;
int analyseSynt = 0;
int analyseSem = 0;

int mainError() {
	fprintf(stderr, "main error\n");
	if (yyin != NULL)
		free(yyin);
	return 0;
}

int main(int argc, char **argv) {

	int i;
	for (i = 1; i < argc; i++) {
		if(strcmp(argv[i], "-l") == 0){
			analyseLex = 1;
			continue;
		}
		if (strcmp(argv[i], "-s") == 0) {
			analyseSynt = 1;
			continue;
		}
		if (strcmp(argv[i], "-S") == 0) {
			analyseSem = 1;
			continue;
		}
		yyin = fopen(argv[i], "r");
		if (yyin == NULL) {
			fprintf(stderr, "impossible d'ouvrir le fichier %s\n", argv[i]);
			return 0;
		}
	}

	int res = 1;
	if (analyseLex) {
		test_yylex_internal(yyin);
	}
	n_prog *prog;
	if (analyseSynt) {
		initialise_premiers();
		initialise_suivants();
		prog = analyse();
		/*if (DEBUG_ABSTR)
			affiche_n_prog(prog);*/
	}
	if(analyseSem) {
		if (!analyseSynt) {
			fprintf(stderr, "In order to run the semantic analyse, you must run syntaxic analyse first\n");
			res = mainError();
		}
		analyseSemantique(prog);
	}
	if (yyin != NULL)
		free(yyin);
	return res;
}
