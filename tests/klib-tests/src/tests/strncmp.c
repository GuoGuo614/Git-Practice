#include <klibtest.h>
#include <stdint.h>

#define N 100

extern const char *strings[N];

void basic_test_strncmp() {
    for (int i = 0; i < N - 1; i++) {
        if (strings[i] == NULL || strings[i + 1] == NULL) continue;
        check(strncmp(strings[i], strings[i], N) == 0);
        check(strncmp(strings[i], strings[i + 1], N) != 0);
        check(strncmp(strings[i + 1], strings[i], N) != 0);
        check(strncmp(strings[i], "", N) != 0);
    }
}

void test_strncmp_overflow() {
    char *a = "hellooa";
    char *b = "helloob";
    check(strncmp(a, b, 7) < 0);
    check(strncmp(b, a, 7) > 0);
    check(strncmp(a, b, 6) == 0);
    check(strncmp(b, a, 6) == 0);
}

void test_strncmp() {
    basic_test_strncmp();
    test_strncmp_overflow();
}