#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>


//The line #define MAX is some syntax used here to mean that MAX is a constant of Voters and Candidates.
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// Two-dimensional array preferences [i][j].
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Every candidate has a name, votes and a bool value called eliminated.
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// The array candidates will keep track of all of the candidates in the election.
candidate candidates[MAX_CANDIDATES];

// The program also has two global variables: voter_count and candidate_count.
int voter_count;
int candidate_count;

// Functions
int find_min(void);
void tabulate(void);
bool is_tie(int min);
void eliminate(int min);
bool print_winner(void);
bool vote(int voter, int rank, string name);

int main(int ac, string av[])
{
    // Validating
    if (ac < 2)
    {
        printf("Command: runoff [candidate]\n");
        return 1;
    }


    candidate_count = ac - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = av[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes.
    for (int i = 0; i < voter_count; i++)
    {


        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Loop until set the winner.
    while (true)
    {

        tabulate();


        bool won = print_winner();
        if (won)
        {
            break;
        }


        int min = find_min();
        bool tie = is_tie(min);


        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }


        eliminate(min);


        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record valid votes.

bool vote(int voter, int rank, string name)
{
    bool exist = false;
    for (int i = 0; i < candidate_count; i++)
    {

        if (strcmp(name, candidates[i].name) == 0)
        {

            preferences[voter][rank] = i;
            exist = true;
            break;

        }
    }
    return exist;
}

// Tabulate those not deleted.
void tabulate(void)
{

    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes += 1;
                break;
            }
        }

    }

    return;
}

// If there is a winner, print.
bool print_winner(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        string most = candidates[i].name;
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", most);
            return true;
        }
    }
    return false;
}

// Returns the minimum number of votes.
int find_min(void)
{
    int minvotes = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes < minvotes)
        {
            minvotes = candidates[i].votes;
        }
    }
    return minvotes;
}

// Informs if there is a tie between all candidates.
bool is_tie(int minvotes)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes != minvotes)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the last placed.
void eliminate(int minvotes)
{
    for (int i = 0; i < candidate_count; i++)
        if (candidates[i].votes == minvotes)
        {
            candidates[i].eliminated = true;
        }
    return;
}