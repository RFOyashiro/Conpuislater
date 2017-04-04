#include "analyseur_semantique.h"

void parcours_n_prog(n_prog *n);
void parcours_l_instr(n_l_instr *n);
void parcours_instr(n_instr *n);
void parcours_instr_si(n_instr *n);
void parcours_instr_tantque(n_instr *n);
void parcours_instr_affect(n_instr *n);
void parcours_instr_appel(n_instr *n);
void parcours_instr_retour(n_instr *n);
void parcours_instr_ecrire(n_instr *n);
void parcours_instr_(n_instr *n);
void parcours_l_exp(n_l_exp *n);
void parcours_exp(n_exp *n);
void parcours_varExp(n_exp *n);
void parcours_opExp(n_exp *n);
void parcours_intExp(n_exp *n);
void parcours_lireExp(n_exp *n);
void parcours_appelExp(n_exp *n);
void parcours_l_dec(n_l_dec *n);
void parcours_dec(n_dec *n);
void parcours_foncDec(n_dec *n);
void parcours_varDec(n_dec *n);
void parcours_tabDec(n_dec *n);
void parcours_var(n_var *n);
void parcours_var_simple(n_var *n);
void parcours_var_indicee(n_var *n);
void parcours_appel(n_appel *n);

int currentGlobalAdr = 0;
int indexCurrentFunc = -1;

void failSemCompil() {
	fprintf(stderr, "Fail to compile semantic part\n");
	exit(EXIT_FAILURE);
}

int nbLabel = 0;

void generateLabel() {
	printf("L%d", nbLabel);
}

void parcours_n_prog(n_prog *n) {

	parcours_l_dec(n->variables);
	//Tout Doux ?
	printf("section .text\n");
	printf("global _start\n");
	printf("_start:\n");
	printf("call _FONC_main\n");
	printf("mov eax,1\n");
	printf("int 0x80\n");
	parcours_l_dec(n->fonctions);
}

/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/

void parcours_l_instr(n_l_instr *n) {
	if (n) {
		parcours_instr(n->tete);
		parcours_l_instr(n->queue);
	}
}

/*-------------------------------------------------------------------------*/

void parcours_instr(n_instr *n) {
	if (n) {
		if (n->type == blocInst) parcours_l_instr(n->u.liste);
		else if (n->type == affecteInst) parcours_instr_affect(n);
		else if (n->type == siInst) parcours_instr_si(n);
		else if (n->type == tantqueInst) parcours_instr_tantque(n);
		else if (n->type == appelInst) parcours_instr_appel(n);
		else if (n->type == retourInst) parcours_instr_retour(n);
		else if (n->type == ecrireInst) parcours_instr_ecrire(n);
	}
}

/*-------------------------------------------------------------------------*/

void parcours_instr_si(n_instr *n) {

	parcours_exp(n->u.si_.test);
	printf("pop eax ;Recuperation resultat test\n");
	printf("cmp eax, 0 ;Si c'est faux\n");
	printf("je ");
	generateLabel(); //je vais chez L1
	printf(" ;Aller la bas\n");

	parcours_instr(n->u.si_.alors);

	printf("jmp ");
	nbLabel++;
	generateLabel(); //goat two L2
	printf(" ; Aller a la suite du si\n");
	nbLabel--;
	generateLabel(); //je suis L1
	nbLabel++;
	printf(": ;Sinon\n");

	if (n->u.si_.sinon) {
		parcours_instr(n->u.si_.sinon);
	}//2610
	generateLabel(); //it's a me L2
	printf(": ;Suite du si\n");
	nbLabel++;
}

/*-------------------------------------------------------------------------*/

void parcours_instr_tantque(n_instr *n) {

	generateLabel(); //here is L1
	int labelLoop = nbLabel;
	printf(": ;Debut de tant que\n");
	nbLabel++;

	parcours_exp(n->u.tantque_.test);

	printf("pop eax ;Recuperation resultat test\n");
	printf("cmp eax, 0 ;Si le test est faux\n");
	printf("je ");
	int labelOut = nbLabel;
	generateLabel(); //go to L2
	nbLabel++;
	printf(" ;Aller a la suite du tant que\n");

	parcours_instr(n->u.tantque_.faire);

	int labelBU = nbLabel;
	nbLabel = labelLoop;
	printf("jmp ");
	generateLabel(); //go to L1
	printf(" ;Retour debut de tant que\n");
	nbLabel = labelOut;
	generateLabel(); //here is L2
	printf(": ;Suite du tant que\n");
	nbLabel = labelBU;
}

