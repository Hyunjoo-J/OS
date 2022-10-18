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
		int print_counter = PRINT_CYCLE; //print_counter 값을 PRINT_CYCLE로 설정 후 1씩 줄여가며 0이 될 때 출력
		int counter = 0;
		int end_ticks; //종료 시간
		int start = uptime(); //시작 시간
				
		int first = 1; //프로세스 별로 한 번만 출력하는지 확인할 변수

		weightset(n + 1); //n + 1값으로 weight 설정
        while (counter <= TOTAL_COUNTER){ //counter 값을 계속 늘리며 TOTAL_COUNTER보다 크면 종료
		  counter++;
		  print_counter--;
		  if(print_counter == 0){ //print_counter 0일 때, 출력
			if(first){
				end_ticks = uptime();
				printf(1, "PID: %d, WEIGHT: %d, ", getpid(), n + 1);
				printf(1, "TIMES: %d ms\n", (end_ticks - start) * 10); //(종료 시간 - 시작 시간) * 10 으로 시간 계산
				first = 0;
			}
			print_counter = PRINT_CYCLE; //출력 후 print_counter 초기화
		  }
		}
		printf(1, "PID: %d terminated\n", getpid()); //프로세스 종료
		exit();
        }
     }

     for(; n > 0; n--){ //forktest.c 참고하여 자식 프로세스가 종료 되기를 기다림
       if(wait() < 0){
            printf(1, "wait stopped early\n");
            exit();
       }
  	}
    if(wait() != -1){
    printf(1, "wait got too many\n");
    exit();
  	}

   printf(1, "end of sdebug command\n"); //sdebug 종료
}

int main(void)
{
   sdebug_func();
   exit();
}
