#include <klibtest.h>
#include <stdint.h>

#define N 32
uint8_t data_c[N];
uint8_t source_c[N];

void reset_c() {
    int i;
    for (i = 0; i < N; i ++) {
        data_c[i] = i + 1;
    }

    for (int i = 0; i < N; i++) {
        source_c[i] = 0;
    }
}

void check_seq_c(int l, int r, int val) {
    int i;
    for (i = l; i < r; i ++) {
        // printf("compare %d with %d\n", data_c[i], val + i - l);
        check(data_c[i] == val + i - l);
    }
}

void check_eq_c(int l, int r) {
    int i;
    for (i = l; i < r; i ++) {
        check(data_c[i] == source_c[i]);
    }
}

void test_memcpy() {
    int l, r;
    for (l = 0; l < N; l ++) {
        for (r = l + 1; r <= N; r ++) {
        reset_c();
        memcpy(data_c + l, source_c + l, r - l);
        check_seq_c(0, l, 1);
        check_eq_c(l, r);
        check_seq_c(r, N, r + 1);
        }
    }
}
