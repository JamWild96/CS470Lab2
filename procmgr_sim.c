#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_CHILDREN 10

void execute_task(int task_number) {
    if (task_number == 0) {
        // Task 1: Echo Hello <Your Name>
        char *args[] = {"echo", "Hello Jam", NULL};
        execvp(args[0], args);
    } else {
        // Other tasks: Example commands (can be modified)
        char *commands[][3] = {
            {"ls", NULL, NULL},
            {"date", NULL, NULL},
            {"whoami", NULL, NULL},
            {"pwd", NULL, NULL},
            {"ps", NULL, NULL},
            {"uname", "-a", NULL},
            {"uptime", NULL, NULL},
            {"hostname", NULL, NULL},
            {"cal", NULL, NULL}
        };

        execvp(commands[task_number - 1][0], commands[task_number - 1]);
    }
    perror("execvp failed"); // If exec fails
    exit(EXIT_FAILURE);
}

int main() {
    pid_t pid;
    int i, status;

    printf("Parent Process (PID: %d) creating child processes...\n", getpid());

    for (i = 0; i < NUM_CHILDREN; i++) {
        pid = fork();

        if (pid < 0) {
            perror("[PARENT] Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {  // Child process
            printf("Child %d (PID: %d) executing task %d\n", i + 1, getpid(), i);
            execute_task(i);
            exit(EXIT_SUCCESS);
        }
    }

    // Parent process waits for all child processes
    for (i = 0; i < NUM_CHILDREN; i++) {
        pid_t child_pid = wait(&status);
        if (WIFEXITED(status)) {
            printf("Child process %d exited normally with exit status %d\n", child_pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process %d terminated by signal %d\n", child_pid, WTERMSIG(status));
        }
    }

    printf("All child processes completed.\n");
    return 0;
}
