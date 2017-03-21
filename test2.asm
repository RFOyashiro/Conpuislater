%include "io.asm"
section .bss
sinput resb 255
$a resd 1
$b resd 1
section .text
global _start
_start:
call main
mov eax,1
int 0x80
main:
mov eax, sinput
call readline
call atoi
push eax
pop ebx
mov [$a], ebx
push dword[$a]
push dword[$a]
pop ebx
pop eax
mul ebx
push eax
pop ebx
mov [$b], ebx
push dword[$b]
pop eax
call iprintLF
ret
