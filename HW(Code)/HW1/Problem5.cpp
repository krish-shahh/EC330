// Krish Shah, U75802512, kshah26@bu.edu

/* Course of Action:
    - 
*/

/* 

Part A:

The algorithm for creating the grid involves populating a two-dimensional array with 'X' and 'O' characters 
and then printing the grid with clear separators. For any given positive integer N, the algorithm calculates the grid size, 
initializes the grid with spaces, places 'X' characters diagonally, and positions 'O' characters based on whether N is even or odd. 
The final step prints the grid, ensuring it is neatly structured with vertical and horizontal dividers. 
This algorithm is versatile and can be applied to grids of any size, not just limited to 10x10, ensuring the grid is generated and displayed accurately for any input N.
*/

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

const int MAX_GRID_SIZE = 10;

// Function to generate and print the grid
void generateGrid(int N) {
    char array[MAX_GRID_SIZE][MAX_GRID_SIZE];

    // Initialize the grid with spaces
    for (int i = 0; i < MAX_GRID_SIZE; i++) {
        for (int j = 0; j < MAX_GRID_SIZE; j++) {
            array[i][j] = ' ';
        }
    }

    // Place 'X' on the grid
    for (int i = 0; i <= N && i < MAX_GRID_SIZE; i++) {
        array[i][i] = 'X';
        array[i + 1][i] = 'X';
    }

    // Place 'O' on the grid based on N
    if (N % 2 == 0) {
        if (N + 1 < MAX_GRID_SIZE) {
            array[N + 1][N + 1] = 'O';
        }
    } else {
        if (N < MAX_GRID_SIZE - 2) {
            array[N][N + 2] = 'O';
            array[N + 2][N + 2] = 'O';
        }
    }

    // For Testing: Print the grid
    // for (int i = MAX_GRID_SIZE - 1; i >= 0; i--) {
    //     for (int j = 0; j < MAX_GRID_SIZE; j++) {
    //         cout << array[i][j];
    //     }
    //     cout << endl;
    // }

    // Print the grid with separators
    for (int i = MAX_GRID_SIZE - 1; i >= 0; i--) {
        for (int j = 0; j < MAX_GRID_SIZE; j++) {
            cout << "+---"; // Horizontal divider
        }
        cout << "+" << endl;

        for (int j = 0; j < MAX_GRID_SIZE; j++) {
            cout << "| " << array[i][j] << " "; 
        }
        cout << "|" << endl;
    }

    // Print the final horizontal divider
    for (int j = 0; j < MAX_GRID_SIZE; j++) {
        cout << "+---";
    }
    cout << "+" << endl;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <N>" << endl;
        return 1;
    }

    int N = atoi(argv[1]);

    if (N < 0 || N > 9) {
        cout << "N must be a positive integer no greater than 9." << endl;
        return 1;
    }

    generateGrid(N);

    return 0;
}

// g++ -std=c++17 Problem5.cpp -o Problem5

