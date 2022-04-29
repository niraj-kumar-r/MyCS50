#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What's your name? ");
    // taking in name

    printf("hello, %s\n", name);
    // printing name
}