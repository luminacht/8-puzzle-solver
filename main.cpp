// Program to print path from root node to destination node
// for N*N -1 puzzle algorithm using Branch and Bound
// The solution assumes that instance of puzzle is solvable
#include <bits/stdc++.h>
#include <list>
#include <algorithm>
#include <stdio.h>

using namespace std;
#define N 3
#define BLANK '0'

class Node
{
public:
    Node *parent;
    char mat[N][N];
    int g, h, t;
    void Heuristics();
    void Astar();
    bool calculateCost();
    bool InClosed();
};

list<Node> closed, fringe;
Node start, ending, cur, temp;
int nodeCount;

typedef enum Moves
{
    UP,
    DOWN,
    LEFT,
    RIGHT, //values for moving up, down, left, right, respectively
    INPUT  //value assigned for initial and goal input states
} Moves;

typedef struct State
{
    Moves action; //action that resulted to this board state
} State;

typedef struct Solution
{
    Moves action;
    struct Solution *next;
} Solution;

int inputState(State *const state)
{

    // Initial configuration
    // Value 0 is used for empty space
    /* 2D array declaration*/
    /*Counter variables for the loop*/
    char i, j;
    char holdCheck[9] = {0};
    state->action = INPUT;

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
                    temp.mat[i][j] = holder;
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
bool calculateCost()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (cur.mat[i][j] && cur.mat[i][j] == ending.mat[i][j])
                return true;
}

void Astar()
{
    cur = start;
    fringe.push_front(cur);
    while (true)
    {
        // process all states in the fringe.
        cur = fringe.front();
        for (list<Node>::iterator it = fringe.begin(); it != fringe.end(); ++it)
        {
            // find the state with the minimum total cost.
            if ((*it) < cur)
            { //using the state < operator..
                cur = (*it);
            }
        }
        // if minimal total cost state is the goal.
        if (cur.calculateCost())
        {
            // print the solution path.
            cout << "Cost: " << cur.g << "\n";
            cout << "Nodes expanded: " << nodeCount << "\n";
            // exit the function.
            return;
        } // if the minimal total cost state is not the goal.
        else
        {
            // expand it;
            nodeCount++;
            Expand();
        }
    }
}

// state heuristic cost calculator.
void Node::Heuristics()
{
    int i, i2, j, j2, Heuristic = 0;
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
                    // finding similar elements.
                    if (ending.mat[i][j] == mat[i2][j2])
                    {
                        //Manhattan Based Heuristic displacement cost.
                        Heuristic += abs(i - i2) + abs(j - j2);
                        found = true;
                    }
                    if (found)
                        break;
                }
                if (found)
                    break;
            }
        }
    } // setting the state heuristic cost.
    h = Heuristic;
}

// State Expanding Function.
void Expand()
{

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
                        temp.Heuristics();
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
                        temp.Heuristics();
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
                        temp.Heuristics();
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
                        temp.Heuristics();
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

bool InClosed(Node &s)
{
    for (list<Node>::iterator it = closed.begin(); it != closed.end(); ++it)
    {
        if ((*it) == s)
        { //using the state == operator
            return true;
        }
    }
    return false;
}

// Driver code
int main()
{
    State initial;
    State goal;

    printf("Initial Board State: \n");
    inputState(&initial);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            start.mat[i][j] = temp.mat[i][j];
        }
    }

    printMatrix(start.mat);

    printf("Desired Goal State: \n");
    inputState(&goal);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            ending.mat[i][j] = temp.mat[i][j];
        }
    }

    printMatrix(ending.mat);

    return 0;
}