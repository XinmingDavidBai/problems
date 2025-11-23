#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int reverse(int x) {
  // integer limits
  if (x >= 2147483647 || x <= -2147483648) return 0;
  if (x > 0) {
    int size = (int)((ceil(log10(x + 1))+1)*sizeof(char));
    char* str = malloc(size);

    sprintf(str, "%d", x);
    for (int i = 0; i < (size - 1) / 2; i++) {
      int last = size - i - 2;
      char temp = str[last];
      str[last] = str[i];
      str[i] = temp;
    }

    int new = atoi(str);
    if (new < 0 || str[0] > str[size - 2] && new < x) {
      return 0;
    } else {
      return new;
    }
  } else {
    int size = (int)((ceil(log10(abs(x) + 1))+1)*sizeof(char));
    char* str = malloc(size + 1);
    sprintf(str, "%d", x);
    
    for (int i = 0; i < (size - 1) / 2; i++) {
      int  last = size - i - 1;
      char temp = str[last];
      str[last] = str[i + 1];
      str[i + 1] = temp;
    }

    int new = atoi(str);
    if (new > 0 || str[1] > str[size - 1] && new > x) {
      return 0;
    } else {
      return new;
    }
    return 0;
  }
}

int main(int argc, char *argv[])
{
  int v = reverse(atoi(argv[1]));
  printf("%d\n", v);
  return 0;
}
