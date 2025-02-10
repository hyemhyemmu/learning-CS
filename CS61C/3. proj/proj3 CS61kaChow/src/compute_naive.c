#include "compute.h"

// functions prototypes
int32_t* flip(matrix_t *matrix);

// Computes the convolution of two matrices
int convolve(matrix_t *a_matrix, matrix_t *b_matrix, matrix_t **output_matrix) {
  // TODO: convolve matrix a and matrix b, and store the resulting matrix in
  
  matrix_t flipped_matrix=(matrix_t*)malloc(sizeof(matrix_t));
  flipped_matrix.rows = a_matrix->rows;
  flipped_matrix.cols = a_matrix->cols;
  flipped_matrix.data = flip(b_matrix);

  // Create a new matrix to store the result
  *output_matrix = malloc(sizeof(matrix_t));
  (*output_matrix)->rows = a_matrix->rows - b_matrix->rows + 1;
  (*output_matrix)->cols = a_matrix->cols - b_matrix->cols + 1;
  (*output_matrix)->data = malloc((*output_matrix)->rows * (*output_matrix)->cols * sizeof(int32_t));

  // Perform convolution
  for (uint32_t i = 0; i < (*output_matrix)->rows; i++) {
    for (uint32_t j = 0; j < (*output_matrix)->cols; j++) {
      int32_t sum = 0;
      // Apply the flipped kernel
      for (uint32_t k = 0; k < b_matrix->rows; k++) {
        for (uint32_t l = 0; l < b_matrix->cols; l++) {
          sum += a_matrix->data[(i + k) * a_matrix->cols + (j + l)] * 
                 flipped_matrix[k * b_matrix->cols + l];
        }
      }
      (*output_matrix)->data[i * (*output_matrix)->cols + j] = sum;
    }
  }

  // Free the flipped matrix
  free(flipped_matrix);
  return 0;
  
  // output_matrix

  return -1;
}

int32_t* flip(matrix_t *matrix){
  uint32_t rows= matrix->rows;
  uint32_t cols= matrix->cols;
  int32_t *original_matrix= matrix->data;
  int32_t* flipped_matrix_data= (int32_t*)malloc(rows*cols*sizeof(int));
  
  // iterate over each elements
  for (uint32_t i=0; i<rows; i++){
    for (uint32_t j=0; j<cols; j++){
      int original_pos = i * cols + j; // （i,j）in original matrix
      int flipped_pos = (rows-i-1) * cols + (cols-j-1); // （rows-i-1, cols-j-1）in flipped matrix

      flipped_matrix_data[flipped_pos] = original_matrix[original_pos];
    }
  }
  
  return flipped_matrix_data;
}

// Executes a task
int execute_task(task_t *task) {
  matrix_t *a_matrix, *b_matrix, *output_matrix;

  char *a_matrix_path = get_a_matrix_path(task);
  if (read_matrix(a_matrix_path, &a_matrix)) {
    printf("Error reading matrix from %s\n", a_matrix_path);
    return -1;
  }
  free(a_matrix_path);

  char *b_matrix_path = get_b_matrix_path(task);
  if (read_matrix(b_matrix_path, &b_matrix)) {
    printf("Error reading matrix from %s\n", b_matrix_path);
    return -1;
  }
  free(b_matrix_path);

  if (convolve(a_matrix, b_matrix, &output_matrix)) {
    printf("convolve returned a non-zero integer\n");
    return -1;
  }

  char *output_matrix_path = get_output_matrix_path(task);
  if (write_matrix(output_matrix_path, output_matrix)) {
    printf("Error writing matrix to %s\n", output_matrix_path);
    return -1;
  }
  free(output_matrix_path);

  free(a_matrix->data);
  free(b_matrix->data);
  free(output_matrix->data);
  free(a_matrix);
  free(b_matrix);
  free(output_matrix);
  free(flip(a_matrix));
  return 0;
}
