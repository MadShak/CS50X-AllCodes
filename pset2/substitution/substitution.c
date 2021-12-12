#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int ac, string av[])
{

    if (ac != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (strlen(av[1]) != 26)
    {
        printf("key must contain 26 characters.\n");
        return 1;
    }

    int avln = strlen(av[1]);
    for (int i = 0; i < avln; i++)
    {
        if (isalpha(av[1][i]) == false)
        {
            printf("Only alphabetic characters.\nPlease, type valids characters.\n");
            return 1;
        }
    }

    char alph[2][26];
    for (int i = 0; i < avln; i++)
    {
        alph[0][i] = 'A' + i;
        alph[1][i] = av[1][i];
    }

    for (int i = 0; i < avln; i++)
    {
        int a = 0;
        for (int b = 0; b < avln; b++)
        {
            if (toupper(alph[1][b]) == toupper(alph[1][i]))
            {
                a++;
                if (a == 2)
                {
                    printf("repeated value!\n");
                    return 1;
                }
            }
        }
    }

    string ptxt = get_string("Plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, a = strlen(ptxt); i < a; i++)
    {
        if (isalpha(ptxt[i]))
        {
            if (islower(ptxt[i]))
            {
                for (int b = 0; b < avln; b++)
                {
                    if (tolower(alph[0][b]) == ptxt[i])
                    {
                        printf("%c", tolower(alph[1][b]));
                    }
                }
            }
            if (isupper(ptxt[i]))
            {
                for (int b = 0; b < avln; b++)
                {
                    if (toupper(alph[0][b]) == ptxt[i])
                    {
                        printf("%c", toupper(alph[1][b]));
                    }
                }
            }
        }
        else
        {
            printf("%c", ptxt[i]);
        }
    }
    printf("\n");
    return 0;
}