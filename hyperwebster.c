#include <stdio.h>
#include <stdlib.h>

#define COUNT_OF(x) ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))

// could be better
void hyperwebsterGenerator(char *alphabet[], size_t length, int wordLength, FILE *fptr)
{
    fprintf(fptr, "[");
    for (size_t c = 0; c < length; c++)
    {
        fprintf(fptr, alphabet[c]);
        if (wordLength > 1)
            hyperwebsterGenerator(alphabet, length, wordLength - 1, fptr);
    }
    fprintf(fptr, "]");
}

int main()
{
    char *englishAlphabet[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    char *binaryAlphabet[] = {"0", "1"};
    int wordLength = 2;

    FILE *fptr = fopen("hyperwebster.out", "w");

    hyperwebsterGenerator(englishAlphabet, COUNT_OF(englishAlphabet), wordLength, fptr);
    fprintf(fptr, "\n");
    hyperwebsterGenerator(binaryAlphabet, COUNT_OF(binaryAlphabet), wordLength, fptr);

    fclose(fptr);
    return 0;
}