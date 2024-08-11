/***************************************************
* 
* 描述：包含竞争条件的程序
* 
* **************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void charactatime(char *);

int main(void)
{
    pid_t pid;

    if ((pid = fork()) < 0) {
        printf("fork error\n");
    } else if (pid == 0) {
        charactatime("output from child\n");
    } else {
        charactatime("output from parent\n");
    }
    exit(0);
}

static void charactatime(char *str)
{
    char *ptr;
    int c;

    setbuf(stdout, NULL);

    for (ptr = str; (c = *ptr++)!= 0;) {
        putc(c, stdout);
    }
}
