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
void IterativeDepthFirstSearch();
void Astar();
void Expand();
void PrintPath(State *s);
bool InClosed(State &s);

int main()
{

    //Asks the user to input the initial state of the puzzle
    printf("Initial Board State: \n");
    inputState(); //input the initial state

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            start_state.s[i][j] = temp_state.s[i][j];
        }
    }

    //Displays the initial state of the puzzle
    cout << "\nInitial Board:";
    printMatrix(start_state.s);

    //Asks the user to input the goal state of the puzzle
    printf("Desired Goal State: \n");
    inputState();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Goal[i][j] = temp_state.s[i][j];
        }
    }

    //Displays the goal state of the puzzle
    cout << "\nGoal Board:";
    printMatrix(Goal);

//Asks the user to input the type of search to be performed
ask:
    int search_select;
    cout << "Select Algorithm:" << endl;
    cout << "1. Iterative Deepening Search" << endl;
    cout << "2. A* Search" << endl;
    cout << "> ";
    cin >> search_select;

    //initialize start state
    start_state.g = 0;                                      // start at root node
    start_state.manhattanHeuristic();                       //set heuristic value
    start_state.total_cost = start_state.g + start_state.h; //total cost
    start_state.parent = NULL;                              // root node

    //selecting the search algorithm
    switch (search_select)
    {
    case 1:
        timer = (clock() * 1000) / CLOCKS_PER_SEC;
        IterativeDepthFirstSearch();
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
void IterativeDepthFirstSearch()
{

    int depth = 0;
    cout << "\nStarting Iterative Depth First Search Algorithm... \n";
    while (true)
    {
        current_state = start_state;           //set current state to start state
        active_list.push_front(current_state); //add current state to active list
        while (!active_list.empty())           //while active list is not empty
        {

            current_state = active_list.front(); //set current state to front of active list

            if (current_state.is_goal()) //checks whether the current state already reached the goal
            {
                runtime = ((clock() * 1000) / CLOCKS_PER_SEC) - timer; //calculates the total runtime of the search
                //print the search costs
                cout << "\nTime = " << runtime << "ms\n";
                cout << "Nodes Expanded = " << nodes << "\n";
                cout << "Moves = " << current_state.g << "\n";
                cout << "Solution Path: \n";
                PrintPath(&current_state);
                //print the solution path
                return;
            } //continue searching child nodes

            else if (depth > current_state.g) //if depth not reached yet
            {
                nodes++;
                Expand(); //expand the current state
            }
            else
            {
                active_list.pop_front(); //remove the current state from active list
            }
        }
        // clear both lists for the next round
        active_list.clear();
        closed_list.clear();
        // increase the search depth
        depth++;
    }
}

//Function for A* Search
void Astar()
{
    cout << "\nStarting A* Algorithm... \n";
    current_state = start_state;           //set current state to start state
    active_list.push_front(current_state); //add current state to active list
    while (true)
    {

        current_state = active_list.front();
        for (list<State>::iterator it = active_list.begin(); it != active_list.end(); ++it)
        {
            // find state with minimum total cost
            if ((*it) < current_state)
            {
                current_state = (*it);
            }
        }

        if (current_state.is_goal()) //checks whether the current state already reached the goal
        {
            // calculate and print the search costs
            runtime = ((clock() * 1000) / CLOCKS_PER_SEC) - timer;
            cout << "\nTime = " << runtime << "ms\n";
            cout << "Nodes Expanded = " << nodes << "\n";
            cout << "Moves = " << current_state.g << "\n";
            cout << "Solution Path: \n";
            PrintPath(&current_state);
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

    closed_list.push_back(current_state);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            //find blank tile in state array
            if (current_state.s[i][j] == 0)
            {
                // if not in the first row
                if (i > 0)
                {
                    //set child
                    temp_state = current_state;
                    temp_state.parent = &(closed_list.back());
                    // shift blank tile UP
                    swap(temp_state.s[i][j], temp_state.s[i - 1][j]);
                    // search for the child in the closed list
                    // if the child not found in the closed list
                    if (!InClosed(temp_state))
                    {
                        temp_state.g += 1;
                        temp_state.manhattanHeuristic();
                        temp_state.total_cost = temp_state.g + temp_state.h;
                        temp_state.moves = 0;
                        active_list.push_front(temp_state);
                    }
                }
                //if not in last row
                if (i < n - 1)
                {
                    temp_state = current_state;
                    temp_state.parent = &(closed_list.back());
                    //shift the blank tile DOWN
                    swap(temp_state.s[i][j], temp_state.s[i + 1][j]);
                    if (!InClosed(temp_state))
                    {
                        temp_state.g += 1;
                        temp_state.manhattanHeuristic();
                        temp_state.total_cost = temp_state.g + temp_state.h;
                        temp_state.moves = 1;
                        active_list.push_front(temp_state);
                    }
                }
                // if not in the first column
                if (j > 0)
                {
                    temp_state = current_state;
                    temp_state.parent = &(closed_list.back());
                    // shift blank tile LEFT
                    swap(temp_state.s[i][j], temp_state.s[i][j - 1]);
                    if (!InClosed(temp_state))
                    {
                        temp_state.g += 1;
                        temp_state.manhattanHeuristic();
                        temp_state.total_cost = temp_state.g + temp_state.h;
                        temp_state.moves = 2;
                        active_list.push_front(temp_state);
                    }
                } // if not in the last column
                if (j < n - 1)
                {
                    temp_state = current_state;
                    temp_state.parent = &(closed_list.back());
                    // shift blank tile RIGHT
                    swap(temp_state.s[i][j], temp_state.s[i][j + 1]);
                    if (!InClosed(temp_state))
                    {
                        temp_state.g += 1;
                        temp_state.manhattanHeuristic();
                        temp_state.total_cost = temp_state.g + temp_state.h;
                        temp_state.moves = 3;
                        active_list.push_front(temp_state);
                    }
                }
            }
        }
    }
    //remove the current state from the active list
    active_list.remove(current_state);
}

void PrintPath(State *s)
{
    //print the solution path
    int counter = 0;
    int sg = s->g; //set the current state's g value
    int temp[sg];  //create a temporary array to store the solution path
    int hold;      //hold the value of the current state's g value

    for (s; s; s = s->parent, counter++) //while the parent of the current state is not null
    {
        temp[counter] = s->moves; //add the move to the temp array
    }

    for (int i = 1; i < sg + 1; i++) //reverse the temp array
    {
        hold = temp[sg - i];                          //hold the value of the current index
        printf("%d. %s \n", i, action[temp[sg - i]]); //print the move
    }
}

//Function to check whether the state is in the closed list
bool InClosed(State &s)
{
    for (list<State>::iterator it = closed_list.begin(); it != closed_list.end(); ++it) //iterate through the closed list
    {
        if ((*it) == s) //if the state is found in the closed list
        {
            return true;
        }
    }
    return false;
}
