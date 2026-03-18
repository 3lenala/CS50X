#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Maximum score you can get for a letter
#define MAX_SCORE 10

int get_letter_score(char word_letter);
int get_word_score(string word);
void compare_results(int score_player_1, int score_player_2);
string toupper_string(string word);

int main(void)
{

    string word_player_1 = get_string("Player 1: ");
    word_player_1 =
        toupper_string(word_player_1); // Ensure all letters are uppercase to standardize scoring
    int score_player_1 = get_word_score(word_player_1);

    string word_player_2 = get_string("Player 2: ");
    word_player_2 = toupper_string(word_player_2);
    int score_player_2 = get_word_score(word_player_2);

    compare_results(score_player_1, score_player_2);
}

int get_letter_score(char word_letter)
{
    // To get the score for a letter
    const char *scores[MAX_SCORE] = {"AEILNORSTU", "DG", "BCMP", "FHVWY", "KX",
                                     "",           "",   "J",    "",      "QZ"};
    // The strings are made of letters that have the same value in the game.
    // Each string at index i contains all the letters worth (i + 1) points.
    // Indices with empty strings (like 5, 6, and 8) correspond to point values not assigned to any
    // letter in ls.
    int points_letter;

    // len will be used to evaluate the number of letters that give the same score
    int len;
    for (int i = 0; i < MAX_SCORE; i++)
    {
        len = strlen(scores[i]);
        // word_letter is compared to every
        // letter in every string of the array
        for (int j = 0; j < len; j++)
        {
            char letter = scores[i][j];
            if (word_letter == letter)
            {
                points_letter = i + 1;
                // once the letter is found, its score is related to its index i
                return (points_letter);
            }
        }
    }
    return 0;
}

int get_word_score(string word)
{
    int length_word = strlen(word);
    int sum = 0;
    char word_letter;
    for (int k = 0; k < length_word; k++)
    {
        word_letter = word[k]; // to get the score of the word we need to evaluate how many points
                               // each letter gives
        sum += get_letter_score(word_letter); // and do the sum over all of them
    }
    return sum;
}

void compare_results(int score_player_1, int score_player_2) // Both scores are compared
{
    if (score_player_1 == score_player_2)
    {
        printf("Tie!\n");
    }
    else if (score_player_1 > score_player_2)
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

string toupper_string(string word) // Every letter in the word is converted to uppercase
{
    for (int n = 0, len = strlen(word); n < len; n++)
    {
        word[n] = toupper(word[n]);
    }
    return word; // returns the same variable that was inputted, in this case it is okay since
} // we won't need the previous value anymore
