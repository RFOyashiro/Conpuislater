#include "suivants.h"
#include "premiers.h"
#include "analyseur_lexical.h"
#include "analyseur_syntaxique.h"
#include "symboles.h"
#include "affiche_arbre_abstrait.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char yytext[100];
FILE *yyin;
int analyseLex = 0;
int analyseSynt = 0;

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
		yyin = fopen(argv[i], "r");
		if (yyin == NULL) {
			fprintf(stderr, "impossible d'ouvrir le fichier %s\n", argv[i]);
			exit(EXIT_FAILURE);
		}
	}

	
	if (analyseLex) {
		test_yylex_internal(yyin);
	}
	if (analyseSynt) {
		initialise_premiers();
		initialise_suivants();
		n_prog *prog = analyse();
		affiche_n_prog(prog);
	}	
	return 0;
}
