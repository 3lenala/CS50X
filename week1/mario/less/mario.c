#include <cs50.h>
#include <stdio.h>

void print_row(int height, int row);
int main(void)
{
    int height;
    do
    {
        // prompt user for the pyramid height between 1 and 8 (inclusive)
        height = get_int("height: ");
    }
    while (height < 1 || height > 8);
    // loop through each row from top (row h) to bottom (row 1)
    for (int row = height; row > 0; row--)
    {
        print_row(height, row); // prints the current row of the pyramid
    }
}
void print_row(int height, int row)
{
    // prints a specific row of the double pyramid based on height and row number
    for (int j = 1; j <= height; j++) // prints spaces and hashed to make the left pyramid
    {
        if (j < row)
        {
            printf(" ");
        }
        else
        {
            printf("#");
        }
    }
    printf("\n"); // moves to the next line for the following row
}
