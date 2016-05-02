#include <stdio.h>
#include "a.h"
#include "b.h"

int a() {
    printf("a: before call to 'b'\n");
    return 1 + b();
}
