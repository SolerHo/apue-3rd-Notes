/***************************************************
* 
* 描述：使用 fgets 和 fputs 将标准输入复制到标准输出，getc 和 putc 的优化版本
* 
* **************************************************
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 4096

int main(void)
{
    char buf[MAXLINE];
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (fputs(buf, stdout) == EOF) {
            printf("output error");
        } 
    }

    if (ferror(stdin)) {
        printf("input error");
    }
    exit(0);
}