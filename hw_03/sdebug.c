#include "types.h"
#include "stat.h"
#include "user.h"

#define PNUM 5 //Process 개수
#define PRINT_CYCLE 10000000 //Process가 정보를 출력하는 주기
#define TOTAL_COUNTER 500000000 //Process가 종료할 때 counter 값

void sdebug_func(void)
{
   int pid;
   int start;
   long long counter;

   printf(1, "start sdebug command\n");

   for (int i = 0; i < PNUM; i++)
   {
      pid = fork();
      if(pid < 0)
         break;
      if(pid == 0)
         {
            start = uptime();
            while (1){
               counter = uptime() - start;
               if (counter >= TOTAL_COUNTER)
                  exit();
               if (counter >= PRINT_CYCLE)
                  printf(1, "PID: %d, WEIGHT: %d, TIMES : %dms", getpid(),1, 2);
            }
         }
   }
     for(int n = 5; n > 0; n--){
       if(wait() < 0){
            printf(1, "wait stopped early\n");
            exit();
       }
  }
    if(wait() != -1){
    printf(1, "wait got too many\n");
    exit();
  }

   printf(1, "end of sdebug command\n");
}

int main(void)
{
   sdebug_func();
   exit();
}