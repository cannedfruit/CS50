/* This program generates 10 random numbers and then sorts them */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
int ctr, inner, outer, didSwap, temp;
int nums[5] = {3, 6, 5, 7, 10};

// Now list the array as it currently is before sorting
puts("\nHere is the list before the sort:");
for (ctr = 0; ctr < 5; ctr++)
{
printf("%d\n", nums[ctr]);
}
// Sort the array
for (outer = 0; outer < 4; outer++)
{
didSwap = 0; //Becomes 1 (true) if list is not yet ordered
for (inner = outer; inner < 5; inner++)
{
if (nums[inner] < nums[outer])
{
temp = nums[inner];
nums[inner] = nums[outer];
nums[outer] = temp;
didSwap = 1;
}
}
if (didSwap == 0)
{
break;
}
}
// Now list the array as it currently is after sorting
puts("\nHere is the list after the sort:");
for (ctr = 0; ctr < 5; ctr++)
{
printf("%d\n", nums[ctr]);
}
return(0);
}
