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
push dword[$a] ;Envoie variable globale
pop ebx ;On ignore la valeur de la variable car on fait une affectation
push 123 ;Expression d'un entier
pop eax ;On recupere la resultat de l'expression
mov [$a], eax ;Affectation variable globale
add esp, 0
pop ebp
ret
