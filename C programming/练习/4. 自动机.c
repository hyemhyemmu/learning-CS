#include <stdio.h>
#define ARRAY_SIZE 21

// function prototypes
void initialize_array(int indx_alive,int array[]);
void print_array(int array[]);
void make_rule(int rule_num, int rule[]);
int get_rule_outcome(int rule[], int left, int center, int right);
void calculateNextState(int currentArray[], int nextArray[], int rule[]);
void simulateGenerations(int iterations, int array[], int rule[]);

int main(){
    // take in input
    int indx_alive;
    int rule_num;
    int iter_num;
    printf("Enter input: ");
    if (scanf("%d %d %d", &indx_alive, &rule_num, &iter_num) != 3 ||
        indx_alive < 0 || indx_alive >= ARRAY_SIZE ||
        rule_num < 0 || rule_num > 255 ||
        iter_num < 0) {
        printf("Invalid input\n");
        return 1;
    }
    while (getchar() != '\n');

    // initialize array
    int array[ARRAY_SIZE];
    initialize_array(indx_alive, array);

    // make an array for the rule 
    int rule[8];
    make_rule(rule_num, rule);

    // simulate generations
    simulateGenerations(iter_num, array, rule);

    return 0;
}

void initialize_array(int indx_alive,int array[]){
    for (int i = 0; i < ARRAY_SIZE; i++){
        array[i] = (i == indx_alive) ? 1 : 0;
    }
}

void print_array(int array[]){
    // set output array
   char array_print[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++){
         if (array[i] == 1){
              array_print[i] = '*';
         } else {
              array_print[i] = ' ';
         }
    }

    // print the array
    for (int i = 0; i < ARRAY_SIZE; i++){
        printf("%c", array_print[i]);
    }
    printf("\n");
}

void make_rule(int rule_num, int rule[]){
    for (int i = 0; i < 8; i++){
        rule[i] = rule_num % 2;
        rule_num = rule_num / 2;
    }
}

// get the outcome of specific index based on the rule
int get_rule_outcome(int rule[], int left, int center, int right){
    int decimal = left * 4 + center * 2 + right;
    return rule[decimal];
}

void calculateNextState(int currentArray[], int nextArray[], int rule[]){
    for (int i = 0; i < ARRAY_SIZE;i++){
        int left = i - 1;
        if (left<0){
            left = ARRAY_SIZE - 1;
        }
        int right = i + 1;
        if (right == ARRAY_SIZE){
            right = 0;
        }

        nextArray[i] = get_rule_outcome(rule, currentArray[left], currentArray[i], currentArray[right]);
    }
}

void simulateGenerations(int iterations, int array[], int rule[]){
    int nextArray[ARRAY_SIZE];
    for (int i = 0; i <iterations; i++){ // iterate through generations
        print_array(array); // print current state first
        calculateNextState(array, nextArray, rule); // generate next state

        for (int j = 0; j < ARRAY_SIZE; j++){
            array[j] = nextArray[j]; // update current state
        }
    }
}