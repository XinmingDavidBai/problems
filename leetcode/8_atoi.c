#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

int myAtoi(char* s) {
  int len = strlen(s);

  int digits    = 0;
  char started  = 0;
  char negative = 0;
  int wspace    = 0;
  for (int i = 0; i < len; i++) {
    char c = s[i];
    if (!started) {
      if (c == ' ') {
        wspace++;
        continue;
      }
      if (c == '-') {
        negative = 1;
        started = 1;
        wspace++;
        continue;
      }
      if (c == '+') {
        started = 1;
        wspace++;
        continue;
      }
      if (isdigit(c)) {
        started = 1;
        digits++;
        continue;
      } 
      break;
    }
    if (started) {
      if (isdigit(c)) {
        digits++;
        continue;
      }
      break;
    }
    break;
  }
  long res = 0;
  for (int i = digits - 1; i > -1; i--) {
    int value  = s[wspace + (digits - 1 - i)] - '0';
    int factor = value * pow(10, i);

    if (factor < 0) {
      if (negative) {
        return pow(-2, 31);
      } else {
        return pow(2, 31) - 1;
      }
    }
    if (negative) {
      res -= factor;
      if (res < pow(-2, 31)) {
        return pow(-2, 31);
      }
    } else {
      res += factor;
      if (res > pow(2,31) - 1) {
        return pow(2, 31) - 1;
      }
    }
  }
  return res;
}

int main(int argc, char *argv[]) {
  int i = myAtoi(argv[1]);
  printf("%d\n", i);
  return 0;
}
