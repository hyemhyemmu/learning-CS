#include "state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"
#define COLS 20
#define ROWS 18

/* Helper function definitions */
static void set_board_at(game_state_t *state, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_state_t *state, unsigned int snum);
static char next_square(game_state_t *state, unsigned int snum);
static void update_tail(game_state_t *state, unsigned int snum);
static void update_head(game_state_t *state, unsigned int snum);
char** create_board(int rows, int cols);
void initialize_board(game_state_t* state);

/* Task 1 */
game_state_t *create_default_state() {
	game_state_t* newGame = (game_state_t*)malloc(sizeof(game_state_t));
	if (newGame == NULL) {
		perror("malloc failed");
		return NULL;
	}
	newGame->board = create_board(ROWS, COLS);
	initialize_board(newGame);

	return newGame;
}

char** create_board(int rows, int cols) {
	char** grid = (char**)malloc(rows * sizeof(char*));
	if (grid == NULL) {
		perror("malloc failed");
		return NULL;
	}

	for (int i = 0; i < rows; i++) {
		grid[i] = (char*)malloc(cols * sizeof(char));

		if (grid[i] == NULL) {
			perror("malloc failed");
			// if any line failed, free all the stuff
			for (int j = 0; j < i; j++) {
				free(grid[j]);
			}
			free(grid);
			return NULL;
		}
	}

	//add #
	for (int i = 0; i < cols; i++) {
		grid[0][i] = '#';
		grid[rows - 1][i] = '#';
	}

	for (int i = 0; i < rows; i++) {
		grid[i][0] = '#';
		grid[i][cols - 1] = '#';
	}

	return grid;
}

void initialize_board(game_state_t* state) {
	char** board = state->board;
	set_board_at(state, 2, 9, '*');
}

/* Task 2 */
void free_state(game_state_t *state) {
	free(state->snakes);
	free(state);
}

/* Task 3 */
void print_board(game_state_t* state, FILE* fp) {
	char** board = state->board;  
	int rows = ROWS;
	int cols = COLS;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			fputc(board[i][j], fp);  
		}
		fputc('\n', fp);  
	}
}


/*
  Saves the current state into filename. Does not modify the state object.
  (already implemented for you).
*/
void save_board(game_state_t *state, char *filename) {
  FILE *f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_state_t *state, unsigned int row, unsigned int col) { return state->board[row][col]; }

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_state_t *state, unsigned int row, unsigned int col, char ch) {
  state->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
	switch (c) {
	case 'w':
	case 'a':
	case 's':
	case 'd':
		return true;
	default:
		return false;
	}
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
	switch (c) {
	case 'W':
	case 'A':
	case 'S':
	case 'D':
	case 'x':
		return true;
	default:
		return false;
	}
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
	switch (c) {
	case 'w':
	case 'a':
	case 's':
	case 'd':
	case '^':
	case '<':
	case 'v':
	case '>':
	case 'W':
	case 'A':
	case 'S':
	case 'D':
	case 'x':
		return true;
	default:
		return false;
	}
}



/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
	switch (c) {
	case '^': return 'w';  // '^' represents moving up, so the tail is 'w'
	case '<': return 'a';  // '<' represents moving left, so the tail is 'a'
	case 'v': return 's';  // 'v' represents moving down, so the tail is 's'
	case '>': return 'd';  // '>' represents moving right, so the tail is 'd'
	}
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
	switch (c) {
	case 'W': return '^';  // 'W' represents moving up, so the body is '^'
	case 'A': return '<';  // 'A' represents moving left, so the body is '<'
	case 'S': return 'v';  // 'S' represents moving down, so the body is 'v'
	case 'D': return '>';  // 'D' represents moving right, so the body is '>'
	}
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
	switch (c) {
	case 'v':
	case 's':
	case 'S':
		return cur_row + 1;  // Move down
	case '^':
	case 'w':
	case 'W':
		return cur_row - 1;  // Move up
	default:
		return cur_row;  // No change
	}
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
	switch (c) {
	case '>':
	case 'd':
	case 'D':
		return cur_col + 1;  // Move right
	case '<':
	case 'a':
	case 'A':
		return cur_col - 1;  // Move left
	default:
		return cur_col;  // No change
	}
}


