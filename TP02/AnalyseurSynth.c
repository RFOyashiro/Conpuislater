#include <stdio.h>
#include <stdlib.h>

#include "AnalyseurSynth.h"
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

/************************************************************************************************
 * ARITHMETIC EXPRESSION PARSING                                                                                             *
 * Use E0() to analyse next serie of token as an arithmetic expression(like $a + 10 * (4 + $b).          *
 * TODO : add variables, tables values ($a[3]), and function call.                                                       *
 ************************************************************************************************/
/**
 * '|'
 */
void E0 (void) {
	openXML("E0");
	E1();
	E0a();
	closeXML("E0");
}

/**
 * Use E0().
 */
void E0a (void) {
	openXML("E0a");
	if (checkToken(OU)) {
		E0();
	}
	else {
		closeXML("E0a");
		return;
	}
	closeXML("E0a");
}

/**
 * '&'
 */
void E1 (void) {
	openXML("E1");
	E2();
	E1a();
	closeXML("E1");
}

/**
 * Use E1a().
 */
void E1a (void) {
	openXML("E1a");
	if (checkToken(ET)) {
		E1();
	}
	else {
		closeXML("E1a");
		return;
	}
	closeXML("E1a");
}

/**
 * '=', '<'
 */
void E2 (void) {
	openXML("E2");
	E3();
	E2a();
	closeXML("E2");
}

/**
 * Use E2.
 */
void E2a (void) {
	openXML("E2a");
	if (checkToken(EGAL)) {
		E2();
	}
	else if (checkToken(INFERIEUR)) {
		E2();
	}
	else {
		closeXML("E2a");
		return;
	}
	closeXML("E2a");
}

/**
 * '+', '-'
 */
void E3 (void) {
	openXML("E3");
	E4();
	E3a();
	closeXML("E3");
}

/**
 * Use E3.
 */
void E3a (void) {
	openXML("E3a");
	if (checkToken(PLUS)) {
		E3();
	}
	else if (checkToken(MOINS)) {
		E3();
	}
	else {
		closeXML("E3a");
		return;
	}
	closeXML("E3a");
}

/**
 * '*', '/'
 */
void E4 (void) {
	openXML("E4");
	E5();
	E4a();
	closeXML("E4");
}

/**
 * Use E4.
 */
void E4a (void) {
	openXML("E4a");
	if (checkToken(FOIS)) {
		E4();
	}
	else if (checkToken(DIVISE)) {
		E4();
	}
	else {
		closeXML("E4a");
		return;
	}
	closeXML("E4a");
}

/**
 * '!'
 */
void E5 (void) {
	openXML("E5");
	if (checkToken(NON)) {
		E5();
	}
	else {
		E6();
	}
	closeXML("E5");
}

/**
 * '(Expression)', Number, Function call, variable
 */
void E6 (void) {
	openXML("E6");
	if (checkToken(PARENTHESE_OUVRANTE)) {
		E0();
		if (!checkToken(PARENTHESE_FERMANTE)) {
			error(currentUnit);
		}
	}
	else if (checkToken(NOMBRE)) {
		closeXML("E6");
		return;
	}
	// TEST de variable et appel de fonction
	else {
		error(currentUnit);
		closeXML("E6");
		return;
	}
	closeXML("E6");
}

/************************************************************************************************
 * /ARITHMETIC EXPRESSION PARSING                                                                                            *
 * Use E0() to analyse next serie of token as an arithmetic expression(like $a + 10 * (4 + $b).          *
 * TODO : add variables, tables values ($a[3]), and function call.                                                       *
 ************************************************************************************************/

/**
 * Main function to use the synthaxic analyser.
 */
void analyse(void) {
	currentUnit = yylex();
	currentIndent = 0;
	
	E0();
	
	if (!checkToken(FIN)) {
		error(FIN);
	}
	else {
		printf("Lexical analyse succeded\n");
	}
}
