#include "simulator.h"

static const void (*fun[]) (t_info) = {
	exe_Optimal,
	exe_FIFO,
	exe_LIFO,
	exe_LRU,
	exe_LFU,
	exe_SC,
	// exe_ESC,
};

int stream[MAX_STREAM];
int frame[10];
int frame_bit[10];
int cnt[31];
int stream_size;

void start_simul(t_info info){
	if (info.data_input == 1)
		getData_random(info);
	else
		getData_file(info);
	exe_Optimal(info);

	for (int i = 1; i < 6; i++){
		if (info.algo[i] == 1){
			printf("===%s execute===\n", algo[i]);
			init(i);
			fun[i](info);
		}
	}
}

void getData_random(t_info info){
	for (int i = 0; i < info.stream_size; i++){
		stream[i] = rand() % 30 + 1;
	}
	stream_size = info.stream_size;
}

void getData_file(t_info info){
	FILE* file;
	int size, num = 0, idx = 0;
	char buffer;

	file = fopen(info.file, "r+");
	if (file == NULL){
		printf("file open error\n");
		exit(1);
	}

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	while (ftell(file) != size){
		fread(&buffer, sizeof(buffer), 1, file);
		if (buffer == ' '){
			stream[idx] = num;
			idx++;
			num = 0;
		}
		else{
			num *= 10;
			num += buffer - '0';
		}
	}
	stream[idx] = num;
	idx++;
	stream_size = idx;
	fclose(file);
}

void exe_Optimal(t_info info){
	init(0);
	int idx, is_fault, page_fault=0;
    int target; //target : 교체 페이지

    for(idx = 0; idx < stream_size; idx++) {
        is_fault = 1;
        for(int i = 0; i<info.frame_size; i++) {
            if(frame[i] == stream[idx]){
                is_fault = 0;
                target = i;
            }      
        }
        
        if(is_fault){
			page_fault++;
		}

        if(page_fault <= info.frame_size && is_fault) {
            target = 0;
            while(frame[target] != -1) target = (target + 1) % info.frame_size;
        }
        else if(is_fault) {
            int temp;
			int use = -1;
            for(int i = 0; i < info.frame_size; i++) {
                temp = optimal_use(frame[i], idx);
                if(use < temp){
                    target = i;
                    use = temp;
                }
            }                        
        }
        frame[target] = stream[idx];
		if (info.algo[0] == 1){
			if(idx == 0)
				printf("===Optimal execute===\n");
			print(info, is_fault, target, idx);
			fprint(info, is_fault, target, idx, 0);
		}
    }
	printf("===Optimal result===\n");
	printf("page fault : %d\n", page_fault);
}

void exe_FIFO(t_info info){
	int is_fault, page_fault = 0;
	int target; //target : 교체 페이지
	for (int idx = 0; idx < stream_size; idx++){
		is_fault = 1;

		for (int i = 0; i < info.frame_size; i++){ //page fault 발생 여부 확인
			if (frame[i] == stream[idx]){
				is_fault = 0;
				target = i;
			}
		}

		if (is_fault == 1)
			page_fault++;
		if (page_fault <= info.frame_size && is_fault){ //page frame 다 적재되지 않은 상태
			target = 0;
			while (frame[target] != -1)
				target = (target + 1) % info.frame_size;
		}
		else if (is_fault){ //가장 먼저 들어온 page 찾기
			target = (page_fault - 1) % info.frame_size;
		}
		frame[target] = stream[idx];
		print(info, is_fault, target, idx);
		fprint(info, is_fault, target, idx, 1);
	}
	printf("===FIFO result===\n");
	printf("page fault : %d\n", page_fault);
}

void exe_LIFO(t_info info){
	int is_fault, page_fault = 0;
	int target; //target : 교체 페이지
	for (int idx = 0; idx < stream_size; idx++){
		is_fault = 1;

		for (int i = 0; i < info.frame_size; i++){ //page fault 발생 여부 확인
			if (frame[i] == stream[idx]){
				is_fault = 0;
				target = i;
			}
		}

		if (is_fault == 1)
			page_fault++;
		if (page_fault <= info.frame_size && is_fault){ //page frame 다 적재되지 않은 상태
			target = 0;
			while (frame[target] != -1)
				target = (target + 1) % info.frame_size;
		}
		else if (is_fault){ //가장 나중에 들어온 page 찾기
			target = (info.frame_size - 1) % info.frame_size;
		}
		frame[target] = stream[idx];
		print(info, is_fault, target, idx);
		fprint(info, is_fault, target, idx, 2);
	}
	printf("===LIFO result===\n");
	printf("page fault : %d\n", page_fault);
}

void exe_LRU(t_info info){
	int is_fault, page_fault = 0;
	int target; //target : 교체 페이지
	for (int idx = 0; idx < stream_size; idx++){
		is_fault = 1;

		for (int i = 0; i < info.frame_size; i++){ //page fault 발생 여부 확인
			if (frame[i] == stream[idx]){
				is_fault = 0;
				target = i;
			}
		}

		if (is_fault == 1)
			page_fault++;
		if (page_fault <= info.frame_size && is_fault){ //page frame 다 적재되지 않은 상태
			target = 0;
			while (frame[target] != -1)
				target = (target + 1) % info.frame_size;
		}
		else if (is_fault){ //가장 오래된 페이지 찾기
			int use = -1;
			int temp;
			for (int i = 0; i < info.frame_size; i++){
				temp = lru_use(frame[i], idx);
				if (use < temp){
					target = i;
					use = temp;
				}
			}
		}
		frame[target] = stream[idx];
		print(info, is_fault, target, idx);
		fprint(info, is_fault, target, idx, 3);
	}
	printf("===LRU result===\n");
	printf("page fault : %d\n", page_fault);
}

