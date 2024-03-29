#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#define ARRAY_SIZE 1000
#define NUM_THREADS 10

// Structure to pass data to thread
typedef struct {
    int thread_id;
    int *array;
    int start_index;
    int end_index;
    int thread ;
} ThreadData;

// Function to count occurrences of process number in a portion of the array
void *countOccurrences(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int *array = data->array;
    int start_index = data->start_index;
    int end_index = data->end_index;
    int process_num = data->thread_id; // Process number
    int thread_id = data->thread;

    // Count occurrences of process number
    int count = 0;
    for (int i = start_index; i < end_index; i++) {
        if (array[i] == process_num) {
            count++;
        }
    }

    // Write results to file
    char filename[50];
    sprintf(filename, "process_%d_thread_result.txt", process_num);
    FILE *file = fopen(filename, "a"); // Open file in append mode
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "Portion: [%d, %d]\n", start_index, end_index);
    fprintf(file, "Occurrences du nombre %d: %d trouvé(es) par le thread %d\n\n", process_num, count, thread_id);
    fclose(file);

    pthread_exit(NULL);
}

int main() {
    int n;
    printf("Entrer le nombre de processus: ");
    scanf("%d", &n);
    // Create processes
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Child process
            printf("Child process %d - PID: %d, PPID: %d\n", i + 1, getpid(), getppid());
            //if ((i + 1) % 2 == 0) { // Even process
                // Generate and write array to file
                int *array = (int *)malloc(sizeof(int) * ARRAY_SIZE);
                for (int j = 0; j < ARRAY_SIZE; j++) {
                    array[j] = rand() % n; // Fill array with random values
                }
                char filename[20];
                sprintf(filename, "array_process_%d.txt", i + 1);
                FILE *file = fopen(filename, "w");
                if (file == NULL) {
                    perror("Error opening file");
                    exit(EXIT_FAILURE);
                }
                for (int j = 0; j < ARRAY_SIZE; j++) {
                    fprintf(file, "%d ", array[j]);
                }
                fclose(file);

            // Divide array into portions for each thread
            pthread_t threads[NUM_THREADS];
            ThreadData thread_data[NUM_THREADS];
            int chunk_size = ARRAY_SIZE / NUM_THREADS;
            for (int k = 0; k < NUM_THREADS; k++) {
                thread_data[k].thread_id = i + 1;
                thread_data[k].array = array;
                thread_data[k].start_index = k * chunk_size;
                thread_data[k].end_index = (k + 1) * chunk_size;
                thread_data[k].thread = k + 1;
                pthread_create(&threads[k], NULL, countOccurrences, (void *)&thread_data[k]);
            }
            // Wait for threads to finish
            for (int j = 0; j < NUM_THREADS; j++) {
                pthread_join(threads[j], NULL);
            }

            free(array);
            exit(EXIT_SUCCESS);
        } else { // Parent process
            wait(NULL);
        }
    }


    return 0;
}
