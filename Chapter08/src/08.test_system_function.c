/***************************************************
* 
* 描述：测试 system 函数使用shell命令
* 
* **************************************************
*/

#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void pr_exit(int status);

int main(void)
{
    int status;

    if (status = system("date") < 0) {
        printf("system error\n");
    }

    pr_exit(status);

    if ((status = system("nosuchcommand")) < 0) {
        printf("system() error\n");
    }

    pr_exit(status);

    if ((status = system("who; exit 44")) < 0) {
        printf("system() error\n");
    }

    pr_exit(status);

    exit(0);
}


void pr_exit(int status)
{
        if(WIFEXITED(status))
                printf("normal termination, exit status = %d\n",
                        WEXITSTATUS(status));
        else if(WIFSIGNALED(status))
                printf("abnormal termination, signal number = %d%s\n",
                        WTERMSIG(status),
#ifdef  WCOREDUMP
                WCOREDUMP(status) ? " (core file generated)" : "");
#else
                "");
#endif
        else if(WIFSTOPPED(status))
                printf("child stopped, signal number = %d\n",
                        WSTOPSIG(status));
}