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
            cout << "matrix["<<i<<"]["<<j<<"]:";
            scanf("%d", &holder);

            if (holder >= 0 && holder < 9)
                if (!holdCheck[holder])
                {
                    temp_state.A[i][j] = holder;
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
void printMatrix(int const A[n][n])
{
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        for (char j = 0; j < n; j++)
            if (A[i][j] == '0')
                printf("|  ");
            else
                printf("| %d ", A[i][j]);
        printf("| \n");
    }
    printf("\n");
}