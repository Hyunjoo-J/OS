#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char* argv[]) {
    int pid, wpid;
    int mask = atoi(argv[1]);
    trace(mask);
    
    pid = fork();
    if(pid < 0) {
        // printf(1, "ssu_trace: fork failed\n"); 
        exit();
    }

    if(pid == 0) {
        exec(argv[2], argv+2);
        printf(1, "ssu_trace:exec %s failed\n", argv[2]);
        exit();
    }

    while((wpid=wait()) >= 0 && wpid != pid) {
        printf(1, "zombie!\n");
    }
    exit();
}
