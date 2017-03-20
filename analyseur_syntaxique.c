#include "analyseur_syntaxique.h"

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
char nomToken[512];
/**
 * Value of current token if needed to be displayed.
 */
char valeur[1024];

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
		case NOMBRE:
			return "nombre";
		default:
			return NULL;
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
	exit(EXIT_FAILURE);
}

n_prog *pg(void) {

	n_l_dec *$odv = NULL;
	n_prog *$pg = NULL;
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
	return NULL;
}

n_l_dec *odv(void) {

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
	return NULL;
}

n_l_dec *ldv(void) {

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
	return NULL;
}

n_l_dec * ldvb(void) {

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
	return NULL;
}

n_dec *dv(void) {

	int $ott = -1;
	n_dec *$dv = NULL;
	openXML(__func__);
	
	if (checkToken(ENTIER)) {

		
		if (checkToken(ID_VAR)) {
			
			char *nom = malloc(1024 * sizeof(char));
			strcpy(nom, valeur);
			$ott = ott();
			if ($ott < 0)
				$dv = cree_n_dec_var(nom);
			else
				$dv = cree_n_dec_tab(nom, $ott);
			closeXML(__func__);
			return $dv;
		}
	}
	error();
	return NULL;
}

int ott(void) {

	int $ott = -1;
	openXML(__func__);
	if (checkToken(CROCHET_OUVRANT)) {

		if (checkToken(NOMBRE)) {
			$ott = atoi(valeur);
			
			if (checkToken(CROCHET_FERMANT)) {
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
	return -1;
}

n_l_dec *ldf(void) {

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
	return NULL;
}

n_dec *df(void) {

	n_dec *$df = NULL;
	n_l_dec *$lp = NULL;
	n_l_dec *$odv = NULL;
	n_instr *$ib = NULL;
	openXML(__func__);
	if (checkToken(ID_FCT)) {

		char *nom = malloc(1024 * sizeof(char));
		strcpy(nom, valeur);
		
		$lp = lp();
		$odv = odv();
		$ib = ib();
		$df = cree_n_dec_fonc(nom, $lp, $odv, $ib);
		closeXML(__func__);
		return $df;
	}
	error();
	return NULL;
}

n_l_dec *lp(void) {

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
	return NULL;
}

n_l_dec *oldv(void) {

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
	error();
	return NULL;
}

n_instr *i(void) {

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
	return NULL;
}

n_instr *iaff(void) {

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
	return NULL;
}

n_instr *ib(void) {

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
	return NULL;
}

n_l_instr *li(void) {

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
	return NULL;
}

n_instr *isi(void) {

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
	return NULL;
}

n_instr *osinon(void) {

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
	return NULL;
}

n_instr *itq(void) {

	n_instr *$itq = NULL;
	n_exp *$exp = NULL;
	n_instr *$ib = NULL;
	openXML(__func__);
	if (checkToken(TANTQUE)) {

		$exp = exp();
		if (checkToken(FAIRE)) {

			$ib = ib();

			$itq = cree_n_instr_tantque($exp, $ib);
			closeXML(__func__);
			return $itq;
		}
	}

	error();
	return NULL;
}

n_instr *ift(void) {

	n_instr *$ib = NULL;
	n_instr *$ift = NULL;
	n_exp *$exp = NULL;
	openXML(__func__);
	if (checkToken(FAIRE)) {
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
	return NULL;
}

n_instr *iapp(void) {

	n_instr *$iapp = NULL;
	n_appel *$appf = NULL;
	openXML(__func__);
	if (est_premier(_appelFct_, currentUnit)) {
		$appf = appf();
		if (checkToken(POINT_VIRGULE)) {

			$iapp = cree_n_instr_appel($appf);
			closeXML(__func__);
			return $iapp;
		}
	}
	error();
	return NULL;
}

n_instr *iret(void) {

	n_exp *$exp = NULL;
	n_instr *$iret = NULL;
	openXML(__func__);
	if (checkToken(RETOUR)) {

		$exp = exp();
		if (checkToken(POINT_VIRGULE)) {

			$iret = cree_n_instr_retour($exp);
			closeXML(__func__);
			return $iret;
		}
	}
	error();
	return NULL;
}

n_instr *iecr(void) {

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
	return NULL;
}

n_instr *ivide(void) {
	
	n_instr *$ivide = NULL;
	openXML(__func__);
	if (checkToken(POINT_VIRGULE)) {

		$ivide = cree_n_instr_vide();
		closeXML(__func__);
		return $ivide;
	}
	error();
	return NULL;
}

n_exp *exp(void) {
	n_exp *$exp = NULL;
	n_exp *$conj = NULL;
	n_exp *$expb = NULL;
	openXML(__func__);
	if (est_premier(_conjonction_, currentUnit)) {
		$conj = conj();
		$expb = expb($conj);
		
		$exp = $expb;
		closeXML(__func__);
		return $exp;
	}
	error();
	return NULL;
}

n_exp *expb(n_exp *herit) {
	
	n_exp* $expb = NULL;
	n_exp *$conj = NULL;
	n_exp *$expb2 = NULL;
	openXML(__func__);
	if (checkToken(OU)) {

		$conj = conj();
		$expb2 = expb($conj);
		$expb = cree_n_exp_op(ou, herit, $expb2);
		closeXML(__func__);
		return $expb;
	}
	if (est_suivant(_expressionBis_, currentUnit)) {
		$expb = herit;
		closeXML(__func__);
		return $expb;
	}
	error();
	return NULL;
}

n_exp *conj(void) {
	
	n_exp *$conj = NULL;
	n_exp *$comp = NULL;
	n_exp *$conjb = NULL;
	openXML(__func__);
	if (est_premier(_comparaison_, currentUnit)) {
		$comp = comp();
		$conjb = conjb($comp);
		$conj = $conjb;
		closeXML(__func__);
		return $conj;
	}
	error();
	return NULL;
}

n_exp *conjb(n_exp* herit) {
	
	n_exp *$conjb = NULL;
	n_exp *$comp = NULL;
	n_exp *$conjb2 = NULL;
	openXML(__func__);
	if (checkToken(ET)) {

		$comp = comp();
		$conjb2 = conjb($comp);
		$conjb = cree_n_exp_op(et, herit, $conjb2);
		closeXML(__func__);
		return $conjb;
	}
	if (est_suivant(_conjonctionBis_, currentUnit)) {
		$conjb = herit;
		closeXML(__func__);
		return $conjb;
	}
	error();
	return NULL;
}

n_exp *comp(void) {
	n_exp *$comp = NULL;
	n_exp *$e = NULL;
	n_exp *$compb = NULL;
	openXML(__func__);
	if (est_premier(_expArith_, currentUnit)) {
		$e = e();
		$compb = compb($e);
		$comp = $compb;
		closeXML(__func__);
		return $comp;
	}
	error();
	return NULL;
}

n_exp *compb(n_exp *herit) {
	
	n_exp *$compb = NULL;
	n_exp *$e = NULL;
	n_exp *$compb2 = NULL;
	openXML(__func__);
	if (checkToken(EGAL)) {

		$e = e();
		$compb2 = compb($e);
		$compb = cree_n_exp_op(egal, herit, $compb2);
		closeXML(__func__);
		return $compb;
	}
	if (checkToken(INFERIEUR)) {

		$e = e();
		$compb2 = compb($e);
		$compb = cree_n_exp_op(inf, herit, $compb2);
		closeXML(__func__);
		return $compb;
	}
	if (est_suivant(_comparaisonBis_, currentUnit)) {
		$compb = herit;
		closeXML(__func__);
		return $compb;
	}

	error();
	return NULL;
}

n_exp *e(void) {
	
	n_exp *$e = NULL;
	n_exp *$t = NULL;
	n_exp *$eb = NULL;
	openXML(__func__);
	if (est_premier(_terme_, currentUnit)) {
		$t = t();
		$eb = eb($t);
		$e = $eb;
		closeXML(__func__);
		return $e;
	}
	error();
	return NULL;
}

n_exp *eb(n_exp *herit) {
	
	n_exp *$eb = NULL;
	n_exp *$t = NULL;
	n_exp *$eb2 = NULL;
	openXML(__func__);
	if (checkToken(PLUS)) {

		$t = t();
		$eb2 = eb($t);
		$eb = cree_n_exp_op(plus, herit, $eb2);
		closeXML(__func__);
		return $eb;
	}
	if (checkToken(MOINS)) {

		$t = t();
		$eb2 = eb($t);
		$eb = cree_n_exp_op(moins, herit, $eb2);
		closeXML(__func__);
		return $eb;
	}
	if (est_suivant(_expArithBis_, currentUnit)) {
		
		$eb = herit;
		closeXML(__func__);
		return $eb;
	}
	error();
	return NULL;
}

n_exp *t(void) {
	
	n_exp *$t = NULL;
	n_exp *$tb = NULL;
	n_exp *$neg = NULL;
	openXML(__func__);
	if (est_premier(_negation_, currentUnit)) {
		$neg = neg();
		$tb = tb($neg);
		$t = $tb;
		closeXML(__func__);
		return $t;
	}
	error();
	return NULL;
}

n_exp *tb(n_exp *herit) {
	
	n_exp *$tb = NULL;
	n_exp *$neg = NULL;
	n_exp *$tb2 = NULL;
	openXML(__func__);
	if (checkToken(FOIS)) {

		$neg = neg();
		$tb2 = tb($neg);
		$tb = cree_n_exp_op(fois, herit, $tb2);
		closeXML(__func__);
		return $tb;
	}
	if (checkToken(DIVISE)) {

		$neg = neg();
		$tb2 = tb($neg);
		$tb = cree_n_exp_op(divise, herit, $tb2);
		closeXML(__func__);
		return $tb;
	}
	if (est_suivant(_termeBis_, currentUnit)) {
		
		$tb = herit;
		closeXML(__func__);
		return $tb;
	}
	error();
	return NULL;
}

n_exp *neg(void) {
	
	n_exp *$neg = NULL;
	n_exp *$neg2 = NULL;
	n_exp *$f = NULL;
	openXML(__func__);
	if (checkToken(NON)) {

		$neg2 = neg();
		$neg = cree_n_exp_op(non, NULL, $neg2);
		closeXML(__func__);
		return $neg;
	}
	if (est_premier(_facteur_, currentUnit)) {
		$f = f();
		$neg = $f;
		closeXML(__func__);
		return $neg;
	}
	error();
	return NULL;
}

n_exp *f(void) {
	
	n_exp *$f = NULL;
	n_exp *$exp = NULL;
	n_appel *$appf = NULL;
	n_var *$var = NULL;
	openXML(__func__);
	if (checkToken(PARENTHESE_OUVRANTE)) {

		$exp = exp();
		$f = $exp;
		if (checkToken(PARENTHESE_FERMANTE)) {

			closeXML(__func__);
			return $f;
		}
	}
	if (checkToken(NOMBRE)) {
		int entier = atoi(valeur);
		$f = cree_n_exp_entier(entier);
		closeXML(__func__);
		return $f;
	}
	if (checkToken(LIRE)) {

		if (checkToken(PARENTHESE_OUVRANTE)) {

			if (checkToken(PARENTHESE_FERMANTE)) {
				$f = cree_n_exp_lire();
				closeXML(__func__);
				return $f;
			}
		}
	}
	if (est_premier(_appelFct_, currentUnit)) {
		$appf = appf();
		$f = cree_n_exp_appel($appf);
		closeXML(__func__);
		return $f;
	}
	if (est_premier(_var_, currentUnit)) {
		$var = var();
		$f = cree_n_exp_var($var);
		closeXML(__func__);
		return $f;
	}
	error();
	return NULL;
}

n_var *var(void) {
	
	n_var *$var = NULL;
	n_exp *$oind = NULL;
	openXML(__func__);
	if (checkToken(ID_VAR)) {

		char *nom = malloc(1024 * sizeof(char));
		strcpy(nom, valeur);
		$oind = oind();
		
		if ($oind == NULL) {
			$var = cree_n_var_simple(nom);
		}
		else {
			$var = cree_n_var_indicee(nom, $oind);
		}
		closeXML(__func__);
		return $var;
	}
	error();
	return NULL;
}

n_exp *oind(void) {
	
	n_exp *$oind = NULL;
	n_exp *$exp = NULL;
	openXML(__func__);
	if (checkToken(CROCHET_OUVRANT)) {

		$exp = exp();
		$oind = $exp;
		if (checkToken(CROCHET_FERMANT)) {

			closeXML(__func__);
			return $exp;
		}
	}
	if (est_suivant(_optIndice_, currentUnit)) {
		closeXML(__func__);
		return NULL;
	}
	error();
	return NULL;
}

n_appel *appf(void) {
	
	n_appel *$appf = NULL;
	n_l_exp *$lexp = NULL;
	openXML(__func__);
	if (checkToken(ID_FCT)) {
		char *nom = malloc(1024 * sizeof(char));
		strcpy(nom, valeur);

		if (checkToken(PARENTHESE_OUVRANTE)) {

			$lexp = lexp();
			if (checkToken(PARENTHESE_FERMANTE)) {
				
				$appf = cree_n_appel(nom, $lexp);
				closeXML(__func__);
				return $appf;
			}
		}
	}
	// Je ne suis pas sur de celui la
	if (est_suivant(_appelFct_, currentUnit)) {
		closeXML(__func__);
		return NULL;
	}
	error();
	return NULL;
}

n_l_exp *lexp(void) {
	n_l_exp *$lexp = NULL;
	n_exp *$exp = NULL;
	n_l_exp *$lexpb = NULL;
	openXML(__func__);
	
	if (est_premier(_expression_, currentUnit)) {
		$exp = exp();
		$lexpb = lexpb();
		$lexp = cree_n_l_exp($exp, $lexpb);
		closeXML(__func__);
		return $lexp;
	}
	if (est_suivant(_listeExpressions_, currentUnit)) {
		closeXML(__func__);
		return NULL;
	}
	error();
	return NULL;
}

n_l_exp *lexpb(void) {
	
	n_l_exp *$lexpb = NULL;
	n_exp *$exp = NULL;
	n_l_exp *$lexpb2 = NULL;
	openXML(__func__);
	if (checkToken(VIRGULE)) {

		$exp = exp();
		$lexpb2 = lexpb();
		$lexpb = cree_n_l_exp($exp, $lexpb2);
		closeXML(__func__);
		return $lexpb;
	}
	if (est_suivant(_listeExpressionsBis_, currentUnit)) {
		closeXML(__func__);
		return NULL;
	}
	error();
	return NULL;
}

/**
 * Main function to use the synthaxic analyser.
 */
n_prog *analyse(void) {
	currentUnit = yylex();
	currentIndent = 0;

	n_prog *prog = pg();

	if (currentUnit != FIN) {
		error();
		return NULL;
	}
	else {
		return prog;
		//printf("Lexical analyse succeded\n");
	}
}
