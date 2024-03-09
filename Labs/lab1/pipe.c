#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define READ_END 0
#define WRITE_END 1

//Defined helper function to close the pipes at the end
void close_pipes(int numPipes, int pipes[][2]) {
    for (int i = 0; i < numPipes; i++) {
        close(pipes[i][READ_END]);
        close(pipes[i][WRITE_END]);
    }
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Error: Requires at least one command to execute.\n");
        // From stdlib.h use EXIT_FAILURE as a non-zero integer to represent failures, EXIT_SUCCESS representing a 0
        return EXIT_FAILURE;
    }

    int argument_count = argc - 1;
    pid_t child_PIDs[argument_count];
    int pipes[argument_count - 1][2];

    // Create pipes
    for (int i = 0; i < argument_count - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Error: Failed to create a pipe");
            return EXIT_FAILURE;
        }
    }

    // Create child processes and set up redirection
    for (int i = 0; i < argument_count; i++) {
        child_PIDs[i] = fork();

        if (child_PIDs[i] < 0) {

            perror("Fork failed");
            close_pipes(argument_count - 1, pipes);
            return EXIT_FAILURE;

          // In child process  
        } else if (child_PIDs[i] == 0) {

            // Not the first command
            if (i != 0) {
                dup2(pipes[i - 1][READ_END], STDIN_FILENO);
            }

            // Not the last command
            if (i != argument_count - 1) {
                dup2(pipes[i][WRITE_END], STDOUT_FILENO);
            }

            // Close all pipes in child process
            close_pipes(argument_count - 1, pipes);

            if (execlp(argv[i + 1], argv[i + 1], NULL) == -1) {
                perror("Error: Command execution has failed. Try again.");
                exit(EXIT_FAILURE);
            }
        }
    }

    // Close all pipes in parent process
    close_pipes(argument_count - 1, pipes);

    // Wait for child processes to finish and then continue
    for (int i = 0; i < argument_count; i++) {

        //Initialized a var for status
        int status;

        if (waitpid(child_PIDs[i], &status, 0) == -1) {
            perror("Failed to wait for child process");
            return EXIT_FAILURE;
        }

        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            fprintf(stderr, "Command '%s' exited with error code %d\n", argv[i + 1], WEXITSTATUS(status));
            return EXIT_FAILURE;
        }
    }

    //Success so we want to return 0 -> EXIT_SUCCESS = 0. 
    return EXIT_SUCCESS;
}
