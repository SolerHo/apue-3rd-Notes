/***************************************************
* 
* 描述：使用 getc 和 putc 将标准输入复制到标准输出
* 
* **************************************************
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int c;
    while ((c =getc(stdin)) != EOF) {
        if (putc(c, stdout) == EOF) {
            printf("output error");
        } 
    }

    if (ferror(stdin)) {
        printf("input error");
    }
    exit(0);
}