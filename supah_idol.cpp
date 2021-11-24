#include <stdio.h>
#include <queue>
#include <list>
#include <algorithm>
#include <string>
#include <time.h>

using namespace std;
#define N 3

class State
{
public:
    char state[N][N]; // state array of the board
    int gc, hc;       // gc = cost, hc = heuristic cost
    void printMatrix()
    {
        printf("\n");
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                if (this->state[i][j] == '0')
                    printf("|  ");
                else
                    printf("| %d ", this->state[i][j]);
            printf("| \n");
        }
        printf("\n");
    }

    int heuristics()
    {
        int sum = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (state[i][j] != '0')
                {
                    int x = state[i][j] / N;
                    int y = state[i][j] % N;
                    sum += abs(x - i) + abs(y - j);
                }
            }
        }
        return sum;
    }

    int inputState()
    {

        // Initial configuration
        // Value 0 is used for empty space
        /* 2D array declaration*/
        /*Counter variables for the loop*/
        char i, j;
        char holdCheck[9] = {0};

        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                int holder;
                printf("matrix[%d][%d]:", i, j);
                scanf("%d", &holder);

                if (holder >= 0 && holder < 9)
                    if (!holdCheck[holder])
                    {
                        state[i][j] = holder;
                        holdCheck[holder] = 1;
                    }
                    else
                    {
                        printf("   ERROR: Number %d is already used. Try again with different input.\n", holder);
                        --j;
                    }
                else
                {
                    printf("   ERROR: Invalid input. Enter a number from 0 to 8.\n");
                    --j;
                }
            }
        }
    }

    int isGoalState()
    {
        int i, j;
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                if (state[i][j] != (i * N + j))
                    return 0;
            }
        }
        return 1;
    }
    /*int heuristics()
{
    int i, i2, j, j2, 
    hc = 0;
    bool found;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            found = false;
            for (i2 = 0; i2 < N; i2++)
            {
                for (j2 = 0; j2 < N; j2++)
                {
                    hc += abs(i - i2) + abs(j - j2);
                    printf("Total Heuristic Cost: %d", &hc);
                    // finding similar elements.
                    if (state[i][j] == state[i2][j2])
                    {
                        //Manhattan Based Heuristic displacement cost.
                        found = true;
                        return hc;
                    }
                }
            }
        }
    } 
}*/
};

class Searches // class for all search algorithms
{
public:
    char State::state[N][N]; // state array of the board
    list<State> open, closed;

    void aStar(State state s, State state g)
    {
        open.push_back()
    }
};

int main()
{
    State initialState;
    State goalState;

    cout << "Enter the initial state: " << endl;
    initialState.inputState();
    initialState.printMatrix();

    cout << "Enter the goal state: " << endl;
    goalState.inputState();
    goalState.printMatrix();
}
