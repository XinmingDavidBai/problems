
double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size) {
    if (nums1Size == 0) {
        if (nums2Size % 2 == 0) {
            int nums2MedianPos = nums2Size / 2;

            int nums2lower = nums2[nums2MedianPos - 1];
            int nums2upper = nums2[nums2MedianPos];

            return (double) (nums2lower + nums2upper) / 2;
        } else {
            return (double) nums2[(int)(nums2Size / 2)];
        }    
    }
    if (nums2Size == 0) {
        if (nums1Size % 2 == 0) {
            int nums1MedianPos = nums1Size / 2;

            int nums1lower = nums1[nums1MedianPos - 1];
            int nums1upper = nums1[nums1MedianPos];
            return (double) (nums1lower + nums1upper) / 2;
        } else {
            return (double) nums1[(int)(nums1Size / 2)];
        }   
    }
    int totalSize = nums1Size + nums2Size;

    if (nums1[nums1Size - 1] <= nums2[0]) {
        if (totalSize % 2 == 0) {

            if (nums1Size == nums2Size) {
                return  ((double)nums1[nums1Size - 1] + nums2[0]) / 2;
            }
            
            if (nums1Size > nums2Size) {
                return ((double) (nums1[totalSize / 2 - 1] + nums1[totalSize / 2 ]) / 2);
            }
            return  ( (double) (nums2[totalSize / 2 - 1 - nums1Size] + nums2[totalSize / 2 - nums1Size]) / 2);

        }

        if (nums1Size > nums2Size) {
            return (double) nums1[totalSize / 2];
        }

        return (double) nums2[totalSize / 2 - nums1Size];

    }      

    if (nums2[nums2Size - 1] <= nums1[0]) {
        if (totalSize % 2 == 0) {

            if (nums1Size == nums2Size) {
                return  ((double)nums2[nums2Size - 1] + nums1[0]) / 2;
            }
            
            if (nums2Size > nums1Size) {
                return ((double) (nums2[totalSize / 2 - 1] + nums2[totalSize / 2 ]) / 2);
            }

            return ((double) (nums1[totalSize / 2 - 1 - nums2Size] + nums1[totalSize / 2 - nums2Size]) / 2);

        }

        if (nums2Size > nums1Size) {
            return (double) nums2[totalSize / 2];
        }

        return (double) nums1[totalSize / 2 - nums2Size];
    }
    int remaining;
    if (totalSize % 2 == 0) {
        remaining = totalSize / 2;
    } else {
        remaining = totalSize / 2 + 1;
    }

    if (totalSize % 2 == 0) {
        char second = 0;
        int saved;

        int p1;
        int p2;
        while (remaining > -1) {
            remaining--;
            if (p1 >= nums1Size) {
                if (second) {
                    return (double) (saved + nums2[p2]) / 2;
                }
                if (!remaining) {
                    second = 1;
                    saved = nums2[p2];
                }
                p2++;
            }
            else if (p2 >= nums2Size) {
                if (second) {
                    return (double) (saved + nums1[p1]) / 2;
                }
                if (!remaining) {
                    second = 1;
                    saved = nums1[p1];
                }
                p1++;
            }
            else if (nums1[p1] < nums2[p2]) {
                if (second) {
                    return (double) (saved + nums1[p1]) / 2;
                }
                if (!remaining) {
                    second = 1;
                    saved = nums1[p1];
                } 
                    p1++;
                
            }
            else if (second) {
                return (double) (saved + nums2[p2]) / 2;
            }
            else if (!remaining) {
                second = 1;
                saved = nums2[p2];
                p2++;

            } else {
            p2++;

            }
        }
    } else {
        int nums1Median = nums1[(nums1Size - 1) / 2];
        int nums2Median = nums2[(nums2Size - 1) / 2];

        int p1 = 0;
        int p2 = 0;

        if (nums1Median < nums2Median) {
            p1 = (nums1Size -1 ) / 2 + 1;
            remaining -= (nums1Size - 1 )/ 2 + 1;
        } else {
            p2 = (nums2Size - 1) / 2 + 1;
            remaining -= (nums2Size - 1)/ 2 + 1;
        }

        while (remaining) {
            remaining--;
            if (p1 >= nums1Size) {
                if (!remaining) {
                    return nums2[p2];
                }
                p2++;
            }
            else if (p2 >= nums2Size) {
                if (!remaining) {
                    return nums1[p1];
                }
                p1++;
            }
            else if (nums1[p1] < nums2[p2]) {
                if (!remaining) {
                    return nums1[p1];
                } 
                    p1++;
                
            }
            else if (!remaining) {
                return nums2[p2];
            } else {
            p2++;

            }
        }
    }
  return 0;
}

