print:
    pusha ; move all reg data to stack

start:
    mov al, [bx] ; 'bx' is the base adderss for the string
    cmp al, 0 ; check for null char
    je done

    mov ah, 0x0e ; tty mode
    int 0x10 ; 'al' alredy has data

    inc bx
    jmp start

done:
    popa ; pop all reg data back
    ret

print_nl:
    pusha

    mov ah, 0x0e
    mov al, 0x0a ; '\n' char
    int 0x10
    mov al, 0x0d ; carriage return 
    int 0x10

    popa
    ret