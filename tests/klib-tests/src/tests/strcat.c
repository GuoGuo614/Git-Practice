#include <klibtest.h>
#include <stdint.h>

#define N 100

extern const char *strings[N];
char dest[N][N];

void test_strcat() {
  for (int i = 0; i < N; i++) {
    if (strings[i] == NULL) continue;
    dest[i][0] = '\0'; // Initialize to empty string
    strcat(dest[i], strings[i]);
    strcat(dest[i], strings[i]);
    char *p = dest[i];
    const char *q = strings[i];
    while (1) {
      if (*p == '\0' || *q == '\0')
        break;
      check(*p == *q);
      p++;
      q++;
    }
    while (1) {
      if (*p == '\0' || *q == '\0')
        break;
      check(*p == *q);
      p++;
      q++;
    }
  }
}
