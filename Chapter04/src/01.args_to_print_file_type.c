/***************************************************
* 
* 描述：对输入文件打印文件类型
* 
* **************************************************
*/


#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *agrv[]) {
    int i;
    struct stat buf;
    char *ptr;

    for (i = 1; i < argc; i++) {
        printf("%s: ", agrv[i]);

        if (lstat(agrv[i], &buf) < 0) {
            printf("lstat error");
            continue;
        }
        if (S_ISREG(buf.st_mode)) {
            ptr = "regular";
        } else if (S_ISDIR(buf.st_mode)) {
            ptr = "directory";
        } else if (S_ISCHR(buf.st_mode)) {
            ptr = "character special";
        }else if (S_ISBLK(buf.st_mode)) {
            ptr = "block special";
        } else if (S_ISFIFO(buf.st_mode)) {
            ptr = "FIFO";
        } else if (S_ISLNK(buf.st_mode)) {
            ptr = "symbolic link";
        }else if (S_ISSOCK(buf.st_mode)) {
            ptr = "socket";
        } else {
            ptr = "** unknown mode **";
        }
        printf("%s\n", ptr);
    }
    exit(0);
}