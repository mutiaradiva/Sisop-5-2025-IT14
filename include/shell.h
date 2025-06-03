#ifndef __SHELL_H__
#define __SHELL_H__

#include "std_type.h"

void shell();
void parseCommand(char *buf, char *cmd, char arg[2][64]);

int stringToInt(char *s);
void intToString(int num, char *buf);
int startsWith(char *str, char *prefix);
void setTerminalColor(int code);
void banner(char* username, char* hostname);

#endif // __SHELL_H__
