#include<stdio.h>
#include <stdlib.h>
#include <string.h>

// declare the functions used in the code
FILE *fp_read, *fp_dll;

// file pointers to read and write files

// functions for the doubly linked list
void insertion(int ele);
void deletion(int ele);
void display_dll();
void search_dll(int ele);
void dll_First_Node_del(int ele);
void dll_Last_Node_del(int ele);

// define the structure
struct node
{
  int data;
  struct node *next;
  struct node *prev;
};

// declare the head pointer for the doubly linked list
struct node *head = NULL;

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
  fp_dll = fopen("dll.txt", "w");
  fclose(fp_dll);

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
      // perform insertion for dll
      insertion(new_num);
    }

    else if(string[0] == '?')
    {
      for(i = 2; i <= strlen(string) - 2; i++)
      {
        new_num = new_num * 10;
        new_num += (string[i] - '0');
      }
      // perform search operations for the dll
      search_dll(new_num);
    }
    
    else if(string[0] == '-')
    {
      for(i = 2; i <= strlen(string) - 2; i++)
      {
        new_num = new_num * 10;
        new_num += (string[i] - '0');
      }
      // perform deletion of the element specified
      deletion(new_num);
    }

    else
    {
      // display by writing to the file
      display_dll();
    }
    new_num = 0;
  }
  // close the input file
  fclose(fp_read);
  return 0;
}

void insertion(int ele)  
{  
  struct node *temp; 
  fp_dll = fopen("dll.txt", "a");  
  temp = (struct node *)malloc(sizeof(struct node));  
  // if it is the first node to be inserted
  if(head == NULL)  
    {  
      temp -> next = NULL;  
      temp -> prev = NULL;  
      temp -> data = ele;  
      head = temp;  
    }  
    else   
    {  
      temp -> data = ele;  
      temp -> prev = NULL;  
      temp -> next = head;  
      head -> prev = temp;  
      head = temp;  
    }  
    fprintf(fp_dll, "inserted %d\n", ele);  
    fclose(fp_dll);   
}  

void deletion(int ele)
{
    struct node *temp;
    fp_dll = fopen("dll.txt", "a");
    int i, flag = 0;
    temp = head;
    if(temp -> data == ele)
      dll_First_Node_del(ele);
    else
    {
      while(temp != NULL)
      {
        if(temp -> data == ele)
        {
          flag = 1;
          break;
        }
        temp = temp -> next;
      }
    }
    if(flag == 0)
      fprintf(fp_dll, "cannot delete %d\n", ele);
    else
    {
      if(temp == NULL)
        dll_Last_Node_del(ele);
      else
      {
        temp -> prev -> next = temp -> next;
        temp -> next -> prev = temp -> prev;
        fprintf(fp_dll, "deleted %d\n", ele);
        free(temp); 
      }
    }
    fclose(fp_dll);
} 

void dll_First_Node_del(int ele)
{
    struct node *delNode;
    fp_dll = fopen("dll.txt", "a");
    if(head == NULL)
        fprintf(fp_dll, "cannot delete %d\n", ele);
    else
    {
        delNode = head;
        head = head -> next;   
        head -> prev = NULL;      
        free(delNode);           
        fprintf(fp_dll, "deleted %d\n", ele);
    }
    fclose(fp_dll);
}

void dll_Last_Node_del(int ele)
{
    struct node *delNode;
    fopen("dll.txt", "a");
    delNode = head;
    if(head -> next == NULL)
    {
      head = NULL;
      free(delNode);
    }
    while(delNode -> next != NULL)
    {
      delNode = delNode -> next;
    }
    delNode -> prev -> next = NULL;
    fprintf(fp_dll, "deleted %d\n", ele);
    free(delNode);
    fclose(fp_dll);
}

void display_dll()
{
  struct node *temp = head;
  fp_dll = fopen("dll.txt", "a");
  if(temp == NULL)
  {
    fprintf(fp_dll, "\n");
    fclose(fp_dll);
    return;
  }
  while(temp -> next != NULL)
  {
    fprintf(fp_dll, "%d ", temp->data);
    temp = temp -> next;
  }
  fprintf(fp_dll, "%d \n", temp->data);
  fclose(fp_dll);
}

void search_dll(int ele)
{
  struct node *temp = head;
  fp_dll = fopen("dll.txt", "a");
  if(temp == NULL)
  {
    fprintf(fp_dll, "not found %d\n", ele);
    fclose(fp_dll);
    return;
  }
  while(temp -> next != NULL)
  {
    if(ele == temp -> data)
    {
      fprintf(fp_dll, "found %d\n", ele);
      fclose(fp_dll);
      return;
    }
    temp = temp -> next;
  }
  fprintf(fp_dll, "not found %d\n", ele);
  fclose(fp_dll);
}
