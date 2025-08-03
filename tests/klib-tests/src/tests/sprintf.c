#include <klibtest.h>
#include <stdint.h>
#include <stdio.h>
#include <limits.h>

#define N 100

extern const char *strings[N];
int data_num[8] = {0, INT_MAX / 17, INT_MAX, INT_MIN, INT_MIN + 1,
              UINT_MAX / 17, INT_MAX / 17, UINT_MAX};
const char *format_strings[8] = {
    "hello 0",
    "how 126322567",
    "good 2147483647",
    "a very very long string for testing strcpy correctness... -2147483648",
    "1234567890!@#$^&*() -2147483647",
    "hfweifnnekfjlesjlfjl 252645135",
    "another string 126322567",
    "yet another one -1"
};

void generate_format() {
    FILE *fp = fopen("format.txt", "w");
    if (!fp) {
        printf("Failed to open format.txt\n");
        return;
    }
    for (int i = 0; i < 8; i++) {
        fprintf(fp, "%s %d\n", strings[i + 1], data_num[i]);
    }
    fclose(fp);
}

void basic_test_sprintf() {
    char buffer[256];
    for (int i = 0; i < 8; i++) {
        sprintf(buffer, "%s %d", strings[i + 1], data_num[i]);
        const char *expected = format_strings[i];
        check(strcmp(buffer, expected) == 0);
    }
}

void test_sprintf() {
    // generate_format();
    basic_test_sprintf();
}
