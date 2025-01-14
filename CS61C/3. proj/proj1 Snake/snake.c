#include <stdio.h>
#include <string.h>

#include "snake_utils.h"
#include "state.h"

int main(int argc, char *argv[]) {
  bool io_stdin = false;
  char *in_filename = NULL;
  char *out_filename = NULL;
  game_state_t *state = NULL;

  // Parse arguments
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-i") == 0 && i < argc - 1) {
      if (io_stdin) {
        fprintf(stderr, "Usage: %s [-i filename | --stdin] [-o filename]\n", argv[0]);
        return 1;
      }
      in_filename = argv[i + 1];
      i++;
      continue;
    } else if (strcmp(argv[i], "--stdin") == 0) {
      if (in_filename != NULL) {
        fprintf(stderr, "Usage: %s [-i filename | --stdin] [-o filename]\n", argv[0]);
        return 1;
      }
      io_stdin = true;
      continue;
    }
    if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
      out_filename = argv[i + 1];
      i++;
      continue;
    }
    fprintf(stderr, "Usage: %s [-i filename | --stdin] [-o filename]\n", argv[0]);
    return 1;
  }

  // Do not modify anything above this line.

  /* Task 7 */

  // Read board from file, or create default board
  if (in_filename != NULL) {
      FILE* file = fopen(in_filename, "r");
      //If the file doesn't exist, return -1
      if (file == NULL)
          return -1;
       //Load the board from in_filename
      state= load_board(file);
     
      //loading failed
      if (state == NULL)
          return -1;

    // Then call initialize_snakes on the state you made
      initialize_snakes(state);

    // close file pointer
      fclose(file);
  } 
  else if (io_stdin) {
    // Load the board from stdin
      game_state_t* state = load_board(stdin);

      if (state == NULL) {
          // If loading failed, return -1
          return -1;
      }

    // Then call initialize_snakes on the state you made
      initialize_snakes(state);
  } else {
    // Create default state
      game_state_t* state = malloc(sizeof(game_state_t));
      if (state == NULL) {
          // If memory allocation fails, return -1
          return -1;
      }

      // Define a simple default board
      const char* default_board[] = {
          "..........",
          "..>v......",
          "..^v......",
          "..^<......",
          ".........."
      };
      state->num_rows = 5;
      state->board = malloc(state->num_rows * sizeof(char*));
      if (state->board == NULL) {
          free(state);
          return -1;
      }

      // Copy default board to state
      for (unsigned int i = 0; i < state->num_rows; i++) {
          state->board[i] = strdup(default_board[i]);
          if (state->board[i] == NULL) {
              // Cleanup on failure
              for (unsigned int j = 0; j < i; j++) {
                  free(state->board[j]);
              }
              free(state->board);
              free(state);
              return -1;
          }
      }

      // Initialize snakes on the default board
      state->num_snakes = 0;
      state->snakes = NULL;
      initialize_snakes(state);
  }

  //\Update state. Use the deterministic_food function
  // (already implemented in snake_utils.h) to add food.
  update_state(state, deterministic_food(state));

  // Write updated board to file or stdout
  // Write updated board to file or stdout
  if (out_filename != NULL) {
      // Save the board to out_filename
      FILE* file = fopen(out_filename, "w");
      if (file == NULL) {
          // Handle file opening error (optional, depending on requirements)
          fprintf(stderr, "Error: Unable to open file %s for writing.\n", out_filename);
          return -1;
      }

      // Call save_board to write the state to the file
      save_board(state, file);

      // Close the file after saving
      fclose(file);
  }
  else {
      // Print the board to stdout
      for (unsigned int i = 0; i < state->num_rows; i++) {
          printf("%s\n", state->board[i]);
      }
  }


  //Free the state
  free(state);
  return 0;
}
