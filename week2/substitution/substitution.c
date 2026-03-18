#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_LENGTH 26

bool error(string message);
char encrypt(char plain_char, string substitution_key);
bool validate_key(int argc, string raw_key, char *substitution_key);

int main(int argc, string argv[])
// expect exactly one command-line argument: the substitution key
{
    char substitution_key[ALPHABET_LENGTH];
    if (!validate_key(argc, argv[1], substitution_key))
    {
        return 1;
    }
    // the key is now valid

    // Prompt the user for input text to encrypt
    string text = get_string("plaintext: ");
    int text_length = strlen(text);
    printf("ciphertext: ");
    for (int i = 0; i < text_length; i++)
    {
        char plain_char = text[i];
        // encrypt only alphabetic characters, leave others unchanged
        if (isalpha(plain_char))
        {
            // NOTE: letter -> in the range of lowercases or in the range of uppercases in ASCII
            printf("%c", encrypt(plain_char, substitution_key));
        }
        else // everything else remains unchanged
        {
            printf("%c", plain_char);
        }
    }
    printf("\n");
    return 0;
}

char encrypt(char plain_char, string substitution_key) // substitution algorithm
{
    char cipher_char;
    int position;
    if (isupper(plain_char))
    {
        // map uppercase letter to corresponding character in key
        position = plain_char - 'A';
        cipher_char = substitution_key[position];
    }
    else
    {
        // map lowercase letter, preserving case in output
        position = plain_char - 'a';
        cipher_char = tolower(substitution_key[position]);
    }
    return cipher_char;
}

bool error(string message)
{
    printf("%s \n", message);
    return false;
}

bool validate_key(int argc, string raw_key, char *substitution_key)
{
    if (argc != 2)
    {

        return error("Usage: ./substitution key \n");
    }
    int key_length = strlen(raw_key);

    if (key_length != ALPHABET_LENGTH)
    {
        return error("Length error: key must contain 26 characters \n");
    }

    int position;
    char key_char;
    // track how many times each letter appears in the key to detect duplicates
    int seen_letters[ALPHABET_LENGTH] = {0};
    for (int i = 0; i < key_length; i++)
    {
        key_char = raw_key[i];
        if (!isalpha(key_char)) // the key must contain only alphabetic characters
        {
            return error("All the characters of the key must be alphabetical \n");
        }

        // convert all key letters to uppercase to simplify encryption logic
        substitution_key[i] = toupper(key_char);
        key_char = substitution_key[i];

        // there should not be duplicates
        // reject keys with repeated letters
        position = key_char - 'A';
        seen_letters[position]++;
        if (seen_letters[position] > 1)
        {
            return error("All the alphabetical characters in the key must be different \n");
        }
    }
    return true;
}
