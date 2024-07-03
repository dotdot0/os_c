#include "../drivers/screen.h"

void main() {
  clear_screen();
  printk_at("|=======|", 40, 0);
  printk_at("|NULL OS|", 40, 1);
  printk_at("|=======|", 40, 2);
}