#include <klibtest.h>
#include <stdint.h>

#define N 100

extern const char *strings[N];

void test_strncpy_overflow() {
  char guard1[8] = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa};
  char buf[8] = {0};
  char guard2[8] = {0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb};

  // 溢出测试：源字符串比 buf 长
  strncpy(buf, "0123456789abcdef", 8); // 超过8字节

  // 检查哨兵区
  for (int i = 0; i < 8; i++) {
    check(guard1[i] == (char)0xaa); // 前哨兵
    check(guard2[i] == (char)0xbb); // 后哨兵
  }
}

void basic_test_strncpy() {
  char dest[N][N];
  for (int i = 0; i < N; i++) {
    if (strings[i] == NULL)
      continue;
    strncpy(dest[i], strings[i], N);
    char *p = dest[i];
    const char *q = strings[i];
    while (1) {
      check(*p == *q);
      if (*p == '\0')
        break;
      p++;
      q++;
    }
  }
}

void test_strncpy() {
  basic_test_strncpy();
  test_strncpy_overflow();
}