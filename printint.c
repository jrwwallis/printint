#include <inttypes.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define xstr(s) str(s)
#define str(s) #s

#define UINT32_MAX_STR (sizeof(xstr(UINT32_MAX)))

struct b_lookup_s {
  char s[UINT32_MAX_STR];
  char *last;
  size_t sz;
};

static struct b_lookup_s b0_lookup[UINT8_MAX + 1];

void init(void) {
  int i;
  for (i = 0; i <= UINT8_MAX; ++i) {
    b0_lookup[i].sz =
        snprintf(b0_lookup[i].s, sizeof(b0_lookup[i].s), "%" PRIu32, i);
    b0_lookup[i].last = b0_lookup[i].s + b0_lookup[i].sz - 1;
  }
}

char *printint(uint32_t u, char *s, size_t s_sz) {
  memset(s, 0, s_sz);
  char *cur = s + s_sz - 1;

  int i;

  uint8_t b = (uint8_t)u;
  u >>= CHAR_BIT;
  memcpy(s, b0_lookup[b].s, b0_lookup[b].sz);

  for (i = 1; u; ++i) {
    b = (uint8_t)u;
    u >>= CHAR_BIT;

    char *d;
    int j;
    for (j = b0_lookup[b].sz - 1; j > 0; --j) {
      d = &b0_lookup[b].s[j];
    }
  }

  return s;
}

int main(int argc, char **argv) {
  init();

  int i;
  char str[UINT32_MAX_STR];
  for (i = 1; i < argc; ++i) {
    uint32_t u;
    u = strtol(argv[i], NULL, 0);
    puts(printint(u, str, sizeof(str)));
  }
}
