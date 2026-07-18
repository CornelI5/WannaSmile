#ifndef LIBWS_H
#define LIBWS_H

#include "engine.h"

#define salloc(x) malloc(x)

void brute_kill(int pid) {
    kill(pid, 9); 
}

void net_ping(char* target) {
    char cmd[100];
    sprintf(cmd, "ping -c 1 %s", target);
    system(cmd);
}

#endif
