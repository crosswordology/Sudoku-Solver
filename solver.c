#include <stdio.h>

// Check if there exist a cell with the same number in the same column
int checkUsedRow(int grid[9][9], int i, int row, int num)
{
    if (grid[row][i] != num)
        return 1;

    return 0;
}

// Check if there exist a cell with the same number in the same column
int checkUsedCol(int grid[9][9], int i, int col, int num)
{
    if (grid[i][col] != num)
        return 1;

    return 0;
}

// Check if there exist a cell with the same number in the same 9x9 box
int checkUsedBox(int grid[9][9], int i, int row, int col, int num)
{
    int rowStart = (row/3) * 3;
    int colStart = (col/3) * 3;

    if(grid[rowStart + (i%3)][colStart + (i/3)] != num)
        return 1;

    return 0;
}

// Check if it's possible to use a number in the corresponding cell
int isAvailable(int grid[9][9], int row, int col, int num)
{
    int rowStart = (row/3) * 3;
    int colStart = (col/3) * 3;
    int i;

    for(i = 0; i < 9; ++i)
    {
        if (grid[row][i] == num) return 0;
        if (grid[i][col] == num) return 0;
        if (grid[rowStart + (i%3)][colStart + (i/3)] == num) return 0;
    }
    return 1;
}

// Takes a partially filled grid and attempts to solve if it has a solution
int solve(int grid[9][9], int row, int col)
{
    int i;
    if(row<9 && col<9)
    {
        if(grid[row][col] != 0)
        {
            if((col+1)<9) return solve(grid, row, col+1);
            else if((row+1)<9) return solve(grid, row+1, 0);
            else return 1;
        }
        else
        {
            for(i=0; i<9; ++i)
            {
                if(isAvailable(grid, row, col, i+1))
                {
                    grid[row][col] = i+1;
                    if((col+1)<9)
                    {
                        if(solve(grid, row, col+1)) return 1;
                        else grid[row][col] = 0;
                    }
                    else if((row+1)<9)
                    {
                        if(solve(grid, row+1, 0)) return 1;
                        else grid[row][col] = 0;
                    }
                    else return 1;
                }
            }
        }
        return 0;
    }
    else return 1;
}

// Simply print the solved grid
void printSolution(int grid[9][9])
{
    int i, j;

    printf("\n*-----*-----*-----*\n");
    for(i = 1; i < 10; ++i)
    {
        for(j = 1; j < 10; ++j) printf("|%d", grid[i-1][j-1]);
        printf("|\n");

        if (i%3 == 0) printf("*-----*-----*-----*\n");
    }
}

// Test the above functions
int main()
{
    // 0 means unknown
    int sudoku[9][9]={
                        {3, 0, 6, 0, 0, 0, 5, 0, 0},
                        {0, 7, 0, 0, 6, 0, 0, 8, 9},
                        {0, 5, 9, 0, 0, 2, 4, 0, 6},
                        {9, 0, 0, 0, 5, 1, 0, 0, 0},
                        {0, 0, 5, 0, 0, 0, 8, 0, 0},
                        {6, 0, 0, 2, 4, 0, 0, 0, 3},
                        {5, 9, 0, 0, 8, 6, 1, 2, 7},
                        {1, 6, 0, 0, 0, 0, 0, 0, 8},
                        {0, 8, 0, 0, 0, 0, 0, 0, 0}
                    };

    if(solve(sudoku, 0, 0))
    {
        printSolution(sudoku);
    }
    else
    {
        printf("\n\nIMPOSSIBLE TO SOLVE\n\n");
    }

    return 0;
}
