#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
int a (char* str) {
    int len = strlen(str);
    int acc = 50;
    int num_acc = 0;
    char left = 0;
    int count = 0;
    for (int i = 0; i < len; i++) {
        char c = str[i];
        if (c == '\n') {
            if (left) {
                int num = num_acc % 100;
                acc -= num;
                if (acc < 0) {
                    acc = 100 + acc;
                }
            } else {
                acc = (acc + num_acc) % 100;  
            }
            num_acc = 0;
            left = 0;
            if (acc == 0) {
                count++;
            }
            continue;
        }
        if (c == 'L') {
            left = 1;
            continue;
        }
        if (isdigit(c)) {
            num_acc = num_acc * 10 + (c - '0');
            continue;
        }
    }
    return count;
}
int b(char* str) {
    int len = strlen(str);
    int acc = 50;
    int num_acc = 0;
    char left = 0;
    int count = 0;
    for (int i = 0; i < len + 1; i++) {
        char c;
        if (i == len) {
            c = '\n';
        } else {
            c = str[i];

        }
        if (c == '\n') {

            if (left) {
                int c = num_acc / 100;
                count += c;
                int num = num_acc % 100;
                char ign = acc == 0;
                acc -= num;
                if (acc < 0) {
                    acc = 100 + acc;
                    if (!ign) {

                        count++;
                    }
                }
            } else {
                int c =  num_acc / 100;
                count += c;
                int num = num_acc % 100;
                char ign = acc == 0;
                acc += num;
                if (acc > 100) {
                    if (!ign) {
                        count++;
                    }

                }
                acc = acc % 100;
            }
            num_acc = 0;
            left = 0;
            if (acc == 0) {
                count++;
            }
            continue;
        }
        if (c == 'L') {
            left = 1;
            continue;
        }
        if (isdigit(c)) {
            num_acc = num_acc * 10 + (c - '0');
            continue;
        }
    }
    return count;    
}
int main (int argc, char** argv)  {
    char* filename = argv[1];
    char* str = readFile(filename);
    int count = b(str);
    printf("%d\n", count);
    return 0;
}