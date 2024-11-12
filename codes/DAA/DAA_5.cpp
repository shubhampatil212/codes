#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<vector<int>>& board, int row, int col, int n) {
    // Check all rows in this column
    for (int i = 0; i < n; i++) {
        if (board[i][col])
            return false;
    }
    
    // Check upper and lower left diagonal
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] && abs(row - i) == abs(col - j))
                return false;
        }
    }
    
    // Check all columns in this row
    for (int j = 0; j < n; j++) {
        if (board[row][j])
            return false;
    }
    
    return true;
}

void printBoard(const vector<vector<int>>& board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (board[i][j] == 1 ? "Q " : ". ");
        }
        cout << endl;
    }
    cout << endl;
}

void findAllSolutions(vector<vector<int>>& board, int row, int n, int& solutionCount, int initial_row) {
    if (row >= n) {
        cout << "Solution " << solutionCount + 1 << ":\n";
        printBoard(board, n);
        solutionCount++;
        return;
    }
    
    // Skip the row where we placed the initial queen
    if (row == initial_row) {
        findAllSolutions(board, row + 1, n, solutionCount, initial_row);
        return;
    }
    
    for (int col = 0; col < n; col++) {
        // Remove the current queen before checking if position is safe
        int temp = board[row][col];
        board[row][col] = 0;
        
        if (isSafe(board, row, col, n)) {
            board[row][col] = 1;
            findAllSolutions(board, row + 1, n, solutionCount, initial_row);
            board[row][col] = 0;
        }
        // Restore the previous state
        board[row][col] = temp;
    }
}

int main() {
    int n;
    cout << "Enter the value of n (size of chessboard): ";
    cin >> n;
    
    vector<vector<int>> board(n, vector<int>(n, 0));
    
    int initial_row, initial_col;
    cout << "Enter the row and column where the first queen is placed (0-based index): ";
    cin >> initial_row >> initial_col;
    
    // Place the first queen and verify if it's a valid position
    board[initial_row][initial_col] = 1;
    
    cout << "\nFinding all possible solutions with first queen at position (" 
         << initial_row << ", " << initial_col << "):\n\n";
    
    int solutionCount = 0;
    
    // Start from row 0 to properly check all constraints
    findAllSolutions(board, 0, n, solutionCount, initial_row);
    
    if (solutionCount == 0) {
        cout << "No solutions exist for the given configuration.\n";
    } else {
        cout << "Total number of solutions found: " << solutionCount << endl;
    }
    
    return 0;
}