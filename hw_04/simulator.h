#ifndef SIMULATOR_H
# define SIMULATOR_H
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>
# include <fcntl.h>

#define MAX_STREAM 100000

typedef struct s_info{
	int algo[7];		// 7개의 알고리즘 실행 여부
	int frame_size;		// 페이지 프레임 수(3~10)
	int data_input;		// 데이터 입력 방식 : 1. 랜덤 2. 파일
	int stream_size;		// 입력 스트림 수
	char file[100];		// 입력 파일 이름
} t_info;

static const char* algo[7] = {"Optimal", "FIFO", "LIFO", "LRU", "LFU", "SC", "ESC"};
static const char* filename[7] = {"Optimal_result.txt", "FIFO_result.txt", "LIFO_result.txt", "LRU_result.txt", "LFU_result.txt", "SC_result.txt", "ESC_result.txt"};

//execute.c function
void start_simul(t_info info);
void getData_random(t_info info);
void getData_file(t_info info);
void exe_Optimal(t_info info);
void exe_FIFO(t_info info);
void exe_LIFO(t_info info);
void exe_LRU(t_info info);
void exe_LFU(t_info info);
void exe_SC(t_info info);
void exe_ESC(t_info info);
void init(int algo);
int use_frame(int num, int pos, t_info info);
void print(t_info info, int is_fault, int target, int idx);
void fprint(t_info info, int is_fault, int target, int idx, int algo);
#endif