#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int i;

void* myworker(void* arg)
{
     
    for (int p = 0; p < 10000000; p++)
        ;

    i = 5;

    return NULL;
}

int main()
{
    pthread_t id;

    i = 3;
    printf("In the main thread, i= %d \n", i);
    printf("Creating a new thread where we will change the value of i and we will print the changed value here\n");
    int failed = pthread_create(&id, NULL, myworker, NULL);
    if (failed) {
        printf("can't create a child thread, process killed\n");
        return 0;
    }
    else {
        printf("Successfully created a child thread\n");
    }
    
    
    pthread_join(id, NULL);
    printf("Child thread has finished changing the value of i\n");
    printf("i is now %d \n", i);

    return 0;
}
