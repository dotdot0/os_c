disk_load:
    pusha
    push dx

    mov ah, 0x02 ; Set function code to 0x02 (read sectors) 
    mov al, dh 
    mov cl, 0x02 ; Read Second Sector(first sector after boot sector)

    mov ch, 0x00 ; Cylinder number 0
    mov dh, 0x00 ; Head No. 0

    int 0x13 ; loads the data from disk to (0x9000) [if error carry bit is set]
    jc disk_error

    pop dx
    cmp al, dh
    jne sectors_error
    popa 
    ret

disk_error:
    mov bx, DISK_ERROR
    call print
    call print_nl
    mov dh, ah
    call print_hex
    jmp disk_loop

sectors_error:
    mov bx, SECTORS_ERROR
    call print
  
disk_loop:
    jmp $
  
DISK_ERROR: db "Disk read error", 0
SECTORS_ERROR: db "Incorrect number of sectors read", 0