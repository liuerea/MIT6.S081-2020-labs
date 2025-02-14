#include "kernel/types.h"
#include "user/user.h"

int readwrite_pipe(int *pl){
    int first;
    read(pl[0], &first, sizeof(first));
    if(first == -1){
        return 0;
    }
    printf("prime %d\n", first);

    close(pl[1]);
    int pr[2];
    if(pipe(pr) < 0){
        exit(1);
    }
    int pid = fork();
    if(pid != 0){
        close(pr[0]);
        int num;
        while(read(pl[0], &num, sizeof(num)) > 0 && num != -1){
            if(num % first != 0){
                write(pr[1], &num, sizeof(num));
            }
        }
        num = -1;
        write(pr[1], &num, sizeof(num));
        wait(0);
        exit(0);
    }else{
        close(pl[0]);
        readwrite_pipe(pr);
        exit(0);
    }
    return 0;
}

int main(int argc, char *argv[]){
    int fds[2];
    if(pipe(fds) < 0){
        exit(1);
    }
    int pid = fork();
    if(pid != 0){
        close(fds[0]);
        int i;
        for(i = 2; i<=35; ++i){
            write(fds[1], &i, sizeof(i));
        }
        i = -1;
        write(fds[1], &i, sizeof(i));
        wait(0);
        exit(0);
    }else{
        readwrite_pipe(fds);
        exit(0);
    }

    exit(0);
}