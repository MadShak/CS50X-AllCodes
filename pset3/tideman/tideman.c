#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

//The line #define MAX 9 is some syntax used here to mean that MAX is a constant (equal to 9).
#define MAX 9

// Two-dimensional array preferences [i][j].
int preferences[MAX][MAX];

// [j] is blocked under [i]
bool lock = true;
bool locked[MAX][MAX];

// There is a loser and a winner per pair.
typedef struct

{
    int loser;
    int winner;
}

pair;


string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Functions.
void valLock(int j);
int comparator(const void *a, const void *b);
void print_winner(void);
void sort_pairs(void);
void record_preferences(int ranks[]);
bool makes_cycles(int start, int loser);
void add_pairs(void);
void lock_pairs(void);
bool vote(int rank, string name, int ranks[]);

int main(int ac, string av[])
{
    // Validating.
    if (ac < 2)
    {
        printf("Command: tideman [candidate]\n");
        return 1;
    }

    // fill candidates array.
    candidate_count = ac - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = av[i + 1];
    }

    // Blocked and trash.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            preferences[i][j] = 0;
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Keep querying for votes.
    for (int i = 0; i < voter_count; i++)
    {

        int ranks[candidate_count];

        // Keep querying for rank.
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    lock_pairs();
    add_pairs();
    print_winner();
    sort_pairs();

    return 0;
}

// Update ranks.
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name,  candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences.
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Register the pairs of candidates who have preference over each other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// Sort.
int comparator(const void *a, const void *b)
{

    pair *orderA = (pair *)a;
    pair *orderB = (pair *)b;

    return (preferences[orderB->winner][orderB->loser] - preferences[orderA->winner][orderA->loser]);

}

void sort_pairs(void)

{
    qsort(pairs, pair_count, sizeof(pair), comparator);
}

// Check for cycles on the graph.
void valLock(int j)
{
    if (j == 0)
    {
        return;
    }

    int r = 0;
    bool rank[j];
    for (int i = 0; i < j; i++)
    {
        rank[i] = false;
    }

    valLock(j - 1);

    for (int i = 0; i < j; i++)

    {
        for (int k = 0; k < j; k++)
        {
            if (locked[i][k] == true)
            {
                rank[i] = true;
            }
        }
    }

    for (int i = 0; i < j; i++)

    {
        if (rank[i] == true)
        {
            r++;
        }
    }

    if (r == j)

    {
        lock = false;
    }

}

// Check cycles.
bool makes_cycles(int start, int loser)

{
    if (loser == start)

    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)

    {
        if (locked[loser][i])

        {
            if (makes_cycles(start, i))

            {
                return true;
            }
        }
    }

    return false;
}

// Block candidate pairs.
void lock_pairs()

{
    for (int i = 0; i < pair_count; i++)

    {
        if (!makes_cycles(pairs[i].winner, pairs[i].loser))

        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner on the screen.
void print_winner(void)
{
    int rank;
    int winner;

    for (int i = 0; i < candidate_count; i++)
    {
        rank = 0;
        for (int k = 0; k < candidate_count; k++)
        {
            if (locked[k][i] == false)
            {
                rank++;
            }
        }

        // Prints all chart names.
        if (rank == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }
}