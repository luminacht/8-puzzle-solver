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
    State();
    char state[N][N]; // state array of the board
    int gc, hc;       // gc = cost, hc = heuristic cost

    State printMatrix()
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

int main()
{
    State initialState;
    State goalState;

    cout << "Enter the initial state: " << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> initialState.state[i][j];
        }
    }
    initialState.printMatrix();

    cout << "Enter the goal state: " << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> goalState.state[i][j];
        }
    }
}
