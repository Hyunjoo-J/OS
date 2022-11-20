#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fn; //페이지 프레임 개수
int stream[10]; //참조 페이지 스트링
int hit; //hit 변수
int pagefaultcnt; //페이지 폴트 카운트
int p[100]; //페이지
int input; // 데이터 입력방식

int main()
{
	char buffer[10];
	int  choice[3];
	int idx = 0;

	printf("A. Page Replacement 알고리즘 시뮬레이터를 선택하시오(최대 3개)\n");
	printf("(1) Optimal (2) FIFO (3) LIFO (4) LRU (5) LFU (6) SC (7) ESC (8) All\n");
	printf("(8) All은 단독으로만 선택 가능하며 선택 시 (1) ~ (7)까지의 모든 알고리즘이 실행됩니다.\n");
	printf("입력 방법 예시 : \"1 2 3\", \"1 2\" \"8\"\n");
	scanf("%[^\n]s", buffer);
	if (buffer[2] && strstr(buffer, "8")){ //두개 이상의 입력에 8이 포함된 경우
		printf("Usage Error : (8) All은 단독으로만 사용해야 합니다.\n");
		return (0);
	}
	char *ptr = strtok(buffer, " ");
	while (ptr != NULL){ //1~8이외의 것 확인
		choice[idx++] = atoi(ptr);
		if (choice[idx - 1] > 8 || choice[idx - 1] < 1){
			printf("Usage Error : 1 ~ 8 사이의 숫자만 입력하세요.\n");
			return (0);
		}
		ptr = strtok(NULL, " ");
	}
	if (idx > 3)
		printf("Usage Error : 선택 개수 초과입니다.\n");

	printf("B. 페이지 프레임의 개수를 입력하시오.(3~10)\n");
	scanf("%d", &fn);
	if (fn < 3 || fn > 10){
		printf("Usage Error : 페이지 프레임 범위를 벗어났습니다.(3~10)\n");
		retrun (0);
	}
	
	printf("C. 데이터 입력 방식을 선택하시오.(1, 2)\n");
	printf("(1) 랜덤하게 생성\n(2) 사용자 생성 파일 오픈\n");
	scanf("%d", &input);
	if (input != 1 && input != 2){
		printf("Usage Error : 1 또는 2를 입력하시오.\n");
		return (0);
	}

	for (int i = 0; i < idx; i++){
		switch (choice[i]){
			case 1 :
				optimal();
				break;
			case 2 :
				fifo();
				break;
			case 3 :
				lifo();
				break;
			case 4 :
				lru();
				break;
			case 5 :
				lfu();
				break;
			case 6 :
				sc();
				break;
			case 7:
				esc();
				break;
			case 8 :
				optimal();
				fifo();
				lifo();
				lru();
				lfu();
				sc();
				esc();
				break;
		}
	}
	return (0);
}