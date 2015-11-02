#include <stdio.h>
#include <pthread.h>

void* watek(void* arg) {
	printf("Drugi watek\n");
}

int main() {
	pthread_t thread;

    pthread_create(&thread, NULL, watek, NULL);
    pthread_join(thread, NULL);

	return 0;
}
