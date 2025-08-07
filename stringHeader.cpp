#include "./stringHeader.h"
#include "./HashTable.h"
#include <fstream>

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
    while (src[i] != '\0')
    {
        dest[len1] = src[i];
        len1++;
        i++;
    }
    dest[len1] = '\0';
    return dest;
}
char *my_strchr(const char *s, char c)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == c)
        {
            return (char *)(s + i);
        }
        i++;
    }
    return nullptr;
}
char *my_strstr(const char *haystack, const char *needle)
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
            return (char *)(haystack + i);
        }
    }
    return nullptr;
}
void reverse_inplace(char *s)
{
    int i = 0, j = my_strlen(s);
    while (i != j)
    {
        char t = s[i];
        s[i] = s[j];
        s[j] = t;
        i++;
        j--;
    }
}
int is_palindrome(char *s)
{
    int left = 0;

    int right = my_strlen(s);
    right--;

    while (left < right)
    {

        while (left < right && !isalnum(s[left]))
            left++;
        while (left < right && !isalnum(s[right]))
            right--;

        if (tolower(s[left]) != tolower(s[right]))
        {
            return 0;
        }

        left++;
        right--;
    }

    return 1;
}
int count_words(const char *s)
{
    int count = 0;
    bool in_word = false;

    while (*s)
    {
        if (*s != ' ')
        {
            if (!in_word)
            {
                count++;
                in_word = true;
            }
        }
        else
        {
            in_word = false;
        }
        s++;
    }

    return count;
}
char *readFile(const char *filepath)
{
    ifstream file(filepath, ios::in);
    if (!file.is_open())
    {
        cout << "Could not open file: " << filepath << endl;
        return nullptr;
    }

    file.seekg(0, ios::end);
    size_t length = file.tellg();
    file.seekg(0, ios::beg);

    char *buffer = new char[length + 1];
    file.read(buffer, length);
    buffer[length] = '\0';

    file.close();
    return buffer;
}

char *removeHTMLTags(char *htmlContent)
{
    int len = my_strlen(htmlContent);
    char *cleanText = new char[len + 1];
    int writeIndex = 0;
    bool insideTag = false;
    bool insideScript = false;
    bool insideStyle = false;

    for (int i = 0; i < len; i++)
    {
        if (i < len - 7 && my_strstr(htmlContent + i, "<script") == htmlContent + i)
        {
            insideScript = true;
            while (i < len && htmlContent[i] != '>')
                i++;
            i++;
            continue;
        }

        if (insideScript && i < len - 8 && my_strstr(htmlContent + i, "</script") == htmlContent + i)
        {
            insideScript = false;
            while (i < len && htmlContent[i] != '>')
                i++;
            i++;
            continue;
        }
        if (i < len - 6 && my_strstr(htmlContent + i, "<style") == htmlContent + i)
        {
            insideStyle = true;
            while (i < len && htmlContent[i] != '>')
                i++;
            continue;
        }

        if (insideStyle && i < len - 7 && my_strstr(htmlContent + i, "</style") == htmlContent + i)
        {
            insideStyle = false;
            while (i < len && htmlContent[i] != '>')
                i++;
            i++;
            continue;
        }
        if (insideScript || insideStyle)
        {
            continue;
        }

        if (htmlContent[i] == '<')
        {
            insideTag = true;
            if (writeIndex > 0 && cleanText[writeIndex - 1] != ' ')
            {
                cleanText[writeIndex++] = ' ';
            }
        }
        else if (htmlContent[i] == '>')
        {
            insideTag = false;
            if (writeIndex > 0 && cleanText[writeIndex - 1] != ' ')
            {
                cleanText[writeIndex++] = ' ';
            }
        }
        else if (!insideTag)
        {
            if (htmlContent[i] == '\n' || htmlContent[i] == '\t')
            {
                if (writeIndex > 0 && cleanText[writeIndex - 1] != ' ')
                {
                    cleanText[writeIndex++] = ' ';
                }
            }
            else
            {
                cleanText[writeIndex++] = htmlContent[i];
            }
        }
    }

    cleanText[writeIndex] = '\0';
    return cleanText;
}

