#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "a.h"
#include "b.h"

int c() {
    printf("In c.\n");
    return 3;
}

int d() {
    return 4;
}

int main() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srandom(tv.tv_sec + tv.tv_usec/1000000);
    long r = random();
    int result = 0;

    printf("In main.\n");
    result += a() + b() + c();
    if (r < RAND_MAX/2) {
        result += d();
    }

    printf("Result was %d\n", result);
    return 0;
}
