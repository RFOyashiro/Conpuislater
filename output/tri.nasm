%include "io.asm"
section .bss
sinput resb 255
$tab resd 40 ;Declaration d'un tableau global
section .text
global _start
_start:
call _FONC_main
mov eax,1
int 0x80

_FONC_initialiser: ;Declaration de fonction
push ebp ;Sauvegarde ebp
mov ebp, esp ;On se place en haut de la pile
;parcour var indicee
push 0 ;Expression d'un entier
pop eax ;Recuperation de l'indice
mov ebx, [$tab + eax * 4] ;Recuperation de la valeur de la case
push ebx ;Envoie de la valeur de la case
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push 8 ;Expression d'un entier
push 0 ;Expression d'un entier
pop ecx ;On recupere l'indice
pop eax ;On recupere la resultat de l'expression
mov [$tab + ecx * 4], eax ;Et on met le resultat de l'expression dans le tableau
;parcour var indicee
push 1 ;Expression d'un entier
pop eax ;Recuperation de l'indice
mov ebx, [$tab + eax * 4] ;Recuperation de la valeur de la case
push ebx ;Envoie de la valeur de la case
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push 6 ;Expression d'un entier
push 1 ;Expression d'un entier
pop ecx ;On recupere l'indice
pop eax ;On recupere la resultat de l'expression
mov [$tab + ecx * 4], eax ;Et on met le resultat de l'expression dans le tableau
;parcour var indicee
push 2 ;Expression d'un entier
pop eax ;Recuperation de l'indice
mov ebx, [$tab + eax * 4] ;Recuperation de la valeur de la case
push ebx ;Envoie de la valeur de la case
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push 9 ;Expression d'un entier
push 2 ;Expression d'un entier
pop ecx ;On recupere l'indice
pop eax ;On recupere la resultat de l'expression
mov [$tab + ecx * 4], eax ;Et on met le resultat de l'expression dans le tableau
;parcour var indicee
push 3 ;Expression d'un entier
pop eax ;Recuperation de l'indice
mov ebx, [$tab + eax * 4] ;Recuperation de la valeur de la case
push ebx ;Envoie de la valeur de la case
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push 9 ;Expression d'un entier
push 3 ;Expression d'un entier
pop ecx ;On recupere l'indice
pop eax ;On recupere la resultat de l'expression
mov [$tab + ecx * 4], eax ;Et on met le resultat de l'expression dans le tableau
;parcour var indicee
push 4 ;Expression d'un entier
pop eax ;Recuperation de l'indice
mov ebx, [$tab + eax * 4] ;Recuperation de la valeur de la case
push ebx ;Envoie de la valeur de la case
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push 4 ;Expression d'un entier
push 4 ;Expression d'un entier
pop ecx ;On recupere l'indice
pop eax ;On recupere la resultat de l'expression
mov [$tab + ecx * 4], eax ;Et on met le resultat de l'expression dans le tableau
;parcour var indicee
push 5 ;Expression d'un entier
pop eax ;Recuperation de l'indice
mov ebx, [$tab + eax * 4] ;Recuperation de la valeur de la case
push ebx ;Envoie de la valeur de la case
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push 2 ;Expression d'un entier
push 5 ;Expression d'un entier
pop ecx ;On recupere l'indice
pop eax ;On recupere la resultat de l'expression
mov [$tab + ecx * 4], eax ;Et on met le resultat de l'expression dans le tableau
;parcour var indicee
push 6 ;Expression d'un entier
pop eax ;Recuperation de l'indice
mov ebx, [$tab + eax * 4] ;Recuperation de la valeur de la case
push ebx ;Envoie de la valeur de la case
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push 3 ;Expression d'un entier
push 6 ;Expression d'un entier
pop ecx ;On recupere l'indice
pop eax ;On recupere la resultat de l'expression
mov [$tab + ecx * 4], eax ;Et on met le resultat de l'expression dans le tableau
;parcour var indicee
push 7 ;Expression d'un entier
pop eax ;Recuperation de l'indice
mov ebx, [$tab + eax * 4] ;Recuperation de la valeur de la case
push ebx ;Envoie de la valeur de la case
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push 1 ;Expression d'un entier
push 7 ;Expression d'un entier
pop ecx ;On recupere l'indice
pop eax ;On recupere la resultat de l'expression
mov [$tab + ecx * 4], eax ;Et on met le resultat de l'expression dans le tableau
;parcour var indicee
push 8 ;Expression d'un entier
pop eax ;Recuperation de l'indice
mov ebx, [$tab + eax * 4] ;Recuperation de la valeur de la case
push ebx ;Envoie de la valeur de la case
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push 4 ;Expression d'un entier
push 8 ;Expression d'un entier
pop ecx ;On recupere l'indice
pop eax ;On recupere la resultat de l'expression
mov [$tab + ecx * 4], eax ;Et on met le resultat de l'expression dans le tableau
;parcour var indicee
push 9 ;Expression d'un entier
pop eax ;Recuperation de l'indice
mov ebx, [$tab + eax * 4] ;Recuperation de la valeur de la case
push ebx ;Envoie de la valeur de la case
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push 5 ;Expression d'un entier
push 9 ;Expression d'un entier
pop ecx ;On recupere l'indice
pop eax ;On recupere la resultat de l'expression
mov [$tab + ecx * 4], eax ;Et on met le resultat de l'expression dans le tableau
add esp, 0
pop ebp
ret

