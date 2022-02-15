#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check(pair lock_pair, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
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

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // find index of candidate name given and add it to the rank array
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // for each rank, i
    for (int i = 0; i < candidate_count; i++)
    {
        // go through the lower ranks, j
        for (int j = i + 1; j < candidate_count; j++)
        {
            // add 1 for i against j
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // for each candidate, i
    for (int i = 0; i < candidate_count; i++)
    {
        // go through each candidate again, j
        for (int j = 0; j < candidate_count; j++)
        {
            // compare candidates, add pair only if i > j
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // bubble sort
    // for i from 0 to n-2
    for (int i = 0; i < pair_count - 1; i++)
    {
        // if i'th and i+1'th elements out of order
        if (preferences[pairs[i].winner][pairs[i].loser] <
            preferences[pairs[i + 1].winner][pairs[i + 1].loser])
        {
            // swap them
            pair x;
            x = pairs[i];
            pairs[i] = pairs[i + 1];
            pairs[i + 1] = x;
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // for each pair,
    for (int i = 0; i < pair_count; i++)
    {
        bool cycle = false;

        // for each person loser wins against, check if they create a cycle
        for (int j = 0; j < MAX; j++)
        {
            // if this pair creates a cycle, change cycle to true
            if (locked[pairs[i].loser][j])
            {
                if (check(pairs[i], j))
                {
                    cycle = true;
                }
            }
        }

        // if no one creates a cycle, lock the pair
        if (!cycle)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// check for cycle
bool check(pair lock_pair, int loser)
{
    // recursive case

    // if loser has won before,
    for (int i = 0; i < MAX; i++)
    {
        // run this function on the person they won against
        if (locked[loser][i])
        {
            return check(lock_pair, i);
        }
    }

    // base case

    // if loser is winner, return true because it is a cycle
    if (loser == lock_pair.winner)
    {
        return true;
    }

    // does not win and is not the same as lock_pair.winner
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < MAX; i++)
    {
        bool lost = false;

        for (int j = 0; j < MAX; j++)
        {
            if (locked[j][i] == true)
            {
                lost = true;
                break;
            }
        }

        if (!lost)
        {
            printf("%s\n", candidates[i]);
            break;
        }
    }
}
