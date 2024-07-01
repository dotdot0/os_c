[org 0x7c00]

mov bx, NAME
call print

call print_nl

mov bx, LAST
call print

call print_nl

jmp $

%include "boot_sect_print.asm"

NAME:
		db "Unamed OS!", 0

LAST:
		db "Done", 0


times 510-($-$$) db 0
db 0x55, 0xaa
