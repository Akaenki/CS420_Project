#include "main.h"

int mian(int argc, char * argv[]){
    
    return 0;
}

long long timer(){// unit of nanosecond (kind of)
    struct timespec ts;
#ifdef __MACH__ // OSX compatible
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    ts.tv_sec = mts.tv_sec;
    ts.tv_nsec = mts.tv_nsec;
#else
    clock_gettime(CLOCK_MONOTONIC, &ts);
#endif
    return 1000000000*ts.tv_sec + ts.tv_nsec;
}