void exe_LFU(t_info info){
	int is_fault, page_fault = 0;
	int target; //target : 교체 페이지

	for (int idx = 0; idx < stream_size; idx++){
		is_fault = 1;

		for (int i = 0; i < info.frame_size; i++){ //page fault 발생 여부 확인
			if (frame[i] == stream[idx]){
				is_fault = 0;
				target = i;
			}
		}

		if (is_fault == 1)
			page_fault++;
		if (page_fault <= info.frame_size && is_fault){ //page frame 다 적재되지 않은 상태
			target = 0;
			while (frame[target] != -1)
				target = (target + 1) % info.frame_size;
		}
		else if (is_fault){ //가장 적게 사용된 page 찾기
			target = lfu_use(idx, info.frame_size);
		}
		cnt[stream[idx]]++;
		frame[target] = stream[idx];
		print(info, is_fault, target, idx);
		fprint(info, is_fault, target, idx, 4);
	}
	printf("===LFU result===\n");
	printf("page fault : %d\n", page_fault);
}

void exe_SC(t_info info){
	int is_fault, page_fault = 0;
	int ptr = 0;
	int target; //target : 교체 페이지

	for (int idx = 0; idx < stream_size; idx++){
		is_fault = 1;

		for (int i = 0; i < info.frame_size; i++){ //page fault 발생 여부 확인
			if (frame[i] == stream[idx]){
				is_fault = 0;
				target = i;
				frame_bit[i] = 1;
			}
		}

		if (is_fault == 1)
			page_fault++;
		while (is_fault){
			if (frame_bit[ptr] == 0){ // 페이지 교체
				target = ptr;
				ptr = (ptr + 1) % info.frame_size;
				break;
			}
			else if (frame_bit[ptr] == 1){ // 페이지 교체 하지 않고 넘어감
				frame_bit[ptr] = 0;
				ptr = (ptr + 1) % info.frame_size;
				continue; // 교체할 페이지를 찾아 계속 진행
			}
		}
		frame[target] = stream[idx];
		print(info, is_fault, target, idx);
		fprint(info, is_fault, target, idx, 5);
	}
	printf("===SC result===\n");
	printf("page fault : %d\n", page_fault);
}

void init(int algo){
	FILE* file = fopen(filename[algo], "w");
	fclose(file);
	for (int i = 0; i < 10; i++){
		frame[i] = -1;
	}
}

//현재 위치로부터 몇 번째 뒤에 같은 stream이 나타나는지 확인
int optimal_use(int num, int pos){
	int ret = 0;
	while (pos <= stream_size){
		if (stream[pos] == num)
			return ret;
		ret++;
		pos++;
	}
	return ret;
}

//현재 위치부터 몇 번째 전에 같은 stream이 나타나는지 확인
int lru_use(int num, int pos){
	int ret = 0;
	while (pos >= 0){
		if (stream[pos] == num)
			return ret;
		ret++;
		pos--;
	}
}

//가장 적게 사용한 page 찾기, 동일 횟수 존재 시 앞에 있는 것 부터 교체
int lfu_use(int pos, int frame_size){
	int ret, min_freq = MAX_INT;
    for(int i=0; i<frame_size; i++) {
        if(cnt[frame[i]] == min_freq){
            if(lru_use(frame[i], pos) < lru_use(frame[ret], pos)) continue;
            min_freq = cnt[frame[i]];
            ret = i;
        }
        if(cnt[frame[i]] < min_freq){
            min_freq = cnt[frame[i]];
            ret = i;
        }
    }
    return ret;
}

void print(t_info info, int is_fault, int target, int idx){
	printf("(%5d) ", idx + 1);
	if (is_fault){
		printf("\033[0;31m");
		printf("[Page Fault]");
		printf("\033[0m");
	}
	else
		printf("[Not  Fault]");
	printf(" : ");
	for (int i = 0; i < info.frame_size; i++){
		if(frame[i] == -1){
			printf("   X");
		}
		else if(i == target){
			printf("\033[0;31m");
			printf("%4d", frame[i]);
			printf("\033[0m");
		}
		else
			printf("%4d", frame[i]);
	}
	printf("\n");
}

void fprint(t_info info, int is_fault, int target, int idx, int algo){
	FILE* file = fopen(filename[algo], "a+");
	if (file == NULL){
		printf("file open error\n");
		exit(1);
	}

	fprintf(file, "(%5d) ", idx + 1);
	if (is_fault)
		fprintf(file, "[Page Fault]");
	else
		fprintf(file, "[Not  Fault]");
	fprintf(file, " : ");
	for (int i = 0; i < info.frame_size; i++){
		if(frame[i] == -1){
			fprintf(file, "   X");
		}
		else
			fprintf(file, "%4d", frame[i]);
	}
	fprintf(file, "\n");
	fclose(file);
}