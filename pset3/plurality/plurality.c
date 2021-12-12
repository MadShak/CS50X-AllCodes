#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

//The line #define MAX 9 is some syntax used here to mean that MAX is a constant (equal to 9).
#define MAX 9

//The file then defines a struct called a candidate. Each candidate has two fields:
//a string called name representing the candidate’s name, and an int called votes.
typedef struct

{
    string name;
    int votes;
}

candidate;
candidate candidates[MAX];

//global variable candidate_count representing the number of candidates in the election.

int candidate_count;
void print_winner(void);

//vote takes a single argument, a string called name, representing the name of the candidate who was voted for.
bool vote(string name);

//main makes a call to the print_winner function to print out the winner (or winners).
int main(int ac, string av[])
{
    if (ac < 2)
    {
        printf("Command: plurality [candidate]\n");
        return 1;
    }

    candidate_count = ac - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = av[i + 1];
        candidates[i].votes = 0;
    }

    int vote_counter = get_int("Number of voters: ");

    for (int i = 0; i < vote_counter; i++)
    {
        string name = get_string("Vote: ");

        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}

//vote function.
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

//print_winner function.
void print_winner(void)
{
    int mxvts = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > mxvts)
        {
            mxvts = candidates[i].votes;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == mxvts)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}