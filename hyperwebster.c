#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define COUNT_OF(x) ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))
#define MAX_SIZE 100

typedef struct
{
    char arr[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack *stack)
{
    stack->top = -1;
}

bool isEmpty(Stack *stack)
{
    return stack->top == -1;
}

bool isFull(Stack *stack)
{
    return stack->top == MAX_SIZE - 1;
}

void push(Stack *stack, char value)
{
    if (isFull(stack))
        return;
    stack->arr[++stack->top] = value;
}

char pop(Stack *stack)
{
    if (isEmpty(stack))
        return -1;

    char popped = stack->arr[stack->top];
    stack->top--;
    return popped;
}

int peek(Stack *stack)
{
    if (isEmpty(stack))
        return -1;
    return stack->arr[stack->top];
}

char *printStack(Stack *stack, bool mode)
{
    static char buffer[MAX_SIZE + 1];
    int i;
    for (i = 0; i <= stack->top; i++)
        if (mode)
            buffer[i] = stack->arr[i] + 'A';
        else
            buffer[i] = stack->arr[i] + '0';
    buffer[i] = '\0';
    return buffer;
}

// still could be better
void hyperwebsterGenerator(char *alphabet[], size_t length, int wordLength, Stack *stack, FILE *fptr)
{
    for (size_t c = 0; c < length; c++)
    {
        fprintf(fptr, printStack(stack, length != 2));
        fprintf(fptr, alphabet[c]);
        fprintf(fptr, "\n");
        push(stack, c);
        if (wordLength > 1)
            hyperwebsterGenerator(alphabet, length, wordLength - 1, stack, fptr);
        pop(stack);
    }
}

int main()
{
    char *englishAlphabet[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    char *binaryAlphabet[] = {"0", "1"};
    int wordLength = 5;

    FILE *fptr = fopen("hyperwebster.out", "w");
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    initialize(stack);

    hyperwebsterGenerator(englishAlphabet, COUNT_OF(englishAlphabet), wordLength, stack, fptr);
    fprintf(fptr, "\n");
    hyperwebsterGenerator(binaryAlphabet, COUNT_OF(binaryAlphabet), wordLength, stack, fptr);

    fclose(fptr);
    return 0;
}
