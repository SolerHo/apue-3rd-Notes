 /***************************************************
 * 
 * 描述：捕获中断信号
 * 
 * **************************************************
 */

#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>

#define MAXLINE 4096 // max line length

static void signal_int(int);

int main(void)
{
    char  buf[MAXLINE];
    pid_t pid;
    int status;

    if (signal(SIG_INT, signal_int) == SIGN_ERR)
        printf("signal error");

    printf("%% "); // printf prompt (printf requires %% to print %)
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0; // replace newline with null;
        
        if ((pid = fork()) < 0) {
            printf("fork error");
        } else if (pid == 0) {
            execlp(buf, buf, (char *)0);
            err_sys("couldn't execute : %s", buf);
            exit(127);
        }

        // parent
        if ((pid = waitpid(pid, &status, 0)) < 0) {
            err_sys("waitpid error");
        }
        printf("%%");
    }
    exit(0);
}

void signal_int(int signo)
{
    printf("interrupt\n%% ");
}