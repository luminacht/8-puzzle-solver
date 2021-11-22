// Program to print path from root node to destination node
// for N*N -1 puzzle algorithm using Branch and Bound
// The solution assumes that instance of puzzle is solvable
#include <bits/stdc++.h>
#include <list>
using namespace std;
#define N 3
#define BLANK '0'

typedef enum Moves {
    UP, DOWN, LEFT, RIGHT, //values for moving up, down, left, right, respectively
    INPUT         //value assigned for initial and goal input states
} Moves;

typedef struct State {
    Moves action;           //action that resulted to this board state
    char mat[N][N];      //resulting board configuration after applying action
    Node *parent;
} State;

class Node;

list<Node> closed, fringe;

typedef struct Solution {
    Moves action;
    struct Solution *next;
} Solution;

void inputState(State * const state) {

    // Initial configuration
    // Value 0 is used for empty space
    /* 2D array declaration*/
    /*Counter variables for the loop*/
    char i, j;
    char tempCheck[9] = {0};
    state->action = INPUT;

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

// State Expanding Function.
void Expand()
{
    State cur, temp;

    //add current state to the closed list.
    closed.push_back(cur);
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            //finding the 0 element in the state array.
            if (cur.mat[i][j] == 0)
            {
                // if the 0 not in the first row.
                if (i > 0)
                {
                    // set the  basic elements
                    temp = cur;
                    temp.parent = &(closed.back());
                    // shift the zero element UP..
                    swap(temp.mat[i][j], temp.mat[i - 1][j]);
                    // search for the child in the closed list.
                    // if the child not found in the closed list.
                    if (!InClosed(temp))
                    {
                        //set remaining elements
                        temp.g += 1;
                        temp.Heurs();
                        temp.t = temp.g + temp.h;
                        fringe.push_front(temp); //push the child into the fringe list
                                                 //space++;//increment the space counter
                    }
                }
                //if the 0 is not in the last row.
                if (i < N - 1)
                {
                    temp = cur;
                    temp.parent = &(closed.back());
                    //shift the zero element DOWN.
                    swap(temp.mat[i][j], temp.mat[i + 1][j]);
                    if (!InClosed(temp))
                    {
                        temp.g += 1;
                        temp.Heurs();
                        temp.t = temp.g + temp.h;
                        fringe.push_front(temp);
                        //space++;
                    }
                } // if the 0 element not in the first column.
                if (j > 0)
                {
                    temp = cur;
                    temp.parent = &(closed.back());
                    // shift it LEFT.
                    swap(temp.mat[i][j], temp.mat[i][j - 1]);
                    if (!InClosed(temp))
                    {
                        temp.g += 1;
                        temp.Heurs();
                        temp.t = temp.g + temp.h;
                        fringe.push_front(temp);
                        //space++;
                    }
                } // if the zero elemnt not in the last column.
                if (j < N - 1)
                {
                    temp = cur;
                    temp.parent = &(closed.back());
                    //shift is right
                    swap(temp.mat[i][j], temp.mat[i][j + 1]);
                    if (!InClosed(temp))
                    {
                        temp.g += 1;
                        temp.Heurs();
                        temp.t = temp.g + temp.h;
                        fringe.push_front(temp);
                        //space++;
                    }
                }
            }
        }
    }
    //remove the expanded state from the fringe list
    fringe.remove(cur);
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