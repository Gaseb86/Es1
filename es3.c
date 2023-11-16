#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char filename[256];
    char path[512] = "/bin/";

    while (1) {
        printf("nano-shell $ ");  // (a) Print the prompt

        // (b) Ask the user for a filename
        if (fgets(filename, sizeof(filename), stdin) == NULL) {  // Handle EOF
            exit(EXIT_SUCCESS);  // (c) Exit with EXIT_SUCCESS
        }

        filename[strcspn(filename, "\n")] = 0;  // Remove the newline character

        // (c) If the user enters "exit", exit with EXIT_SUCCESS
        if (strcmp(filename, "exit") == 0) {
            exit(EXIT_SUCCESS);
        }

        strcat(path, filename);  // Append the filename to the path

        // (d) Execute /bin/filename, giving an appropriate error message if the execution fails
        if (fork() == 0) {
            execl(path, filename, NULL);
            perror("execl");  // Print an error message if execl() fails
            exit(EXIT_FAILURE);
        }

        // (e) Wait for the child process to terminate
        wait(NULL);

        // Reset the path for the next iteration
        strcpy(path, "/bin/");
    }

    return 0;
}