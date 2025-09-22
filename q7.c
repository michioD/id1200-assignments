#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

// #define N 100 

int main(int argc, char *argv[]) {
    // argv points to argv[0]
    // argv[0] points to the program ./q7
    // argv[1] points to the N value you enter 
    int N = atoi(argv[1]);

    srand(time(NULL)); 

    // allocate memory on heap for N floats
    // set array to point to the first address   
    float *array = (float *)malloc(N * sizeof(float));

    for (int i = 0; i < N; i++){
        // set whatever is at this address to a random float. Divide by RAND_MAX to make the range [0,1]
        *(array + i) = (float)rand() / RAND_MAX;
    }

    // creation and error handling for the pipes here 

    int pipe1[2], pipe2[2];
    if (pipe(pipe1) < 0 || pipe(pipe2) < 0){
        perror("pipe failed");
        free(array);
        return 1;
    }

    // error handling for first fork
    int pid1 = fork();
    if (pid1 < 0){
        printf("fork failed");
        free(array);
        return 1;
    }

    if (pid1 == 0){
        close(pipe1[0]);
        float sum1 = 0;
        for (int i = 0; i < N / 2; i++){
            sum1 += array[i];
        }
        write(pipe1[1], &sum1, sizeof(sum1));
        close(pipe1[1]);
        free(array);
        printf("child 1 pid %d\n", getpid());
        //succesful exit
        exit(0);
    }

    // error handling for second fork
    int pid2 = fork();
    if (pid2 < 0){
        printf("fork failed");
        free(array);
        return 1;
    }

    if (pid2 == 0){
        close(pipe2[0]);
        float sum2 = 0;
        for (int i = N/2; i < N; i++){
            sum2 += array[i];
        }
        write(pipe2[1], &sum2, sizeof(sum2));
        close(pipe2[1]);
        free(array);
        printf("child 2 pid %d\n", getpid());
        //succesful exit
        exit(0);
    }

    // back to parent
    //

    close(pipe1[1]);
    close(pipe2[1]);

    float sum1, sum2;

    read(pipe1[0], &sum1, sizeof(sum1));
    read(pipe2[0], &sum2, sizeof(sum2));
    close(pipe1[0]);
    close(pipe2[0]);

    float total = sum1 +sum2;

    printf("Total sum = %f\n", total);

    free(array);
    // delete the 2 zombies
    wait(NULL);
    wait(NULL);

}

