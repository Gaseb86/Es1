#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    
    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Errore nella fork\n");
    }
    else if (pid == 0)
    {
        printf("Child: Sono il processo figlio\n");
        printf("Child: Il mio PID è %d\n", getpid());
        printf("Child: Il PID del mio genitore è %d\n", getppid());
        
        char cwd[1024];

        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("Directory corrente: %s\n", cwd);
        }
        else
        {
            perror("Errore ottenendo la directory corrente");
        }
        char *args[] = {"ls", "-l", NULL};
        char *env[] = {NULL};
        execve("/bin/ls", args, env);
    }
    else
    {
        printf("Parent: Sono il processo padre, il PID del mio figlio è %d\n", pid);
        printf("Parent: Il PID del mio genitore è %d\n", getppid());
        int status;
        if (wait(&status) < 0)
        { // wait() attende la terminazione del processo figlio
            perror("wait");
            exit(-1);
        }
        if (WIFEXITED(status))
        {                                                                         // WIFEXITED() ritorna true se il processo figlio è terminato normalmente
            printf("Child process exited with status %d\n", WEXITSTATUS(status)); // WEXITSTATUS() ritorna lo status del processo figlio

            
        }
        int *z = malloc(100*sizeof(int));
        free(z);

    }
    return 0;
    

  
}