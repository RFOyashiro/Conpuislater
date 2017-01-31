#include <stdio.h>
#include <stdlib.h>

#include "analyseur_syntaxique.h"
#include "symboles.h"
#include "analyseur_lexical.h"

// Number of sapce per indentation level.
#define NB_SPACE_PER_INDENT 4
// Display debug values if is 1.
#define DEBUG 1

/**
 * Last value returned by lexical analyser.
 */
char currentUnit;
/**
 * Name of current token if needed to be displayed.
 */
char nomToken[100];
/**
 * Value of current token if needed to be displayed.
 */
char valeur[100];

/**
 * Current indentation level.
 */
int currentIndent;

/**
 * Indent depending of the current level of indentation.
 */
void DisplayIndent(void) {
	int i;
	for (i = 0; i < currentIndent; ++i) {
		printf(" ");
	}
}

/**
 * DEBUG
 * Display a XML open tag with indentation.
 * char * foncName Tag name
 */
void openXML(char *tagName) {
	if (!DEBUG) return;
	DisplayIndent();
	printf("<%s>\n", tagName);
	currentIndent += NB_SPACE_PER_INDENT;
}

/**
 * DEBUG
 * Display a XML close tag with indentation.
 * char * foncName Tag name
 */
void closeXML(char *tagName) {
	if (!DEBUG) return;
	currentIndent -= NB_SPACE_PER_INDENT;
	DisplayIndent();
	printf("</%s>\n", tagName);
}

/**
 * DEBUG
 * Display the token value with indentation.
 */
void putToken(int token) {
	if (!DEBUG) return;
	nom_token(token, nomToken, valeur);
	DisplayIndent();
	printf("%s\n", valeur);
}

/**
 * check if current token correspond to the expected token and , if so, display it (only if DEBUG) and get next token.
 * int token expected token
 * return true if match found and next token token get, just false otherwise.
 */
int checkToken(int token) {
	if (token == currentUnit) {
		putToken(currentUnit);
		currentUnit = yylex();
		return 1;
	}
	return 0;
}

/**
 * Display "Error on token : " with the value of the token.
 * int token the token to be displayed (usually currentUnit).
 */
void error(int token) {
	nom_token(token, nomToken, valeur);
	fprintf(stderr, "Error on token : %s\n", valeur);
	exit (-1);
}



void PG (void) {
	
}

void ODV (void) {
	
}

void LDV (void) {
	
}

void LDVB (void) {
	
}

void DV (void) {
	
}

void OTT (void) {
	
}

void LDF (void) {
	
}

void DF (void) {
	
}

void LP (void) {
	
}

void OLDV (void) {
	
}

void I (void) {
	
}

void IAFF (void) {
	
}

void IB (void) {
	
}

void LI (void) {
	
}

void ISI (void) {
	
}

void OSINON (void) {
	
}

void ITQ (void) {
	
}

void IAPP (void) {
	
}

void IRET (void) {
	
}

void IECR (void) {
	
}

void IVIDE (void) {
	
}

void EXP (void) {
	
}

void EXPB (void) {
	
}

void CONJ (void) {
	
}

void CONJB (void) {
	
}

void COMP (void) {
	
}

void COMPB (void) {
	
}

void E (void) {
	
}

void EB (void) {
	
}

void T (void) {
	
}

void TB (void) {
	
}

void NEG (void) {
	
}

void F (void) {
	
}

void VAR (void) {
	
}

void OIND (void) {
	
}

void APPF (void) {
	
}

void LEXP (void) {
	
}

void LEXPB (void) {
	
}




/**
 * Main function to use the synthaxic analyser.
 */
void analyse(void) {
	currentUnit = yylex();
	currentIndent = 0;
	
	//E0();
	
	if (!checkToken(FIN)) {
		error(FIN);
	}
	else {
		printf("Lexical analyse succeded\n");
	}
}
