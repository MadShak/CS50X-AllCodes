#include <stdio.h>
#include <cs50.h>


int main(void)

{

    int n;

// ask for Height

    do
    {

        n = get_int("Whats the Height? ");

    }

    while (n < 1 || n > 8);

// Show # by the number 1

    if (n == 1)

    {

        printf("#  #\n");

    }

// Show # by the number 2

    if (n == 2)

    {

        printf(" #  #\n##  ##\n");

    }

// Show # by the number 3

    if (n == 3)

    {

        printf("  #  #\n ##  ##\n###  ###\n");

    }

// Show # by the number 4

    if (n == 4)

    {

        printf("   #  #\n  ##  ##\n ###  ###\n####  ####\n");

    }

// Show # by the number 5

    if (n == 5)

    {

        printf("    #  #\n   ##  ##\n  ###  ###\n ####  ####\n#####  #####\n");

    }

// Show # by the number 6

    if (n == 6)

    {

        printf("     #  #\n    ##  ##\n   ###  ###\n  ####  ####\n #####  #####\n######  ######\n");

    }

// Show # by the number 7

    if (n == 7)

    {

        printf("      #  #\n     ##  ##\n    ###  ###\n   ####  ####\n  #####  #####\n ######  ######\n#######  #######\n");

    }

// Show # by the number 8

    if (n == 8)

    {

        printf("       #  #\n      ##  ##\n     ###  ###\n    ####  ####\n   #####  #####\n  ######  ######\n #######  #######\n########  ########\n");

    }

}