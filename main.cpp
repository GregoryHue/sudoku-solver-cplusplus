#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

const string PATH_TO_FILE = "sudoku.txt";
const int N = 9;

void showGrid(int **grid)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool solveCase(int **grid, int num, int row, int col)
{
    // cout << "num: " << num << "\t| row: " << row << "\t| col: " << col << "\n";
    // showGrid(grid);

    // Check row
    for (int i = 0; i < N; i++)
    {
        if (num == grid[row][i])
        {
            return false;
        }
    }

    // Check column
    for (int i = 0; i < N; i++)
    {
        if (grid[i][col] == num)
        {
            return false;
        }
    }

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i + startRow][j + startCol] == num)
            {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(int **grid)
{
    int i, j;
    bool sudokuSolved = true;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (grid[i][j] == 0)
            {
                sudokuSolved = false;
                break;
            }
        }
        if (!sudokuSolved)
        {
            break;
        }
    }
    // cout << "sudokuSolved: " << sudokuSolved << "\t| i: " << i << "\t| j: " << j << "\n";

    if (sudokuSolved)
    {
        return true;
    }

    for (int num = 1; num <= N; num++)
    {
        if (solveCase(grid, num, i, j))
        {
            grid[i][j] = num;

            if (solveSudoku(grid))
            {
                return true;
            }
            grid[i][j] = 0;
        }
    }

    return false;
}

bool isGridViable(string path)
{
    ifstream infile(PATH_TO_FILE);
    char character;
    int character_count;
    while (infile >> character)
    {
        if (!isdigit(character))
        {
            return false;
        }
        // cout << character << " ";
        character_count = character_count + 1;
    }
    if (character_count != N * N)
    {
        cout << "\n";
        return false;
    }
    cout << "\n";
    return true;
}

int **loadGrid(string path)
{
    int **grid = new int *[N];
    for (int i = 0; i < N; ++i)
    {
        grid[i] = new int[N];
        for (int j = 0; j < N; ++j)
        {
            grid[i][j] = 0;
        }
    }
    ifstream infile(PATH_TO_FILE);
    char character;
    int i, j = 0;
    while (infile >> character)
    {
        grid[j][i] = character - '0';
        i = i + 1;
        if (i == N)
        {
            i = 0;
            j = j + 1;
        }
    }
    return grid;
}

int main()
{
    cout << "Start:\n";

    int **grid;

    if (isGridViable(PATH_TO_FILE))
    {
        // cout << "Grid is OK\n";
        grid = loadGrid(PATH_TO_FILE);
        showGrid(grid);
        if (solveSudoku(grid))
        {
            showGrid(grid);
            cout << "Soduku solved.\n";
            return 0;
        }
        showGrid(grid);
        cout << "Soduku not solved.\n";
    }
    else
    {
        cout << "File is impossible to find or grid is broken.\n";
        return 0;
    };

    return 0;
}