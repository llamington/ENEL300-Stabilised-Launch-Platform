#ifndef __UTIL_H
#define __UTIL_H

#define MIN(x, y) \
    (((x) < (y)) ? (x) : (y))

#define MAX(x, y) \
    (((x) > (y)) ? (x) : (y))

#define BOUND(low, high, value) \
    MAX(MIN(high, value), low)

#endif