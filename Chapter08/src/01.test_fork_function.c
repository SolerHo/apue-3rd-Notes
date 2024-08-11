/***************************************************
* 
* 描述：测试fork函数
* 
* **************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

int globvar = 6;
char buf[] = "a write to stdout\n"


int main(void)
{
    int var;
    pid_t pid;

    var = 18;
    // strlen() 计算不包括终止符null字节的字符串长度
    // sizeof() 计算包含终止符null字符的缓冲区长度，在编译时计算缓冲区长度。
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) { // 目的：避免将终止null字符写出
        printf("write error\n");
    }

    printf("before fork\n");

    if ((pid = fork()) < 0) {
        printf("fork error");
    } else if (pid == 0) { // 子进程
        globvar++; // 修改变量
        var++;
    } else {
        sleep(2); // 父进程
    }

    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    exit(0);
}