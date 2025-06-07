#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

char buf[128];
char num_buf[16];
char username[32] = "user";
char hostname[16] = "";
int color_code;

void banner(char* username, char* hostname) {
    printString(username);
    printString(hostname);
    printString("> ");
}

void setTerminalColor(int code) {
    color_code = code;
}

void clearBuffer(char* buffer, int size) {
    int i;
    for (i = 0; i < size; i++) {
        buffer[i] = '\0';
    }
}

void shell() {
    int i, j;
    int is_user_command;

    strcpy(username, "user");
    clearBuffer(hostname, sizeof(hostname));
    printString("Welcome to EorzeOS!\r\n");

    while (1) {
        // Pastikan buffer bersih sebelum setiap iterasi
        clearBuffer(buf, sizeof(buf));
        clearBuffer(num_buf, sizeof(num_buf));
        banner(username, hostname);
        readString(buf);

        is_user_command = (buf[0] == 'u' && buf[1] == 's' && buf[2] == 'e' &&
                           buf[3] == 'r' && buf[4] == ' ');

        // 1. Yo/Gurt
        if (strcmp(buf, "yo") == 0) {
            printString("gurt\n");
        } else if (strcmp(buf, "gurt") == 0) {
            printString("yo\r\n");
        }

        // 2. Ganti username dengan "user nama"
        else if (is_user_command) {
            for (i = 5, j = 0; buf[i] != '\0' && j < 31; i++, j++) {
                username[j] = buf[i];
            }
            username[j] = '\0';
            printString("Username changed to ");
            printString(username);
            printString("\r\n");
        }

        // 3. Reset username ke "user"
        else if (strcmp(buf, "user") == 0) {
            strcpy(username, "user");
            printString("Username changed to user\n");
        }

        // 4. Grandcompany
        else if (startsWith(buf, "grandcompany")) {
            char cmd[4];
            char args[2][64];
            parseCommand(buf, cmd, args);
            if (strcmp(args[0], "maelstrom") == 0) {
                setTerminalColor(0x0c);
                strcpy(hostname, "@storm");
                clearScreen(color_code);
            } else if (strcmp(args[0], "twinadder") == 0) {
                setTerminalColor(0x0e);
                strcpy(hostname, "@serpent");
                clearScreen(color_code);
            } else if (strcmp(args[0], "immortalflames") == 0) {
                setTerminalColor(0x09);
                strcpy(hostname, "@flame");
                clearScreen(color_code);
            } else {
                printString("unknown company");
            }
            printString("\r\n");
        }

        // 5. Kalkulator: add, sub, mul, div
        else if (startsWith(buf, "add ") || startsWith(buf, "sub ") ||
                 startsWith(buf, "mul ") || startsWith(buf, "div ")) {
            char cmd[4];
            char args[2][64];
            int x, y, result, valid, remainder;

            parseCommand(buf, cmd, args);

            x = stringToInt(args[0]);
            y = stringToInt(args[1]);
            result = 0;
            valid = 1;

            if (strcmp(cmd, "add") == 0) {
                result = x + y;
            } else if (strcmp(cmd, "sub") == 0) {
                result = x - y;
            } else if (strcmp(cmd, "mul") == 0) {
                int sign = 1;
                if (x < 0) {
                    sign = -sign;
                    x = -x;
                }
                if (y < 0) {
                    sign = -sign;
                    y = -y;
                }

                result = 0;
                for (i = 0; i < y; i++) {
                    result += x;
                }

                result = sign * result;
            } else if (strcmp(cmd, "div") == 0) {
                if (y == 0) {
                    printString("Error: Division by zero\n");
                    valid = 0;
                } else {
                    int sign = 1;
                    if (x < 0) {
                        sign = -sign;
                        x = -x;
                    }
                    if (y < 0) {
                        sign = -sign;
                        y = -y;
                    }

                    result = 0;
                    remainder = x;
                    while (remainder >= y) {
                        remainder -= y;
                        result++;
                    }

                    result = sign * result;
                }
            }

            if (valid) {
                clearBuffer(num_buf, sizeof(num_buf)); // Bersihkan sebelum digunakan
                intToString(result, num_buf);
                printString(num_buf);
                printString("\r\n");
                clearBuffer(num_buf, sizeof(num_buf)); // Bersihkan setelah digunakan
            }
        }

        // 6. Exit
        else if (strcmp(buf, "clear") == 0) {
            strcpy(hostname, "");
            clearScreen(0x07);
            break;
        }

        // 7. Yogurt
        else if (strcmp(buf, "yogurt") == 0) {
            char answer[3][100];
            char prev_username[32];
            int tick;

            // Simpan username sebelumnya untuk dipulihkan nanti
            strcpy(prev_username, username);

            // Ubah prompt menjadi "gurt"
            strcpy(username, "gurt");

            // Tampilkan prompt "gurt>" segera setelah input "yogurt"
            banner(username, hostname);

            // Siapkan semua jawaban
            strcpy(answer[0], "yo");
            strcpy(answer[1], "ts unami gng </3");
            strcpy(answer[2], "sygau");

            // Pilih satu jawaban secara acak menggunakan tick BIOS
            tick = mod(getBiosTick(), 3);

            // Tampilkan hanya jawaban yang dipilih
            printString(answer[tick]);
            printString("\r\n");

            // Pulihkan username ke nilai sebelumnya
            strcpy(username, prev_username);
        }

        // 8. Echo
        else {
            printString(buf);
            printString("\r\n");
        }
    }
}

