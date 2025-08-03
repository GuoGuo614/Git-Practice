#include <klibtest.h>
#include <stdint.h>

#define N 100

const char *strings[N] = {
    [1] = "hello",
    [2] = "how",
    [3] = "good",
    [4] = "a very very long string for testing strcpy correctness...",
    [5] = "1234567890!@#$^&*()",
    [6] = "hfweifnnekfjlesjlfjl",
    [7] = "another string",
    [8] = "yet another one",
    [9] = "short",
    [10] = "longer string for testing purposes",
    [11] = "1234567890",
    [12] = "abcdefg",
    [13] = "klmnopqrs",
    [14] = "tuvwxyz",
    [15] = "testing with special characters !@#$%^&*()_+",
    [16] = "empty string",
    [17] = "single character a",
    [18] = "single character b",
    [19] = "single character c",
    [20] = "this is a longer string to test the strcpy function",
    [21] = "another example of a string",
    [22] = "more strings for testing",
    [23] = "testing with numbers 1234567890",
    [24] = "testing with punctuation !@#$%^&*()",
    [25] = "testing with spaces and tabs\t",
};

void basic_test_strcpy() {
  char dest[N][N];
  for (int i = 0; i < N; i++) {
    if (strings[i] == NULL) continue;
    strcpy(dest[i], strings[i]);
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

void test_strcpy() {
  basic_test_strcpy();
  // test_strcpy_overflow();
}