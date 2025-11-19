#include <stdlib.h>
struct tTuple {
  int val;
  int ind;
};

int comp(const void *a, const void *b) {
  struct tTuple *c = (struct tTuple *)a;
  struct tTuple *d = (struct tTuple *)b;
  return c->val - d->val;
}

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
  int *res = malloc(2 * sizeof(int));
  struct tTuple *sortedTuples = malloc(numsSize * sizeof(struct tTuple));

  for (int i = 0; i < numsSize; i++) {
    sortedTuples[i].val = nums[i];
    sortedTuples[i].ind = i;
  }
  qsort(sortedTuples, numsSize, sizeof(struct tTuple), comp);

  int left = 0;
  int right = numsSize - 1;
  int sum;
  while (1) {
    sum = sortedTuples[left].val + sortedTuples[right].val;

    if (sum == target) {
      *returnSize = 2;
      res[0] = sortedTuples[left].ind;
      res[1] = sortedTuples[right].ind;
      break;
    } else if (sum > target) {
      right--;
    } else {
      left++;
    }
  }
  free(sortedTuples);
  return res;
}
