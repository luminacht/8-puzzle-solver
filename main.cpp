/* Nestor Rafael Oscillada
   Paul Marren Claveron
   Lestor Bonto
   Jan Vincent Rada */

#include <iostream>
#include <list>
#include <ctime>

#include "class.h"
#include "input.h"
#define n 3

using namespace std;

bool aSearch = false;
int Goal[n][n];
const char *action[4] = {"UP", "DOWN", "LEFT", "RIGHT"};

//tracks generated nodes in search process
int nodes = 0;
//tracks runtime of search
int runtime = 0, timer = 0;

//Declaration of the functions for searching, expanding, and printing
void IDS();
void Astar();
void Expand();
void PrintPath(State *r);
bool InClosed(State &r);

int main()
{

    //Asks the user to input the initial state of the puzzle
    cout << "Initial Board State: \n";
    inputState(); //input the initial state

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            startState.s[i][j] = tempState.s[i][j];
        }
    }

    //Displays the initial state of the puzzle
    cout << "\nInitial Board:";
    printMatrix(startState.s);

    //Asks the user to input the goal state of the puzzle
    cout << "Desired Goal State: << \n";
    inputState();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Goal[i][j] = tempState.s[i][j];
        }
    }

    //Displays the goal state of the puzzle
    cout << "\nGoal Board:";
    printMatrix(Goal);

//Asks the user to input the type of search to be performed
ask:
    int select;
    cout << "Select Algorithm:" << endl;
    cout << "1. Iterative Deepening Search" << endl;
    cout << "2. A* Search" << endl;
    cout << "> ";
    cin >> select;

    //initialize start state
    startState.g = 0;                                    // start at root node
    startState.manhattanHeuristic();                     //set heuristic value
    startState.totalCost = startState.g + startState.h; //total cost
    startState.parent = NULL;                            // root node

    //selecting the search algorithm
    switch (select)
    {
    case 1:
        timer = (clock() * 1000) / CLOCKS_PER_SEC;
        IDS();
        break;
    case 2:
        aSearch = true;
        timer = (clock() * 1000) / CLOCKS_PER_SEC;
        Astar();
        break;
    default:
        cout << "Invalid Input" << endl;
        goto ask; //revert back to asking for input if invalid input
    }
    return 0;
}

//Function for Iterative Deepening Search
void IDS()
{

    int depth = 0;
    cout << "\nInitiatizing Iterative Deepening Search: \n";
    while (true)
    {
        currentState = startState;            //set current state to start state
        fringeList.push_front(currentState); //add current state to fringe list
        while (!fringeList.empty())          //while fringe list is not empty
        {

            currentState = fringeList.front(); //set current state to front of fringe list

            if (currentState.is_goal()) //checks whether the current state already reached the goal
            {
                runtime = ((clock() * 1000) / CLOCKS_PER_SEC) - timer; //calculates the total runtime of the search
                //print the search costs
                cout << "\nTime = " << runtime << "ms\n";
                cout << "Nodes Expanded = " << nodes << "\n";
                cout << "Moves = " << currentState.g << "\n";
                cout << "Solution Path: \n";
                PrintPath(&currentState);
                //print the solution path
                return;
            } //continue searching child nodes

            else if (depth > currentState.g) //if depth not reached yet
            {
                nodes++;
                Expand(); //expand the current state
            }
            else
            {
                fringeList.pop_front(); //remove the current state from fringe list
            }
        }
        // clear both lists for the next round
        fringeList.clear();
        closedList.clear();
        // increase the search depth
        depth++;
    }
}

