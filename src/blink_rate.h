#ifndef BLINK_RATE_H_
#define BLINK_RATE_H_

// blink speeds in us
enum {
    BLINK_MOUNTED = 1000000,
    BLINK_UMOUNTED = 500000,
    BLINK_SUSPENDED = 2000000
};

enum {
    MOUNTED_STATE = 0,
    UMOUNTED_STATE = 1,
    SUSPENDED_STATE = 2
};

#endif