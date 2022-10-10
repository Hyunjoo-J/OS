#include "types.h"
#include "stat.h"
#include "user.h"

#define PNUM 5 //Process 개수
#define PRINT_CYCLE 10000000 //Process가 정보를 출력하는 주기
#define TOTAL_COUNTER 500000000 //Process가 종료할 때 counter 값

void sdebug_func(void)
{
    int n, pid;
    long counter;

    printf(1, "start sdebug command\n");

    for (int i = 0; i < PNUM; i++)
    {
        pid = fork();
        if(pid < 0)
            break;
        if(pid == 0)
            exit();
    }

    printf(1, "end of sdebug command\n");
}

int main(void)
{
    sdebug_func();
    exit();
}