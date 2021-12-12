#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>


int main(int ac, string av[])
{

// ARGUMENTS

    if (ac == 2)
    {
        // KEY
        for (int i = 0; i < strlen(av[1]); i++)
        {
            // ERROR
            if (isdigit(av[1][i]) == false)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        int k = atoi(av[1]);

        string ptxt = get_string("plaintext: ");
        printf("ciphertext: ");

// READ -- CONVERT

        // PLAINTXT TO CIPHERTXT
        for (int i = 0; i < strlen(ptxt); i++)
        {
            //LOWER LETTER
            if (ptxt[i] >= 'a' && ptxt[i] <= 'z')
            {
                printf("%c", ((((ptxt[i] - 'a') + k) % 26) + 'a'));
            }
            // UPPER LETTER
            else if (ptxt[i] >= 'A' && ptxt[i] <= 'Z')
            {
                printf("%c", ((((ptxt[i] - 'A') + k) % 26) + 'A'));
            }
            // DIFFERENT CHARACTER OF THE ALPHABET
            else
            {
                printf("%c", ptxt[i]);
            }
        }
        printf("\n");
        return 0;
    }
    // ERROR
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}