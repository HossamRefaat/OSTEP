#include "types.h"
#include "user.h"

int main() {
    char buf[10];

    read(0, buf, 5);
    read(0, buf, 5);

    int x = getreadcount();

    printf(1, "readcount = %d\n", x);

    exit();
}