#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define DEAD ' '
#define ALIVE "█" 

int WIDTH, HEIGHT;

typedef enum {
	alive,
	dead,
} cell_t;

cell_t** grid;
cell_t** new_grid;

void free_grids() {
	for (int i = 0; i < HEIGHT; ++i) {
		free(grid[i]);
		free(new_grid[i]);
	}
	free(grid);
	free(new_grid);
}

void clear_screen() {
	printf("\x1b[2J");
}

void hide_cursor() {
	printf("\x1b[?25l");
}

void show_cursor() {
	printf("\x1b[?25h");
}

void move_home() {
	printf("\x1b[0;0H]");
}

int count_neighbors(int row, int col) {
    int count = 0;

    for (int y = row - 1; y <= row + 1; ++y) {
        for (int x = col - 1; x <= col + 1; ++x) {
            if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH && !(y == row && x == col)) {
                count += (grid[y][x] == alive) ? 1 : 0;
            }
        }
    }

    return count;		
}

void init_grid() {
    grid = (cell_t**)malloc(HEIGHT * sizeof(cell_t*));
    new_grid = (cell_t**)malloc(HEIGHT * sizeof(cell_t*));

    for (int i = 0; i < HEIGHT; ++i) {
        grid[i] = (cell_t*)malloc(WIDTH * sizeof(cell_t));
        new_grid[i] = (cell_t*)malloc(WIDTH * sizeof(cell_t));

        for (int j = 0; j < WIDTH; ++j) {
            grid[i][j] = (rand() % 2) ? alive : dead; 
        }
    }
}

void print_grid() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
			if (grid[y][x] == dead) {
				printf("%c%c", DEAD, DEAD);
			} else {
				int n = count_neighbors(y, x);
				if (n < 2) {
					// underpopulation
					printf("\x1b[36m");
				} else if (n == 2 || n == 3) {
					// good
					printf("\x1b[34m");
				} else if (n > 3) {
					// overpopulation 
					printf("\x1b[35m");
				}
				printf(ALIVE);
				printf(ALIVE);
				printf("\x1b[0m");
			}
        }

        printf("\n");
    }
}

void next() {
	for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            int neighbors = count_neighbors(y, x);

            if (grid[y][x] == alive) {
                new_grid[y][x] = (neighbors == 2 || neighbors == 3) ? alive : dead;
            } else {
                new_grid[y][x] = (neighbors == 3) ? alive : dead;
            }
        }
    }

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            grid[y][x] = new_grid[y][x];
        }
    }
}

void init_terminal_size() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    WIDTH = w.ws_col / 2;
    HEIGHT = w.ws_row;
}

void on_exit() {
	show_cursor();
	free_grids();
}

int main() {
	init_terminal_size();
    init_grid();
	hide_cursor();

	atexit(free_grids);
	atexit(show_cursor);

	while (1) {
		clear_screen();
		move_home();
		print_grid();
		usleep(100 * 1000); // 100 milliseconds
		next();
	}

	show_cursor();
    return 0;
}
