7.11 (Bubble Sort) The comparisons on each pass proceed as follows—the 0th element value is compared 
to the 1st, the 1st is compared to the 2nd, the 2nd is compared to the third, ..., the second-to-last 
element is compared to the last element. Write a program that sorts an array of 10 integers using bubble sort.

7.12 (Bubble Sort Enhancements) The bubble sort described in Exercise 7.11 is inefficient for large
arrays. Make the following simple modifications to improve the performance of the bubble sort:
a) After the first pass, the largest number is guaranteed to be in the highest-numbered element of the array; 
after the second pass, the two highest numbers are “in place,” and
so on. Instead of making nine comparisons on every pass, modify the bubble sort to
make eight comparisons on the second pass, seven on the third pass, and so on.
b) The data in the array may already be in the proper order or near-proper order, so why
make nine passes if fewer will suffice? Modify the sort to check at the end of each pass
if any swaps have been made. If none have been made, then the data must already be in
the proper order, so the program should terminate. If swaps have been made, then at
least one more pass is needed.