//Function for A* Search
void Astar()
{
    cout << "\nInitializing A* Search: \n";
    currentState = startState;            //set current state to start state
    fringeList.push_front(currentState); //add current state to fringe list
    while (true)
    {

        currentState = fringeList.front();
        for (list<State>::iterator it = fringeList.begin(); it != fringeList.end(); ++it)
        {
            // find state with minimum total cost
            if ((*it) < currentState)
            {
                currentState = (*it);
            }
        }

        if (currentState.is_goal()) //checks whether the current state already reached the goal
        {
            // calculate and print the search costs
            runtime = ((clock() * 1000) / CLOCKS_PER_SEC) - timer;
            cout << "\nTime = " << runtime << "ms\n";
            cout << "Nodes Expanded = " << nodes << "\n";
            cout << "Moves = " << currentState.g << "\n";
            cout << "Solution Path: \n";
            PrintPath(&currentState);
            // print the solution path
            return;
        }
        else
        { //continue searching child nodes
            nodes++;
            Expand();
        }
    }
}
void Expand()
{

    closedList.push_back(currentState);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            //find blank tile in state array
            if (currentState.s[i][j] == 0)
            {
                // if not in the first row
                if (i > 0)
                {
                    //set child
                    tempState = currentState;
                    tempState.parent = &(closedList.back());
                    // shift blank tile UP
                    swap(tempState.s[i][j], tempState.s[i - 1][j]);
                    // search for the child in the closed list
                    // if the child not found in the closed list
                    if (!InClosed(tempState))
                    {
                        tempState.g += 1;
                        tempState.manhattanHeuristic();
                        tempState.totalCost = tempState.g + tempState.h;
                        tempState.moves = 0;
                        fringeList.push_front(tempState);
                    }
                }
                //if not in last row
                if (i < n - 1)
                {
                    tempState = currentState;
                    tempState.parent = &(closedList.back());
                    //shift the blank tile DOWN
                    swap(tempState.s[i][j], tempState.s[i + 1][j]);
                    if (!InClosed(tempState))
                    {
                        tempState.g += 1;
                        tempState.manhattanHeuristic();
                        tempState.totalCost = tempState.g + tempState.h;
                        tempState.moves = 1;
                        fringeList.push_front(tempState);
                    }
                }
                // if not in the first column
                if (j > 0)
                {
                    tempState = currentState;
                    tempState.parent = &(closedList.back());
                    // shift blank tile LEFT
                    swap(tempState.s[i][j], tempState.s[i][j - 1]);
                    if (!InClosed(tempState))
                    {
                        tempState.g += 1;
                        tempState.manhattanHeuristic();
                        tempState.totalCost = tempState.g + tempState.h;
                        tempState.moves = 2;
                        fringeList.push_front(tempState);
                    }
                } // if not in the last column
                if (j < n - 1)
                {
                    tempState = currentState;
                    tempState.parent = &(closedList.back());
                    // shift blank tile RIGHT
                    swap(tempState.s[i][j], tempState.s[i][j + 1]);
                    if (!InClosed(tempState))
                    {
                        tempState.g += 1;
                        tempState.manhattanHeuristic();
                        tempState.totalCost = tempState.g + tempState.h;
                        tempState.moves = 3;
                        fringeList.push_front(tempState);
                    }
                }
            }
        }
    }
    //remove the current state from the fringe list
    fringeList.remove(currentState);
}

void PrintPath(State *r)
{
    //print the solution path
    int counter = 0;
    int rg = r->g; //set the current state's g value
    int temp[rg];  //create a temporary array to store the solution path
    int hold;      //hold the value of the current state's g value

    for (r; r; r = r->parent, counter++) //while the parent of the current state is not null
    {
        temp[counter] = r->moves; //add the move to the temp array, this is to reverse the order of the moves.
    }

    for (int i = 1; i < rg + 1; i++) 
    {
        hold = temp[rg - i];               //hold the value of the current index
        cout << i << ". " << action[hold]; //print the move
    }
}

//Function to check whether the state is in the closed list
bool InClosed(State &r)
{
    for (list<State>::iterator it = closedList.begin(); it != closedList.end(); ++it) //iterate through the closed list
    {
        if ((*it) == r) //if the state is found in the closed list
        {
            return true;
        }
    }
    return false;
}
