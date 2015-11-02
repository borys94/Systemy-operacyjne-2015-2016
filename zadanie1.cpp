#include <stdio.h>
#include <pthread.h>

// watek
void* watek(void* arg) {
	printf("Drugi watek\n");
}

int main() {
	pthread_t thread;

    // tworzenie nowego watku
    pthread_create(&thread, NULL, watek, NULL);

    // czekanie na zakonczenie watku
    pthread_join(thread, NULL);

	return 0;
}
