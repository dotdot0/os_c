mov ah, 0x0e

mov bx, 0x7c0
mov ds, bx
mov al, [char]
int 0x10

jmp $

char:
    db 'X'
times 510 - ($-$$) db 0
dw 0xaa55