/***************************************************
* 
* 描述：fork 两次以避免僵死进程
* 
* **************************************************
*/

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    if ((pid = fork()) == 0) {
        printf("fork error\n");
    } else if (pid == 0) {
        if ((pid = fork()) < 0) {
            printf("fork error\n");
        } else if (pid > 0) {
            exit(0);
        }
        sleep(2); // 保证打印父进程ID时子进程已终止。
        printf("second child, parent pid = %ld\n", (long)getppid());
        exit(0);
    }

    if (waitpid(pid, NULL, 0) != pid) {
        printf("waitpid error\n");
    }
    exit(0);
}