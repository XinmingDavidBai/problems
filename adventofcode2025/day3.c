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
	int first  = 0;
	int firstIndx = 0;
	int index = 0;
	int second = 0;
	bool firstFound = 0;
	for (int i = 0; i < len; i++) {
		char c = str[i];
		char nextC = 0;
		if (i != len - 1) {
			nextC = str[i+1];
		}
		if (nextC == '\n' && c != '\n') {
			int largest = 0;
			int ind = firstIndx + 1;
			char sc = str[ind];
			while (ind < len) {
				sc = str[ind];
	  			if (sc == '\n') {
					break;
	printf("%lu\n", acc);
				}
				int v = sc - '0';
	  			if (v > largest) {
					largest = v;
				}
				ind++;
			}
			second = largest;
			acc += (first * 10) + second;
			first = 0;
			firstIndx = 0;
			index = 0;
			second = 0;
			firstFound = 0;
			continue;
		}

		if (isdigit(c)) {
			int v = c - '0';
			if (v > first) {
				first = v;
				firstIndx = i;
			}
		}
	
	}
	return acc;
}
unsigned long bHelper (char* str) {
	int len = strlen(str);
	unsigned long acc = 0;
	int remaining = 12;
	int index = 0;
	int largest = 0;
	int largestInd = 0;
	while (remaining > 0) {
		char c = str[index];
		char remainC = str[index + remaining];
		
		int v = c - '0';
		if (v > largest) {
			largest = v;
			largestInd = index;
		}

		if (remainC == '\n') {
			acc = acc * 10 + largest;
			index = largestInd + 1;
			remaining--;
			largest = 0;
			largestInd = 0;
		} else {
			index++;
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
	char** a = malloc(lineCount * sizeof(char*));
	for (int i = 0; i < lineCount; i++) {
		a[i] =  malloc(chars);
		char* s = a[i];
		for (int j = 0; j < chars; j++) {
			int index = chars*i+ j;
			char c = str[chars* i +j];
			s[j] = str[chars * i + j];
		}
	}
	
	for (int i = 0; i < lineCount; i++) {
		acc += 	bHelper(a[i]);
	}

	return acc;
}

int main(int argc, char** argv) {
	char* str =  readFile(argv[1]);
	unsigned long acc = b(str);
	free(str);
	printf("%lu\n", acc);

}
