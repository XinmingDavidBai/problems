// !!!!!Unfinished!!!!!
#include <math.h>
double recursiveHelper(int *nums1, int *nums2, int nums1start, int nums1end,
                       int nums2start, int nums2end, int prevLower,
                       int prevUpper) {
  int lower;
  int upper;

  char lowerIs1;
  char upperIs1;

  int nums1lower;
  int nums1upper;

  int nums1Size = nums1end - nums1start;
  double nums1MedianPos = nums1start + (double)nums1Size / 2;
  if (nums1Size % 2 == 0) {
    nums1lower = nums1[(int)floor(nums1MedianPos)];
    nums1upper = nums1[(int)ceil(nums1MedianPos)];
  } else {
    int median = nums1[(int)(nums1start + nums1Size / 2)];
    nums1lower = median;
    nums1upper = median;
  }

  int nums2lower;
  int nums2upper;
  int nums2Size = nums1end - nums1start;
  double nums2MedianPos = nums2start + (double)nums2Size / 2;
  if (nums2Size % 2 == 0) {
    nums2lower = nums2[(int)floor(nums2MedianPos)];
    nums2upper = nums2[(int)ceil(nums2MedianPos)];
  } else {
    int median = nums2[(int)(nums1start + nums2Size / 2)];
    nums2lower = median;
    nums2upper = median;
  }

  if (nums1lower < nums2lower) {
    lower = nums1lower;
    lowerIs1 = 1;
  } else {
    lower = nums2lower;
    lowerIs1 = 0;
  }

  if (nums1upper > nums2upper) {
    upper = nums1upper;
    upperIs1 = 1;
  } else {
    upper = nums2upper;
    upperIs1 = 0;
  }

  lower = lower > prevLower ? lower : prevLower;
  upper = upper < prevUpper ? upper : prevUpper;

  int new1start = lowerIs1 ? nums1MedianPos : nums1start;
  int new1end = upperIs1 ? nums1MedianPos : nums1end;

  int new2start = lowerIs1 ? nums2start : nums2MedianPos;
  int new2end = upperIs1 ? nums2end : nums2MedianPos;

  if (new1start == new1end && new2start == new2end) {
    return (double)(lower + upper) / 2;
  } else {
    return recursiveHelper(nums1, nums2, new1start, new1end, new2start, new2end,
                           lower, upper);
  }
}
double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2,
                              int nums2Size) {
  int lower;
  int upper;

  char lowerIs1;
  char upperIs1;

  int nums1lower;
  int nums1upper;

  double nums1MedianPos = (double)nums1Size / 2;
  if (nums1Size % 2 == 0) {
    nums1lower = nums1[(int)floor(nums1MedianPos)];
    nums1upper = nums1[(int)ceil(nums1MedianPos)];
  } else {
    int median = nums1[(int)(nums1Size / 2)];
    nums1lower = median;
    nums1upper = median;
  }

  int nums2lower;
  int nums2upper;
  double nums2MedianPos = (double)nums2Size / 2;
  if (nums2Size % 2 == 0) {
    nums2lower = nums2[(int)floor(nums2MedianPos)];
    nums2upper = nums2[(int)ceil(nums2MedianPos)];
  } else {
    int median = nums2[(int)(nums2Size / 2)];
    nums2lower = median;
    nums2upper = median;
  }

  if (nums1lower < nums2lower) {
    lower = nums1lower;
    lowerIs1 = 1;
  } else {
    lower = nums2lower;
    lowerIs1 = 0;
  }

  if (nums1upper > nums2upper) {
    upper = nums1upper;
    upperIs1 = 1;
  } else {
    upper = nums2upper;
    upperIs1 = 0;
  }

  int new1start = lowerIs1 ? nums1MedianPos : 0;
  int new1end = upperIs1 ? nums1MedianPos : nums1Size - 1;

  int new2start = lowerIs1 ? 0 : nums2MedianPos;
  int new2end = upperIs1 ? nums2Size - 1 : nums2MedianPos;

  if (new1start == new1end && new2start == new2end) {
    return (double)(lower + upper) / 2;
  } else {
    return recursiveHelper(nums1, nums2, new1start, new1end, new2start, new2end,
                           lower, upper);
  }
}
