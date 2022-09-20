#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char** argv){
	int pid, wpid;

	if (argc < 3){
		printf(1, "Usage : ssu_trace <mask> <command>");
		exit();
	}

	trace(atoi(argv[1]));

	pid = fork();
	if (pid < 0){
		printf(1, "error : fork failed\n");
		exit();
	}
	if (pid == 0){
		exec(argv[2], argv + 2);
		printf(1, "error : ssu_trace <%s> failed\n", argv[2]);
		exit();
	}
	while ((wpid = wait()) >= 0 && wpid != pid){
		printf(1, "zombie!\n");
	}
	exit();
}
