[org 0x7c00]
mov bp, 0x8000
mov sp, bp

mov bx, 0x9000
mov dh, 3 ; No. of sectors to read
call disk_load ; loads the data read from disk (0x9000)
mov dx, [0x9000]
call print_hex

call print_nl

mov dx, [0x9000 + 512]
call print_hex

call print_nl

mov dx, [0x9000 + 2*512]
call print_hex

call print_nl

jmp $

%include "boot_sect_print.asm"
%include "boot_sect_hex.asm"
%include "boot_sect_disk.asm"


times 510-($-$$) db 0
db 0x55, 0xaa

times 256 dw 0xdada
times 256 dw 0xfafd
times 256 dw 0xaa00