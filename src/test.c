#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define ALIVE '#'
#define DEAD '.'

int WIDTH, HEIGHT;  // Updated to dynamic size

char** grid;
char** newGrid;

void initGrid() {
    grid = (char**)malloc(HEIGHT * sizeof(char*));
    newGrid = (char**)malloc(HEIGHT * sizeof(char*));

    for (int i = 0; i < HEIGHT; ++i) {
        grid[i] = (char*)malloc(WIDTH * sizeof(char));
        newGrid[i] = (char*)malloc(WIDTH * sizeof(char));

        for (int j = 0; j < WIDTH; ++j) {
            grid[i][j] = (rand() % 2) ? ALIVE : DEAD; // Random initialization
        }
    }
}

void printGrid() {
    system("clear");  // Clear the console (UNIX-like systems)
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
    usleep(100000);  // Sleep for 100 milliseconds to slow down the animation
}

int countNeighbors(int row, int col) {
    int count = 0;

    for (int i = row - 1; i <= row + 1; ++i) {
        for (int j = col - 1; j <= col + 1; ++j) {
            if (i >= 0 && i < HEIGHT && j >= 0 && j < WIDTH && !(i == row && j == col)) {
                count += (grid[i][j] == ALIVE) ? 1 : 0;
            }
        }
    }

    return count;
}

void updateGrid() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            int neighbors = countNeighbors(i, j);

            if (grid[i][j] == ALIVE) {
                newGrid[i][j] = (neighbors == 2 || neighbors == 3) ? ALIVE : DEAD;
            } else {
                newGrid[i][j] = (neighbors == 3) ? ALIVE : DEAD;
            }
        }
    }

    // Copy the new grid back to the original grid
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            grid[i][j] = newGrid[i][j];
        }
    }
}

void getTerminalSize() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    WIDTH = w.ws_col;
    HEIGHT = w.ws_row;
}

int main() {
    getTerminalSize();
    initGrid();

    while (1) {
        printGrid();
        updateGrid();
    }

    return 0;
}

