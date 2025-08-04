#include "./stringHeader.h"

int my_strlen(char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return i;
}
int my_strcmp(char *a, char *b)
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] > b[i])
        {
            return a[i] - b[i];
        }
        if (a[i] < b[i])
        {
            return a[i] - b[i];
        }
        i++;
    }
    if (a[i] != b[i])
    {
        return a[i] - b[i];
    }
    return 0;
}
char *my_strcpy(char *dest, char *src)
{

    char *original = dest;
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return original;
}
char *my_strcat(char *dest, const char *src)
{
    int len1 = my_strlen(dest);
    // len1++;
    int i = 0;
    cout<<src<<endl;
    cout<<dest<<endl;
    while (src[i] != '\0')
    {
        dest[len1] = src[i];
        len1++;
        i++;
    }
    dest[len1] = '\0';
    cout<<dest<<endl;
    return dest;
}
int my_strchr(char *s, char c)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == c)
        {
            return i;
        }
        i++;
    }
    return -1;
}
int my_strstr(char *haystack, char *needle)
{
    if (!*needle)
        return 0;

    for (int i = 0; haystack[i] != '\0'; i++)
    {
        int j = 0;
        while (needle[j] != '\0' && haystack[i + j] == needle[j])
        {
            j++;
        }
        if (needle[j] == '\0')
        {
            return i;
        }
    }
    return -1;
}
 void reverse_inplace(char *s)
 {
    int i=0,j=my_strlen(s);
    while(i!=j)
    {
        char t=s[i];
        s[i]=s[j];
        s[j]=t;
        i++;
        j--;
    }
 }
int is_palindrome(char *s) {
    int left = 0;

    int right = my_strlen(s);
    right--; 

    while (left < right) {
        
        while (left < right && !isalnum(s[left])) left++;
        while (left < right && !isalnum(s[right])) right--;

        if (tolower(s[left]) != tolower(s[right])) {
            return 0; 
        }

        left++;
        right--;
    }

    return 1;
}
int count_words(const char *s) {
    int count = 0;
    bool in_word = false;

    while (*s) {
        if (*s != ' ') {
            if (!in_word) {
                count++; 
                in_word = true;
            }
        } else {
            in_word = false; 
        }
        s++;
    }

    return count;
}
// int my_strtok(char* str,char deli)
// {

// }