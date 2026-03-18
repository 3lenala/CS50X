#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char encrypt(char character, int key);
bool is_upper(char character);

int main(int argc, string argv[]) // void no, incluir int argc, string argv[]
// argc = 2, argv = [caesar.c, #key]
{
    // we ask for the plain text
    // we want to cipher it
    if (argc != 2)
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }
    string argv_1 = argv[1];
    int len_argv = strlen(argv_1);
    for (int i = 0; i < len_argv; i++)
    {
        if (!isdigit(argv_1[i]))
        {
            printf("Usage: ./caesar key \n");
            return 1;
        }
    }
    // turn argv[1] from string to int
    // key is the number of places that the letter is shifted
    int key = atoi(argv_1);
    if (key % 26 != 0)
    {
        key %= 26; // to avoid loops if key > 26
    }
    // ensures key is always within a valid range before encryption

    string text = get_string("plaintext: ");
    int len_text = strlen(text);
    char encrypted;
    printf("ciphertext: ");
    for (int i = 0; i < len_text; i++)
    {
        char character = text[i];
        if (isalpha(character)) // only the letters are encrypted
        {
            // letter -> in the range of lowercases or in the range of uppercases in ASCII
            encrypted = encrypt(character, key);
            printf("%c", encrypted);
        }
        else // everything else is kept the same way
        {
            encrypted = character;
            printf("%c", encrypted);
        }
    }
    printf("\n");
}

char encrypt(char character, int key) // differenciate
// between uppercase letters and lowercase letters
// upper and lower in different sections of the ASCII table
// turn lower into another lower and uper into uper
{
    char encrypted_letter;
    if (is_upper(character))
    {
        encrypted_letter = ((character - 'A') + key) % 26 + 'A';
        // 'A' + number of places that needs to be shifted
    }
    else // if it's lower
    {
        encrypted_letter = ((character - 'a') + key) % 26 + 'a';
        // 'a' + number of places that needs to be shifted
    }
    return encrypted_letter;
}

bool is_upper(char character) // given a letter to check if it is within the
                              // range of upper cases in ASCII
{
    if (character >= 'A' && character <= 'Z')
    {
        return true;
    }
    return false;
}
