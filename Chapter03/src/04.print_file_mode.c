
/***************************************************
* 
* 描述：只使用read 和 write 函数复制一个文件
* 
* **************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int val;
    
    if (argc != 2) {
        printf("usage : a.out <descriptior#>");
        return 0;
    }

    if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0) {
        printf("fcntl error for fd %d", atoi(argv[1]));
    }

    switch (val & O_ACCMODE) {
        case O_RDONLY:
            printf("read only");
            break;
        case O_WRONLY:
            printf("only write");
            break; 
        case O_RDWR:
            printf("read write");
            break;
        default:
            printf("unknown access mode");
    }

    if (val & O_APPEND) {
        printf(", append");
    }
    if (val & O_NONBLOCK) {
        printf(", nonblocking");
    }
    if (val & O_SYNC) {
        printf(", synchronous writes");
    }

    // 功能测试宏 _POSIX_C_SOURCE
    #if !defined(_POSIX_C_SOURCE) && defined (O_SYNC) && (O_FSYNC != O_SYNC)
        if (val & O_SYNC) {
            printf(", synchronous writes");
        }
    #endif

    putchar('\n');
    exit(0);
}
