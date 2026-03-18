ls#include <cs50.h>
#include <stdio.h>

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
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void merge_sort(int list[], int length_list, int indx[]);

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
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
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
    return;
}

// Sort pairs in decreasing order by strength of victory
// merge sort algorithm
void sort_pairs(void)
{
    int strength[pair_count];
    int indx[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        strength[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        indx[i] = i;
    }
    merge_sort(strength, pair_count, indx);
    pair temp_pair[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        temp_pair[i].winner = pairs[indx[i]].winner;
        temp_pair[i].loser = pairs[indx[i]].loser;
    }
    for (int j = 0; j < pair_count; j++)
    {
        pairs[j].winner = temp_pair[j].winner;
        pairs[j].loser = temp_pair[j].loser;
    }
    return;
}

void merge_sort(int list[], int length_list, int indx[])
{
    if (length_list <= 1)
    {
        return;
    }
    int length_left = length_list / 2;
    int length_right = length_list - length_left;
    int left[length_left];
    int right[length_right];
    int left_index[length_left];
    int right_index[length_right];
    for (int i = 0; i < length_left; i++)
    {
        left[i] = list[i];
        left_index[i] = indx[i];
    }
    merge_sort(left, length_left, left_index);
    for (int i = length_left; i < length_list; i++)
    {
        right[i-length_left] = list[i];
        right_index[i - length_left] = indx[i];
    }
    merge_sort(right, length_right, right_index);
    int i = 0;
    int j = 0;
    int k = 0;
    int temp_list[length_list];
    int temp_index[length_list];

    while (j < length_left || i < length_right)
    {
        if (j >= length_left)
        {
            temp_list[k] = right[i];
            temp_index[k] = right_index[i];
            i++;
        }
        else if (i >= length_right)
        {
            temp_list[k] = left[j];
            temp_index[k] = left_index[j];
            j++;
        }
        else if (right[i] > left[j])
        {
            temp_list[k] = right[i];
            temp_index[k] = right_index[i];
                i++;
        }
        else
        {
            temp_list[k] = left[j];
            temp_index[k] = left_index[j];
            j++;
        }
        k++;
    }

    for (int i = 0; i < length_list; i++)
    {
        list[i] = temp_list[i];
        indx[i] = temp_index[i];
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    return;
}

// Print the winner of the election
void print_winner(void)
{

    return;
}
