#include <klibtest.h>

void (*entry)() = NULL; // mp entry

static const char *tests[256] = {
  ['m'] = "memset",
  ['s'] = "strcpy",
  ['n'] = "strncpy",
  ['c'] = "memcpy",
  ['v'] = "memmove",
  ['a'] = "strcat",
  ['p'] = "strcmp",
  ['t'] = "strncmp",
  ['e'] = "memcmp",
  ['g'] = "sprintf",
  ['l'] = "malloc",
};

int main(const char *args) {
  switch (args[0]) {
    case 'm': {
      extern void test_memset();
      entry = test_memset;
      test_memset(); break;
    }
    case 's': {
      extern void test_strcpy();
      entry = test_strcpy;
      test_strcpy(); break;
    }
    case 'n': {
      extern void test_strncpy();
      entry = test_strncpy;
      test_strncpy(); break;
    }
    case 'c': {
      extern void test_memcpy();
      entry = test_memcpy;
      test_memcpy(); break;
    }
    case 'v': {
      extern void test_memmove();
      entry = test_memmove;
      test_memmove(); break;
    }
    case 'a': {
      extern void test_strcat();
      entry = test_strcat;
      test_strcat(); break;
    }
    case 'p': {
      extern void test_strcmp();
      entry = test_strcmp;
      test_strcmp(); break;
    }
    case 't': {
      extern void test_strncmp();
      entry = test_strncmp;
      test_strncmp(); break;
    }
    case 'e': {
      extern void test_memcmp();
      entry = test_memcmp;
      test_memcmp(); break;
    }
    case 'g': {
      extern void test_sprintf();
      entry = test_sprintf;
      test_sprintf(); break;
    }
    case 'l': {
      extern void test_malloc();
      entry = test_malloc;
      test_malloc(); break;
    }
    default:
      printf("Usage: make run mainargs=*\n");
      for (int ch = 0; ch < 256; ch++) {
        if (tests[ch]) {
          printf("  %c: %s\n", ch, tests[ch]);
        }
      }
  }
  return 0;
}