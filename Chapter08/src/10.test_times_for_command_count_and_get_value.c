/***************************************************
* 
* 描述：将命令行参数作为shell命令串执行，对每个命令计时，并打印从tms结构取得的值
* 
* **************************************************
*/

#include <sys/times.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void pr_times(clock_t, struct tms *, struct tms *);
static void do_cmd(char *);
void pr_exit(int status);

int main(int argc, char *argv[])
{
    int i;
    setbuf(stdout, NULL);

    for (i = 1; i < argc; i++) {
        do_cmd(argv[i]);
    }
    exit(0);
}

static void do_cmd(char *cmd) {
    struct tms tmsstart, tmsend;
    clock_t start, end;

    int status;

    printf("\ncommand : %s\n", cmd);

    if ((start = times(&tmsstart)) == -1) {
        printf("times error\n");
    }

    if ((status = system(cmd)) < 0) {
        printf("system error\n");
    }

    if ((end = times(&tmsend)) == -1) {
        printf("times error\n");
    }

    pr_times(end-start, &tmsstart, &tmsend);
    pr_exit(status);
}
static void pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend)
{
    static long clktck = 0;

    if (clktck == 0) {
        if ((clktck = sysconf(_SC_CLK_TCK)) < 0) {
            printf("ssyconf error\n");
        }
    }

    printf("  real: %7.2f\n", real / (double) clktck);
    printf("  user: %7.2f\n", tmsend->tms_utime - tmsstart->tms_utime / (double) clktck);
    printf("  sys : %7.2f\n", tmsend->tms_stime - tmsstart->tms_stime / (double) clktck);
    printf("  child user: %7.2f\n", tmsend->tms_cutime - tmsstart->tms_cutime / (double) clktck);
    printf("  child sys : %7.2f\n", tmsend->tms_cstime - tmsstart->tms_cstime / (double) clktck);
}

void pr_exit(int status)
{
        if(WIFEXITED(status))
                printf("normal termination, exit status = %d\n",
                        WEXITSTATUS(status));
        else if(WIFSIGNALED(status))
                printf("abnormal termination, signal number = %d%s\n",
                        WTERMSIG(status),
#ifdef  WCOREDUMP
                WCOREDUMP(status) ? " (core file generated)" : "");
#else
                "");
#endif
        else if(WIFSTOPPED(status))
                printf("child stopped, signal number = %d\n",
                        WSTOPSIG(status));
}