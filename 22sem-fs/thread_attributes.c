#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 5

void* func(void* smth) {
    printf("hello\n");
    return NULL;
}

int main() {
    pthread_t tids[N];

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));
    pthread_attr_setguardsize(&attr, 0);

    // 1MB
    // int res = pthread_attr_setstacksize(&attr, 10);
    // if (res) {
    //     printf("failed\n");
    // }

    printf("%ld\n", sysconf(_SC_THREAD_STACK_MIN));
    for (int i = 0; i != N; ++i) {
        pthread_create(&tids[i], &attr, func, NULL);
    }
    pthread_attr_destroy(&attr);

    for (int i = 0; i != N; ++i) {
        pthread_join(tids[i], NULL);
    }
}
