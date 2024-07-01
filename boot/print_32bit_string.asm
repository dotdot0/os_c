[bits 32] ; using 32 bit protected mode

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f ; color byte for each char

print_string:
      pusha
      mov edx, VIDEO_MEMORY

print_string_loop:
      mov al, [ebx] ; address of the char
      mov ah, WHITE_ON_BLACK

      cmp al, 0
      je print_string_done

      mov [edx], ax ; store char in video memory
      add ebx, 1
      add edx, 2

      jmp print_string_loop


print_string_done:
      popa
      ret