#include "simulator.h"

t_info info;

int main()
{
	char buffer[100];
	int cnt = 0;

	printf("===Page Replacement Simulaotr===\n");
	printf("A. Page Replacement 알고리즘 시뮬레이터를 선택하시오(최대 3개)\n");
	printf("(1) Optimal (2) FIFO (3) LIFO (4) LRU (5) LFU (6) SC (7) ESC (8) All\n");
	printf("(8) All은 단독으로만 선택 가능하며 선택 시 (1) ~ (7)까지의 모든 알고리즘이 실행됩니다.\n");
	printf("입력 방법 예시 : \"1 2 3\", \"1 2\" \"8\"\n");
	fgets(buffer, 100, stdin);
	if (buffer[2] && strstr(buffer, "8")){ //두개 이상의 입력에 8이 포함된 경우
		printf("Usage Error : (8) All은 단독으로만 사용해야 합니다.\n");
		return (0);
	}

	if (strcmp(buffer, "8\n") == 0){
		for (int i = 0; i < 7; i++)
			info.algo[i] = 1;
	}
	else{
		char *ptr =strtok(buffer, " ");

		while (ptr){
			cnt++;
			info.algo[atoi(ptr) - 1] = 1;
			ptr = strtok(NULL, " ");
		}
		if (cnt > 3){
			printf("Usage Error : 선택 개수 초과입니다.\n");
			return (0);
		}
	}

	printf("B. 페이지 프레임의 개수를 입력하시오.(3~10)\n");
	scanf("%d", &info.frame_size);
	if (info.frame_size < 3 || info.frame_size > 10){
		printf("Usage Error : 페이지 프레임 범위를 벗어났습니다.(3~10)\n");
		return (0);
	}
	
	printf("C. 데이터 입력 방식을 선택하시오.(1, 2)\n");
	printf("(1) 랜덤하게 생성\n(2) 사용자 생성 파일 오픈\n");
	scanf("%d", &info.data_input);
	if (info.data_input != 1 && info.data_input != 2){
		printf("Usage Error : 1 또는 2를 입력하시오.\n");
		return (0);
	}
	if (info.data_input == 1){
		printf("C-1.입력 스트림 개수를 입력하시오.\n");
		scanf("%d", &info.stream_size);
	}
	else{
		printf("C-2.파일명을 입력하시오.\n");
		scanf("%s", info.file);
	}

	//현재까지 입력 내용 출력
	printf("selected algorithms : ");
	for (int i = 0; i < 7; i++){
		if (info.algo[i] == 1)
			printf("%s ", algo[i]);
	}
	printf("\nnumber of page frame : %d\n", info.frame_size);
	printf("data input option : %d\n", info.data_input);
	start_simul(info);
	return (0);
}