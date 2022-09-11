#include<stdio.h>
#include <stdlib.h>
#include <string.h>

// declare the functions used in the code
FILE *fp_read, *fp_q;

// file pointers to read and write files

// functions for queue
int enqueue(int new_num, int sq_size, int count_q);
int dequeue(int count_q);
void display();
void search_queue(int new_num);

// define the structure
struct node
{
  int data;
  struct node *next;
};

// declare the front and rear pointers for the queue
struct node *q_front = NULL;
struct node *q_rear = NULL;

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
  fp_q = fopen("queue.txt", "w");
  fclose(fp_q);

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
      // perform enqueue
      count_q = enqueue(new_num, sq_size, count_q);
    }

    else if(string[0] == '?')
    {
      for(i = 2; i <= strlen(string) - 2; i++)
      {
        new_num = new_num * 10;
        new_num += (string[i] - '0');
      }
      // perform search operations for the queue
      search_queue(new_num);
    }
    
    else if(string[0] == '-')
    {
      for(i = 2; i <= strlen(string) - 2; i++)
      {
        new_num = new_num * 10;
        new_num += (string[i] - '0');
      }
      // perform dequeue 
      count_q = dequeue(count_q);
    }

    else
    {
      // display by writing to the file
      display();
    }
    new_num = 0;
  }
  // close the input file
  fclose(fp_read);
  return 0;
}

// queue operations
// enqueue operation
int enqueue(int ele, int sq_size, int count_q)
{
  struct node *newNode = (struct node*) malloc(sizeof(struct node));
  // check the overflow condition
  if(count_q == sq_size)
  {
    fp_q = fopen("queue.txt", "a");
    fprintf(fp_q, "overflow\n");
    fclose(fp_q);
    return count_q;
  }
  newNode -> data = ele;
  newNode -> next = NULL;

  // if this is the first node being inserted
  if(q_front == NULL)
  {
    q_front = newNode;
    q_rear = newNode;
  }
  else
  {
    q_rear -> next = newNode;
    q_rear = newNode;
  }
  q_rear -> next = q_front;
  count_q = count_q + 1;
  fp_q = fopen("queue.txt", "a");
  fprintf(fp_q, "enqueued %d\n", ele);
  fclose(fp_q);
  return count_q;
}

int dequeue(int count_q)
{
  int x;
  // check the underflow condition
  if(q_front == NULL)
  {
    fprintf(fp_q, "underflow\n");
    return count_q; 
  }
  // if the queue has only a single node
  else if (q_front == q_rear) 
  {
    x = q_front->data;
    free(q_front);
    q_front = NULL;
    q_rear = NULL;
  }
  else
  {
    struct node *temp = q_front;
    x = temp -> data;
    q_front = q_front -> next;
    q_rear -> next = q_front;
    free(temp);
  }
  count_q = count_q - 1;
  fp_q = fopen("queue.txt", "a");
  fprintf(fp_q, "dequeued %d\n", x);
  fclose(fp_q);
  return count_q;
}

void display()
{
  struct node *temp = q_front;
  fp_q = fopen("queue.txt", "a");
  // if there is no element in the queue
  if((q_front == NULL) && (q_rear == NULL))
		fprintf(fp_q, "\n");
	else
  {
		do
    {
			fprintf(fp_q, "%d ",temp -> data);
			temp = temp -> next;
		}while(temp != q_front);
    fprintf(fp_q, "\n");
	}
  fclose(fp_q);
}

void search_queue(int ele)
{
  struct node *temp = q_front;
  fp_q = fopen("queue.txt", "a");
  
  // for an empty queue
  if((q_front == NULL) && (q_rear == NULL))
    fprintf(fp_q, "\n");
	else
  {
		do
    {
			if(ele == temp -> data)
      {
        fprintf(fp_q, "found %d\n", ele);
        fclose(fp_q);
        return;
      }
			temp = temp -> next;
		}while(temp != q_front);
	}
  fprintf(fp_q, "not found %d\n", ele);
  fclose(fp_q);
}