_FONC_afficher: ;Declaration de fonction
push ebp ;Sauvegarde ebp
mov ebp, esp ;On se place en haut de la pile
sub esp, 4 ;Reservation d'une variable locale
mov eax, [ebp - 4] ;Recuperation variable locale
push eax ;Envoie variable locale
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push 0 ;Expression d'un entier
pop eax ;On recupere la resultat de l'expression
mov [ebp - 4], eax ;Affectation variable locale
L0: ;Debut de tant que
mov eax, [ebp - 4] ;Recuperation variable locale
push eax ;Envoie variable locale
mov eax, [ebp + 8] ;Recuperation argument
push eax ;Envoie argument
pop ebx ;Recuperation 2e operandes
pop eax ;Recuperation 1e operande
cmp eax, ebx ;Si op1 < op2
jl L1 ;Aller mettre 1
mov eax, 0 ;Mettre 0
jmp L2 ;Aller envoyer resultat
L1:
mov eax, 1 ;Mettre 1
L2: ;Envoyer resultat
push eax ;Envoie resultat
pop eax ;Recuperation resultat test
cmp eax, 0 ;Si le test est faux
je L3 ;Aller a la suite du tant que
;parcour var indicee
mov eax, [ebp - 4] ;Recuperation variable locale
push eax ;Envoie variable locale
pop eax ;Recuperation de l'indice
mov ebx, [$tab + eax * 4] ;Recuperation de la valeur de la case
push ebx ;Envoie de la valeur de la case
pop eax ;Recuperation resultat expression ecrire
call iprintLF ;Appel a ecrire
mov eax, [ebp - 4] ;Recuperation variable locale
push eax ;Envoie variable locale
pop ebx ;On ignore la valeur de la variable car on fait une affectation
mov eax, [ebp - 4] ;Recuperation variable locale
push eax ;Envoie variable locale
push 1 ;Expression d'un entier
pop ebx ;Recuperation 2e operandes
pop eax ;Recuperation 1e operande
add eax, ebx ;Ajout op1 += op2
push eax ;Envoie resultat
pop eax ;On recupere la resultat de l'expression
mov [ebp - 4], eax ;Affectation variable locale
jmp L0 ;Retour debut de tant que
L3: ;Suite du tant que
push 0 ;Expression d'un entier
pop eax ;Recuperation resultat expression ecrire
call iprintLF ;Appel a ecrire
add esp, 4
pop ebp
ret

_FONC_echanger: ;Declaration de fonction
push ebp ;Sauvegarde ebp
mov ebp, esp ;On se place en haut de la pile
sub esp, 4 ;Reservation d'une variable locale
mov eax, [ebp - 4] ;Recuperation variable locale
push eax ;Envoie variable locale
pop ebx ;On ignore la valeur de la variable car on fait une affectation
;parcour var indicee
mov eax, [ebp + 8] ;Recuperation argument
push eax ;Envoie argument
pop eax ;Recuperation de l'indice
mov ebx, [$tab + eax * 4] ;Recuperation de la valeur de la case
push ebx ;Envoie de la valeur de la case
pop eax ;On recupere la resultat de l'expression
mov [ebp - 4], eax ;Affectation variable locale
;parcour var indicee
mov eax, [ebp + 8] ;Recuperation argument
push eax ;Envoie argument
pop eax ;Recuperation de l'indice
mov ebx, [$tab + eax * 4] ;Recuperation de la valeur de la case
push ebx ;Envoie de la valeur de la case
pop ebx ;On ignore la valeur de la variable car on fait une affectation
;parcour var indicee
mov eax, [ebp + 12] ;Recuperation argument
push eax ;Envoie argument
pop eax ;Recuperation de l'indice
mov ebx, [$tab + eax * 4] ;Recuperation de la valeur de la case
push ebx ;Envoie de la valeur de la case
mov eax, [ebp + 8] ;Recuperation argument
push eax ;Envoie argument
pop ecx ;On recupere l'indice
pop eax ;On recupere la resultat de l'expression
mov [$tab + ecx * 4], eax ;Et on met le resultat de l'expression dans le tableau
;parcour var indicee
mov eax, [ebp + 12] ;Recuperation argument
push eax ;Envoie argument
pop eax ;Recuperation de l'indice
mov ebx, [$tab + eax * 4] ;Recuperation de la valeur de la case
push ebx ;Envoie de la valeur de la case
pop ebx ;On ignore la valeur de la variable car on fait une affectation
mov eax, [ebp - 4] ;Recuperation variable locale
push eax ;Envoie variable locale
mov eax, [ebp + 12] ;Recuperation argument
push eax ;Envoie argument
pop ecx ;On recupere l'indice
pop eax ;On recupere la resultat de l'expression
mov [$tab + ecx * 4], eax ;Et on met le resultat de l'expression dans le tableau
add esp, 4
pop ebp
ret

