#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/param.h"

int main(int argc, char *argv[]){
    char *cmd[MAXARG] = {0};
    int i = 0;
    for(i=1; i<argc; ++i){
        cmd[i - 1] = argv[i];
    }

    char input[MAXARG];
    int n = 0;
    while(read(0, &input[n], 1) == 1){
        if(input[n] == '\n'){
            input[n] = '\0';
            cmd[argc-1] = input;
            cmd[argc] = 0;

            if(fork() == 0){
                exec(cmd[0], cmd);
                exit(1);
            }
            wait(0);
            n = 0;
        }else{
            ++n;
        }
    }

    for(int j=0; j<MAXARG; ++j){
        if(cmd[j]){
            free(cmd[j]);
        }
    }

    exit(0);
}