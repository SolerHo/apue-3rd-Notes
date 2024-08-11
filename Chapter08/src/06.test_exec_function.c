/***************************************************
* 
* 描述：测试exec函数
* 
* **************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(void)
{
    pid_t pid;
    if ((pid = fork()) < 0) {
        printf("fork error\n");
    } else if (pid == 0) {
        if (execle("/home/sar/bin/echoall", "echoall", "myargl", "MY ARG2", (char *)0, env_init) < 0) {
            printf("execle error\n");
        }
    }
    if ((pid = fork()) < 0) {
        printf("fork error\n");
    } else if (pid == 0) {
        if (execlp("echoall", "echoall", "only 1 arg", (char *)0) < 0) {
            printf("execlp error\n");
        }
    }

    exit(0);
}