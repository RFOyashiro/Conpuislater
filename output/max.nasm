%include "io.asm"
section .bss
sinput resb 255
section .text
global _start
_start:
call _FONC_main
mov eax,1
int 0x80

_FONC_max: ;Declaration de fonction
push ebp ;Sauvegarde ebp
mov ebp, esp ;On se place en haut de la pile
mov eax, [ebp + 12] ;Recuperation argument
push eax ;Envoie argument
mov eax, [ebp + 8] ;Recuperation argument
push eax ;Envoie argument
pop ebx ;Recuperation 2e operandes
pop eax ;Recuperation 1e operande
cmp eax, ebx ;Si op1 < op2
jl L0 ;Aller mettre 1
mov eax, 0 ;Mettre 0
jmp L1 ;Aller envoyer resultat
L0:
mov eax, 1 ;Mettre 1
L1: ;Envoyer resultat
push eax ;Envoie resultat
pop eax ;Recuperation resultat test
cmp eax, 0 ;Si c'est faux
je L2 ;Aller la bas
mov eax, [ebp + 8] ;Recuperation argument
push eax ;Envoie argument
pop eax ;Recuperation resultat expression retour
mov [ebp + 16], eax ;Passage de valeur de retour
add esp, 0 ;Liberation variables locales
pop ebp ;Restauration ebp
ret ;Return
jmp L3 ; Aller a la suite du si
L2: ;Sinon
L3: ;Suite du si
mov eax, [ebp + 12] ;Recuperation argument
push eax ;Envoie argument
pop eax ;Recuperation resultat expression retour
mov [ebp + 16], eax ;Passage de valeur de retour
add esp, 0 ;Liberation variables locales
pop ebp ;Restauration ebp
ret ;Return
add esp, 0
pop ebp
ret

_FONC_main: ;Declaration de fonction
push ebp ;Sauvegarde ebp
mov ebp, esp ;On se place en haut de la pile
sub esp, 4 ;Reservation d'une variable locale
sub esp, 4 ;Reservation d'une variable locale
mov eax, [ebp - 4] ;Recuperation variable locale
push eax ;Envoie variable locale
pop ebx ;On ignore la valeur de la variable car on fait une affectation
mov eax, sinput ;Preparation a lire
call readline ;Appel lire
call atoi ;Transformation en entier
push eax ;Envoie resultat expression lire
pop eax ;On recupere la resultat de l'expression
mov [ebp - 4], eax ;Affectation variable locale
mov eax, [ebp - 8] ;Recuperation variable locale
push eax ;Envoie variable locale
pop ebx ;On ignore la valeur de la variable car on fait une affectation
mov eax, sinput ;Preparation a lire
call readline ;Appel lire
call atoi ;Transformation en entier
push eax ;Envoie resultat expression lire
pop eax ;On recupere la resultat de l'expression
mov [ebp - 8], eax ;Affectation variable locale
sub esp, 4 ;Reservation espace valeur de retour
mov eax, [ebp - 4] ;Recuperation variable locale
push eax ;Envoie variable locale
mov eax, [ebp - 8] ;Recuperation variable locale
push eax ;Envoie variable locale
call _FONC_max ;Appel de la fonction
add esp, 8 ;Liberation de l'espace des arguments
mov eax, [ebp - 4] ;Recuperation variable locale
push eax ;Envoie variable locale
pop ebx ;Recuperation 2e operandes
pop eax ;Recuperation 1e operande
cmp eax, ebx ;EGAL
je L4
mov eax, 0
jmp L5
L4:
mov eax, 1
L5:
push eax ;Envoie resultat
pop eax ;Recuperation resultat test
cmp eax, 0 ;Si c'est faux
je L6 ;Aller la bas
mov eax, [ebp - 4] ;Recuperation variable locale
push eax ;Envoie variable locale
pop eax ;Recuperation resultat expression ecrire
call iprintLF ;Appel a ecrire
jmp L7 ; Aller a la suite du si
L6: ;Sinon
mov eax, [ebp - 8] ;Recuperation variable locale
push eax ;Envoie variable locale
pop eax ;Recuperation resultat expression ecrire
call iprintLF ;Appel a ecrire
L7: ;Suite du si
add esp, 8
pop ebp
ret
