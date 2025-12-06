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

unsigned long a (char* str) {
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

  int line = lineCount - 2;
  int cha = 0;
  int chaStart = 0;
  unsigned long lAcc = 0;
  unsigned long sAcc = 0;
  int longest = 0;
  char op = 0;
  while (true) {
    int index = line * chars + cha;
    c = str[index];
    if (c == '+' || c == '*') {
      op = c;
      line--;
      continue;
    }
    if (sAcc == 0 && c == ' ') {
      cha++;
      continue;
    }
    if (c == ' ' || c == '\n') {
      if (op == '+') {
        lAcc += sAcc;
      } else {
        unsigned long before = lAcc;
        if (lAcc == 0) {
          lAcc += sAcc;
        } else {
          lAcc *= sAcc;
        }
      }
      sAcc = 0;
      if (line == 0) {
        acc += lAcc;
        if (c == '\n') {
          break;
        }
        lAcc = 0;
        line = lineCount - 2;
        cha = chaStart + longest + 1;
        longest =0;
        chaStart = cha;
        continue;
      }
      cha = chaStart;
      line--;
      continue;
    }
    if (isdigit(c)) {
      sAcc = sAcc * 10 + (c - '0');
      cha++;
      if (cha - chaStart > longest) {
        longest = cha - chaStart;
      } 
      continue;
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

  int line = 0;
  int cha = 0;
  int chaStart = 0;
  unsigned long lAcc = 0;
  unsigned long sAcc = 0;
  int longest = 0;
  char op = 0;
  while (true) {
    int index = line * chars + cha;
    c = str[index];
    if (c == '+' || c == '*') {
      op = c;
      line = 0;
      cha++;
      acc += lAcc;
      lAcc = sAcc;
      sAcc = 0;
      continue;
    }
    if (c == '\n') {
      acc += lAcc;
      break;
    }
    if (c == ' ') {
      if (line == lineCount - 2) {
        if (sAcc == 0) {
          line = 0;
          cha++;
          continue;
        }
        if (op == '+') {
          lAcc += sAcc;
        } else {
          lAcc *= sAcc;
        }
        line = 0;
        sAcc = 0;
        cha++;
      } else {

      line++;
      continue;
      }
    }
    if (isdigit(c)) {
      sAcc = sAcc * 10 + (c - '0');
      line++;
      continue;
    } 
    }
  return acc;
}
int main(int argc, char *argv[]) {
  char* str = readFile(argv[1]);
  unsigned long res = b(str);
  printf("%lu\n", res);
  return 0;
}
