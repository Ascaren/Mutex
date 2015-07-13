#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>

pthread_mutex_t MTX = PTHREAD_MUTEX_INITIALIZER ;
pthread_cond_t COND = PTHREAD_COND_INITIALIZER ;
bool PRINT = false;

void* foo(void *arg){
   pthread_mutex_lock(&MTX);
   while( !PRINT ){
        pthread_cond_wait(&COND,&MTX);
    printf("Can printf \n");
    pthread_mutex_unlock(&MTX);
    return 0;
   }
}

int main(int c, char** u){
    pthread_t = 0;
    pthread_create(&t,0,foo,0);
    sleep(5);
    pthread_mutex_lock(&MTX);
    PRINT = true;
    pthread_cond_signal(&COND);
    pthread_mutex_unlock(&MTX);
    pthread_join(t);
    return 0;
}
