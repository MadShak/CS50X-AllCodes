#include <stdio.h>
#include <cs50.h>

// solicita nome e mostra na tela

int main(void)

{
    string name = get_string("What is your name?\n");

    printf("hello, %s\n", name);
}