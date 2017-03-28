%include "io.asm"
section .bss
sinput resb 255
$a resd 1
section .text
global _start
_start:
call main
mov eax,1
int 0x80
main:
push ebp
mov ebp, esp
push dword[$a]
push 123
pop eax
pop ebx
mov [$a], eax
push dword[$a]
pop eax
call iprintLF
pop ebp
ret