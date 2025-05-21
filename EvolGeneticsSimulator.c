#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
 
#define GENOME_SIZE 10 
#define MAX_GENERATIONS 10 
#define MUTATION_RATE 0.3 
 
// Function to generate a random permutation 
void generate_permutation(char *permutation, int size) { 
    int i, j; 
    char temp; 
    // Initialize permutation array 
    for (i = 0; i < size; i++) { 
        permutation[i] = 'A' + i; // Use letters A, B, C, ... as gene symbols 
    } 
    // Shuffle permutation array using Fisher-Yates algorithm 
    for (i = size - 1; i > 0; i--) { 
        j = rand() % (i + 1); 
        temp = permutation[i]; 
        permutation[i] = permutation[j]; 
        permutation[j] = temp; 
    } 
} 
 
// Function to perform gene duplication 
void perform_duplication(char *genome, int size, int duplication_point) { 
    int i; 
    // Shift elements to make space for duplication 
    for (i = size - 1; i >= duplication_point; i--) { 
        genome[i + 1] = genome[i]; 
    } 
    // Duplicate gene at duplication point 
    genome[duplication_point] = genome[duplication_point - 1]; 
} 
 
// Function to perform gene deletion 
void perform_deletion(char *genome, int size, int deletion_point) { 
    int i; 
    // Shift elements to close the gap created by deletion 
    for (i = deletion_point; i < size - 1; i++) { 
        genome[i] = genome[i + 1]; 
    } 
} 
 
// Function to perform gene inversion 

void perform_inversion(char *genome, int size, int start_point, int end_point) { 
    int i, j; 
    char temp; 
    // Reverse elements between start_point and end_point 
    for (i = start_point, j = end_point; i < j; i++, j--) { 
        temp = genome[i]; 
        genome[i] = genome[j]; 
        genome[j] = temp; 
    } 
} 
 
// Function to print a permutation 
void print_permutation(char *permutation, int size) { 
    int i; 
    for (i = 0; i < size; i++) { 
        printf("%c ", permutation[i]); 
    } 
    printf("\n"); 
} 
 
int main() { 
    char original_genome[GENOME_SIZE]; 
    char mutated_genome[GENOME_SIZE]; 
    int num_generations, generation, mutation_event, mutation_point, i; 
 
    // Seed the random number generator 
    srand(time(NULL)); 
 
    // Ask user for the number of generations 
    printf("Enter the number of generations (up to %d): ", MAX_GENERATIONS); 
    scanf("%d", &num_generations); 
    if (num_generations > MAX_GENERATIONS || num_generations <= 0) { 
        printf("Invalid number of generations. Exiting...\n"); 
        return 1; 
    } 
 
    // Generate random original genome permutation 
    generate_permutation(original_genome, GENOME_SIZE); 
 
    // Print original genome 
    printf("Original genome permutation: "); 
    print_permutation(original_genome, GENOME_SIZE); 
 
    // Perform gene mutations for multiple generations 
    for (generation = 1; generation <= num_generations; generation++) { 
        // Copy original genome for mutation 
        for (i = 0; i < GENOME_SIZE; i++) { 

            mutated_genome[i] = original_genome[i]; 
        } 
        // Randomly select mutation event (duplication, deletion, inversion) 
        mutation_event = rand() % 3; 
        // Randomly select mutation point 
        mutation_point = rand() % (GENOME_SIZE - 1) + 1; 
        // Perform mutation based on mutation event 
        switch (mutation_event) { 
            case 0: // Duplication 
                perform_duplication(mutated_genome, GENOME_SIZE, mutation_point); 
                printf("Mutated genome after generation %d (Duplication at position %d): ", 
generation, mutation_point); 
                break; 
            case 1: // Deletion 
                perform_deletion(mutated_genome, GENOME_SIZE, mutation_point); 
                printf("Mutated genome after generation %d (Deletion at position %d): ", 
generation, mutation_point); 
                break; 
            case 2: // Inversion 
                mutation_point = rand() % (GENOME_SIZE - 2) + 1; // Avoid inversion at end of genome 
                perform_inversion(mutated_genome, GENOME_SIZE, mutation_point, GENOME_SIZE - 
1); 
                printf("Mutated genome after generation %d (Inversion from position %d to end): ", generation, mutation_point); 
                break; 
        } 
        print_permutation(mutated_genome, GENOME_SIZE); 
    } 
 
    return 0; 
} 