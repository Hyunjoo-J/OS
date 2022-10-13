#include "types.h"
#include "stat.h"
#include "user.h"

#define PNUM 5 //Process 개수
#define PRINT_CYCLE 10000000 //Process가 정보를 출력하는 주기
#define TOTAL_COUNTER 500000000 //Process가 종료할 때 counter 값

void sdebug_func(void)
{
   int n,pid;

   printf(1, "start sdebug command\n");

   for (n = 0; n < PNUM; n++)
   {
      pid = fork();
      if(pid < 0){
         break;}
      if(pid == 0)
      {
			     weightset(n + 1);
					 int print_counter = PRINT_CYCLE;
					 int counter = 0;
					 int end_ticks;
					 int start = uptime();
					
					 int first = 1;

            while (counter <= TOTAL_COUNTER){
							 counter++;
							 print_counter--;
							 if(print_counter == 0)
							 {
								 if(first)
								 {
									 
									 end_ticks = uptime();
									 printf(1, "PID: %d, WEIGHT: %d, ", getpid(), n + 1);
									 printf(1, "TIMES: %d ms\n", (end_ticks - start) *10);
									 first = 0;
								 }
								 print_counter = PRINT_CYCLE;
							 }
						}
						printf(1, "PID: %d terminated\n", getpid());
						exit();
          }
     }
     for(int n = PNUM; n > 0; n--){
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
