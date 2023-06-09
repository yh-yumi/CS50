#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int j = 0; j < candidate_count; j++) //search the candidates
    {
        if (strcmp(name, candidates[j].name) == 0) // string cannot compare, have to use the strcmp func
        {
            candidates[j].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    string loser_name;
    int loser_votes;

    for (int n = 0; n < candidate_count - 1; n++)
    {
        if (candidates[n].votes > candidates[n + 1].votes)
        {
            loser_name = candidates[n + 1].name;
            loser_votes = candidates[n + 1].votes;
            candidates[n + 1].name = candidates[n].name;
            candidates[n + 1].votes = candidates[n].votes;
            candidates[n].name = loser_name;
            candidates[n].votes = loser_votes;

        }
    }
    for (int m = 0; m < candidate_count - 1; m++)
    {
        if (candidates[m].votes == candidates[candidate_count - 1].votes)
        {
            printf("%s\n", candidates[m].name);
        }
    }
    printf("%s\n", candidates[candidate_count - 1].name);
    return;
}