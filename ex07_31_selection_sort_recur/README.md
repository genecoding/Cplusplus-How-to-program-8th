7.31 (Selection Sort) A selection sort searches an array looking for the smallest element. Then,
the smallest element is swapped with the first element of the array. The process is repeated for the
subarray beginning with the second element of the array. Each pass of the array results in one element 
being placed in its proper location. This sort performs comparably to the insertion sort—for
an array of n elements, n – 1 passes must be made, and for each subarray, n – 1 comparisons must
be made to find the smallest value. When the subarray being processed contains one element, the
array is sorted. Write recursive function selectionSort to perform this algorithm.
