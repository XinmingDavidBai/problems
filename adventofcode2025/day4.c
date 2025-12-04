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

int getIndex(int i, int j, int chars) {
  return i * chars + j;
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
  for (int i = 0; i < lineCount; i++) {
    for (int j = 0; j < chars; j++) {
      int nAcc = 0;
      char c = str[getIndex(i, j, chars)];
      if (c != '@') {
        continue;
      }
      if (i > 0 && j > 0) {
        c = str[getIndex(i - 1, j - 1, chars)] ;
        nAcc += c == '@' ? 1 : 0;
      }
      if (i > 0) {
        c = str[getIndex(i-1, j, chars)];
        nAcc += c == '@' ? 1 : 0;
      }
      if (i > 0 && j < chars) {
        c = str[getIndex(i-1, j+1, chars)];
        nAcc += c == '@' ? 1 : 0;
      }
      if (j < chars) {
        c = str[getIndex(i, j+1, chars)];
        nAcc += c == '@' ? 1 : 0;
      }
      if (i < lineCount && j < chars) {
        c = str[getIndex(i+1, j+1, chars)];
        nAcc += c == '@' ? 1 : 0;
      }
      if (i < lineCount) {
        c = str[getIndex(i+1, j, chars)];
        nAcc += c == '@' ? 1 : 0;
      }
      if (i < lineCount && j > 0) {
        c = str[getIndex(i+1, j-1, chars)];
        nAcc += c == '@' ? 1 : 0;
      }
      if (j > 0) {
        c = str[getIndex(i, j-1, chars)];
        nAcc += c == '@' ? 1 : 0;
      }
      if (nAcc < 4) {
        acc++;
      }
      nAcc = 0;
    }
  }
  
  
 return acc; 
}

int b (char* str) {
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
  int before = -1;
  while (before != acc) {
  before = acc;
  for (int i = 0; i < lineCount; i++) {
    for (int j = 0; j < chars; j++) {
      int nAcc = 0;
      char c = str[getIndex(i, j, chars)];
      if (c != '@') {
        continue;
      }
      if (i > 0 && j > 0) {
        c = str[getIndex(i - 1, j - 1, chars)] ;
        nAcc += c == '@' ? 1 : 0;
      }
      if (i > 0) {
        c = str[getIndex(i-1, j, chars)];
        nAcc += c == '@' ? 1 : 0;
      }
      if (i > 0 && j < chars) {
        c = str[getIndex(i-1, j+1, chars)];
        nAcc += c == '@' ? 1 : 0;
      }
      if (j < chars) {
        c = str[getIndex(i, j+1, chars)];
        nAcc += c == '@' ? 1 : 0;
      }
      if (i < lineCount && j < chars) {
        c = str[getIndex(i+1, j+1, chars)];
        nAcc += c == '@' ? 1 : 0;
      }
      if (i < lineCount) {
        c = str[getIndex(i+1, j, chars)];
        nAcc += c == '@' ? 1 : 0;
      }
      if (i < lineCount && j > 0) {
        c = str[getIndex(i+1, j-1, chars)];
        nAcc += c == '@' ? 1 : 0;
      }
      if (j > 0) {
        c = str[getIndex(i, j-1, chars)];
        nAcc += c == '@' ? 1 : 0;
      }
      if (nAcc < 4) {
        acc++;
        str[getIndex(i,j, chars)] = 'x';
      }
      nAcc = 0;
    }
  }
  }
  
  
 return acc; 
}

int main (int argc, char** argv) {
  char* str = readFile(argv[1]);
  int acc = b(str);
  free(str);
  printf("%d\n", acc);
  return 0;
}
