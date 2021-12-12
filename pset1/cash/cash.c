#include <stdio.h>
#include <cs50.h>
#include <math.h>

int c(int cents);

int main(void)

{

//Get input
    float n;

    do
    {

        n = get_float("How much change?\n");

    }

    while (n < 0);

//Set Output

    printf("%d\n", c((int)round(n * 100)));

}

int c(int cents)

{
    return cents / 25 + (cents % 25) / 10 + ((cents % 25) % 10) / 5 + ((cents % 25) % 10) % 5;
}