#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Function to be executed by each thread
void *run_client(void *arg)
{
    char *command = (char *)arg;
    system(command);    // Execute the shell command
    pthread_exit(NULL); // Exit the thread
}

int main()
{
    pthread_t threads[10]; // We will create 10 threads
    char *commands[10] = {
        "./client_08_19 127.0.0.1 8080 -input input/input1.txt > output/output1.txt",
        "./client_08_19 127.0.0.1 8080 -input input/input2.txt > output/output2.txt",
        "./client_08_19 127.0.0.1 8080 -input input/input3.txt > output/output3.txt",
        "./client_08_19 127.0.0.1 8080 -input input/input4.txt > output/output4.txt",
        "./client_08_19 127.0.0.1 8080 -input input/input5.txt > output/output5.txt",
        "./client_08_19 127.0.0.1 8080 -input input/input6.txt > output/output6.txt",
        "./client_08_19 127.0.0.1 8080 -input input/input7.txt > output/output7.txt",
        "./client_08_19 127.0.0.1 8080 -input input/input8.txt > output/output8.txt",
        "./client_08_19 127.0.0.1 8080 -input input/input9.txt > output/output9.txt",
        "./client_08_19 127.0.0.1 8080 -input input/input10.txt > output/output10.txt"};

    // Create threads to execute the commands
    for (int i = 0; i < 10; i++)
    {
        if (pthread_create(&threads[i], NULL, run_client, (void *)commands[i]) != 0)
        {
            perror("Failed to create thread");
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < 10; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
