#include <cs50.h>
#include <stdio.h>

int greedy(int coins[], int change, int i_max);
int main(void)
{
    int change;
    int n_coins = 0;
    // The available coins are considered in an array
    int coins[] = {25, 10, 5, 1};
    // Calculates the number of elements in the array by dividing
    // the total size of the array (in bytes) by the size of one element
    // can be changed for different currency
    int i_max = sizeof(coins) / sizeof(coins[0]); // // sizeof returns the total number
    // of bytes used by the array or structure
    do // to make sure that the user introduces a positive integer
    {
        change = get_int("change owed (in cents): ");
    }
    while (change <= 0);

    n_coins = greedy(coins, change, i_max);

    printf("You need to give %d coins \n", n_coins);
    return 0;
}

int greedy(int coins[], int change, int i_max) // the greedy function will give the number of coins
{
    int coin;
    int n_coins = 0;
    for (int i = 0; i < i_max; i++)
    {
        coin = coins[i];
        n_coins += change / coin;
        change %= coin;
    }
    return n_coins;
}
