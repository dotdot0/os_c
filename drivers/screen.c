#include "screen.h"
#include "ports.h"

int get_cursor_offset();
int set_cursor_offset(int offset);
void set_char_at_video_memory(char c, int offset, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);

void set_char_at_video_memory(char c, int offset, char attr){
  unsigned char *vid_mem = (unsigned char*) VIDEO_ADDRESS;
  vid_mem[offset] = c;
  vid_mem[offset+1] = !attr ? GREEN_ON_BLACK : attr;
}

int get_offset(int col, int row){
  return 2 * (row * MAX_COLS + col);
}

int get_offset_row(int offset){
  return offset / (2 * MAX_COLS);
}

int get_offset_col(int offset){
  return (offset - (get_offset_row(offset)*2*MAX_COLS))/2;
}

int get_cursor_offset(){
  /*Use the VGA Ports to get the current cursor pos
  1. Ask for the High byte of the cursor offset by sending 14 to CTRL_REG
  2. Ask for the lower byte of the cursor offset by sending 15 to CTRL_REG  
  
+---------------------------+       +---------------------------+
| CPU                       |       | VGA Controller            |
|                           |       |                           |
| Write to 0x3D4 (14)       |------>| Register Selector         |
|                           |       |                           |
| Read from 0x3D5           |<------| Register 14 (High Byte)   |
|                           |       |                           |
| Write to 0x3D4 (15)       |------>| Register Selector         |
|                           |       |                           |
| Read from 0x3D5           |<------| Register 15 (Low Byte)    |
+---------------------------+       +---------------------------+
  */
  port_byte_out(REG_SCREEN_CTRL, 14);
  int pos = port_byte_in(REG_SCREEN_DATA) << 8;
  port_byte_out(REG_SCREEN_CTRL, 15);
  pos += port_byte_in(REG_SCREEN_DATA);
  return pos * 2;
}

int set_cursor_offset(int offset){
  offset/=2;
  /* Write the high byte */
  port_byte_out(REG_SCREEN_CTRL, 14); // Select High byte reg
  port_byte_out(REG_SCREEN_DATA,(unsigned char) (offset>>8)); // Write the High Byte

  /* Write the lower byte */
  port_byte_out(REG_SCREEN_CTRL, 15); // Select Low byte reg
  port_byte_out(REG_SCREEN_DATA,(unsigned char) (offset&0xff)); // Write the low byte

}

void clear_screen(){
  int size_s = MAX_COLS * MAX_ROWS;
  unsigned char*screen = (unsigned char* )VIDEO_ADDRESS;
  for(int i = 0; i < size_s; i++){
    screen[i*2] = ' ';
    screen[i*2+1] = WHITE_ON_BLACK;
  }
  set_cursor_offset(get_offset(0, 0));
}

int offset_new_line(int offset){
  return get_offset(0, get_offset_row(offset) + 1);
}

void printk(char *message){
  int offset = get_cursor_offset();
  int i=0;
  while(message[i]!='\0'){
    if(message[i]=='\n'){
      int row = get_offset_row(offset);
      offset = get_offset(0, row+1);
    }else{
      set_char_at_video_memory(message[i], offset, 0);
      offset+=2;
    }
    i++;
  }
  set_cursor_offset(offset);
}

void printk_at(char* message, int col, int row){
  int offset = get_offset(col, row);  
  set_cursor_offset(offset);
  printk(message);
}