#include <stdio.h>
#include <bits/stdc++.h>
#include <queue>
#include <algorithm>
#include <string>
#include <time.h>

using namespace std;
#define N 3

class State
{
public:
    State *parent; // parent node
    char state[N][N]; // state array of the board
    int gc, hc;       // gc = cost, hc = heuristic cost
    State *action;
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

    int manhattanDistance()
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
};

enum Move
{
    UP, DOWN, LEFT, RIGHT
};

int inputState(State *state)
    {
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
                    state->state[i][j] = holder;
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

State *createState(State *state, Move move) {
    State *newState;
    State *action;

    //copy the board configuration of `state` to `newState`
    //while searching for the row and column of the blank character
    char i, j;        //used for traversing the 3x3 arrays
    char row, col;    //coordinates of the blank character

    for(i = 0; i < 3; ++i) {
        for(j = 0; j < 3; ++j) {
            if(state->state[i][j] == '0') {
                row = i;
                col = j;
            }

            newState->state[i][j] = state->state[i][j];
        }
    }

    //test if the coordinates are valid after translation based on the move
    //if it is, swap the concerned board values to reflect the move
    if(move == UP && row - 1 >= 0) {
        char temp = newState->state[row - 1][col];
        newState->state[row - 1][col] = '0';
        newState->state[row][col] = temp;
        newState->action = UP;
        return newState;
    }
    else if(move == DOWN  && row + 1 < 3) {
        char temp = newState->state[row + 1][col];
        newState->state[row + 1][col] = '0';
        newState->state[row][col] = temp;
        newState->action = DOWN;
        return newState;
    }
    else if(move == LEFT  && col - 1 >= 0) {
        char temp = newState->state[row][col - 1];
        newState->state[row][col - 1] = '0';
        newState->state[row][col] = temp;
        newState->action = LEFT;
        return newState;
    }
    else if(move == RIGHT && col + 1 < 3) {
        char temp = newState->state[row][col + 1];
        newState->state[row][col + 1] = '0';
        newState->state[row][col] = temp;
        newState->action = RIGHT;
        return newState;
    }
    return NULL;
}

int main()
{
    State initialState;
    State goalState;

    cout << "INITIAL STATE: " << endl;
    inputState(&initialState);
    initialState.printMatrix();

    cout << "GOAL STATE: " << endl;
    inputState(&goalState);
    goalState.printMatrix(); 
}
