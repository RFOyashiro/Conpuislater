%include "io.asm"
section .bss
sinput resb 255
$i resd 1 ;Declaration d'une variable globale
$carre resd 1 ;Declaration d'une variable globale
section .text
global _start
_start:
call _FONC_main
mov eax,1
int 0x80

_FONC_main: ;Declaration de fonction
push ebp ;Sauvegarde ebp
mov ebp, esp ;On se place en haut de la pile
push dword[$i] ;Envoie variable globale
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push 0 ;Expression d'un entier
pop eax ;On recupere la resultat de l'expression
mov [$i], eax ;Affectation variable globale
L0: ;Debut de tant que
push dword[$i] ;Envoie variable globale
push 10 ;Expression d'un entier
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
push dword[$carre] ;Envoie variable globale
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push dword[$i] ;Envoie variable globale
push dword[$i] ;Envoie variable globale
pop ebx ;Recuperation 2e operandes
pop eax ;Recuperation 1e operande
mul ebx ;Multiplication op1 *= op2
push eax ;Envoie resultat
pop eax ;On recupere la resultat de l'expression
mov [$carre], eax ;Affectation variable globale
push dword[$carre] ;Envoie variable globale
pop eax ;Recuperation resultat expression ecrire
call iprintLF ;Appel a ecrire
push dword[$i] ;Envoie variable globale
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push dword[$i] ;Envoie variable globale
push 1 ;Expression d'un entier
pop ebx ;Recuperation 2e operandes
pop eax ;Recuperation 1e operande
add eax, ebx ;Ajout op1 += op2
push eax ;Envoie resultat
pop eax ;On recupere la resultat de l'expression
mov [$i], eax ;Affectation variable globale
jmp L0 ;Retour debut de tant que
L3: ;Suite du tant que
add esp, 0
pop ebp
ret
