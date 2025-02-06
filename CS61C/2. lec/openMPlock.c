#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
    omp_lock_t lock; // Declare a lock
    omp_init_lock(&lock); // Initialize the lock

    #pragma omp parallel
    {
        int id=omp_get_thread_num();
        //parallel section...
        // ...

        omp_set_lock(&lock); // Lock the lock
        //start sequencial section...
        //...
        printf("id=%d\n", id);

        //end sequencial section...
        omp_unset_lock(&lock); // Unlock the lock

        //parallel section...
        //...
    } 

omp_destroy_lock(&lock); // Destroy the lock

}