bool isCommonWord(char *word)
{
    char lowWord[100];
    int i = 0;
    while (word[i] && i < 99)
    {
        if (word[i] >= 'A' && word[i] <= 'Z')
        {
            lowWord[i] = word[i] + 32;
        }
        else
        {
            lowWord[i] = word[i];
        }
        i++;
    }
    lowWord[i] = '\0';

    const char *commonWords[] = {
        "the", "and", "for", "are", "but", "not", "you", "all",
        "can", "had", "her", "was", "our", "get", "has", "him", "his", "how", "its", "may", "new",
        "now", "old", "see", "two", "way", "who", "did",
        "this", "that", "with", "have", "they", "will", "your", "from", "been", "said",
        "each", "make", "most", "over", "very", "what",
        "well", "were", "here", "just", "like", "many", "when", "made",
        "more", "move", "much", "must", "name", "need", "only",
        "other", "right", "same", "still", "take", "than", "them",
        "these", "things", "think", "those", "through", "turn", "before", "being", "between", "both",
        "came", "does", "even", "first", "give", "going", "group",
        "hand", "hard", "high", "important", "into", "large",
        "later", "left", "let", "line", "little", "live", "local","www",
        "might", "never", "next", "often", "com",
        "open", "order", "own", "part", "place", "point", "put", "seem", "several", "show", "side",
        "since", "small", "social", "something", "state", "system",
        "their", "then", "there", "thing", "too", "took", "under", "until", "where", "which", "while",
        nullptr};

    for (int j = 0; commonWords[j] != nullptr; j++)
    {
        if (my_strcmp(lowWord, (char *)commonWords[j]) == 0)
        {
            return true;
        }
    }

    return false;
}

void extractWords(char *url, char *filePath)
{
    cout << "\nProcessing File: " << filePath << " ---" << endl;

    char *buffer = readFile(filePath);
    if (buffer == nullptr)
    {
        cout << "Error: Could not read file " << filePath << endl;
        return;
    }

    char *cleanText = removeHTMLTags(buffer);
    delete[] buffer;

    if (cleanText == nullptr)
    {
        cout << "Error: Could not process HTML content" << endl;
        return;
    }
    cout << "Words found in " << url << ":" << endl;
    HashTable<char *, int> wordFreqTable;

    int len = my_strlen(cleanText);
    char word[100];
    int wordIndex = 0;
    int wordCount = 0;
    char *mostFrequentWord = nullptr;
    int maxFrequency = 0;

    for (int i = 0; i <= len; i++)
    {
        char c = cleanText[i];

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') || c == '\'' || c == '-')
        {
            if (wordIndex < 99)
            {
                word[wordIndex++] = c;
            }
        }
        else
        {
            if (wordIndex > 0)
            {
                word[wordIndex] = '\0';
                if (wordIndex > 2 && !isCommonWord(word))
                {
                    cout << "  " << word << endl;
                    wordCount++;
                    wordFreqTable.insert(word, 1); // insert karee
                    int freq;
                    if (wordFreqTable.search(word, freq)) // ab freq dekhre
                    {
                        if (freq > maxFrequency)
                        {
                            maxFrequency = freq;

                            if (mostFrequentWord)
                                delete[] mostFrequentWord;

                            mostFrequentWord = new char[my_strlen(word) + 1];
                            my_strcpy(mostFrequentWord, word);
                        }
                    }
                }
                wordIndex = 0;
            }
        }
    }

    cout << "Total meaningful words found: " << wordCount << endl;

    if (mostFrequentWord)
    {
        cout << "Most frequent word: " << mostFrequentWord << " (frequency: " << maxFrequency << ")" << endl;
        delete[] mostFrequentWord;
    }

    delete[] cleanText;
    cout << "End of file processing ---" << endl;
}