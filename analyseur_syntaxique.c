#include <stdio.h>
#include <stdlib.h>

#include "analyseur_syntaxique.h"
#include "symboles.h"
#include "analyseur_lexical.h"
#include "premiers.h"
#include "suivants.h"

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
void openXML(const char *tagName) {
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
void closeXML(const char *tagName) {
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
void error() {
	nom_token(currentUnit, nomToken, valeur);
	fprintf(stderr, "Error on token : %s\n", valeur);
	exit (EXIT_FAILURE);
}



void PG (void) {
	openXML(__func__);
	if (est_premier(_optDecVariables_, currentUnit) || 
	  est_premier(_listeDecFonctions_, currentUnit) ||
	  est_suivant(_programme_, currentUnit)) {
		ODV();
		LDF();
		closeXML(__func__);
		return;	
	}
	error();
	closeXML(__func__);
}

void ODV (void) {
	openXML(__func__);
	if (est_premier(_listeDecVariables_, currentUnit)) {
		LDV();
		if (checkToken(POINT_VIRGULE)) {
			
			closeXML(__func__);
			return;
		}
	}
	if (est_suivant(_optDecVariables_, currentUnit)) {
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void LDV (void) {
	openXML(__func__);
	if (est_premier(_declarationVariable_, currentUnit)) {
		DV();
		LDVB();
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void LDVB (void) {
	openXML(__func__);
	if (checkToken(VIRGULE)) {
		DV();
		LDVB();
		closeXML(__func__);
		return;
	}
	if (est_suivant(_listeDecVariablesBis_, currentUnit)) {
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void DV (void) {
	openXML(__func__);
	if (checkToken(ENTIER)) {
		
		if (checkToken(ID_VAR)) {
			
			OTT();
			closeXML(__func__);
			return;
		}
	}
	error();
	closeXML(__func__);
}

void OTT (void) {
	openXML(__func__);
	if (checkToken(CROCHET_OUVRANT)) {
		
		if (checkToken(NOMBRE)) {
			
			if (checkToken(CROCHET_FERMANT)) {
				
				closeXML(__func__);
				return;
			}
		}
	}
	if (est_suivant(_optTailleTableau_, currentUnit)) {
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void LDF (void) {
	openXML(__func__);
	if (est_premier(_declarationFonction_, currentUnit)) {
		DF();
		LDF();
		closeXML(__func__);
		return;
	}
	if (est_suivant(_listeDecFonctions_, currentUnit)) {
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void DF (void) {
	openXML(__func__);
	if (checkToken(ID_FCT)) {
		
		LP();
		ODV();
		IB();
		closeXML(__func__);
		return;
	}
	error();	
	closeXML(__func__);
}

void LP (void) {
	openXML(__func__);
	if (checkToken(PARENTHESE_OUVRANTE)) {
		
		OLDV();
		if (checkToken(PARENTHESE_FERMANTE)) {
			
			closeXML(__func__);
			return;
		}
	}
	error();
	closeXML(__func__);
}

void OLDV (void) {
	openXML(__func__);
	if (est_premier(_listeDecVariables_, currentUnit)) {
		LDV();
		closeXML(__func__);
		return;
	}
	if (est_suivant(_optListeDecVariables_, currentUnit)) {
		closeXML(__func__);
		return;
	}
	closeXML(__func__);
	error();
}

void I (void) {
	openXML(__func__);
	if (est_premier(_instructionAffect_, currentUnit)) {
		IAFF();
		closeXML(__func__);
		return;
	}
	if (est_premier(_instructionBloc_, currentUnit)) {
		IB();
		closeXML(__func__);
		return;
	}
	if (est_premier(_instructionSi_, currentUnit)) {
		ISI();
		closeXML(__func__);
		return;
	}
	if (est_premier(_instructionTantque_, currentUnit)) {
		ITQ();
		closeXML(__func__);
		return;
	}
	if (est_premier(_instructionAppel_, currentUnit)) {
		IAPP();
		closeXML(__func__);
		return;
	}
	if (est_premier(_instructionRetour_, currentUnit)) {
		IRET();
		closeXML(__func__);
		return;
	}
	if (est_premier(_instructionEcriture_, currentUnit)) {
		IECR();
		closeXML(__func__);
		return;
	}
	if (est_premier(_instructionVide_, currentUnit)) {
		IVIDE();
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void IAFF (void) {
	openXML(__func__);
	if (est_premier(_var_, currentUnit)) {
		VAR();
		if (checkToken(EGAL)) {
			
			EXP();
			if (checkToken(POINT_VIRGULE)) {
				
				closeXML(__func__);
				return;
			}
		}
	}
	error();
	closeXML(__func__);
}

void IB (void) {
	openXML(__func__);
	if (checkToken(ACCOLADE_OUVRANTE)) {
		
		LI();
		if (checkToken(ACCOLADE_FERMANTE)) {
			
			closeXML(__func__);
			return;
		}
	}
	error();
	closeXML(__func__);
}

void LI (void) {
	openXML(__func__);
	if (est_premier(_instruction_, currentUnit)) {
		I();
		LI();
		closeXML(__func__);
		return;
	}
	if (est_suivant(_listeInstructions_, currentUnit)) {
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void ISI (void) {
	openXML(__func__);
	if (checkToken(SI)) {
		
		EXP();
		if (checkToken(ALORS)) {
			
			IB();
			OSINON();
			closeXML(__func__);
			return;
		}
	}
	error();
	closeXML(__func__);	
}

void OSINON (void) {
	openXML(__func__);
	if (checkToken(SINON)) {
		
		IB();
		closeXML(__func__);
		return;
	}
	if (est_suivant(_optSinon_, currentUnit)) {
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void ITQ (void) {
	openXML(__func__);
	if (checkToken(TANTQUE)) {
		
		EXP();
		if (checkToken(FAIRE)) {
			
			IB();
			closeXML(__func__);
			return;
		}
	}
	error();
	closeXML(__func__);
}

void IAPP (void) {
	openXML(__func__);
	if (est_premier(_appelFct_, currentUnit)) {
		APPF();
		if (checkToken(POINT_VIRGULE)) {
			
			closeXML(__func__);
			return;
		}
	}
	error();
	closeXML(__func__);
}

void IRET (void) {
	openXML(__func__);
	if (checkToken(RETOUR)) {
		
		EXP();
		if (checkToken(POINT_VIRGULE)) {
			
			closeXML(__func__);
			return;
		}
	}
	error();
	closeXML(__func__);
}

void IECR (void) {
	openXML(__func__);
	if (checkToken(ECRIRE)) {
		
		if (checkToken(PARENTHESE_OUVRANTE)) {
			
			EXP();
			if (checkToken(PARENTHESE_FERMANTE)) {
				
				if (checkToken(POINT_VIRGULE)) {
					
					closeXML(__func__);
					return;
				}
			}
		}
	}
	error();
	closeXML(__func__);
}

void IVIDE (void) {
	openXML(__func__);
	if (checkToken(POINT_VIRGULE)) {
		
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void EXP (void) {
	openXML(__func__);
	if (est_premier(_conjonction_, currentUnit)) {
		CONJ();
		EXPB();
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void EXPB (void) {
	openXML(__func__);
	if (checkToken(OU)) {
		
		CONJ();
		EXPB();
		closeXML(__func__);
		return;
	}
	if (est_suivant(_expressionBis_, currentUnit)) {
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void CONJ (void) {
	openXML(__func__);
	if (est_premier(_comparaison_, currentUnit)) {
		COMP();
		CONJB();
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void CONJB (void) {
	openXML(__func__);
	if (checkToken(ET)) {
		
		COMP();
		CONJB();
		closeXML(__func__);
		return;
	}
	if (est_suivant(_conjonctionBis_, currentUnit)) {
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void COMP (void) {
	openXML(__func__);
	if (est_premier(_expArith_, currentUnit)) {
		E();
		COMPB();
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void COMPB (void) {
	openXML(__func__);
	if (checkToken(EGAL)) {
		
		E();
		COMPB();
		closeXML(__func__);
		return;
	}
	if (checkToken(INFERIEUR)) {
		
		E();
		COMPB();
		closeXML(__func__);
		return;
	}
	if (est_suivant(_comparaisonBis_, currentUnit)) {
		closeXML(__func__);
		return;
	}
	
	error();	
	closeXML(__func__);
}

void E (void) {
	openXML(__func__);
	if (est_premier(_terme_, currentUnit)) {
		T();
		EB();
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void EB (void) {
	openXML(__func__);
	if (checkToken(PLUS)) {
		
		T();
		EB();
		closeXML(__func__);
		return;
	}
	if (checkToken(MOINS)) {
		
		T();
		EB();
		closeXML(__func__);
		return;
	}
	if (est_suivant(_expArithBis_, currentUnit)) {
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void T (void) {
	openXML(__func__);
	if (est_premier(_negation_, currentUnit)) {
		NEG();
		TB();
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void TB (void) {
	openXML(__func__);
	if (checkToken(FOIS)) {
		
		NEG();
		TB();
		closeXML(__func__);
		return;
	}
	if (checkToken(DIVISE)) {
		
		NEG();
		TB();
		closeXML(__func__);
		return;
	}
	if (est_suivant(_termeBis_, currentUnit)) {
		closeXML(__func__);
		return;
	}
	error();	
	closeXML(__func__);
}

void NEG (void) {
	openXML(__func__);
	if (checkToken(NON)) {
		
		NEG();
		closeXML(__func__);
		return;
	}
	if (est_premier(_facteur_, currentUnit)) {
		F();
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void F (void) {
	openXML(__func__);
	if (checkToken(PARENTHESE_OUVRANTE)) {
		
		EXP();
		if (checkToken(PARENTHESE_FERMANTE)) {
			
			closeXML(__func__);
			return;
		}
	}
	if (checkToken(NOMBRE)) {
		
		closeXML(__func__);
		return;
	}
	if (checkToken(LIRE)) {
		
		if (checkToken(PARENTHESE_OUVRANTE)) {
			
			if (checkToken(PARENTHESE_FERMANTE)) {
				
				closeXML(__func__);
				return;
			}
		}
	}
	if (est_premier(_appelFct_, currentUnit)) {
		APPF();
		closeXML(__func__);
		return;
	}
	if (est_premier(_var_, currentUnit)) {
		VAR();
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void VAR (void) {
	openXML(__func__);
	if (checkToken(ID_VAR)) {
		
		OIND();
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void OIND (void) {
	openXML(__func__);
	if (checkToken(CROCHET_OUVRANT)) {
		
		EXP();
		if (checkToken(CROCHET_FERMANT)) {
			
			closeXML(__func__);
			return;
		}
	}
	if (est_suivant(_optIndice_, currentUnit)) {
		closeXML(__func__);
		return;
	}
	error();	
	closeXML(__func__);
}

void APPF (void) {
	openXML(__func__);
	if (checkToken(ID_FCT)) {
		
		if (checkToken(PARENTHESE_OUVRANTE)) {
			
			LEXP();
			if (checkToken(PARENTHESE_FERMANTE)) {
				
				closeXML(__func__);
				return;
			}
		}
	}
	if (est_suivant(_appelFct_, currentUnit)) {
		closeXML(__func__);
		return;
	}
	error();	
	closeXML(__func__);
}

void LEXP (void) {
	openXML(__func__);
	if (est_premier(_expression_, currentUnit)) {
		EXP();
		LEXPB();
		closeXML(__func__);
		return;
	}
	if (est_suivant(_listeExpressions_, currentUnit)) {
		closeXML(__func__);
		return;
	}
	error();	
	closeXML(__func__);
}

void LEXPB (void) {
	openXML(__func__);
	if (checkToken(VIRGULE)) {
		
		EXP();
		LEXPB();
		closeXML(__func__);
		return;
	}
	if (est_suivant(_listeExpressionsBis_, currentUnit)) {
		closeXML(__func__);
		return;
	}
	error();	
	closeXML(__func__);
}


/**
 * Main function to use the synthaxic analyser.
 */
void analyse(void) {
	currentUnit = yylex();
	currentIndent = 0;
	
	PG();
	
	if (!checkToken(FIN)) {
		error();
	}
	else {
		printf("Lexical analyse succeded\n");
	}
}
