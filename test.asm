%include "io.asm"
section .bss
sinput resb 255
$tab resd 40
section .text
global _start
_start:
call _FONC_main
mov eax,1
int 0x80
_FONC_initialiser:
push ebp
mov ebp, esp
push 0
pop eax
mov ebx [$tab + eax]
push ebx
push 8
pop eax
pop ebx
push 0
pop eax
mov [$tab + eax] ebx
push 1
pop eax
mov ebx [$tab + eax]
push ebx
push 6
pop eax
pop ebx
push 1
pop eax
mov [$tab + eax] ebx
push 2
pop eax
mov ebx [$tab + eax]
push ebx
push 9
pop eax
pop ebx
push 2
pop eax
mov [$tab + eax] ebx
push 3
pop eax
mov ebx [$tab + eax]
push ebx
push 9
pop eax
pop ebx
push 3
pop eax
mov [$tab + eax] ebx
push 4
pop eax
mov ebx [$tab + eax]
push ebx
push 4
pop eax
pop ebx
push 4
pop eax
mov [$tab + eax] ebx
push 5
pop eax
mov ebx [$tab + eax]
push ebx
push 2
pop eax
pop ebx
push 5
pop eax
mov [$tab + eax] ebx
push 6
pop eax
mov ebx [$tab + eax]
push ebx
push 3
pop eax
pop ebx
push 6
pop eax
mov [$tab + eax] ebx
push 7
pop eax
mov ebx [$tab + eax]
push ebx
push 1
pop eax
pop ebx
push 7
pop eax
mov [$tab + eax] ebx
push 8
pop eax
mov ebx [$tab + eax]
push ebx
push 4
pop eax
pop ebx
push 8
pop eax
mov [$tab + eax] ebx
push 9
pop eax
mov ebx [$tab + eax]
push ebx
push 5
pop eax
pop ebx
push 9
pop eax
mov [$tab + eax] ebx
_FONC_afficher:
push ebp
mov ebp, esp
sub esp, 4
mov eax, [ebp - 4]
push eax
push 0
pop eax
pop ebx
mov [ebp - 4], eax
L0:
mov eax, [ebp - 4]
push eax
mov eax, [ebp + 8]
push eax
pop ebx
pop eax
cmp eax, ebx
jl L1
mov eax, 0
jmp L2
L1:
mov eax, 1
L2:
push eax
pop eax
cmp eax, 0
je L3
mov eax, [ebp - 4]
push eax
pop eax
mov ebx [$tab + eax]
push ebx
pop eax
call iprintLF
mov eax, [ebp - 4]
push eax
mov eax, [ebp - 4]
push eax
push 1
pop ebx
pop eax
add eax, ebx
push eax
pop eax
pop ebx
mov [ebp - 4], eax
jmp L0
L3:
push 0
pop eax
call iprintLF
_FONC_echanger:
push ebp
mov ebp, esp
sub esp, 4
mov eax, [ebp - 4]
push eax
mov eax, [ebp + 8]
push eax
pop eax
mov ebx [$tab + eax]
push ebx
pop eax
pop ebx
mov [ebp - 4], eax
mov eax, [ebp + 8]
push eax
pop eax
mov ebx [$tab + eax]
push ebx
mov eax, [ebp + 12]
push eax
pop eax
mov ebx [$tab + eax]
push ebx
pop eax
pop ebx
mov eax, [ebp + 8]
push eax
pop eax
mov [$tab + eax] ebx
mov eax, [ebp + 12]
push eax
pop eax
mov ebx [$tab + eax]
push ebx
mov eax, [ebp - 4]
push eax
pop eax
pop ebx
mov eax, [ebp + 12]
push eax
pop eax
mov [$tab + eax] ebx
_FONC_trier:
push ebp
mov ebp, esp
sub esp, 4
sub esp, 4
sub esp, 4
mov eax, [ebp - 12]
push eax
mov eax, [ebp + 8]
push eax
pop eax
pop ebx
mov [ebp - 12], eax
mov eax, [ebp - 4]
push eax
push 1
pop eax
pop ebx
mov [ebp - 4], eax
L4:
mov eax, [ebp - 4]
push eax
push 1
pop ebx
pop eax
cmp eax, ebx
je L5
mov eax, 0
jmp L6
L5:
mov eax, 1
L6:
push eax
pop eax
cmp eax, 0
je L7
mov eax, [ebp - 4]
push eax
push 0
pop eax
pop ebx
mov [ebp - 4], eax
mov eax, [ebp - 8]
push eax
push 0
pop eax
pop ebx
mov [ebp - 8], eax
L7:
mov eax, [ebp - 8]
push eax
mov eax, [ebp - 12]
push eax
push 1
pop ebx
pop eax
sub eax, ebx
push eax
pop ebx
pop eax
cmp eax, ebx
jl L8
mov eax, 0
jmp L9
L8:
mov eax, 1
L9:
push eax
pop eax
cmp eax, 0
je L10
mov eax, [ebp - 8]
push eax
push 1
pop ebx
pop eax
add eax, ebx
push eax
pop eax
mov ebx [$tab + eax]
push ebx
mov eax, [ebp - 8]
push eax
pop eax
mov ebx [$tab + eax]
push ebx
pop ebx
pop eax
cmp eax, ebx
jl L10
mov eax, 0
jmp L11
L10:
mov eax, 1
L11:
push eax
pop eax
cmp eax, 0
je L12
sub esp, 4
mov eax, [ebp - 8]
push eax
mov eax, [ebp - 8]
push eax
push 1
pop ebx
pop eax
add eax, ebx
push eax
call _FONC_echanger
add esp, 8
mov eax, [ebp - 4]
push eax
push 1
pop eax
pop ebx
mov [ebp - 4], eax
jmp L13
L12:
L13:
mov eax, [ebp - 8]
push eax
mov eax, [ebp - 8]
push eax
push 1
pop ebx
pop eax
add eax, ebx
push eax
pop eax
pop ebx
mov [ebp - 8], eax
jmp L7
L14:
mov eax, [ebp - 12]
push eax
mov eax, [ebp - 12]
push eax
push 1
pop ebx
pop eax
sub eax, ebx
push eax
pop eax
pop ebx
mov [ebp - 12], eax
jmp L4
L15:
_FONC_main:
push ebp
mov ebp, esp
sub esp, 4
call _FONC_initialiser
add esp, 0
sub esp, 4
push 10
call _FONC_afficher
add esp, 4
sub esp, 4
push 10
call _FONC_trier
add esp, 4
sub esp, 4
push 10
call _FONC_afficher
add esp, 4
add esp, 0
pop ebp
ret
