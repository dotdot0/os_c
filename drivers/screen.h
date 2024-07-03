#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define RED_ON_BLACK 0x04
#define BLUE_ON_BLACK 0x01
#define GREEN_ON_BLACK 0x0A


/* Screen I/O ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5


/* Kernel API(Public) */
void clear_screen();
void printk(char *message);
void printk_at(char *message, int col, int row);