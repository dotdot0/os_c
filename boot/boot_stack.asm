mov ah, 0x0e ; tty Mode

mov bp, 0x8000 ; stack base
mov sp, bp

push 'A'
push 'B'
push 'C'

mov al, [0x7ffe]
int 0x10

pop bx ; bx is a 16 bit register(pop instrucion only works with 16 bit reg so bh will be zero and bl has data)
mov al, bl
int 0x10 

pop bx 
mov al, bl 
int 0x10

pop bx
mov al, bl
int 0x10

mov al, [0x8000]
int 0x10

jmp $
times 510-($-$$) db 0
dw 0xaa55