_FONC_trier: ;Declaration de fonction
push ebp ;Sauvegarde ebp
mov ebp, esp ;On se place en haut de la pile
sub esp, 4 ;Reservation d'une variable locale
sub esp, 4 ;Reservation d'une variable locale
sub esp, 4 ;Reservation d'une variable locale
mov eax, [ebp - 12] ;Recuperation variable locale
push eax ;Envoie variable locale
pop ebx ;On ignore la valeur de la variable car on fait une affectation
mov eax, [ebp + 8] ;Recuperation argument
push eax ;Envoie argument
pop eax ;On recupere la resultat de l'expression
mov [ebp - 12], eax ;Affectation variable locale
mov eax, [ebp - 4] ;Recuperation variable locale
push eax ;Envoie variable locale
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push 1 ;Expression d'un entier
pop eax ;On recupere la resultat de l'expression
mov [ebp - 4], eax ;Affectation variable locale
L4: ;Debut de tant que
mov eax, [ebp - 4] ;Recuperation variable locale
push eax ;Envoie variable locale
push 1 ;Expression d'un entier
pop ebx ;Recuperation 2e operandes
pop eax ;Recuperation 1e operande
cmp eax, ebx ;EGAL
je L5
mov eax, 0
jmp L6
L5:
mov eax, 1
L6:
push eax ;Envoie resultat
pop eax ;Recuperation resultat test
cmp eax, 0 ;Si le test est faux
je L7 ;Aller a la suite du tant que
mov eax, [ebp - 4] ;Recuperation variable locale
push eax ;Envoie variable locale
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push 0 ;Expression d'un entier
pop eax ;On recupere la resultat de l'expression
mov [ebp - 4], eax ;Affectation variable locale
mov eax, [ebp - 8] ;Recuperation variable locale
push eax ;Envoie variable locale
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push 0 ;Expression d'un entier
pop eax ;On recupere la resultat de l'expression
mov [ebp - 8], eax ;Affectation variable locale
L8: ;Debut de tant que
mov eax, [ebp - 8] ;Recuperation variable locale
push eax ;Envoie variable locale
mov eax, [ebp - 12] ;Recuperation variable locale
push eax ;Envoie variable locale
push 1 ;Expression d'un entier
pop ebx ;Recuperation 2e operandes
pop eax ;Recuperation 1e operande
sub eax, ebx ;Soustractino op1 -= op2
push eax ;Envoie resultat
pop ebx ;Recuperation 2e operandes
pop eax ;Recuperation 1e operande
cmp eax, ebx ;Si op1 < op2
jl L9 ;Aller mettre 1
mov eax, 0 ;Mettre 0
jmp L10 ;Aller envoyer resultat
L9:
mov eax, 1 ;Mettre 1
L10: ;Envoyer resultat
push eax ;Envoie resultat
pop eax ;Recuperation resultat test
cmp eax, 0 ;Si le test est faux
je L11 ;Aller a la suite du tant que
;parcour var indicee
mov eax, [ebp - 8] ;Recuperation variable locale
push eax ;Envoie variable locale
push 1 ;Expression d'un entier
pop ebx ;Recuperation 2e operandes
pop eax ;Recuperation 1e operande
add eax, ebx ;Ajout op1 += op2
push eax ;Envoie resultat
pop eax ;Recuperation de l'indice
mov ebx, [$tab + eax * 4] ;Recuperation de la valeur de la case
push ebx ;Envoie de la valeur de la case
;parcour var indicee
mov eax, [ebp - 8] ;Recuperation variable locale
push eax ;Envoie variable locale
pop eax ;Recuperation de l'indice
mov ebx, [$tab + eax * 4] ;Recuperation de la valeur de la case
push ebx ;Envoie de la valeur de la case
pop ebx ;Recuperation 2e operandes
pop eax ;Recuperation 1e operande
cmp eax, ebx ;Si op1 < op2
jl L12 ;Aller mettre 1
mov eax, 0 ;Mettre 0
jmp L13 ;Aller envoyer resultat
L12:
mov eax, 1 ;Mettre 1
L13: ;Envoyer resultat
push eax ;Envoie resultat
pop eax ;Recuperation resultat test
cmp eax, 0 ;Si c'est faux
je L14 ;Aller la bas
sub esp, 4 ;Reservation espace valeur de retour
mov eax, [ebp - 8] ;Recuperation variable locale
push eax ;Envoie variable locale
mov eax, [ebp - 8] ;Recuperation variable locale
push eax ;Envoie variable locale
push 1 ;Expression d'un entier
pop ebx ;Recuperation 2e operandes
pop eax ;Recuperation 1e operande
add eax, ebx ;Ajout op1 += op2
push eax ;Envoie resultat
call _FONC_echanger ;Appel de la fonction
add esp, 8 ;Liberation de l'espace des arguments
add esp, 4 ;Si c'est un simple appel on ignore la valeur de retour
mov eax, [ebp - 4] ;Recuperation variable locale
push eax ;Envoie variable locale
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push 1 ;Expression d'un entier
pop eax ;On recupere la resultat de l'expression
mov [ebp - 4], eax ;Affectation variable locale
jmp L15 ; Aller a la suite du si
L14: ;Sinon
L15: ;Suite du si
mov eax, [ebp - 8] ;Recuperation variable locale
push eax ;Envoie variable locale
pop ebx ;On ignore la valeur de la variable car on fait une affectation
mov eax, [ebp - 8] ;Recuperation variable locale
push eax ;Envoie variable locale
push 1 ;Expression d'un entier
pop ebx ;Recuperation 2e operandes
pop eax ;Recuperation 1e operande
add eax, ebx ;Ajout op1 += op2
push eax ;Envoie resultat
pop eax ;On recupere la resultat de l'expression
mov [ebp - 8], eax ;Affectation variable locale
jmp L8 ;Retour debut de tant que
L11: ;Suite du tant que
mov eax, [ebp - 12] ;Recuperation variable locale
push eax ;Envoie variable locale
pop ebx ;On ignore la valeur de la variable car on fait une affectation
mov eax, [ebp - 12] ;Recuperation variable locale
push eax ;Envoie variable locale
push 1 ;Expression d'un entier
pop ebx ;Recuperation 2e operandes
pop eax ;Recuperation 1e operande
sub eax, ebx ;Soustractino op1 -= op2
push eax ;Envoie resultat
pop eax ;On recupere la resultat de l'expression
mov [ebp - 12], eax ;Affectation variable locale
jmp L4 ;Retour debut de tant que
L7: ;Suite du tant que
add esp, 12
pop ebp
ret

_FONC_main: ;Declaration de fonction
push ebp ;Sauvegarde ebp
mov ebp, esp ;On se place en haut de la pile
sub esp, 4 ;Reservation espace valeur de retour
call _FONC_initialiser ;Appel de la fonction
add esp, 0 ;Liberation de l'espace des arguments
add esp, 4 ;Si c'est un simple appel on ignore la valeur de retour
sub esp, 4 ;Reservation espace valeur de retour
push 10 ;Expression d'un entier
call _FONC_afficher ;Appel de la fonction
add esp, 4 ;Liberation de l'espace des arguments
add esp, 4 ;Si c'est un simple appel on ignore la valeur de retour
sub esp, 4 ;Reservation espace valeur de retour
push 10 ;Expression d'un entier
call _FONC_trier ;Appel de la fonction
add esp, 4 ;Liberation de l'espace des arguments
add esp, 4 ;Si c'est un simple appel on ignore la valeur de retour
sub esp, 4 ;Reservation espace valeur de retour
push 10 ;Expression d'un entier
call _FONC_afficher ;Appel de la fonction
add esp, 4 ;Liberation de l'espace des arguments
add esp, 4 ;Si c'est un simple appel on ignore la valeur de retour
add esp, 0
pop ebp
ret
