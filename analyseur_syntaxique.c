#include <stdio.h>
#include <stdlib.h>

#include "analyseur_syntaxique.h"
#include "symboles.h"
#include "analyseur_lexical.h"
#include "premiers.h"
#include "suivants.h"

// Number of sapce per indentation level.
#define NB_SPACE_PER_INDENT 2
// Display debug values if is 1.
#define DEBUG 1

/**
 * Last value returned by lexical analyser.
 */
char currentUnit;
/**
 * Name of current token if needed to be displayed.
 */
char *nomToken;
/**
 * Value of current token if needed to be displayed.
 */
char *valeur;

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
 * Get the tag corresponding to the token (terminal symbol only)
 */
char * getTokenTag(int token) {
	if (!DEBUG) return NULL;
	switch (token) {
		case ENTIER:
		case SI:
		case ALORS:
		case SINON:
		case TANTQUE:
		case FAIRE:
		case RETOUR:
		case LIRE:
		case ECRIRE:
			return "mot_clef";
		case POINT_VIRGULE:
		case PLUS:
		case MOINS:
		case FOIS:
		case DIVISE:
		case PARENTHESE_OUVRANTE:
		case PARENTHESE_FERMANTE:
		case CROCHET_OUVRANT:
		case CROCHET_FERMANT:
		case ACCOLADE_OUVRANTE:
		case ACCOLADE_FERMANTE:
		case EGAL:
		case INFERIEUR:
		case ET:
		case OU:
		case NON:
		case VIRGULE:
			return "symbole";
		case ID_VAR:
			return "id_variable";
		case ID_FCT:
			return "id_fonction";
		case NOMBRE :
			return "nombre";
	}
}

/**
 * DEBUG
 * Display the token value with indentation.
 */
