#include "std_lib.h"

int div(int a, int b) {
    int sign = 1;
    int result = 0;
    
    if (a < 0) {
        sign = -sign;
        a = -a;
    }
    if (b < 0) {
        sign = -sign;
        b = -b;
    }
    
    while (a >= b) {
        a = a - b;
        result = result + 1;
    }
    
    return sign * result;
}

int mod(int a, int b) {
    int division = div(a, b);
    return a - (division * b);
}

bool strcmp(char *str1, char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1 = str1 + 1;
        str2 = str2 + 1;
    }
    return *str1 - *str2;
}

void strcpy(char *dst, char *src) {
    while (*src) {
        *dst = *src;
        dst = dst + 1;
        src = src + 1;
    }
    *dst = '\0';
}

void clear(byte *buf, unsigned int size) {
    unsigned int i;
    for (i = 0; i < size; i = i + 1) {
        buf[i] = 0;
    }
}

void atoi(char *str, int *num) {
    int sign = 1;
    int result = 0;
    int i = 0;
    
    if (str[0] == '-') {
        sign = -1;
        i = i + 1;
    }
    
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i = i + 1;
    }
    
    *num = sign * result;
}

void itoa(int num, char *str) {
    int i = 0;
    int isNegative = 0;
    int start, end;
    char temp;
    
    /* Handle 0 case */
    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    
    /* Handle negative numbers */
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }
    
    /* Extract digits */
    while (num > 0) {
        int digit = 0;
        int temp_num = num;
        
        /* Calculate digit without using % operator */
        while (temp_num >= 10) {
            temp_num = temp_num - 10;
            digit = digit + 1;
        }
        
        str[i] = temp_num + '0';
        i = i + 1;
        num = digit;
    }
    
    /* Add negative sign */
    if (isNegative) {
        str[i] = '-';
        i = i + 1;
    }
    
    str[i] = '\0';
    
    /* Reverse the string */
    start = 0;
    end = i - 1;
    while (start < end) {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start = start + 1;
        end = end - 1;
    }
}