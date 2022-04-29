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
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
int get_index_in_candidates(string name);
void record_preferences(int ranks[]);
void add_pairs(void);
int get_victory_margin(pair check_pair);
void sort_pairs(void);
bool check_cycle_in_graph(int start_at, int never_encounter);
void lock_pairs(void);
void print_winner(void);

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = get_index_in_candidates(name);
            return true;
        }
    }
    return false;
}

int get_index_in_candidates(string name)
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(candidates[j], name) == 0)
        {
            return j;
        }
    }

    return -1;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        int win_candidate_index = ranks[i];

        for (int j = i + 1; j < candidate_count; j++)
        {
            int loss_candidate_index = ranks[j];
            preferences[win_candidate_index][loss_candidate_index]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int margin_of_victory_of_i = preferences[i][j] - preferences[j][i];

            if (margin_of_victory_of_i > 0)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (margin_of_victory_of_i < 0)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

int get_victory_margin(pair check_pair)
{
    return preferences[check_pair.winner][check_pair.loser] - preferences[check_pair.loser][check_pair.winner];
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        pair max_pair = pairs[i];
        int max_index = i;

        for (int j = i + 1; j < pair_count; j++)
        {
            if (get_victory_margin(pairs[j]) > get_victory_margin(max_pair))
            {
                max_pair = pairs[j];
                max_index = j;
            }
        }

        pairs[max_index] = pairs[i];
        pairs[i] = max_pair;
    }
    return;
}

/**
 * @param {number} star_at - the loser
 * @param {number} never_encounter - the winner
 * @returns {bool} - true if cycle is found
 * */
bool check_cycle_in_graph(int start_at, int never_encounter)
{
    int wins_from = 0;
    int wins_from_index_array[candidate_count];
    bool encountered = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[start_at][i])
        {
            wins_from_index_array[wins_from] = i;
            wins_from++;
            if (i == never_encounter)
            {
                encountered = true;
            }
        }
    }
    if (encountered)
    {
        return true;
    }
    else if (wins_from == 0)
    {
        return false;
    }
    else
    {
        bool return_array[wins_from];
        for (int j = 0; j < wins_from; j++)
        {
            return_array[j] = check_cycle_in_graph(wins_from_index_array[j], never_encounter);
        }
        bool flag = false;
        for (int k = 0; k < wins_from; k++)
        {
            flag = flag || return_array[k];
            if (flag == true)
            {
                return true;
            }
        }
        return false;
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!check_cycle_in_graph(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool winner_found = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                winner_found = false;
                break;
            }
        }
        if (winner_found)
        {
            printf("%s\n", candidates[i]);
            break;
        }
    }
    return;
}