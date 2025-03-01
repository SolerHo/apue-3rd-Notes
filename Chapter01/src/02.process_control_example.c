/***************************************************
 * 
 * 描述：从标准输入读取 命令，然后执行这些命令
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

int main(void)
{
    char  buf[MAXLINE];
    pid_t pid;
    int status;

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