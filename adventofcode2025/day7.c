#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

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
  for (int i = 0; i < len; i++) {
    char c = str[i];
    if (c == '\n') lineCount++;
  }
  int chars = 0;
  char c;
  while (c != '\n') {
    c = str[chars];
    chars++;
  }
  for (int i = 1; i < lineCount; i++) {
    for (int j = 0; j < chars; j++) {
      int index = i*chars + j;
      int aboveIndex = (i-1)*chars + j;
      
      int c = str[index];
      int above = str[aboveIndex];

      if (above == 'S') {
        str[index] = '|';
        continue;
      }

      if (above == '|') {

        if (c == '^') {
          acc++;
          str[index - 1] = '|';
          str[index + 1] = '|';
          continue;
        }
        str[index] = '|';
        continue;
      }
    }
  } 
  return acc;
}
unsigned long b (char* str) {
  int len = strlen(str);
  unsigned long acc = 0;
  int lineCount = 0;
  for (int i = 0; i < len; i++) {
    char c = str[i];
    if (c == '\n') lineCount++;
  }
  int chars = 0;
  char c;
  while (c != '\n') {
    c = str[chars];
    chars++;
  }
  unsigned long* numbers = calloc(chars * lineCount, sizeof(unsigned long));
  for (int i = 1; i < lineCount; i++) {
    for (int j = 0; j < chars; j++) {
      int index = i*chars + j;
      int aboveIndex = (i-1)*chars + j;
      
      int c = str[index];
      unsigned long above = numbers[aboveIndex];

      if (str[aboveIndex] == 'S') {
        numbers[index] = 1;
        continue;
      }
      if (above != 0) {
        if (c == '^') {
          numbers[index - 1] += above; 
          numbers[index + 1] += above;
          continue;
        }
        numbers[index] += above;
        continue;
      }
    }
  }
  for (int i = 0; i < chars; i++) {
    int index = (lineCount - 2) * chars + i;
    acc+=numbers[index];
  }
  return acc;
}
int main(int argc, char *argv[]) {
  char* str = readFile(argv[1]);
  unsigned long res  = b(str);
  printf("%lu\n", res);
}

