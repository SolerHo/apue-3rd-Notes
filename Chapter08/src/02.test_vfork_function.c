/***************************************************
* 
* 描述：测试vfork函数
* 
* **************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

int globvar = 6;

int main(void)
{
    int var;
    pid_t pid;

    var = 88;
    printf("before vfork\n");

    if ((pid = vfork()) < 0) {
        printf("vfork error");
    } else if (pid == 0) { // 子进程
        globvar++; // 修改父进程的变量
        var++;
        _exit(0); // 子进程终止
    }

    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    exit(0);
}