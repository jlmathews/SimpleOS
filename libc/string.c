#include <stdint.h>

#include "string.h"

void itoa(int n, char *str)
{
    int i = 0, sign = 0;
    if (n < 0) {
	    n = -n;
	    sign = 1;
    }
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign)
	    str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

void htoa(uint32_t n, char *str)
{
    uint32_t temp;
    uint32_t i;

    strcat(str, "0x\0");

    for (i = 28; i > 0; i -= 4) {
        temp = (n >> i) & 0xF;
        if (temp > 0xA) append(str, temp - 0xA + 'a');
        else append(str, temp + '0');
    }

    temp = n & 0xF;
    if (temp >= 0xA) append(str, temp - 0xA + 'a');
    else append(str, temp + '0');
}

void reverse(char *str)
{
    char temp;
    uint32_t i, j;
    uint32_t size = strlen(str);
    for (i = 0, j = size-1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}


void append(char *str, char n)
{
    uint32_t size = strlen(str);
    str[size] = n;
    str[size+1] = '\0';
}

void rstrip(char *str, uint32_t size)
{
    uint32_t len = strlen(str);
    if(size >= len) {
	    str[0] = '\0';
    }
    else {
	    str[len-size] = '\0';
    }
}

void strcat(char *dest, char *src)
{
    uint32_t index = strlen(dest);
    uint32_t src_index = 0;
    uint32_t src_size = strlen(src);
    uint32_t size = index + src_size + 1;
    for(;index < size; index++, src_index++) {
	    dest[index] = src[src_index];
    }
}

 // Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2
int strcmp(char *str1, char *str2)
{
    uint32_t i = 0;
    while( str1[i] == str2[i]) {
        if (str1[i] == '\0')
		return 0;
	i++;
    }
    return str1[i] - str2[i];
}

int strlen(char *str)
{
    uint32_t i = 0;
    while (str[i] != '\0') ++i;
    return i;
}