void parseCommand(char *buf, char *cmd, char args[2][64]) {
    int i = 0;
    int arg_num = 0;
    int char_pos = 0;
    int in_word = 0;

    // Bersihkan cmd dan args sebelum digunakan
    clearBuffer(cmd, 4);
    clearBuffer(args[0], 64);
    clearBuffer(args[1], 64);

    while (buf[i] != '\0') {
        if (buf[i] == ' ' || buf[i] == '\t') {
            if (in_word) {
                if (arg_num == 0) {
                    cmd[char_pos] = '\0';
                } else {
                    args[arg_num - 1][char_pos] = '\0';
                }
                in_word = 0;
                char_pos = 0;
                if (arg_num < 2) arg_num++;
            }
        } else {
            if (!in_word) in_word = 1;
            if (arg_num == 0) {
                cmd[char_pos++] = buf[i];
            } else if (arg_num <= 2) {
                args[arg_num - 1][char_pos++] = buf[i];
            }
        }
        i++;
    }

    if (in_word) {
        if (arg_num == 0) {
            cmd[char_pos] = '\0';
        } else {
            args[arg_num - 1][char_pos] = '\0';
        }
    }
}

int stringToInt(char *s) {
    int num = 0;
    int i = 0;
    int sign = 1;

    if (s[0] == '-') {
        sign = -1;
        i++;
    }

    while (s[i] >= '0' && s[i] <= '9') {
        num = num * 10 + (s[i] - '0');
        i++;
    }

    return num * sign;
}

void intToString(int num, char *buf) {
    int i = 0;
    int is_neg = 0;
    int j, k;
    char tmp;
    int digit;
    int temp;
    int reduced;

    // Bersihkan buffer sebelum digunakan
    clearBuffer(buf, 16);

    if (num < 0) {
        is_neg = 1;
        num = -num;
    }

    if (num == 0) {
        buf[i++] = '0';
    } else {
        while (num > 0) {
            digit = 0;
            temp = num;

            while (temp >= 10) {
                temp -= 10;
                digit++;
            }

            buf[i++] = temp + '0';

            reduced = 0;
            while (num >= 10) {
                num -= 10;
                reduced++;
            }
            num = reduced;
        }
    }

    if (is_neg) {
        buf[i++] = '-';
    }

    buf[i] = '\0';

    j = 0;
    k = i - 1;
    while (j < k) {
        tmp = buf[j];
        buf[j] = buf[k];
        buf[k] = tmp;
        j++;
        k--;
    }
}

int startsWith(char *str, char *prefix) {
    while (*prefix) {
        if (*str != *prefix) return 0;
        str++;
        prefix++;
    }
    return 1;
}
