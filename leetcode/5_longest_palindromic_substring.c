#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longestPalindrome(char *s) {
  int len = strlen(s);

  if (len < 2) {
    return s;
  }
  
  int max       = 1;
  int maxStart  = 0;
  int maxEnd    = 0;

  for (int i = 1; i < len - 1; i++) {
    int   iter  = 1;
    int   start = i - 1;
    int   end   = i + 1;
    char  run  = start >= 0 && end < len;
    
    while (run) {
      if (s[start] == s[end]) {
        if (iter * 2 + 1 > max) {
          max       = iter * 2 + 1;
          maxStart  = start;
          maxEnd    = end;
        }
        start   -= 1;
        end     += 1;
        iter    += 1;
        run     = start >= 0 && end < len;
      } else {
        run = 0;
      }
    }
  }

  for (int i = 0; i < len - 1; i++) {
    if (s[i] == s[i + 1]) {
      int iter  = 1;
      int start = i - 1;
      int end   = i + 2;
      char run  = start >= 0 && end < len;
      if (max < 2) {
        max       = 2;
        maxStart  = i;
        maxEnd    = i + 1;
      }
      while (run) {
        if (s[start] == s[end]) {
          if (iter * 2 + 2 > max) {
            max       = iter * 2 + 2;
            maxStart  = start;
            maxEnd    = end;
          }
          start   -= 1;
          end     += 1;
          iter    += 1;
          run     = start >= 0 && end < len;
        } else {
          run = 0;
        }
      }
    }
  }

  char *str = malloc(max + 1);
  str[max]  = '\0';
  
  for (int i = maxStart; i < maxEnd + 1; i++) {
    str[i - maxStart] = s[i];
  }
  return str;
}

int main(int argc, char *argv[]) {
  char *res = longestPalindrome(argv[1]);
  printf("%s\n", res);
  return 0;
}
