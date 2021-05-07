#include <stdio.h>

#include "hy_time.h"

int main(int argc, char *argv[])
{
    hy_uint64_t start_us = HyTimeGetCurrentTime2Us();

    hy_uint64_t interval = HyTimeGetTimeInterval(start_us);

    printf("interval: %lld \n", interval);

    return 0;
}
