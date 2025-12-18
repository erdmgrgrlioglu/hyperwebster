#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//could be better

int bit_length(int n)
{
    int bits = 0;
    do
    {
        bits++;
        n >>= 1;
    } while (n > 0);
    return bits;
}

char **BinaryAlphabetGenerator(int n)
{
    if (n <= 0)
        return NULL;

    int max_value = n - 1;
    int bits = bit_length(max_value);

    char **alphabet = malloc(n * sizeof(char *));
    if (!alphabet)
        return NULL;

    for (int i = 0; i < n; i++)
    {
        alphabet[i] = malloc(bits + 1); // +1 for '\0'
        if (!alphabet[i])
            return NULL;

        for (int j = 0; j < bits; j++)
            alphabet[i][j] = '0';

        alphabet[i][bits] = '\0';

        int value = i;
        int pos = bits - 1;
        while (value > 0 && pos >= 0)
        {
            alphabet[i][pos] = (value & 1) ? '1' : '0';
            value >>= 1;
            pos--;
        }
    }
    return alphabet;
}

void hyperwebsterGenerator(char *alphabet[], size_t length, size_t wordLength, FILE *fptr)
{
    for (size_t i = 0; i < length; i++)
    {
        fprintf(fptr, alphabet[i]);
        if (wordLength > 1)
            hyperwebsterGenerator(alphabet, length, wordLength - 1, fptr);
    }
}

void hyperwebsterReader(char *alphabet[], size_t length, size_t wordLength, size_t index, FILE *fptr)
{
    size_t characterLength = bit_length(length - 1);
    size_t chapterSize = 0;
    for (size_t l = 0; l < wordLength; l++)
    {
        chapterSize += pow(length, l);
    }

    size_t size = ((index % chapterSize) + 1) * characterLength;
    char buf[size];
    fseek(fptr, chapterSize * floor(index / chapterSize) * characterLength, 0);
    fwrite(buf, 1, fread(buf, 1, size, fptr), stdout);
}

int main()
{
    size_t wordLength = 3;
    int numberOfCharactersInAlphabet = 2;
    char **alphabet = BinaryAlphabetGenerator(numberOfCharactersInAlphabet);
    FILE *fptr = fopen("hyperwebster.out", "w+");

    hyperwebsterGenerator(alphabet, numberOfCharactersInAlphabet, wordLength, fptr);
    hyperwebsterReader(alphabet, numberOfCharactersInAlphabet, wordLength, 13, fptr);

    fclose(fptr);
    return 0;
}
