#include <iostream>
#include <vector>
using namespace std;

class NQueensSolver {
private:
    int n;
    vector<vector<int>> board;
    vector<vector<vector<int>>> allSolutions;
    int solutionCount;

    bool isSafe(int row, int col) {
        // Check row on left side
        for (int j = 0; j < col; j++)
            if (board[row][j] == 1)
                return false;

        // Check row on right side
        for (int j = col + 1; j < n; j++)
            if (board[row][j] == 1)
                return false;

        // Check upper diagonal on left side
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
            if (board[i][j] == 1)
                return false;

        // Check lower diagonal on left side
        for (int i = row, j = col; i < n && j >= 0; i++, j--)
            if (board[i][j] == 1)
                return false;

        // Check upper diagonal on right side
        for (int i = row, j = col; i >= 0 && j < n; i--, j++)
            if (board[i][j] == 1)
                return false;

        // Check lower diagonal on right side
        for (int i = row, j = col; i < n && j < n; i++, j++)
            if (board[i][j] == 1)
                return false;

        return true;
    }

    void findAllSolutionsUtil(int col) {
        // Base case: If all queens are placed, save the solution
        if (col >= n) {
            allSolutions.push_back(board);
            solutionCount++;
            return;
        }

        // Check if current column already has a manually placed queen
        for (int i = 0; i < n; i++) {
            if (board[i][col] == 1) {
                findAllSolutionsUtil(col + 1);
                return;
            }
        }

        // Try placing queen in all rows of current column
        for (int i = 0; i < n; i++) {
            if (isSafe(i, col)) {
                board[i][col] = 1;
                findAllSolutionsUtil(col + 1);
                board[i][col] = 0;  // Backtrack
            }
        }
    }

public:
    NQueensSolver(int size) : n(size), solutionCount(0) {
        board = vector<vector<int>>(n, vector<int>(n, 0));
    }

    bool placeQueen(int row, int col) {
        if (row < 0 || row >= n || col < 0 || col >= n) {
            cout << "Invalid position! Position should be within 0 to " << n-1 << endl;
            return false;
        }
        
        if (board[row][col] == 1) {
            cout << "Queen already placed at this position!" << endl;
            return false;
        }

        if (!isSafe(row, col)) {
            cout << "Cannot place queen at this position - it conflicts with other queens!" << endl;
            return false;
        }

        board[row][col] = 1;
        return true;
    }

    void findAllSolutions() {
        allSolutions.clear();
        solutionCount = 0;
        findAllSolutionsUtil(0);
    }

    void printBoard(const vector<vector<int>>& board) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 1)
                    cout << "Q ";
                else
                    cout << ". ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void printCurrentBoard() {
        cout << "\nCurrent board state:\n";
        printBoard(board);
    }

    void printAllSolutions() {
        if (solutionCount == 0) {
            cout << "No solutions exist with the given queen placements!" << endl;
            return;
        }

        cout << "\nTotal number of solutions: " << solutionCount << "\n\n";
        for (int i = 0; i < solutionCount; i++) {
            cout << "Solution " << (i + 1) << ":\n";
            printBoard(allSolutions[i]);
        }
    }
};

int main() {
    int n;
    cout << "Enter the size of the chessboard (n x n): ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid board size!" << endl;
        return 1;
    }

    NQueensSolver solver(n);
    int numQueens;
    cout << "How many queens do you want to place manually? ";
    cin >> numQueens;

    if (numQueens < 0 || numQueens > n) {
        cout << "Invalid number of queens!" << endl;
        return 1;
    }

    // Manual queen placement
    for (int i = 0; i < numQueens; i++) {
        int row, col;
        cout << "\nEnter position for queen " << (i+1) << " (row and column, 0-based): ";
        cin >> row >> col;

        if (!solver.placeQueen(row, col)) {
            i--; // Retry this queen
            continue;
        }
        
        solver.printCurrentBoard();
    }

    cout << "\nFinding all possible solutions...\n";
    solver.findAllSolutions();
    solver.printAllSolutions();

    return 0;
}