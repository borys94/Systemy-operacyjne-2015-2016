#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_N 5

sem_t widelec[MAX_N];
pthread_t filozof[MAX_N];
int arg[MAX_N];

void *jedzenieLubMyslenie(void *id) {
    int pid = *((int *)(id));

    while(true) {
        sem_wait(&widelec[pid]);
        sem_wait(&widelec[(pid+1)%MAX_N]);

        fprintf(stdout, "folozof nr %d je\n", pid);
        usleep(rand() % 100000 + 1000);

        fprintf(stdout, "folozof nr %d mysli\n", pid);
        sem_post(&widelec[pid]);
        sem_post(&widelec[(pid+1)%MAX_N]);

        usleep(rand() % 100000 + 1000);
    }
}

int main(int argc, char *argv[]) {
    for(int i = 0;i < MAX_N;i++)
        sem_init(&widelec[i], 0, 1);

    for(int i = 0;i < MAX_N;i++) {
        arg[i] = i;
        pthread_create(&filozof[i], NULL, jedzenieLubMyslenie, &arg[i]);
    }

    for(int i = 0;i < MAX_N;i++)
        pthread_join(filozof[i], NULL);
}
