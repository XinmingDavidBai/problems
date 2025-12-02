#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

char* readFile(char* filename) {
    char *buffer;
    long length;
    FILE *f = fopen (filename, "rb");

    if (f)
    {
    fseek (f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer)
    {
        fread (buffer, 1, length, f);
    }
    fclose (f);
    }
    return buffer;
}

unsigned long long getValForRange(unsigned long long a, unsigned long long b) {
  unsigned long long acc = 0;
  for (unsigned long long i = a; i <= b; i++) {
    int size = (int)((ceil(log10(i))+1)*sizeof(char));
    if ((size - 1) % 2 != 0) {
      continue;
    }
    char* str = malloc(size);
    sprintf(str, "%llu", i);
    int mid = size / 2;
    bool skip = 0;
    for (int j = 0; j < mid; j++) {
      char f = str[j];
      char s = str[j + mid];
      if (f != s) {
        skip = 1;
      }
    }
    free(str);
    if (skip) {
      continue;
    }
    acc += i;
  }
  return acc;
}

unsigned long long getValForRangeB(unsigned long long a, unsigned long long b) {
  unsigned long long acc = 0;
  for (unsigned long long i = a; i <= b; i++) {
    int size = (int)((ceil(log10(i))+1)*sizeof(char));
    if (size == 2) {
      continue;
    }
    char* str = malloc(size);
    sprintf(str, "%llu", i);
    int slice = size / 2;
    while (slice > 0) {
      if ((size - 1) % slice != 0) {
        slice--;
        continue;
      }
      int count = (size - 1) / slice;
      bool skip = 0;
      for (int j = 0; j < slice; j++ ) {
        char c = str[j];
        for (int h = 1; h < count; h++) {
          int index = h * slice + j;
          char x = str[index];
          if (x != c) {
            skip = 1;
            break;
          }
        }
        if (skip) {
          break;
        }
      }
      if (!skip) {
        acc += i;
        break;
      }
      slice--;
    }
    free(str);
  }
  return acc;
}
int main(int argc, char** argv) {
  char* str = readFile(argv[1]);
  int len = strlen(str);
  unsigned long long first = 0;
  unsigned long long second = 0;
  bool isFirst = 1;
  unsigned long long acc = 0;
  for (int i = 0; i < len; i++) {
    char c = str[i];
    if (c == ',' || i == len - 1) {
      unsigned long long t = getValForRangeB(first, second);
      acc += t;
      first = 0;
      second = 0;
      isFirst = 1;
      continue;
    }
    if (c == '-') {
      isFirst = 0;
      continue;
    }
    if (isdigit(c)) {
      if (isFirst) {
        first = first * 10 + (c - '0');
      } else {
        second = second * 10 + (c - '0');
      }
    } 
  }
  printf("%llu\n", acc);
  return 0;
}
