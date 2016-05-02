#include <stdio.h>
#include "b.h"
#include "lib.h"

// Externally visible, but no other unit calls this.
void foo() {
    printf("foo\n");
}

int b() {
    printf("b: before call to 'foo'\n");
    foo();
    printf("b: before call to 'lib'\n");
    return 2 + lib();
}
