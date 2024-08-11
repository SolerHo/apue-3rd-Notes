/***************************************************
* 
* 描述：测试执行一个解释器文件的程序
* 
* **************************************************
*/

#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    if ((pid == fork()) < 0) {
        printf("fork error\n");
    } else if (pid == 0) { // 子进程
        if (execl("/home/sar/bin/testinterp", "testinterp", "myargl", "MY ARG2", (char *)0) < 0) {
            printf("execl error\n");
        }
    }

    if (waitpid(pid, NULL, 0) < 0) { // 父进程
        printf("waitpid error\n");
    }
    exit(0);
}