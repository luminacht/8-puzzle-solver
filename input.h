#define n 3
using namespace std;

void inputState()
{
    // Initial configuration
    // Value 0 is used for empty space
    /* 2D array declaration*/
    /*Counter variables for the loop*/
    int i, j;
    int holdCheck[9] = {0};

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            int holder;
            cout << "Board [" << i << "][" << j << "]:";
            cin >> holder;

            if (holder >= 0 && holder < 9)
                if (!holdCheck[holder])
                {
                    temp_state.s[i][j] = holder;
                    holdCheck[holder] = 1;
                }
                else
                {
                    cout << "   ERROR: Number " << holder << "is already used. Try again with different input.\n"
                         << holder;
                    --j;
                }
            else
            {
                cout << "   ERROR: Invalid input. Enter a number from 0 to 8. \n";
                --j;
            }
        }
    }
}

// Function to print N x N matrix
void printMatrix(int const s[n][n])
{
    cout << "\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (s[i][j] == '0')
                cout << "|  ";
            else
                cout << "| " << s[i][j] << " ";
        cout << "| \n";
    }
    cout << "\n";
}