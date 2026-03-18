#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define PER_WORDS 100 // we want to evaluate a certain number per 100 words

void count_text_elements(string text, float *letters, float *words, float *sentences);
float calc_index(float L, float S);
void classify_index(int index);

int main(void)
{
    float letters, words, sentences;
    // ask the user for some text
    // until the user introduces a non-zero
    do
    {
        string text = get_string("Text; ");
        // we obtain the letter, word, and sentence count
        count_text_elements(text, &letters, &words, &sentences);
    }
    while (letters == 0 || words == 0 || sentences == 0);

    // obtain the average number of letters per word = number of letters / number of words
    float L = letters / words;
    // multiply the average number of letters/word per 100 words
    L = L * PER_WORDS;

    // obtain the average number of words per sentence = number of words / number of sentences, and
    // divide 100 / words per sentence (it will give us the average number of sentences per 100
    // words)
    float words_per_sentence = words / sentences;
    float S = PER_WORDS / words_per_sentence;

    // use the formula to get the index
    float I = calc_index(L, S);
    int index = round(I);
    // classify the reading level based on the result from the index formula
    classify_index(index);
}
// L is the average number of letters per 100 words
// S is the average number of sentences per 100 words

void count_text_elements(string text, float *letters, float *words, float *sentences)
{
    // counts the total number of letter, words, and sentences so that we only need to
    // scan the text once and then operate
    int len_text = strlen(text);
    char character;
    float word_count = 1; // the first word doesn't include a space before
    // we will use the character ' ' to determine whether a new word starts or not
    float letter_count = 0;
    float sentence_count = 0;
    for (int i = 0; i < len_text; i++)
    {
        character = text[i];
        // I need to obtain the total number of letters, the total number of sentences
        // and the total number of words
        // ASCII table to tabulate the options: letter means
        // (character >= 'A' and character <= 'Z') or (character >= 'a' and character <= 'z')
        if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z'))
        {
            letter_count++;
        }
        else if (character == '.' || character == '!' || character == '?')
        {
            sentence_count++;
        }
        else if (character == ' ')
        {
            word_count++;
        }
    }
    *letters = letter_count;
    *words = word_count;
    *sentences = sentence_count;
}

float calc_index(float L, float S) // the formula to obtain the index
{
    const float INDEX_CONST_L = 0.0588; // constants for the index
    const float INDEX_CONST_S = -0.296;
    const float INDEX_CONST_FREE = -15.8;
    float I;
    I = INDEX_CONST_L * L + INDEX_CONST_S * S + INDEX_CONST_FREE;
    return I;
}

void classify_index(int index) // the calculated index represents the grade
{
    if (index < 1) // with I < 1 and I > 16 as boundary situations
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
}
