// Program to print path from root node to destination node
// for N*N -1 puzzle algorithm using Branch and Bound
// The solution assumes that instance of puzzle is solvable
#include <bits/stdc++.h>
using namespace std;
#define N 3
#define BLANK_CHARACTER '0'

typedef enum Move {
    UP, DOWN, LEFT, RIGHT, //values for moving up, down, left, right, respectively
    NOT_APPLICABLE         //value assigned for initial and goal input states
} Move;

typedef struct State {
    Move action;           //action that resulted to this board state
    char mat[N][N];      //resulting board configuration after applying action
} State;

void inputState(State * const state) {

    // Initial configuration
    // Value 0 is used for empty space
    /* 2D array declaration*/
    /*Counter variables for the loop*/
    char i, j;
    char tempCheck[9] = {0};
    state->action = NOT_APPLICABLE;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            int temp;
            printf("matrix[%d][%d]:", i, j);
            scanf("%d", &temp);

            if (temp >= 0 && temp < 9)
                if (!tempCheck[temp]) {
                    state->mat[i][j] = temp;
                    tempCheck[temp] = 1;
                } else {
                    printf("   ERROR: Number %d is already used. Try again with different input.\n", temp);
                    --j;
                }
            else {
                printf("   ERROR: Invalid input. Enter a number from 0 to 8.\n");
                --j;

            }
        }
    }
}

// Function to print N x N matrix
void printMatrix(char const mat[N][N])
{
    printf("\n");
    for (char i = 0; i < N; i++)
    {
        for (char j = 0; j < N; j++)
            printf("| %d ", mat[i][j]);
        printf("| \n");
    }
    printf("\n");
}

// Function to calculate the number of misplaced tiles
// ie. number of non-blank tiles not in their goal position
int calculateCost(int initial[N][N], int final[N][N])
{
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (initial[i][j] && initial[i][j] != final[i][j])
                count++;
    return count;
}

// Function to check if (x, y) is a valid matrix coordinate
int isSafe(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Driver code
int main()
{
    State initial;
    State goal;

    printf("Initial Board State: \n");
    inputState(&initial);
    printMatrix(initial.mat);

    printf("Desired Goal State: \n");
    inputState(&goal);
    printMatrix(goal.mat);

    return 0;
}