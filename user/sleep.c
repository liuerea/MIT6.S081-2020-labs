#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: sleep seconds...\n");
        exit(1);
    }
    int time = atoi(argv[1]);
    int ret = sleep(time);
    if(ret == -1){
        printf("unexpected error\n");
        exit(1);
    }
    exit(0);
}