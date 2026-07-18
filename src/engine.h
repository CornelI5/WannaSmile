#ifndef ENGINE_H
#define ENGINE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define T int
#define U main
#define t int
#define cm return 0
#define ?(c) if(c)
#define I else
#define : =
#define - ,
#define s(x) printf(x)
#define x(c) if(fork()==0){execlp(c,c,NULL);exit(0);}
#define A(x) {x}

#endif
