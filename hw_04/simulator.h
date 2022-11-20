#ifndef SIMULATOR_H
# define SIMULATOR_H
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct _info{
	int algo[7];		// 7개의 알고리즘 실행 여부
	int frame_size;		// 페이지 프레임 수(3~10)
	int data_input;		// 데이터 입력 방식 : 1. 랜덤 2. 파일
	int stream_size;		// 입력 스트림 수
	char file[100];		// 입력 파일 이름
} info;
#endif