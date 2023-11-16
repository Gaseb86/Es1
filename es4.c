#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }
    printf("%d", fd);

    int stdout_backup = dup(STDOUT_FILENO);
    if (stdout_backup == -1) {
        perror("dup");
        return EXIT_FAILURE;
    }
    printf("Lista files1\n");
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        return EXIT_FAILURE;
    }
    printf("Lista files2\n");
    close(fd);
    
    printf("Lista files3\n");
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }
    else if (pid == 0) {
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");  // execlp() returns only on error
        return EXIT_FAILURE;
    }
    else {
        wait(NULL);
  
        printf("Lista files4\n");
   


      

        if (dup2(stdout_backup, STDOUT_FILENO) == -1) {
            perror("dup2");
            return EXIT_FAILURE;
        }
        printf("Lista files5, %d\n", stdout_backup);
    }
}