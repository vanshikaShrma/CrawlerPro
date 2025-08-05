#include <iostream>
using namespace std;
#define MAX_LEN 100

int my_strlen(char *s);
int my_strcmp(char *a, char *b);
char *my_strcpy(char *dest, char *src);
char *my_strcat(char *dest, const char *src);
char *my_strchr(const char *s, char c);
char *my_strstr(const char *haystack, const char *needle);
void reverse_inplace(char *s);
int is_palindrome(char *s);
int count_words(const char *s);
char* readFile(const char* filepath);