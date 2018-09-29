#ifndef SIMPLEOS_STRING_H
#define SIMPLEOS_STRING_H

void itoa(int n, char *str);
void htoa(uint32_t n, char *str);

void reverse(char *str);

void append(char *str, char n);
void rstrip(char *str, uint32_t size);

void strcat(char *dest, char *src);
int strcmp(char *str1, char *str2);
int strlen(char *str);

#endif