void putToken(int token) {
	if (!DEBUG) return;
	nom_token(token, nomToken, valeur);
	DisplayIndent();
	char * tag = getTokenTag(token);
	printf("<%s>%s</%s>\n", tag, valeur, tag);
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
 * Display "Error on token : " with the value of the currentUnit.
 */
void error() {
	nom_token(currentUnit, nomToken, valeur);
	fprintf(stderr, "Error on token : %s\n", valeur);
	exit (EXIT_FAILURE);
}



n_prog *pg (void) {

	n_l_dec *$odv = NULL;
	n_prog *$odv = NULL;
	n_l_dec *$ldf = NULL;
	openXML(__func__);
	if (est_premier(_optDecVariables_, currentUnit) || 
	  est_premier(_listeDecFonctions_, currentUnit) ||
	  est_suivant(_programme_, currentUnit)) {
                $odv = odv();
                $ldf = ldf();
                $pg = cree_n_prog($odv, $ldf);
		closeXML(__func__);
		return $pg;	
	}
	error();
	closeXML(__func__);
}

n_l_dec *odv (void) {

	n_l_dec *$odv = NULL;
	openXML(__func__);
	if (est_premier(_listeDecVariables_, currentUnit)) {
        $odv = ldv();
		if (checkToken(POINT_VIRGULE)) {
			closeXML(__func__);
			return $odv;
		}
	}
	if (est_suivant(_optDecVariables_, currentUnit)) {
		closeXML(__func__);
		return NULL;
	}
	error();
	closeXML(__func__);
}

n_l_dec *ldv (void) {

	n_l_dec *$ldv = NULL;
	n_l_dec *$ldvb = NULL;
	n_dec *$dv = NULL;
	openXML(__func__);
	if (est_premier(_declarationVariable_, currentUnit)) {
                $dv = dv();
                $ldvb = ldvb();
                $ldv = cree_n_l_dec($dv, $ldvb);
		closeXML(__func__);
		return $ldv;
	}
	error();
	closeXML(__func__);
}

n_l_dec * ldvb (void) {

	n_l_dec *$ldvb = NULL;
	n_l_dec *$ldvb2 = NULL;
	n_dec *$dv = NULL;
	openXML(__func__);
	if (checkToken(VIRGULE)) {
                $dv = dv();
                $ldvb2 = ldvb();
                $ldvb = cree_n_l_dec($dv, $ldvb2);
		closeXML(__func__);
		return $ldvb;
	}
	if (est_suivant(_listeDecVariablesBis_, currentUnit)) {
		closeXML(__func__);
		return NULL;
	}
	error();
	closeXML(__func__);
}

n_dec *dv (void) {

	int $ott = -1;
	n_dec *$dv = NULL;
	openXML(__func__);
	if (checkToken(ENTIER)) {
		
		if (checkToken(ID_VAR)) {
            $ott = ott();
            if ($ott < 0)
            	$dv = cree_n_dec_var(valeur);
            else 
            	$dv = cree_n_dec_tab(valeur, $ott);
			closeXML(__func__);
			return $dv;
		}
	}
	error();
	closeXML(__func__);
}

int ott (void) {

	int $ott = -1;
	openXML(__func__);
	if (checkToken(CROCHET_OUVRANT)) {
		
		if (checkToken(NOMBRE)) {
			
			if (checkToken(CROCHET_FERMANT)) {
				$ott = atoi(valeur);
				closeXML(__func__);
				return $ott;
			}
		}
	}
	if (est_suivant(_optTailleTableau_, currentUnit)) {
		closeXML(__func__);
		return -1;
	}
	error();
	closeXML(__func__);
}

n_l_dec *ldf (void) {

	n_l_dec *$ldf = NULL;
	n_l_dec *$ldf2 = NULL;
	n_dec *$df = NULL;
	openXML(__func__);
	if (est_premier(_declarationFonction_, currentUnit)) {
                $df = df();
                $ldf2 = ldf();
                $ldf = cree_n_l_dec($df, $ldf2);
		closeXML(__func__);
		return $ldf;
	}
	if (est_suivant(_listeDecFonctions_, currentUnit)) {
		closeXML(__func__);
		return NULL;
	}
	error();
	closeXML(__func__);
}

n_dec *df (void) {

	n_dec *$df = NULL;
	n_l_dec *$lp = NULL;
	n_l_dec *$odv = NULL;
	n_instr *$ib = NULL;
	openXML(__func__);
	if (checkToken(ID_FCT)) {
		
        $lp = lp();
        $odv = odv();
        $ib = ib();
        $df = cree_n_dec_fonc(valeur, $lp, $odv, $ib);
		closeXML(__func__);
		return $df;
	}
	error();	
	closeXML(__func__);
}

n_l_dec *lp (void) {

	n_l_dec *$oldv = NULL;
	openXML(__func__);
	if (checkToken(PARENTHESE_OUVRANTE)) {
		
        $oldv = oldv();
		if (checkToken(PARENTHESE_FERMANTE)) {
			
			closeXML(__func__);
			return $oldv;
		}
	}
	error();
	closeXML(__func__);
}

n_l_dec *oldv (void) {

	n_l_dec *$oldv = NULL;
	openXML(__func__);
	if (est_premier(_listeDecVariables_, currentUnit)) {
        $oldv = ldv();
		closeXML(__func__);
		return $oldv;
	}
	if (est_suivant(_optListeDecVariables_, currentUnit)) {
		closeXML(__func__);
		return NULL;
	}
	closeXML(__func__);
	error();
}

n_instr *i (void) {

	n_instr *$i = NULL;
	openXML(__func__);
	if (est_premier(_instructionAffect_, currentUnit)) {
        $i = iaff();
		closeXML(__func__);
		return $i;
	}
	if (est_premier(_instructionBloc_, currentUnit)) {
        $i = ib();
		closeXML(__func__);
		return $i;
	}
	if (est_premier(_instructionSi_, currentUnit)) {
        $i = isi();
		closeXML(__func__);
		return $i;
	}
	if (est_premier(_instructionTantque_, currentUnit)) {
        $i = itq();
		closeXML(__func__);
		return $i;
	}
	if (est_premier(_instructionAppel_, currentUnit)) {
        $i = iapp();
		closeXML(__func__);
		return $i;
	}
	if (est_premier(_instructionRetour_, currentUnit)) {
        $i = iret();
		closeXML(__func__);
		return $i;
	}
	if (est_premier(_instructionEcriture_, currentUnit)) {
        $i = iecr();
		closeXML(__func__);
		return $i;
	}
	if (est_premier(_instructionVide_, currentUnit)) {
        $i = ivide();
		closeXML(__func__);
		return $i;
	}
	if (est_premier(_instructionFaire_, currentUnit)) {
        $i = ift();
		closeXML(__func__);
		return $i;
	}
	error();
	closeXML(__func__);
}

n_instr *iaff (void) {

	n_instr *$iaff = NULL;
	n_var *$var = NULL;
	n_exp *$exp = NULL;
	openXML(__func__);
	if (est_premier(_var_, currentUnit)) {
        $var = var();
		if (checkToken(EGAL)) {
			
            $exp = exp();
			if (checkToken(POINT_VIRGULE)) {
				
				$iaff = cree_n_instr_affect($var, $exp);
				closeXML(__func__);
				return $iaff;
			}
		}
	}
	error();
	closeXML(__func__);
}

n_instr *ib (void) {

	n_instr *$ib = NULL;
	n_l_instr *$li = NULL;
	openXML(__func__);
	if (checkToken(ACCOLADE_OUVRANTE)) {
		
        $li = li();
		if (checkToken(ACCOLADE_FERMANTE)) {
			
			$ib = cree_n_instr_bloc($li);
			closeXML(__func__);
			return $ib;
		}
	}
	error();
	closeXML(__func__);
}

n_l_instr *li (void) {

	n_l_instr *$li = NULL;
	n_l_instr *$li2 = NULL;
	n_instr *$i = NULL;
	openXML(__func__);
	if (est_premier(_instruction_, currentUnit)) {
        $i = i();
        $li2 = li();
        
        $li = cree_n_l_instr($i, $li2);
		closeXML(__func__);
		return $li;
	}
	if (est_suivant(_listeInstructions_, currentUnit)) {
		closeXML(__func__);
		return NULL;
	}
	error();
	closeXML(__func__);
}

n_instr *isi (void) {

	n_instr *$isi = NULL;
	n_instr *$ib = NULL;
	n_exp *$exp = NULL;
	n_instr *$osinon = NULL;
	openXML(__func__);
	if (checkToken(SI)) {
		
        $exp = exp();
		if (checkToken(ALORS)) {
			
            $ib = ib();
            $osinon = osinon();
            
            $isi = cree_n_instr_si($exp, $ib, $osinon);
			closeXML(__func__);
			return $isi;
		}
	}
	error();
	closeXML(__func__);	
}

n_instr *osinon (void) {

	n_instr *$osinon = NULL;
	openXML(__func__);
	if (checkToken(SINON)) {
		
        $osinon = ib();
		closeXML(__func__);
		return $osinon;
	}
	if (est_suivant(_optSinon_, currentUnit)) {
		closeXML(__func__);
		return NULL;
	}
	error();
	closeXML(__func__);
}

n_instr *itq (void) {

	n_instr *$itq = NULL;
	n_exp *$exp = NULL;
	n_instr *$ib = NULL;
	openXML(__func__);
	if (checkToken(TANTQUE)) {
		
        $exp = exp();
		if (checkToken(FAIRE)) {
			
            $ib = ib();
            
            $itq = cree_n_instr_tantque(n_exp *test, n_instr *faire);
			closeXML(__func__);
			return $itq;
		}
	}
	
	error();
	closeXML(__func__);
}

n_instr *ift(void) {

	n_instr *$ib = NULL;
	n_instr *$ift = NULL;
	n_exp *$exp = NULL;
	openXML(__func__);
	if (checkToken(FAIRE)){
		$ib = ib();
		if (checkToken(TANTQUE)) {
			$exp = exp();
			
			if (checkToken(POINT_VIRGULE)) {
			
				$ift = cree_n_instr_faire($ib, $exp);
				closeXML(__func__);
				return $ift;
			}
		}	
	}
	error();
	closeXML(__func__);
}

n_instr *iapp (void) {

	n_instr *$iapp = NULL;
	n_appel *$appf = NULL;
	openXML(__func__);
	if (est_premier(_appelFct_, currentUnit)) {
        $appf = appf();
		if (checkToken(POINT_VIRGULE)) {
			
			$iapp = cree_n_instr_appel(n_appel *appel);
			closeXML(__func__);
			return $iapp;
		}
	}
	error();
	closeXML(__func__);
}

n_instr *iret (void) {

	n_exp *$exp = NULL;
	n_instr *$iret = NULL;
	openXML(__func__);
	if (checkToken(RETOUR)) {
		
        $exp = exp();
		if (checkToken(POINT_VIRGULE)) {
			
			$iret = cree_n_instr_retour(n_exp *expression);
			closeXML(__func__);
			return $iret;
		}
	}
	error();
	closeXML(__func__);
}

n_instr *iecr (void) {

	n_instr *$iecr = NULL;
	n_exp *$exp = NULL;
	openXML(__func__);
	if (checkToken(ECRIRE)) {
		
		if (checkToken(PARENTHESE_OUVRANTE)) {
			
            $exp = exp();
			if (checkToken(PARENTHESE_FERMANTE)) {
				
				if (checkToken(POINT_VIRGULE)) {
					
					$iecr = cree_n_instr_ecrire($exp);
					closeXML(__func__);
					return $iecr;
				}
			}
		}
	}
	error();
	closeXML(__func__);
}

void ivide (void) {
	openXML(__func__);
	if (checkToken(POINT_VIRGULE)) {
		
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void exp (void) {
	openXML(__func__);
	if (est_premier(_conjonction_, currentUnit)) {
                conj();
                expb();
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void expb (void) {
	openXML(__func__);
	if (checkToken(OU)) {
		
                conj();
                expb();
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

void conj (void) {
	openXML(__func__);
	if (est_premier(_comparaison_, currentUnit)) {
                comp();
                conjb();
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void conjb (void) {
	openXML(__func__);
	if (checkToken(ET)) {
		
                comp();
                conjb();
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

void comp (void) {
	openXML(__func__);
	if (est_premier(_expArith_, currentUnit)) {
                e();
                compb();
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void compb (void) {
	openXML(__func__);
	if (checkToken(EGAL)) {
		
                e();
                compb();
		closeXML(__func__);
		return;
	}
	if (checkToken(INFERIEUR)) {
		
                e();
                compb();
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

void e (void) {
	openXML(__func__);
	if (est_premier(_terme_, currentUnit)) {
                t();
                eb();
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void eb (void) {
	openXML(__func__);
	if (checkToken(PLUS)) {
		
                t();
                eb();
		closeXML(__func__);
		return;
	}
	if (checkToken(MOINS)) {
		
                t();
                eb();
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

void t (void) {
	openXML(__func__);
	if (est_premier(_negation_, currentUnit)) {
                neg();
                tb();
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void tb (void) {
	openXML(__func__);
	if (checkToken(FOIS)) {
		
                neg();
                tb();
		closeXML(__func__);
		return;
	}
	if (checkToken(DIVISE)) {
		
                neg();
                tb();
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

void neg (void) {
	openXML(__func__);
	if (checkToken(NON)) {
		
                neg();
		closeXML(__func__);
		return;
	}
	if (est_premier(_facteur_, currentUnit)) {
                f();
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void f (void) {
	openXML(__func__);
	if (checkToken(PARENTHESE_OUVRANTE)) {
		
                exp();
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
                appf();
		closeXML(__func__);
		return;
	}
	if (est_premier(_var_, currentUnit)) {
                var();
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void var (void) {
	openXML(__func__);
	if (checkToken(ID_VAR)) {
		
                oind();
		closeXML(__func__);
		return;
	}
	error();
	closeXML(__func__);
}

void oind (void) {
	openXML(__func__);
	if (checkToken(CROCHET_OUVRANT)) {
		
                exp();
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

void appf (void) {
	openXML(__func__);
	if (checkToken(ID_FCT)) {
		
		if (checkToken(PARENTHESE_OUVRANTE)) {
			
                        lexp();
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

void lexp (void) {
	openXML(__func__);
	if (est_premier(_expression_, currentUnit)) {
                exp();
                lexpb();
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

void lexpb (void) {
	openXML(__func__);
	if (checkToken(VIRGULE)) {
		
                exp();
                lexpb();
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
	
        pg();
	
	if (currentUnit != FIN) {
		error();
	}
	else {
		//printf("Lexical analyse succeded\n");
	}
}
