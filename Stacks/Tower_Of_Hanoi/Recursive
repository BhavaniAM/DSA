#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* A = NULL;
int* B = NULL;
int* C = NULL;

int top_a = -1, top_b = -1, top_c = -1;
int size_stack = 0;

int emp_stack_check(int top);
int full_stack_check(int top);
int push_into_stack(int ele, int* Stack, int top);
int pop_from_stack(int* Stack, int top);
void print_stack(int* Stack, int top);
void toh(int size_stack, char A, char C, char B);

int main(int argc, char* argv[])
{
    if(argc < 2)
    { 
        printf("Enter the maximum size of the stack");
        exit(0);
    }
    size_stack = atoi(argv[1]);

    A = (int*)malloc(size_stack);
    B = (int*)malloc(size_stack);
    C = (int*)malloc(size_stack);

    if(A == NULL || B == NULL || C == NULL)
    {
        printf("Memory allocation error \n");
        exit(0);
    }

    for(int i = size_stack; i>=1;i--)
    {
      top_a = push_into_stack(i, A, top_a);
      printf("Push disk %d to Stack %c\n", i, 'A');
    }
    
    toh(size_stack, 'A', 'C', 'B');
    //printf("Stack C: \n");
    //print_stack(C, top_c);
    return 0;
 }
    
int emp_stack_check(int top)
{
  if(top == -1)
    return 1;
  else
    return 0;
}
    
int full_stack_check(int top)
{
  if(top == size_stack- 1)
    return 1;
  else
    return 0;
}
    
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
    
int pop_from_stack(int* Stack, int top)
{
  int ele;
  if(!emp_stack_check(top))
  {
    ele = Stack[top];
    top = top - 1;
    //printf("Popped element: %d\n",ele);
    return top;
  }
  else
  {
    printf("Stack is empty\n");
    exit(0);
  }
}
    
void print_stack(int* Stack, int top)
{
  int i;
  for(i=0;i<size_stack;i++)
  {
    printf("stack[%d] = %d \n", i, Stack[i]);
  }
  printf("top = %d\n", top);
}

void toh(int size_stack, char a, char c, char b)
{
	if (size_stack == 0)
	{
		return;
	}
	toh(size_stack - 1, a, b, c);

  printf("Pop disk %d from Stack %c\n", size_stack, a);
  if(a == 'A')
  {
    top_a = pop_from_stack(A, top_a);
    //printf("top_a = %d\n", top_a);
  }
  else if(a == 'B')
  {
    top_b = pop_from_stack(B, top_b);
    //printf("top_b = %d\n", top_b);
  }
  else
  {
    top_c = pop_from_stack(C, top_c);
    //printf("top_c = %d\n", top_c);
  }

  printf("Push disk %d to Stack %c\n", size_stack, c);
  if(c == 'A')
    top_a = push_into_stack(size_stack, A, top_a);
  else if(c == 'B')
    top_b = push_into_stack(size_stack, B, top_b);
  else
  {
    top_c = push_into_stack(size_stack, C, top_c);
    //printf("push_top_c = %d\n", top_c);
  }

	//printf("Move disk %d from Stack %c to Stack %c\n", size_stack, A, C);
	toh(size_stack - 1, b, c, a);
}
