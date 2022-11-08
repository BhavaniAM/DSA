%%writefile Radix_Sort.c
#include<stdio.h>
#include <stdlib.h>

// input format :- ./a.out input.txt 4
// 4 is the number of digits. Give the maximum number of digits for a number

// declare the functions used in the code
void print_array(int a[], int count);
void radix_sort(int a[], int d, int n);
void countingSort(int a[], int pos, int n);

// file pointers to read and write files
FILE *fp_read,*fp_write;

//declare or initialise global variables
int x;

int main(int argc, char* argv[])
{
  int n = 0, num_dig, ind = 0, ele;
  
  // read the file
  fp_read = fopen(argv[1], "r");

  // take the second argument and convert it to an integer
  num_dig = (int)*argv[2];
  num_dig = num_dig - '0';

  // throw error if the file is not found
  if(fp_read == NULL)
	{
		printf("Error: Could not find the file");
		exit(0);
	}

  // iterate over the file to count the number of lines
  // Done so that a random size does not have to be given to the array which will waste memory space
  while(fscanf(fp_read, "%d", &x) != EOF)
  {
    n = n + 1;
  }

  // go to the first line of the file 
  rewind(fp_read);

  // initialise the array for the required size
  int *a;
  a = malloc(sizeof(int)*n);

  // populate the array elements
  while(fscanf(fp_read, "%d", &ele) != EOF)
  {
    a[ind] = ele;
    ind++;
  }
  fclose(fp_read); 

  // call the main radix_sort function
  radix_sort(a, num_dig, n);

  // print the sorted array
  print_array(a, n);  
  
  return 0;
}

// print the final array to the output file
void print_array(int a[], int n)
{
  fp_write = fopen("radix.txt", "w");
  for(int ent = 0; ent < n; ent++)
    fprintf(fp_write, "%d\n", a[ent]);
  fclose(fp_write);
}

// call the counting sort algorithm that is used to sort all the digits present in a specific position (units, tens, hundreds etc)
void radix_sort(int a[], int num_dig, int n)
{
  for(int i = 0; i < num_dig; i++)
    countingSort(a, i, n);
}

// the main algorithm
void countingSort(int a[], int pos, int n)
{
  int i, dig;
  // declare the digit count, helper or auxillary array and the digit separation arrays
  int dig_sep[n], dig_count[10], helper_arr[n];

  // extract the digits at the specific position
  // divide by 10 pos times to reach the position and modulo by 10 to get the digit
  for(i = 0; i < n; i++)
  {
    int k = pos;
    dig = a[i];
    while(k--)
    {
      dig = dig / 10;
    }
    dig_sep[i] = dig % 10;
  }

  // initialise the digit count array to 0
  for(i = 0; i < 10; i++)
    dig_count[i] = 0;

  // increment the values in the digit count array to store the number of occurences of each digit 
  for(i = 0; i < n; i++)
    dig_count[dig_sep[i]]++;

  // take the cumulative sum
  for(i = 1; i < 10; i++)
    dig_count[i] = dig_count[i] + dig_count[i-1];

  // sort the digits and decrement the count in the digit count array
  for(i = n - 1; i >= 0; i--)
  { 
    helper_arr[dig_count[dig_sep[i]] - 1] = a[i];
    dig_count[dig_sep[i]]--;
  }

  // replace the elements in the original array with elements from the helper array
  for(i = 0; i < n; i++)
    a[i] = helper_arr[i];
}
