global main
extern printf
extern atoi
extern scanf
extern puts
section .data
arr: times 38 db 0
men:  db "the number is %d ",10,0
LC5:    db  "%d",0
choice: dw 0
section .text
main:
mov rdi, LC5
mov rsi, choice 
xor eax, eax
call scanf 
mov eax,[choice]

;----------51 ID 0
mov word[arr+0],AX

;------------ done printing
mov rdi, LC5
mov rsi, choice 
xor eax, eax
call scanf 
mov eax,[choice]

;----------51 ID 2
mov word[arr+2],AX

;------------ done printing
mov rax,0
mov BX,word[arr+0]
cmp BX,0
MOV rbx,0xFFFFFFFFFFFFFFFF
cmovl rax,rbx
mov AX,word[arr+0]
push    rax
push    rcx
mov     rdi, men
mov     rsi, rax
xor     rax, rax
call    printf
pop     rcx
pop     rax