/*-------------------------------------------------------------------------*/

void parcours_instr_affect(n_instr *n) {

	parcours_var(n->u.affecte_.var);
	
	printf("pop ebx ;On ignore la valeur de la variable car on fait une affectation\n");
	
	parcours_exp(n->u.affecte_.exp);

	int i = rechercheExecutable(n->u.affecte_.var->nom);
	desc_identif var = tabsymboles.tab[i];

	if (var.type == T_ENTIER) {

		printf("pop eax ;On recupere la resultat de l'expression\n");
		
		if (var.portee == P_VARIABLE_GLOBALE) {
			printf("mov [%s], eax ;Affectation variable globale\n", var.identif);
		}
		else if (var.portee == P_ARGUMENT) {
			int nbArgs = tabsymboles.tab[indexCurrentFunc].complement;
			printf("mov  [ebp + %i], eax ;Affectation argument\n", (4 + 4 * nbArgs - var.adresse));
		}
		else {

			printf("mov [ebp - %i], eax ;Affectation variable locale\n", 4 + var.adresse);
		}
	}
	else {
		
	    // Push index value
	    parcours_exp(n->u.affecte_.var->u.indicee_.indice);
		//Calcule adresse tableau
		printf("pop ecx ;On recupere l'indice\n");
		printf("pop eax ;On recupere la resultat de l'expression\n");
		printf("mov [%s + ecx * 4], eax ;Et on met le resultat de l'expression dans le tableau\n", var.identif);
	}
}

/*-------------------------------------------------------------------------*/

void parcours_instr_appel(n_instr *n) {
	parcours_appel(n->u.appel);
	printf("add esp, 4 ;Si c'est un simple appel on ignore la valeur de retour\n");
}

/*-------------------------------------------------------------------------*/

int countCallArgs(n_appel *n) {
	int i = 0;
	n_l_exp *currentArg = n->args;
	while (currentArg) {
		++i;
		currentArg = currentArg->queue;
	}
	return i;
}

void parcours_appel(n_appel *n) {

	int i = rechercheExecutable(n->fonction);
	//name do not exist in this scope
	if (i == -1) {
		fprintf(stderr, "Function %s hasn't been declared\n", n->fonction);
		failSemCompil();
	}
	if (tabsymboles.tab[i].complement != countCallArgs(n)) {
		fprintf(stderr, "Function %s is called without enough arguments\n", n->fonction);
		failSemCompil();
	}
	printf("sub esp, 4 ;Reservation espace valeur de retour\n");
	parcours_l_exp(n->args);
	printf("call _FONC_%s ;Appel de la fonction\n", n->fonction);
	int args = countCallArgs(n);
	printf("add esp, %i ;Liberation de l'espace des arguments\n", args * 4);
}

/*-------------------------------------------------------------------------*/

void parcours_instr_retour(n_instr *n) {

	int params = tabsymboles.tab[indexCurrentFunc].complement;

	parcours_exp(n->u.retour_.expression);

	printf("pop eax ;Recuperation resultat expression retour\n");
	printf("mov [ebp + %i], eax ;Passage de valeur de retour\n", 8 + (params * 4));
	printf("add esp, %i ;Liberation variables locales\n", adresseLocaleCourante);
	printf("pop ebp ;Restauration ebp\n");
	printf("ret ;Return\n");
}

/*-------------------------------------------------------------------------*/

void parcours_instr_ecrire(n_instr *n) {

	parcours_exp(n->u.ecrire_.expression);

	printf("pop eax ;Recuperation resultat expression ecrire\n");
	printf("call iprintLF ;Appel a ecrire\n");

}

/*-------------------------------------------------------------------------*/

void parcours_l_exp(n_l_exp *n) {

	if (n) {
		parcours_exp(n->tete);
		parcours_l_exp(n->queue);
	}
}

/*-------------------------------------------------------------------------*/

