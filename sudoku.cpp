/*
    CodeAlpha Internship - Task 3: Sudoku Solver
    ------------------------------------------------
    - Represents the grid as a 2D array (9x9), 0 = empty cell
    - Solves it using a recursive backtracking algorithm
    - Validates row, column, and 3x3 subgrid constraints before
      placing any number
*/

#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 9;
const int EMPTY = 0;

// ---------- Print the grid ----------
void printGrid(const vector<vector<int>> &grid) {
    for (int row = 0; row < SIZE; row++) {
        if (row % 3 == 0 && row != 0) {
            cout << "------+-------+------\n";
        }
        for (int col = 0; col < SIZE; col++) {
            if (col % 3 == 0 && col != 0) {
                cout << "| ";
            }
            if (grid[row][col] == EMPTY) {
                cout << ". ";
            } else {
                cout << grid[row][col] << " ";
            }
        }
        cout << "\n";
    }
}

// ---------- Check if placing num at (row, col) is valid ----------
bool isValid(const vector<vector<int>> &grid, int row, int col, int num) {
    // Row constraint
    for (int c = 0; c < SIZE; c++) {
        if (grid[row][c] == num) return false;
    }

    // Column constraint
    for (int r = 0; r < SIZE; r++) {
        if (grid[r][col] == num) return false;
    }

    // 3x3 subgrid constraint
    int boxRowStart = (row / 3) * 3;
    int boxColStart = (col / 3) * 3;
    for (int r = boxRowStart; r < boxRowStart + 3; r++) {
        for (int c = boxColStart; c < boxColStart + 3; c++) {
            if (grid[r][c] == num) return false;
        }
    }

    return true;
}

// ---------- Find the next empty cell ----------
// Returns true and sets row/col if an empty cell is found, false if the
// grid is completely filled.
bool findEmptyCell(const vector<vector<int>> &grid, int &row, int &col) {
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (grid[row][col] == EMPTY) {
                return true;
            }
        }
    }
    return false;
}

// ---------- Recursive backtracking solver ----------
bool solveSudoku(vector<vector<int>> &grid) {
    int row, col;

    // Base case: no empty cells left -> solved
    if (!findEmptyCell(grid, row, col)) {
        return true;
    }

    for (int num = 1; num <= 9; num++) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid)) {
                return true; // this number worked, propagate success up
            }

            grid[row][col] = EMPTY; // backtrack: undo and try the next number
        }
    }

    return false; // no number worked here -> trigger backtracking further up
}

// ---------- Validate that a starting puzzle is well-formed ----------
bool isValidPuzzle(const vector<vector<int>> &grid) {
    if (grid.size() != SIZE) return false;
    for (const auto &row : grid) {
        if (row.size() != SIZE) return false;
        for (int val : row) {
            if (val < 0 || val > 9) return false;
        }
    }

    // Check no duplicate given numbers break the rules from the start
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            int val = grid[row][col];
            if (val != EMPTY) {
                // Temporarily clear it to check against the rest of the grid
                vector<vector<int>> temp = grid;
                temp[row][col] = EMPTY;
                if (!isValid(temp, row, col, val)) {
                    return false;
                }
            }
        }
    }

    return true;
}

int main() {
    // 0 represents an empty cell. This is a classic medium-difficulty puzzle.
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Puzzle to solve:\n\n";
    printGrid(grid);

    if (!isValidPuzzle(grid)) {
        cout << "\nThis puzzle is invalid (conflicting given numbers).\n";
        return 1;
    }

    cout << "\nSolving...\n\n";

    if (solveSudoku(grid)) {
        cout << "Solved!\n\n";
        printGrid(grid);
    } else {
        cout << "No solution exists for this puzzle.\n";
    }

    return 0;
}
