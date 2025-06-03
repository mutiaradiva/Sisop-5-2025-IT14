#include "shell.h"
#include "kernel.h"

void main() {
  clearScreen(0x07);
  shell();
}

/* Cetak string ke layar */
void printString(char *str) {
  while (*str) {
    interrupt(0x10, 0x0E00 | *str++, 0, 0, 0);
  }
}

/* Baca input dari keyboard */
void readString(char *buf) {
  char ch;
  int i = 0;
  
  while (1) {
    ch = interrupt(0x16, 0, 0, 0, 0);  // Baca keyboard
    
    if (ch == 0x0D) {  // Enter
      buf[i] = 0;
      printString("\r\n");
      break;
    }
    else if (ch == 0x08 && i > 0) {  // Backspace
      i--;
      printString("\b \b");
    }
    else if (ch >= 32 && ch <= 126 && i < 255) {  // Karakter printable
      buf[i++] = ch;
      interrupt(0x10, 0x0E00 | ch, 0, 0, 0);  // Echo ke layar
    }
  }
}

/* Bersihkan layar */
void clearScreen(int color) {
  int i;
  for (i = 0; i < 2000; i++) {
    putInMemory(0xB800, i*2, ' ');
    putInMemory(0xB800, i*2+1, color);
  }
}