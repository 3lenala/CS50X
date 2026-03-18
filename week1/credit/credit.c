#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int check_first_digit(int first_digit);
bool is_valid_amex(int len, int second_digit);
bool is_valid_visa(int len, int second_digit);
bool is_valid_mastercard(int len, int second_digit);
int get_card_type(int len, int digits[]);
int calculate_luhn_sum(int len, int digits[]);
bool validate_luhn_sum(int sum);

// Valid cards have between 13 and 16 digits
#define MAX_DIGITS 16
#define MIN_DIGITS 13

// 4 possibilities considered, each identified with its index in the position array
// i.e., VISA is represented by the int 2; 0 represents failure
const string possibilities[4] = {"INVALID", "AMEX", "VISA", "MASTERCARD"};

// the lenghts for each valid card
#define LEN_AMEX 15
#define LEN_MASTERCARD 16
#define LEN_VISA_1 13 // two possibilities for VISA
#define LEN_VISA_2 16

// the first digit of each valid card
#define FIRST_AMEX 3
#define FIRST_VISA 4
#define FIRST_MASTERCARD 5

// the second digit of each valid card
#define SECOND_AMEX_1 4
#define SECOND_AMEX_2 7
#define SECOND_MIN_MASTERCARD 1 // second digit of mastercard can be any number
#define SECOND_MAX_MASTERCARD 5 // between 1 and 5 (inclusive)

int main(void)
{
    long card;
    do
    {
        card = get_long("Card number: ");
    }
    while (card <= 0);

    // Convert the card number into an array of digits

    int reversed_card[MAX_DIGITS];
    int len = 0;

    // Store the digits of the card number in reverse order
    while (card > 0)
    {
        reversed_card[len] = card % 10;
        len++;
        card /= 10;
        if (len > MAX_DIGITS)
        {
            printf("INVALID\n");
            return 0;
        }
    }
    if (len < MIN_DIGITS)
    {
        printf("INVALID\n");
        return 0;
    }
    int digits[len];
    for (int i = 0; i < len; i++) // Reverse the array to get digits in correct order
    {
        digits[i] = reversed_card[len - i - 1];
    }

    int card_type = get_card_type(len, digits);
    // Check if the first two digit and the length match a card brand

    // If they don't match there is no need to check for the luhn relation
    if (card_type != 0) // If it could exist, we check the result of the luhn algorithm
    {
        int sum = calculate_luhn_sum(len, digits);
        if (!validate_luhn_sum(sum))
        {
            card_type = 0;
            // If the card doesn't check the Luhn algorithm, it's INVALID, represented by 0
        }
    }
    printf("%s\n", possibilities[card_type]);
}

// FUNCTIONS USED IN THE PROGRAM

// Returns the card brand code based on the first digit
int check_first_digit(int first_digit)
{
    if (first_digit == FIRST_AMEX)
    {
        return 1;
    }
    else if (first_digit == FIRST_VISA)
    {
        return 2;
    }
    else if (first_digit == FIRST_MASTERCARD)
    {
        return 3;
    }
    return 0;
}

// Given the brand associated with the first digit, the following conditions are checked

bool is_valid_amex(int len, int second_digit)
{
    const int second_amex_1 = 4;
    const int second_amex_2 = 7;
    if (len != LEN_AMEX)
    {
        return false;
    }
    if (second_digit != second_amex_1 && second_digit != second_amex_2)
    {
        return false;
    }
    return true;
}

bool is_valid_visa(int len, int second_digit)
{
    if (len == LEN_VISA_1 || len == LEN_VISA_2)
    {
        return true;
    }
    return false;
}

bool is_valid_mastercard(int len, int second_digit)
{
    if (len != LEN_MASTERCARD)
    {
        return false;
    }
    if (second_digit < SECOND_MIN_MASTERCARD || second_digit > SECOND_MAX_MASTERCARD)
    {
        return false;
    }
    return true;
}
// If the conditions given above are not met, the number is not valid

int get_card_type(int len, int digits[])
{
    int first_numb = check_first_digit(digits[0]);
    if (first_numb == 1)
    {
        if (is_valid_amex(len, digits[1]))
        {
            return first_numb;
        }
    }
    else if (first_numb == 2)
    {
        if (is_valid_visa(len, digits[1]))
        {
            return first_numb;
        }
    }
    else if (first_numb == 3)
    {
        if (is_valid_mastercard(len, digits[1]))
        {
            return first_numb;
        }
    }
    return 0; // 1 represents failure
}

// Calculates Luhn's checksum for the card number
int calculate_luhn_sum(int len, int digits[])
{
    int sum = 0;
    int value;

    for (int j = len - 2; j >= 0; j -= 2) // step 1 and 2 of the luhn method
    {
        value = 2 * digits[j];
        if (value >= 10)
        {
            value = value / 10 + value % 10;
        }
        sum += value;
    }

    for (int k = len - 1; k >= 0; k -= 2) // step 3 of the luhn method
    {
        sum += digits[k];
    }
    return sum;
}

// Returns true if the Luhn checksum is valid (divisible by 10)
bool validate_luhn_sum(int sum) // we check  if the luhn algorithm checks
{
    if (sum % 10 == 0)
    {
        return true;
    }
    return false;
}
