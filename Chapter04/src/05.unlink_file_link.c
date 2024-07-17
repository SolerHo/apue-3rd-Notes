/***************************************************
* 
* 描述：测试unlink函数
* 
* **************************************************
*/

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    if (open("tempfile", O_RDWR) < 0) {
        printf("open error");
    }
    if (unlink("tempfile") < 0) {
        printf("unlink error");
    }
    printf("file unlinked \n");

    sleep(15);
    printf("Done\n");
    exit(0);
}