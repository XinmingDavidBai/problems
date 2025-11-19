#include <stdio.h>
#include <stdlib.h>

int lengthOfLongestSubstring(char *s) {
  int *seenAt = calloc(256, sizeof(int));
  int max = 0;
  int start = 1;

  for (int i = 0; s[i]; i++) {
    char c = s[i];

    if (seenAt[c] >= start) {
      start = seenAt[c] + 1;
    }

    seenAt[c] = i + 1;

    if (i - (start - 1) >= max) {
      max = i - (start - 2);
    }
  }
  free(seenAt);
  return max;
}

int main(int argc, char *argv[]) {
  int num = lengthOfLongestSubstring(argv[1]);
  printf("%d\n", num);

  return 0;
}