void parcours_exp(n_exp *n) {

	if (n->type == varExp) parcours_varExp(n);
	else if (n->type == opExp) parcours_opExp(n);
	else if (n->type == intExp) parcours_intExp(n);
	else if (n->type == appelExp) parcours_appelExp(n);
	else if (n->type == lireExp) parcours_lireExp(n);
}

/*-------------------------------------------------------------------------*/

void parcours_varExp(n_exp *n) {
	parcours_var(n->u.var);
}

/*-------------------------------------------------------------------------*/
void parcours_opExp(n_exp *n) {

	/*if (n->u.opExp_.op == plus);
	else if (n->u.opExp_.op == moins);
	else if (n->u.opExp_.op == fois);
	else if (n->u.opExp_.op == divise);
	else if (n->u.opExp_.op == egal);
	else if (n->u.opExp_.op == diff);
	else if (n->u.opExp_.op == inf);
	else if (n->u.opExp_.op == infeg);
	else if (n->u.opExp_.op == ou);
	else if (n->u.opExp_.op == et);
	else if (n->u.opExp_.op == non);*/
	if (n->u.opExp_.op1 != NULL) {
		parcours_exp(n->u.opExp_.op1);
	}
	if (n->u.opExp_.op2 != NULL) {
		parcours_exp(n->u.opExp_.op2);
		printf("pop ebx ;Recuperation 2e operandes\n");
	}
	printf("pop eax ;Recuperation 1e operande\n");
	switch (n->u.opExp_.op) {
		case plus:
			printf("add eax, ebx ;Additino op1 += op2\n");
			break;
		case fois:
			printf("mul ebx ;Multiplicatino op1 *= op2\n");
			break;
		case moins:
			printf("sub eax, ebx ;Soustractino op1 -= op2\n");
			break;
		case divise:
			printf("mov edx, 0 ;Reinitialisatino edx\n");
			printf("div ebx ;Divisino op1 /= op2\n");
			break;
		case modulo:
			printf("mov edx, 0 ;Reinitialisatino edx\n");
			printf("div ebx ;Divisino op1 /= op2\n");
			printf("mov eax, edx ;Reste\n");
			break;
		case inf:
			printf("cmp eax, ebx ;Si op1 < op2\n");
			printf("jl ");
			generateLabel(); //go to L1
			printf(" ;Aller mettre 1\n");
			printf("mov eax, 0 ;Mettre 0\n");
			printf("jmp ");
			nbLabel++;
			generateLabel(); //2L ot og
			printf(" ;Aller envoyer resultat\n");
			nbLabel--;
			generateLabel(); //here is L1
			nbLabel++;
			printf(":\nmov eax, 1 ;Mettre 1\n");
			generateLabel(); //2L si ereh
			nbLabel++;
			printf(": ;Envoyer resultat\n");
			break;
		case et:
			printf("mul ebx ;Multiplication du ET\n");
			printf("cmp eax, 0 ;Si ca vaut 0, au moins l'un des deux est faux\n");
			printf("jne ");
			generateLabel(); //go to L1
			printf(" ;Donc si ca vaut pas 0 aller mettre vrai\n");
			printf("mov eax, 0 ;Mettre faux\n");
			printf("jmp ");
			nbLabel++;
			generateLabel(); //e ikimasu L2
			printf(" ;Aller envoyer\n");
			nbLabel--;
			generateLabel(); //here is L1
			nbLabel++;
			printf(":\nmov eax, 1 ;Mettre vrai\n");
			generateLabel(); //watashi wa L2
			nbLabel++;
			printf(": ;Envoyer\n");
			break;
		case ou:
			printf("cmp eax, 0 ;OU\n");
			printf("jne ");
			generateLabel(); //go to L1
			printf("\n");
			printf("cmp ebx, 0\n");
			printf("jne ");
			generateLabel(); //go to L1
			printf("\n");
			printf("mov eax, 0\n");
			printf("jmp ");
			nbLabel++;
			generateLabel(); //go to L2
			printf("\n");
			nbLabel--;
			generateLabel(); //here is L1
			printf(":\nmov eax, 1\n");
			nbLabel++;
			generateLabel(); //here is L2
			nbLabel++;
			printf(":\n");
			break;
		case egal:
			printf("cmp eax, ebx ;EGAL\n");
			printf("je ");
			generateLabel(); //got you L1
			nbLabel++;
			printf("\n");
			printf("mov eax, 0\n");
			printf("jmp ");
			generateLabel(); //go to L2
			nbLabel--;
			printf("\n");
			generateLabel(); // i am L1
			nbLabel++;
			printf(":\nmov eax, 1\n");
			generateLabel(); // i am L2
			printf(":\n");
			nbLabel++;
			break;
		case non:
		    printf("cmp eax, 0 ;NON\n");
			printf("je ");
			generateLabel(); //got you L1
			nbLabel++;
			printf("\n");
			printf("mov eax, 0\n");
			printf("jmp ");
			generateLabel(); //go to L2
			nbLabel--;
			printf("\n");
			generateLabel(); // i am L1
			nbLabel++;
			printf(":\nmov eax, 1\n");
			generateLabel(); // i am L2
			printf(":\n");
			nbLabel++;
			break;
		default:
		    fprintf(stderr, "operation %i not supported\n", n->u.opExp_.op);
		    failSemCompil();
		    break;
	}
	printf("push eax ;Envoie resultat\n");
}

