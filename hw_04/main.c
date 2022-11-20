#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fn; //페이지 프레임 개수
int stream[10]; //참조 페이지 스트링
int hit; //hit 변수
int pagefaultcnt; //페이지 폴트 카운트
int p[100]; //페이지

int main()
{
	char buffer[10];
	int  choice[3];
	int idx = 0;

	while (1){
		printf("Page Replacement 알고리즘 시뮬레이터를 선택하시오(최대 3개)\n");
		printf("(1) Optimal (2) FIFO (3) LIFO (4) LRU (5) LFU (6) SC (7) ESC (8) All\n");
		printf("(8) All은 단독으로만 선택 가능하며 선택 시 (1) ~ (7)까지의 모든 알고리즘이 실행됩니다.\n");
		printf("입력 방법 예시 : \"1 2 3\", \"1 2\"\n");
		scanf("%s", &buffer);

		if (buffer[2] && buffer, "8"){ //두개 이상의 입력에 8이 포함된 경우
			printf("Usage Error : (8) All은 단독으로만 사용해야 합니다.\n");
			return (0);
		}
		char *ptr = strtok(buffer, " ");

		while (ptr != NULL){ //1~8이외의 것 확인
			choice[idx++] = atoi(ptr);
			ptr = strtok(NULL, " ");
		}
		if (idx > 3){
			prinft("Usage Error : 선택 개수 초과\n");
		}
	}
}