#include <klibtest.h>
#include <stdint.h>

#define N 32
uint8_t data_v[N];
uint8_t source_v[N];

void reset_v() {
    int i;
    for (i = 0; i < N; i ++) {
        data_v[i] = i + 1;
    }

    for (int i = 0; i < N; i++) {
        source_v[i] = 0;
    }
}
void check_seq_v(int l, int r, int val) {
    int i;
  for (i = l; i < r; i ++) {
    // printf("compare %d with %d\n", data[i], val + i - l);
    check(data_v[i] == val + i - l);
  }
}

void check_eq_v(int l, int r) {
    int i;
    for (i = l; i < r; i ++) {
        check(data_v[i] == source_v[i]);
    }
}

void reset_source_v() {
    for (int i = 0; i < N; i++) {
        source_v[i] = 0;
    }
}

void test_basic_memmove() {
    int l, r;
    for (l = 0; l < N; l ++) {
        for (r = l + 1; r <= N; r ++) {
            reset_v();
            reset_source_v();
            memmove(data_v + l, source_v + l, r - l);
            check_seq_v(0, l, 1);
            check_eq_v(l, r);
            check_seq_v(r, N, r + 1);
        }
    }
}

void test_memmove_overlap() {
    int offset = 1;
    for (; offset < N; offset++) {
        reset_v();
        memmove(data_v, data_v + offset, N - offset);
        check_seq_v(0, N - offset, 1 + offset);
        check_seq_v(N - offset, N - 1, N - offset + 1);
    }

    for (offset = 1; offset < N; offset++) {
        reset_v();
        memmove(data_v + offset, data_v, N - offset);
        check_seq_v(0, offset, 1);
        check_seq_v(offset, N, 1);
    }
}

void test_memmove() {
    test_basic_memmove();
    test_memmove_overlap();
}