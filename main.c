#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>

int turn = 0;
pthread_mutex_t MTX = PTHREAD_MUTEX_INITIALIZER ;
pthread_cond_t COND = PTHREAD_COND_INITIALIZER ;
bool PRINT = true;

void* foo(void *arg){
    while(turn){
       pthread_mutex_lock(&MTX);
       while( !PRINT )
            pthread_cond_wait(&COND,&MTX);

        printf("PING \n");
        PRINT = false;
        pthread_cond_signal(&COND);
        pthread_mutex_unlock(&MTX);
    }
   return 0;
}
void* foo2(void *arg){
    while(turn--){
        pthread_mutex_lock(&MTX);
        while( PRINT )
            pthread_cond_wait(&COND,&MTX);

        printf("PONG \n");
        PRINT = true;
        pthread_cond_signal(&COND);
        pthread_mutex_unlock(&MTX);
    }
    return 0;
}

int main(int argc, char ** argv){
    pthread_t t = 0;
    pthread_t s = 0;

    turn = atoi(argv[1]);

    pthread_create(&t,0,foo,0);
    pthread_create(&s,0,foo2,0);

    pthread_join(t,NULL);
    pthread_join(s,NULL);

    return 0;
}