/*-------------------------------------------------------------------------*/

void parcours_intExp(n_exp *n) {
	printf("push %d ;Expression d'un entier\n", n->u.entier);
}

/*-------------------------------------------------------------------------*/
void parcours_lireExp(n_exp *n) {
	printf("mov eax, sinput ;Preparation a lire\n");
	printf("call readline ;Appel lire\n");
	printf("call atoi ;Transformation en entier\n");
	printf("push eax ;Envoie resultat expression lire\n");
}

/*-------------------------------------------------------------------------*/

void parcours_appelExp(n_exp *n) {
	parcours_appel(n->u.appel);
}

/*-------------------------------------------------------------------------*/

void parcours_l_dec(n_l_dec *n) {

	if (n) {
		parcours_dec(n->tete);
		parcours_l_dec(n->queue);
	}
}

int countParamDec(n_l_dec *n) {
	int params = 0;
	n_l_dec *nTemp = n;
	while (nTemp) {
		nTemp = nTemp->queue;
		params++;
	}
	return params;
}

/*-------------------------------------------------------------------------*/

void parcours_dec(n_dec *n) {

	if (n) {
		if (n->type == foncDec) {
			parcours_foncDec(n);
		}
		else if (n->type == varDec) {
			parcours_varDec(n);
		}
		else if (n->type == tabDec) {
			parcours_tabDec(n);
		}
	}
}

/*-------------------------------------------------------------------------*/

void parcours_foncDec(n_dec *n) {

	indexCurrentFunc = rechercheDeclarative(n->nom);

	if (indexCurrentFunc != -1) {
		fprintf(stderr, "Function %s is already declared\n", n->nom);
		failSemCompil();
	}
	int params = countParamDec(n->u.foncDec_.param);	
	
	ajouteIdentificateur(n->nom, portee, T_FONCTION,
			0, params);
	
	indexCurrentFunc = rechercheDeclarative(n->nom);

	currentGlobalAdr = adresseLocaleCourante;
	adresseLocaleCourante = 0;

	entreeFonction();
	int porteeBackUp = portee;

	portee = P_ARGUMENT;
	parcours_l_dec(n->u.foncDec_.param);
	portee = porteeBackUp;

	adresseLocaleCourante = 0;
	currentGlobalAdr = adresseLocaleCourante;


	printf("\n_FONC_%s: ;Declaration de fonction\n", n->nom);
	printf("push ebp ;Sauvegarde ebp\n");
	printf("mov ebp, esp ;On se place en haut de la pile\n");

	parcours_l_dec(n->u.foncDec_.variables);
	parcours_instr(n->u.foncDec_.corps);

	if (DEBUG_SEM) {
		afficheTabsymboles();
	}

	printf("add esp, %i\n", adresseLocaleCourante);
	printf("pop ebp\n");
	printf("ret\n");

	sortieFonction();
	adresseLocaleCourante = currentGlobalAdr;
}

/*-------------------------------------------------------------------------*/

