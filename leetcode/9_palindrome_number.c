#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// pretty bad solution
// better is to build a new number from reverse
// and check if x == new
bool isPalindrome(int x) {
  if (x < 0) {
    return false;
  }

  if (x % 10 == 0) {
    return false;
  }
  // log10(0) is undefined
  if (x ==  0) {
    return true;
  }
  int len = log10(x)+1;
  for (int i = 0; i < len / 2; i++) {
    int firstSeq = x % (int) pow(10, len - i);
    int powT = pow(10, len - i - 1);
    int left  = firstSeq / powT;

    int lastSeq = x % (int) pow(10, i + 1);
    int right = lastSeq / pow(10, i);
    
    if (left != right) {
      return false;
    }
  }

  return true;
}
int main(int argc, char *argv[]) {
  bool x = isPalindrome(atoi(argv[1]));
  printf("%b\n",x );
  return 0;
}
