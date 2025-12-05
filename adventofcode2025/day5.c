#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
    long left;
    long right;
} range;

char* readFile(char* filename){ 
    char *buffer;
    long length;
    FILE *f = fopen (filename, "rb");

    if (f) {
    fseek (f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer) {
        fread (buffer, 1, length, f);
    }
    fclose (f);
    }
    return buffer;
}

int a (char* str) {
  int len = strlen(str);
  int acc = 0;
  int lineCount = 0;
  char before;
  for (int i = 0; i < len; i++) {
    char c = str[i];
    if (c == before && c == '\n') break;
    if (c == '\n') lineCount++;
    before = c;
  }
  range** ranges = malloc(lineCount * sizeof(range*));
  for (int i = 0; i < lineCount; i++) {
    ranges[i] = malloc(sizeof(range));
  }
  unsigned long counter = 0;
  int line = 0;
  int charCount = 0;

  while (line < lineCount) {
    char c = str[charCount];
    if (c == '-') {
        ranges[line]->left = counter;
        counter = 0;
    } else if (c == '\n') {
        ranges[line]->right = counter;
        counter = 0;
        line++;
    } else if (isdigit(c)) {
        counter = counter * 10 + (c - '0'); 
    }
    charCount++;
  } 
  bool activated = false;
  before = 0;
  long fAcc = 0;
  for (int i = 0; i < len; i++) {
    char c = str[i];
    if (!activated) {
        if (c == before) {
            activated = true;
            continue;
        }
        before = c;
        continue;
    }
    if (c == '\n') {
        for (int j = 0; j < lineCount ; j++) {
            range* r = ranges[j];
            if ((fAcc - r->left) >= 0 && (fAcc - r->right) <= 0) {
                acc++;                
                break;
            }
        }
        fAcc = 0;

        continue;
    }
    if (isdigit(c)) {
        fAcc = fAcc * 10 + (c - '0');
    }
  }
  for (int i = 0; i < lineCount; i++) {
    free(ranges[i]);
  }
  free(ranges);
  return acc;
}
int compLeft(const void *a, const void *b) {
  range *c = (range *)a;
  range *d = (range *)b;
  long t  = c->left - d->left;
  return t > 0 ? 1 : t == 0 ? 0 : -1;
}

unsigned long b (char* str) {
  int len = strlen(str);
  unsigned long acc = 0;
  int lineCount = 0;
  char before;
  for (int i = 0; i < len; i++) {
    char c = str[i];
    if (c == before && c == '\n') break;
    if (c == '\n') lineCount++;
    before = c;
  }
  range* ranges = malloc(lineCount * sizeof(range));

  unsigned long counter = 0;
  int line = 0;
  int charCount = 0;

  while (line < lineCount) {
    char c = str[charCount];
    if (c == '-') {
        ranges[line].left = counter;
        counter = 0;
    } else if (c == '\n') {
        ranges[line].right = counter;
        counter = 0;
        line++;
    } else if (isdigit(c)) {
        counter = counter * 10 + (c - '0'); 
    }
    charCount++;
  } 
  range* leftSorted = malloc(lineCount * sizeof(range));

  memcpy(leftSorted, ranges, lineCount * sizeof(range));

  qsort(leftSorted, lineCount, sizeof(range), compLeft);
  
  for (int i = 0; i < lineCount; i++) {
    range l = leftSorted[i];
    long left = l.left;
    long right = l.right;
    for (int h = 0; h < i; h++) {
        range t = leftSorted[h];
        if (left >= t.left && left <= t.right) {
            left = t.right + 1;
        }
        if (right >= t.left && right <= t.right) {
            right = t.left - 1;
        }
    }
    leftSorted[i].left = left;
    leftSorted[i].right = right;
    printf("%lu, %lu\n", left, right);
    if (left > right) {
        continue;
    }
    acc += (right - left) + 1;
  }

  free(ranges);
  return acc;
}
int main (int argc, char** argv) {
  char* str = readFile(argv[1]);
  unsigned long acc = b(str);
  free(str);
  printf("%lu\n", acc);
  return 0;
}