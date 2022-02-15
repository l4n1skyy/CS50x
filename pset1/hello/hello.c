// 1. Prompts user for their name.
// 2. Prints hello, name.

#include <stdio.h>
#include <cs50.h>

void hello(void);
int main(void)
{
    hello();
}

void hello(void)
{
    // ask user for name and greet user
    string name = get_string("What is your name?\nAnswer: ");
    printf("hello, %s\n", name);
}
