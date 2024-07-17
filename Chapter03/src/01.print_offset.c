 /***************************************************
 * 
 * 描述：测试对其标准输入能否设置偏移量
 * 
 * **************************************************
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1) {
        printf("cannot seek\n");
    } else {
        printf("seek ok\n");
    }
    exit(0);
}