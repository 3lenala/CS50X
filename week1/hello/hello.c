#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // asks for input using get_string (Included in cs50.h)
    string name = get_string("What's your name? ");
    printf("hello, %s\n", name);
}