/*
  Task 4.2

  Helper function for update_state. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_state_t *state, unsigned int snum) {
	if (snum > state->num_snakes)
		return NULL;
	snake_t* snake = &state->snakes[snum];
	int head_row = snake->head_row;
	int head_col = snake->head_col;
	char head = get_board_at(state, head_row, head_col);

	switch (head) {
	case 'W': return get_board_at(state, head_row - 1, head_col);  // Move up
	case 'A': return get_board_at(state, head_row, head_col - 1);  // Move left
	case 'S': return get_board_at(state, head_row + 1, head_col);  // Move down
	case 'D': return get_board_at(state, head_row, head_col + 1);  // Move right
	default: return NULL;
	}
}



/*
  Task 4.3

  Helper function for update_state. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_state_t* state, unsigned int snum) {
	if (snum >= state->num_snakes) {
		return;
	}

	snake_t* snake = &state->snakes[snum];

	// Get the current head position
	int head_row = snake->head_row;
	int head_col = snake->head_col;

	// Get the direction the snake's head is moving
	char head = get_board_at(state, head_row, head_col);

	// Use next_square to get the character in the target position
	char next_cell = next_square(state, snum);

	// Remove the old head position from the board
	set_board_at(state, head_row, head_col, ' ');  // Assume space ' ' is used to clear the old position

	// Update the head position based on the direction
	switch (head) {
	case 'W': 
		head_row --;
		break;
	case 'A':
		head_col --;
		break;
	case 'S': 
		head_row ++;
		break;
	case 'D': 
		head_col ++;
		break;
	default:
		return; // If the direction is invalid, do nothing
	}

	// Update the snake's head position in the snake struct
	snake->head_row = head_row;
	snake->head_col = head_col;

	// Place the new head on the board at the new position
	set_board_at(state, head_row, head_col, head);
}


/*
  Task 4.4

  Helper function for update_state. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_state_t* state, unsigned int snum) {
	if (snum >= state->num_snakes) {
		return;
	}

	snake_t* snake = &state->snakes[snum];

	int tail_row = snake->tail_row;
	int tail_col = snake->tail_col;

	// Get the direction of the current tail (the body direction)
	char tail = get_board_at(state, tail_row, tail_col);

	// Remove the old tail position from the board
	set_board_at(state, tail_row, tail_col, ' ');  // Assume space ' ' is used to clear the old position

	// Update the tail position based on the direction
	switch (tail) {
	case '^': 
		tail_row -= 1;
		break;
	case '<': 
		tail_col -= 1;
		break;
	case 'v': 
		tail_row += 1;
		break;
	case '>': 
		tail_col += 1;
		break;
	default:
		return; // If the tail direction is invalid, do nothing
	}

	// Update the snake's tail position in the snake struct
	snake->tail_row = tail_row;
	snake->tail_col = tail_col;

	// Set the new tail on the board with the appropriate tail character (w, a, s, d)
	char tail_char = body_to_tail(tail);  // Convert the body direction to a tail direction
	set_board_at(state, tail_row, tail_col, tail_char);  // Place the new tail on the board
}



/* Task 4.5 */
void update_state(game_state_t *state, int (*add_food)(game_state_t *state)) {
	//get the next square to see if dead or eat fruit
	//check every snakes
	for (unsigned int snum = 0; snum < state->num_snakes; snum++) {
		snake_t* snake = &state->snakes[snum];

		int head_row = snake->head_row;
		int head_col = snake->head_col;
		char head = get_board_at(state, head_row, head_col);

		char next = next_square(state, snum);

		//dead
		if (next == '#' || is_snake(next)) {
			set_board_at(state, head_row, head_col, 'x');
			snake->live = false;
		}
		//fruit
		else if (next == '*') { //we can achieve this by only update the head but not the tail 
			update_head(state, snum);
			add_food(state);
		}
		//empty
		else {
			update_head(state, snum);
			update_tail(state, snum);
		}
	}

	
  return;
}

/* Task 5.1 */
char* readline(FILE* fp) {
	char buffer[1024]; // Temporary buffer for the line
	if (fgets(buffer, sizeof(buffer), fp) == NULL) {
		return NULL; // End of file or error
	}

	// Remove the newline character, if present
	char* newline = strchr(buffer, '\n');
	if (newline) {
		*newline = '\0';
	}

	return strdup(buffer);
}

/* Task 5.2 */
game_state_t *load_board(FILE *fp) {
	if (!fp)
		return NULL;
	
	game_state_t* state = malloc(sizeof(game_state_t));
	if (state == NULL) {
		perror("malloc failed");
		return NULL;
	}

	state->num_rows = 0;
	state->num_cols = 0;
	state->board = NULL;
	state->num_snakes = 0;
	state->snakes = NULL;

	// Read each line using readline
	char* line;
	while ((line = readline(fp)) != NULL) {
		unsigned int row_length = strlen(line);

		// Update the maximum column count
		if (row_length > state->num_cols) {
			state->num_cols = row_length;
		}
	}

	// Expand the board array to fit the new row
	char** new_board = realloc(state->board, (state->num_rows + 1) * sizeof(char*));
	if (!new_board) {
		// Cleanup if memory allocation fails
		for (unsigned int i = 0; i < state->num_rows; i++) {
			free(state->board[i]);
		}
		free(state->board);
		free(state);
		free(line);
		return NULL;
	}
	state->board = new_board;

	// Add the new line to the board
	state->board[state->num_rows] = line;
	state->num_rows++;

	return state;
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_state_t *state, unsigned int snum) {
	snake_t* snake = &state->snakes[snum];

	unsigned int row = snake->tail_row;
	unsigned int col = snake->tail_col;

	char current_char = get_board_at(state, row, col);
	char next_char = body_to_tail(current_char);

	while (!is_head(current_char)) {

		if (current_char == '^') {
			row--;  
		}
		else if (current_char == 'v') {
			row++;  
		}
		else if (current_char == '<') {
			col--; 
		}
		else if (current_char == '>') {
			col++; 
		}

		current_char = get_board_at(state, row, col);
	}

	snake->head_row = row;
	snake->head_col = col;
}

/* Task 6.2 */
game_state_t *initialize_snakes(game_state_t *state) {
	state->num_snakes = 0;
	for (unsigned int row = 0; row < state->num_rows; row++) {
		for (unsigned int col = 0; state->board[row][col] != '\0'; col++) {
			char c = state->board[row][col];

			// if find snake tail
			if (c == 'w' || c == 'a' || c == 's' || c == 'd') {

				state->snakes = realloc(state->snakes, (state->num_snakes + 1) * sizeof(snake_t));
				if (state->snakes == NULL) {
					perror("malloc failed");
					return NULL;
				}

			
				snake_t* new_snake = &state->snakes[state->num_snakes];
				new_snake->tail_row = row;
				new_snake->tail_col = col;

				find_head(state, state->num_snakes);

				new_snake->live = true;

				state->num_snakes++;
			}
		}
	}

	return state;
}
