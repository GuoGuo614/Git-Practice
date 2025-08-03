#include <klibtest.h>
#include <stdint.h>

#define N 100

extern const char *strings[N];

void test_strcmp() {
    for (int i = 0; i < N - 1; i++) {
        if (strings[i] == NULL || strings[i + 1] == NULL) continue;
        check(strcmp(strings[i], strings[i]) == 0);
        check(strcmp(strings[i], strings[i + 1]) != 0);
        check(strcmp(strings[i + 1], strings[i]) != 0);
        check(strcmp(strings[i], "") != 0);
    }
}