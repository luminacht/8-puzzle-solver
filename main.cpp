#include <iostream>
#include <list>
#include <ctime>

#include "class.h"
#include "input.h"
#define n 3

using namespace std;

bool aSearch = false;
int Goal[n][n];

//tracks generated nodes in search process
int nodes = 0;
//tracks runtime of search
int runtime = 0, timer = 0;

void IterativeDepthFirstSearch();
void Astar();
void Expand();
void PrintPath(State *s);
bool InClosed(State &s);


int main() {

    printf("Initial Board State: \n");
    inputState();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            start_state.A[i][j] = temp_state.A[i][j];
        }
    }

	cout<<"\nInitial Board:";
    printMatrix(start_state.A);

    printf("Desired Goal State: \n");
    inputState();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Goal[i][j] = temp_state.A[i][j];
        }
    }

	cout<<"\nGoal Board:";
	printMatrix(Goal);

    int search_select;
    cout << "Select Algorithm:" << endl;
    cout << "1. Iterative Deepening Search" << endl;
    cout << "2. A* Search" << endl;
    cout << "> ";
    cin >> search_select;

    //initialize start state
    start_state.g = 0; // start at root node
    start_state.manhattanHeuristic(); //set heuristic value
    start_state.total_cost = start_state.g + start_state.h; //total cost
    start_state.parent = NULL; // root node

    //selecting the search algorithm
    switch (search_select) {
        case 1:
            timer = (clock() * 1000) / CLOCKS_PER_SEC;
            IterativeDepthFirstSearch();
            break;
        case 2:
            aSearch = true;
            timer = (clock() * 1000) / CLOCKS_PER_SEC;
            Astar();
    }
    return 0;
}


void IterativeDepthFirstSearch() {
	
    int depth = 0;
    cout << "\nStarting Iterative Depth First Search Algorithm... \n";
    while (true) {
        current_state = start_state;
        active_list.push_front(current_state);
        while (!active_list.empty())
        {

            current_state = active_list.front();

            if (current_state.is_goal()) {

                runtime = ((clock() * 1000) / CLOCKS_PER_SEC) - timer;
                //print the search costs
                cout << "\nTime = " << runtime << "ms\n";
                cout << "Nodes Expanded = " << nodes << "\n";
                cout << "Moves = " << current_state.g << "\n";
                cout << "Solution Path: \n";
                PrintPath(&current_state);
                //print the solution path
                return;
            } //continue searching child nodes if depth not reached

            else if (depth > current_state.g) {
                nodes++;
                Expand();
            }
            else {
                active_list.pop_front();
            }
        }
        // clear both lists for the next round
        active_list.clear();
        closed_list.clear();
        // increase the search depth
        depth++;
    }
}
void Astar() {

    cout << "\nStarting A* Algorithm... \n";
    current_state = start_state;
    active_list.push_front(current_state);
    while (true) {

        current_state = active_list.front();
        for (list<State>::iterator it = active_list.begin(); it != active_list.end(); ++it) {
            // find state with minimum total cost
            if ((*it) < current_state) {
                current_state = (*it);
            }
        }

        if (current_state.is_goal()) {
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
        else { //continue searching child nodes
            nodes++;
            Expand();
        }
    }
}
void Expand() {

    closed_list.push_back(current_state);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            //find blank tile in state array
            if (current_state.A[i][j] == 0) {
                // if not in the first row
                if (i > 0) {
                    //set child
                    temp_state = current_state;
                    temp_state.parent = &(closed_list.back());
                    // shift blank tile UP
                    swap(temp_state.A[i][j], temp_state.A[i - 1][j]);
                    // search for the child in the closed list
                    // if the child not found in the closed list
                    if (!InClosed(temp_state)) {
                        temp_state.g += 1;
                        temp_state.manhattanHeuristic();
                        temp_state.total_cost = temp_state.g + temp_state.h;
						temp_state.moves = 0;
                        active_list.push_front(temp_state);
                    }
                }
                //if not in last row
                if (i < n - 1) {
                    temp_state = current_state;
                    temp_state.parent = &(closed_list.back());
                    //shift the blank tile DOWN
                    swap(temp_state.A[i][j], temp_state.A[i + 1][j]);
                    if (!InClosed(temp_state)) {
                        temp_state.g += 1;
                        temp_state.manhattanHeuristic();
                        temp_state.total_cost = temp_state.g + temp_state.h;
						temp_state.moves = 1;
                        active_list.push_front(temp_state);
                    }
                }
                // if not in the first column
                if (j > 0) {
                    temp_state = current_state;
                    temp_state.parent = &(closed_list.back());
                    // shift blank tile LEFT
                    swap(temp_state.A[i][j], temp_state.A[i][j - 1]);
                    if (!InClosed(temp_state)) {
                        temp_state.g += 1;
                        temp_state.manhattanHeuristic();
                        temp_state.total_cost = temp_state.g + temp_state.h;
						temp_state.moves = 2;
                        active_list.push_front(temp_state);
                    }
                }// if not in the last column
                if (j < n - 1) {
                    temp_state = current_state;
                    temp_state.parent = &(closed_list.back());
                    // shift blank tile RIGHT
                    swap(temp_state.A[i][j], temp_state.A[i][j + 1]);
                    if (!InClosed(temp_state)) {
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

    active_list.remove(current_state);
}

void PrintPath(State *s) {

	int counter = 0;
	const char *action[4] = {"UP", "DOWN", "LEFT", "RIGHT"};
	int sg = s->g;
	int temp[sg];

	for(s; s; s = s->parent, counter++)
	{
		temp[counter] = s->moves;
	}

	for(int i = 1; i < sg + 1; i++)
	{
		int hold = temp[sg - i];
		printf("%d. %s \n", i, action[hold]);
	}
}

bool InClosed(State &s) {
    for (list<State>::iterator it = closed_list.begin(); it != closed_list.end(); ++it) {
        if ((*it) == s) {
            return true;
        }
    }
    return false;
}
