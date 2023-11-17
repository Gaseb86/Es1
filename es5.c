#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/param.h>

const bool debug = false;

int main(int argc, char *argv[])
{

    const char *commandsPath = "/bin/";
    const char *com1 = "ps";
    const char *arg1 = "aux";
    const char *com2 = "grep";
    const char *arg2 = "bash";
    const char *username = getenv("USER"); // getting username with fork and exec.
    {
        if (username == NULL)
        {
            perror("getenv error. Exiting program...");
            return 0;
        }
    }

    char *currentd = getcwd(currentd, MAXPATHLEN);

    printf(" %s:~%s $ ", username, currentd);
    char *userInput = malloc(256);
    scanf("%s", userInput);
    if (debug)
        printf("%s", userInput);

    pid_t id = fork();

    if (id == 0)
    {
    }
    else
    {
    }
    free(userInput);
    return 0;
}