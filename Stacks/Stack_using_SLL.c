#include<stdio.h>
#include <stdlib.h>
#include <string.h>

// declare the functions used in the code
FILE *fp_read, *fp_write;

// file pointers to read and write files

// functions for stack
int push_to_stack(int ele, int sq_size, int count);
void search_in_stack(int ele);
int pop(int count);
void display_stack();

// define the structure
struct node
{
  int data;
  struct node *next;
};

// declare the top pointer for the stack
struct node *top = NULL;

int main(int argc, char* argv[])
{
  int sq_size, x, i;
  int count = 0, count_q = 0;

  // read the file
  fp_read = fopen(argv[1], "r");
  int MAX_LEN = 1000000;
  int new_num = 0;
  char string[MAX_LEN];
  
  // take the second argument
  sq_size = atoi(argv[2]);

  if(fp_read == NULL)
	{
		printf("Error: Could not find the file");
		exit(0);
	}
  fp_write = fopen("stack.txt", "w");
  fclose(fp_write);

  // read each line from the input file
  while(fgets(string, MAX_LEN, fp_read) != NULL)
  {  
    // convert the digits from characters to integer
    if(string[0] == '+')
    {
      for(i = 2; i <= strlen(string) - 2; i++)
      {
        new_num = new_num * 10;
        new_num += (string[i] - '0');
      }
      // perform push operations
      count = push_to_stack(new_num, sq_size, count);
    }

    else if(string[0] == '?')
    {
      for(i = 2; i <= strlen(string) - 2; i++)
      {
        new_num = new_num * 10;
        new_num += (string[i] - '0');
      }
      // perform search operations for the stack
      search_in_stack(new_num);
    }
    
    else if(string[0] == '-')
    {
      for(i = 2; i <= strlen(string) - 2; i++)
      {
        new_num = new_num * 10;
        new_num += (string[i] - '0');
      }
      // perform pop operation
      count = pop(count);
    }

    else
    {
      // display by writing to the file
      display_stack();
    }
    new_num = 0;
  }
  // close the input file
  fclose(fp_read);
  return 0;
}

int push_to_stack(int ele, int sq_size, int count)
{
  // check for the overflow condition (when the stack is full)
  if(count == sq_size)
  {
    fp_write = fopen("stack.txt", "a");
    fprintf(fp_write, "overflow\n");
    fclose(fp_write);
    return count;
  }

  // create a new node 
  struct node *newNode = (struct node*)malloc(sizeof(struct node));
  newNode -> data = ele; 

  // push the element into the stack
  if (top == NULL) 
    newNode -> next = NULL;
  else
    newNode -> next = top; 
  top = newNode;

  // count stores the number of elements present in the stack
  count = count + 1;
  fp_write = fopen("stack.txt", "a");
  fprintf(fp_write, "pushed %d\n", ele);
  fclose(fp_write);
  return count;
}

int pop(int count) 
{
  // check the underflow condition (deleting from an empty stack)
  if (top == NULL) 
  {
    fp_write = fopen("stack.txt", "a");
    fprintf(fp_write, "underflow\n");
    fclose(fp_write);
  }
  else 
  {
    // delete the element from the stack 
    struct node *temp;
    int temp_data = top -> data;
    temp = top;
    top = top -> next;
    // free the memory
    free(temp);
    fp_write = fopen("stack.txt", "a");
    fprintf(fp_write, "popped %d\n", temp_data);
    fclose(fp_write);
    count = count - 1;
  }
  return count;
}

void display_stack() 
{
  // display the elements of the stack
  struct node *temp = top;
  fp_write = fopen("stack.txt", "a");
  if (top == NULL) 
   fprintf(fp_write, "\n");
  else 
  {
    // iterate over each element and print it
    while (temp -> next != NULL) 
    {
      fprintf(fp_write, "%d ", temp -> data); 
      temp = temp -> next;
    }
    fprintf(fp_write, "%d \n", temp -> data);
  }
  fclose(fp_write);
}

void search_in_stack(int ele)
{
  // if no element is present in the stack
  if (top == NULL) 
  {
    fp_write = fopen("stack.txt", "a");
    fprintf(fp_write, "\n");
    fclose(fp_write);
  }
  else 
  {
    fp_write = fopen("stack.txt", "a");
    struct node *temp = top;
    // iterate over each element and check if it matches the element being searched
    while(temp -> next != NULL) 
    {
      if(ele == temp -> data)
      {
        fprintf(fp_write, "found %d\n", ele);
        fclose(fp_write);
        return;
      }
      temp = temp -> next;
    }
    fprintf(fp_write, "not found %d\n", ele);
  }
  fclose(fp_write);
}
