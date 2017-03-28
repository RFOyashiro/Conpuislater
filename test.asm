%include "io.asm"
section .bss
sinput resb 255
section .text
global _start
_start:
call main
mov eax,1
int 0x80
sub esp, 4
sub esp, 4
max:
push ebp
mov ebp, esp
mov eax, [ebp - 0]
push eax
mov eax, [ebp - 4]
push eax
pop ebx
pop eax
cmp eax, ebx
jl L0
mov eax, 0
jmp L1
L0:
mov eax, 1
L1:
push eax
pop eax
cmp eax, 0
je L2
mov eax, [ebp - 4]
push eax
pop eax
mov [ebp + 8], eax
add esp, 0
jmp L3
L2:
L3:
mov eax, [ebp - 0]
push eax
pop eax
mov [ebp + 8], eax
add esp, 0
pop ebp
ret
main:
push ebp
mov ebp, esp
sub esp, 4
sub esp, 4
mov eax, [ebp - 0]
push eax
mov eax, sinput
call readline
call atoi
push eax
pop eax
pop ebx
mov [$v_1], eax
mov eax, [ebp - 4]
push eax
mov eax, sinput
call readline
call atoi
push eax
pop eax
pop ebx
mov [$v_2], eax
sub esp, 4
mov eax, [ebp - 0]
push eax
mov eax, [ebp - 4]
push eax
call max
add esp, 8
mov eax, [ebp - 0]
push eax
pop ebx
pop eax
cmp eax, ebx
je L4
mov eax, 0
L4:
mov eax, 1
push eax
pop eax
cmp eax, 0
je L5
mov eax, [ebp - 0]
push eax
pop eax
call iprintLF
jmp L6
L5:
mov eax, [ebp - 4]
push eax
pop eax
call iprintLF
L6:
pop ebp
ret
