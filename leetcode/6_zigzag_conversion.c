#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
  char val;
  struct node* next;
} node;

void pushChar (node** parent, char c) {
  if (*parent == NULL) {
    *parent = malloc(sizeof(node));
    (*parent)->val = c;
    (*parent)->next = NULL;
  } else {
    node* current = *parent;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next       = malloc(sizeof(node));
    current->next->val  = c;
    current->next->next = NULL;
  }
}

char* convert(char* s, int numRows) {
  if (numRows == 1) {
    return s;
  }
  node** nodes = malloc(numRows * sizeof(node*));

  for (int i = 0; i < numRows; i++) {
    nodes[i] = NULL;
  }

  unsigned int len  = strlen(s); 
  
  int layer = 0;
  char up = 1;
  for (int i = 0; i < len; i++) {
    pushChar(&nodes[layer], s[i]);
    if (up) {
      layer++;
    } else {
      layer--;
    }
    if (layer == numRows - 1 || layer == 0) {
      up = !up;
    }
  }
  
  int c = 0;
  for (int i = 0; i < numRows; i++) {
    node* parent = nodes[i];
    while (parent != NULL) {
      char val = parent->val;
      s[c] = val;
      c++;
      parent = parent->next;
    }
  }

  free(nodes);
  return s;
}

int main(int argc, char *argv[]) {
  char* result = malloc(strlen(argv[1]));
  result = convert(argv[1], atoi(argv[2]));

  printf("%s\n", result);
  return 0;
}
