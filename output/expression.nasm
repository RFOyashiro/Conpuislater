%include "io.asm"
section .bss
sinput resb 255
$a resd 1 ;Declaration d'une variable globale
section .text
global _start
_start:
call _FONC_main
mov eax,1
int 0x80

_FONC_main: ;Declaration de fonction
push ebp ;Sauvegarde ebp
mov ebp, esp ;On se place en haut de la pile
push 5 ;Expression d'un entier
push 2 ;Expression d'un entier
pop ebx ;Recuperation 2e operandes
pop eax ;Recuperation 1e operande
mul ebx ;Multiplication op1 *= op2
push eax ;Envoie resultat
pop eax ;Recuperation resultat expression ecrire
call iprintLF ;Appel a ecrire
add esp, 0
pop ebp
ret
