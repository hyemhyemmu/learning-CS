#include <iostream>
#include <vector>
#include <string>
using namespace std;

/**
 * The classic "8 queens" problem:
 * trying to place 8 queens on a chess board 
 * such that no queens can attack another queen
 */

// Define Board class first
class Board {
private:
    vector<vector<bool>> board;  // true for queen presence, false for empty cell
    int size;                    // size of the board

public:
    // Constructor: Create an empty board
    Board(int n) : size(n) {
        board = vector<vector<bool>>(n, vector<bool>(n, false));
    }

    // Check if it's safe to place a queen at the specified position
    bool isSafe(int row, int col) {
        // Check same row to the left
        for (int i = 0; i < col; i++) {
            if (board[row][i]) return false;
        }

        // Check upper left diagonal
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j]) return false;
        }

        // Check lower left diagonal
        for (int i = row, j = col; i < size && j >= 0; i++, j--) {
            if (board[i][j]) return false;
        }

        return true;
    }

    void place(int row, int col) {
        board[row][col] = true;
    }

    void remove(int row, int col) {
        board[row][col] = false;
    }

    string toString() {
        string result;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result += board[i][j] ? "Q " : ". ";
            }
            result += "\n";
        }
        return result;
    }
};

// Forward declaration of helper function
bool solveQueensHelper(Board& board, int col, int n);

// Main solving function
void solveQueens(int n) {
    Board board(n);
    if (solveQueensHelper(board, 0, n)) {
        cout << "Solution found:\n" << board.toString();
    } else {
        cout << "No solution exists.\n";
    }
}

// Helper function implementation
bool solveQueensHelper(Board& board, int col, int n) {
    if (col >= n) {
        return true;
    }
    
    for (int row = 0; row < n; row++) {
        if (board.isSafe(row, col)) {
            board.place(row, col);
            if (solveQueensHelper(board, col + 1, n)) {
                return true;
            }
            board.remove(row, col);
        }
    }
    return false;
}

int main() {
    cout << "Solving 8-Queens Problem:\n";
    solveQueens(8);
    return 0;
}
