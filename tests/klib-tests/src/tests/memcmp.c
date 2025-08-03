#include <klibtest.h>
#include <stdint.h>

#define N 32
extern uint8_t data[N];

void reset();

void test_memcmp() {
    for (int l = 0; l < N; l++) {
        reset();
        check(memcmp(data, data, N - l) == 0);
    }

    for (int l = 1; l < N; l++) {
        reset();
        check(memcmp(data, data + l, N - l) < 0);
    }

    for (int l = 1; l < N; l++) {
        reset();
        check(memcmp(data + l, data, N - l) > 0);
    }
}