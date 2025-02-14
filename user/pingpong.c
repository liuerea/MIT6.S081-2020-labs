#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    char a = 'a';
    int fds[2];
    if(pipe(fds) < 0){
        printf("pipe() failed\n");
      exit(1);
    }
    int pid = fork();
    if(pid != 0){
        a = 'b';
        write(fds[1], &a, 1);
        wait(0);
        read(fds[0], &a, 1);
        if(a == 'c'){
            printf("%d: received pong\n", getpid());
        }
    }else{
        read(fds[0], &a, 1);
        if(a == 'b'){
            printf("%d: received ping\n", getpid());
        }
        a = 'c';
        write(fds[1], &a, 1);
        exit(0);
    }
    exit(0);
}