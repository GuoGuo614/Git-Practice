#include <klibtest.h>
#include <stdint.h>

#define N 32
uint8_t data[N];

void reset() {
  int i;
  for (i = 0; i < N; i ++) {
    data[i] = i + 1;
  }
}

void check_seq(int l, int r, int val) {
  int i;
  for (i = l; i < r; i ++) {
    // printf("compare %d with %d\n", data[i], val + i - l);
    check(data[i] == val + i - l);
  }
}

void check_eq(int l, int r, int val) {
  int i;
  for (i = l; i < r; i ++) {
    check(data[i] == val);
  }
}

void test_memset() {
  int l, r;
  for (l = 0; l < N; l ++) {
    for (r = l + 1; r <= N; r ++) {
      reset();
      uint8_t val = (l + r) / 2;
      memset(data + l, val, r - l);
      check_seq(0, l, 1);
      check_eq(l, r, val);
      check_seq(r, N, r + 1);
    }
  }
  // printf("""test_memset() passed!\n, test int %d and string %s\n", 123, "hello");
}