void parcours_varDec(n_dec *n) {
	if (rechercheDeclarative(n->nom) != -1) {
		fprintf(stderr, "Var %s is already declared\n", n->nom);
		failSemCompil();
	}

	ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseLocaleCourante, 0);
	adresseLocaleCourante += 4;

	if (portee == P_VARIABLE_GLOBALE) {
		printf("%s resd 1 ;Declaration d'une variable globale\n", n->nom);
	}
	else if (portee == P_ARGUMENT) {
		// Nothing to do
	}
	else {
		printf("sub esp, 4 ;Reservation d'une variable locale\n");
	}
}

/*-------------------------------------------------------------------------*/

void parcours_tabDec(n_dec *n) {

	if (portee != P_VARIABLE_GLOBALE) {
		fprintf(stderr, "Array %s is declared as an array but not in global scope\n", n->nom);
		failSemCompil();
	}

	//name already used in this scope
	if (rechercheDeclarative(n->nom) != -1) {
		fprintf(stderr, "Array %s is already declared\n", n->nom);
		failSemCompil();
	}
	ajouteIdentificateur(n->nom, portee, T_TABLEAU_ENTIER, adresseLocaleCourante,
			n->u.tabDec_.taille);
	adresseLocaleCourante += n->u.tabDec_.taille * 4;
	printf("%s resd %i ;Declaration d'un tableau global\n", n->nom, n->u.tabDec_.taille * 4);
}

/*-------------------------------------------------------------------------*/

void parcours_var(n_var *n) {
	if (n->type == simple) {
		parcours_var_simple(n);
	}
	else if (n->type == indicee) {
		parcours_var_indicee(n);
	}
}

/*-------------------------------------------------------------------------*/
void parcours_var_simple(n_var *n) {
	int i = rechercheExecutable(n->nom);
	//name do not exist in this scope
	if (i == -1) {
		fprintf(stderr, "Var %s hasn't been declared\n", n->nom);
		failSemCompil();
	}
	//int having index
	if (tabsymboles.tab[i].complement != 0) {
		fprintf(stderr, "Var %s is a simple var but is used as array\n", n->nom);
		failSemCompil();
	}

	if (tabsymboles.tab[i].portee == P_VARIABLE_GLOBALE) {
		printf("push dword[%s] ;Envoie variable globale\n", n->nom);
	}
	else if (tabsymboles.tab[i].portee == P_ARGUMENT) {
		int nbArgs = tabsymboles.tab[indexCurrentFunc].complement;
		printf("mov eax, [ebp + %i] ;Recuperation argument\n", (4 + 4 * nbArgs - tabsymboles.tab[i].adresse));
		printf("push eax ;Envoie argument\n");
	}
	else {

		printf("mov eax, [ebp - %i] ;Recuperation variable locale\n", 4 + tabsymboles.tab[i].adresse);
		printf("push eax ;Envoie variable locale\n");
	}

}

void parcours_var_indicee(n_var *n) {
	int i = rechercheExecutable(n->nom);
	//name do not exist in this scope
	if (i == -1) {
		fprintf(stderr, "Array %s hasn't been declared\n", n->nom);
		failSemCompil();
	}
	//tab not having index
	if (tabsymboles.tab[i].complement == 0) {

		fprintf(stderr, "Array %s is an array but no index used when called\n", n->nom);
		failSemCompil();
	}

	printf(";parcour var indicee\n");
	// Push de l'indice entre corchets
	parcours_exp(n->u.indicee_.indice);
	printf("pop eax ;Recuperation de l'indice\n");
	printf("mov ebx, [%s + eax * 4] ;Recuperation de la valeur de la case\n", n->nom);
	printf("push ebx ;Envoie de la valeur de la case\n");
}

void analyseSemantique(n_prog *pg) {

	printf("%%include \"io.asm\"\n");
	printf("section .bss\n");
	printf("sinput resb 255\n");
	portee = P_VARIABLE_GLOBALE;
	adresseLocaleCourante = 0;
	adresseArgumentCourant = 0;

	parcours_n_prog(pg);

	int indiceMain = rechercheDeclarative("main");
	if (indiceMain == -1) {
		fprintf(stderr, "No main found\n");
				failSemCompil();
	}
	if (tabsymboles.tab[indiceMain].complement > 0) {
		fprintf(stderr, "Too much arguments\n");
				failSemCompil();
	}
}
