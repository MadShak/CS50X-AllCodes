/*

- This program prompt the user for a string of text.
- Count the number of letters, words, and sentences in the text.
- Print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula, rounded to the nearest integer.

*/

#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>


int main(void)

{

// Prompt the user for a string - gets some text input from the user.

    string txt = get_string("Txt: ");

    int letters = 0;
    int sentence = 0;
    int word = 1;

// COUNTER - Count the number of letters, words, and sentences in the text.

    for (int i = 0; i < strlen(txt); i++)
    {
        if ((txt[i] >= 'a' && txt[i] <= 'z') || (txt[i] >= 'A' && txt[i] <= 'Z'))
        {
            letters++;
        }
        else if (txt[i] == '.' || txt[i] == '!' || txt[i] == '?')
        {
            sentence++;
        }
        else if (txt[i] == ' ')
        {
            word++;
        }

    }

// Putting it All Together - Print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula.

    float g = 0.0588 * (100 * (float) letters / (float) word) - 0.296 * (100 * (float) sentence / (float) word) - 15.8;
    if (g < 16 && g >= 0)
    {
        printf("Grade %i\n", (int) round(g));
    }
    else if (g >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }

}