%%writefile Merge_Sort.c
#include<stdio.h>
#include <stdlib.h>

// declare the functions used in the code
void merge_sort_recurse(int a[], int l, int r);
void merge_func(int a[], int l, int mid, int r);
void print_array(int a[], int count);

// file pointers to read and write files
FILE *fp_r,*fp_w;

//initialise global variables
int count = 0;

int main(int argc, char* argv[])
{
  int ind = 0, ele, x;
  fp_r = fopen (argv[1], "r");
  if(fp_r == NULL)
	{
		printf("Error:- Could not find such a file");
		exit(0);
	}
  
  // iterate over the file to count the number of lines
  // Done so that a random size does not have to be given to the array which will waste memory space 
  while(fscanf(fp_r,"%d",&x)!=EOF)
    count = count + 1;

  // point back to the first line of the file
  rewind(fp_r);

  // initialise the array for the required size
  int *a;
  a = malloc(sizeof(int)*count);

  // populate the array elements
  while(fscanf(fp_r,"%d",&ele)!=EOF)
  {
    a[ind] = ele;
    ind++;
  }
  fclose(fp_r);               

  // call the merge_sort_recurse function
  merge_sort_recurse(a, 0, count-1);
  
  // function to generate the final output file
  print_array(a,count);
  return 0;
}

void merge_sort_recurse(int a[], int l, int r)
{
  if(l < r)
  {
    // find the middle index of the array in each recursion
    int mid = (r-l)/2 + l;

    // split the left half of the array down to one element
    merge_sort_recurse(a, l , mid);

    // split the right half of the array down to one element
    merge_sort_recurse(a, mid+1, r);

    // perform the comparison and sort the elements
    merge_func(a, l, mid, r);
  }
}

void merge_func(int a[], int l, int mid, int r)
{
  int i, j, k, lower_half = mid - l + 1, upper_half = r - mid;
  
  // dynamic memory allocation for the left and the right half arrays
  int *L;
  L = malloc(sizeof(int)*lower_half);
  
  int *R;
  R = malloc(sizeof(int)*upper_half);

  //initialise the left and right half arrays to zeros to avoid garbage values
  for(i = 0; i < lower_half; i++)
    L[i] = 0;

  for(j = 0; j < upper_half; j++)
    R[j] = 0;

  // populate the arrays with the elements
  for(i = 0; i < lower_half; i++)
    L[i] = a[l + i];

  for(j = 0; j < upper_half; j++)
    R[j] = a[j + 1 + mid];

  i = 0;
  j = 0;
  k = l;

  // compare the elements and sort
  while(i<lower_half && j<upper_half)
  {
    if(L[i] <= R[j])
    {
      a[k] = L[i];
      i++;
    }
    else
    {
      a[k] = R[j];
      j++;
    }
    k++;
  }
  
  // include all the remaining elements in the final sorted array
  while (i < lower_half) 
  {
        a[k] = L[i];
        i++;
        k++;
  }

  while (j < upper_half) 
  {
      a[k] = R[j];
      j++;
      k++;
  }
}

// print the final array to the output file
void print_array(int a[], int count)
{
  fp_w = fopen("mergesort.txt", "w");
  for(int ent = 0; ent < count; ent++)
    fprintf(fp_w, "%d\n", a[ent]);
  fclose(fp_w);
}
