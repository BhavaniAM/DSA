#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initialize the 3 stacks and the other global variables

int* A = NULL;
int* B = NULL;
int* C = NULL;

int top_a = -1, top_b = -1, top_c = -1;
int size_stack = 0;

// Declare all the functions that will be used

int emp_stack_check(int top);
int full_stack_check(int top);
int push_into_stack(int ele, int* Stack, int top);
int pop_from_stack(int* Stack, int top);
void print_stack(int* Stack, int top);
void toh(int size_stack, char A, char C, char B);
// file pointer
FILE *fp_w;

int main(int argc, char* argv[])
{
    
    if(argc < 2)
    { 
        printf("Enter the maximum size of the stack");
        exit(0);
    }
    size_stack = atoi(argv[1]);

    // assign memory locations to the stacks
    
    A = (int*)malloc(size_stack);
    B = (int*)malloc(size_stack);
    C = (int*)malloc(size_stack);

    if(A == NULL || B == NULL || C == NULL)
    {
        printf("Memory allocation error \n");
        exit(0);
    }

    // Print the presence of the n disks in stack A
    // Open the file to be written to in write mode so that any other text present in the file is gotten rid of

    fp_w = fopen("toh.txt", "w");
    for(int i = size_stack; i >= 1; i--)
    {
      top_a = push_into_stack(i, A, top_a);
      fprintf(fp_w, "Push disk %d to Stack %c\n", i, 'A');
    }
    fclose(fp_w);

    // Main logic for the program is present in this function

    toh(size_stack, 'A', 'C', 'B');

    return 0;
 }
    
// Check if the stack is empty

int emp_stack_check(int top)
{
  if(top == -1)
    return 1;
  else
    return 0;
}

// Check if the stack is full

int full_stack_check(int top)
{
  if(top == size_stack- 1)
    return 1;
  else
    return 0;
}

// Function to push the elements into the stack

int push_into_stack(int ele, int* Stack, int top)
{
  if(!full_stack_check(top))
  {
    top = top + 1;
    Stack[top] = ele;
    return top;
  }
  else
  {
    printf("Stack is full\n");
    exit(0);
  }
}

// Function to pop the elements from the stack

int pop_from_stack(int* Stack, int top)
{
  int ele;
  if(!emp_stack_check(top))
  {
    ele = Stack[top];
    top = top - 1;
    return top;
  }
  else
  {
    printf("Stack is empty\n");
    exit(0);
  }
}
    
// Function to print the stack

void print_stack(int* Stack, int top)
{
  int i;
  for(i = 0; i < size_stack; i++)
  {
    printf("stack[%d] = %d \n", i, Stack[i]);
  }
  printf("top = %d\n", top);
}

// Main logic of the code. Is a recursive algorithm to dis-assemble and assemble the tower of hanoi.

void toh(int size_stack, char a, char c, char b)
{

  // base case of the recursive algorithm. The code comes out of the loop if the base case is violated.

	if (size_stack == 0)
    return;

	toh(size_stack - 1, a, b, c);
  
  // Open the file in append mode to add to the existing text. Do not overwrite the file.

  fp_w = fopen("toh.txt","a");
  fprintf(fp_w, "Pop disk %d from Stack %c\n", size_stack, a);
  fclose(fp_w);

  if(a == 'A')
    top_a = pop_from_stack(A, top_a);
  else if(a == 'B')
    top_b = pop_from_stack(B, top_b);
  else
    top_c = pop_from_stack(C, top_c);

  fp_w = fopen("toh.txt","a");
  fprintf(fp_w, "Push disk %d to Stack %c\n", size_stack, c);
  fclose(fp_w);

  if(c == 'A')
    top_a = push_into_stack(size_stack, A, top_a);
  else if(c == 'B')
    top_b = push_into_stack(size_stack, B, top_b);
  else
    top_c = push_into_stack(size_stack, C, top_c);

	toh(size_stack - 1, b, c, a);
}
