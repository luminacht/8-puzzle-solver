#define n 3
using namespace std;

// External variables from main file
extern int Goal[n][n];
extern bool aSearch;

class State
{
public:
    State *parent;        // The parent state
    int s[n][n];          // The state of the puzzle
    int moves;            // The number of moves to reach this state
    int g, h, total_cost; // g: cost from initial state to this state
                          // h: heuristic cost from this state to goal state
                          // total_cost: g + h

    State();        // Default constructor for State
    bool is_goal(); // Check if this state is the goal state
    bool operator==(const State &) const;
    bool operator<(const State &) const;
    void manhattanHeuristic(); // Calculate the heuristic cost
};

State::State()
{
    g = h = total_cost = 0; // Initialize g, h, and total_cost
    parent = NULL;          // Initialize parent
}

void State::manhattanHeuristic()
{
    int h_val = 0;              // Initialize temporary holder for heuristic value
    bool found;                 // Flag to check if the value is found
    for (int i = 0; i < n; i++) // Loop through the rows of Goal state
    {
        for (int j = 0; j < n; j++) // Loop through the columnns of Goal state
        {
            found = false;                 // Reset the flag
            for (int i2 = 0; i2 < n; i2++) // Loop through the rows of current state
            {
                for (int j2 = 0; j2 < n; j2++) // Loop through the columns of current state
                {

                    if (Goal[i][j] == s[i2][j2]) // If the value is found
                    {
                        //dx + dy
                        h_val += abs(i - i2) + abs(j - j2); // Calculate the heuristic value from the current state to the goal state
                        found = true;
                    }
                    if (found)
                        break;
                }
                if (found)
                    break;
            }
        }
    }
    h = h_val; // Copy the heuristic value from temporary holder to h
}

// Check if this state is the goal state
bool State::is_goal()
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // if any two items not equal - not goal
            if (s[i][j] != Goal[i][j])
                return false;
        }
    }
    //reaching this point means all items are equal - goal state found
    return true;
}

bool State::operator==(const State &r) const
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            //if any two items not equal - not goal
            if (s[i][j] != r.s[i][j])
                return false;
        }
    }
    // states are equal
    return true;
}

bool State::operator<(const State &r) const
{

    if (aSearch)
    { // for heuristic based algorithms
        return total_cost < r.total_cost;
    }
    else
    {
        return g < r.g; // for normal search algorithms
    }
}

list<State> closed_list, active_list; // closed list and active list for fringe
State startState, currentState, tempState;