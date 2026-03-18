#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void to_lower_word(char *word, char *lower_word);

int main(void)
{
    char word[] = "HOL'A!#¢∞";
    char *lower_word = malloc(sizeof(word));
    to_lower_word(word, lower_word);
    printf("w: %s\n", word);
    printf("lw: %s\n", lower_word);
    free(lower_word);
}

void to_lower_word(char *word, char *lower_word)
{
    for (int i = 0, length_word = strlen(word); i < length_word; i++)
    {
        lower_word[i] = tolower(word[i]);
    }
}
