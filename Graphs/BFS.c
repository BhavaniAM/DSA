%%writefile 190020011.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// create the structure for the adjacency list that stores the neighboring vertices for each vertex
struct node
{
  int data;
  struct node *next;
};
struct node* adj_list[2000];

// let max_Size = 2000 as the maximum number of vertices can be 2000
int max_Size = 2000;

// create a queue for the BFS implementation
int queue[2000];

// declare all the functions
void insert_into_adj_list(int src_vertex, int dest_vertex);
void print_adj_list(int num_V);

int enqueue(int queue[],int ele, int rear);
int dequeue(int queue[], int rear);
int isEmpty(int rear);

void BFS_SD(int num_V, int num_E);
int Breadth_First_Search(int x, int target, int num_V, int num_E);

// define all file pointers
FILE *fp_read, *fp_write;

// insert the vertices into an adjacency list. Since the graph is undirected and un-weighted, create the edge both ways and don't assign any weight to the edges
void insert_into_adj_list(int src_vertex, int dest_vertex)
{   
  // src -> dest
  struct node *src_to_dest = (struct node*)malloc(sizeof(struct node));

  src_to_dest -> data = dest_vertex;
  src_to_dest -> next = adj_list[src_vertex];
  adj_list[src_vertex] = src_to_dest;

  // dest -> src
  struct node *dest_to_src = (struct node*)malloc(sizeof(struct node));

  dest_to_src -> data = src_vertex;
  dest_to_src -> next = adj_list[dest_vertex];
  adj_list[dest_vertex] = dest_to_src;
}

// implementation of the BFS algorithm to find the shortest distance between the source vertex and every other vertex
int Breadth_First_Search(int x, int target, int num_V, int num_E)
{
  int rear = -1, c = -1;
  int i;

  for(i = 0; i < num_V; i++)
    queue[i] = 0;

  int dp[num_V], distances[num_E], visited[num_V], u, ele;

  
  for(i = 0; i < num_V; i++) 
  {
    visited[i] = 0;
    distances[i] = 1e5;
  }

  visited[0] = 1;
  distances[0] = 0;
  rear = enqueue(queue, 0, rear);

  // visit each vertex and calculate the distance as you visit each vertex
  while(!isEmpty(rear))
  {
    u = queue[0];
    rear = dequeue(queue, rear);
    struct node* temp = adj_list[u];
    while(temp)
    {
      ele = temp -> data;
      if(visited[ele] == 0)
      {
        visited[ele] = 1;
        distances[ele] = distances[u] + 1;

        rear = enqueue(queue, ele, rear);

        if(ele == target)
        {
          c = distances[ele];
          break;
        }
      }
      temp = temp -> next;
    }
    if(c != -1)
      break;
  }
  return c;
}

// compute the shortest distance for each vertex
void BFS_SD(int num_V, int num_E)
{
  int i, source = 0;
  fp_write = fopen("sd.txt", "a");
  for(i = 1; i < num_V; i++)
  {
    int x = Breadth_First_Search(source, i, num_V, num_E);
    fprintf(fp_write, "%d\n", x);
  }
  fclose(fp_write);
}

// add an element to the queue
int enqueue(int queue[], int ele, int rear)
{
  rear = rear + 1;
  queue[rear] = ele;
  return rear;
}

// remove the element at the front of the queue
int dequeue(int queue[], int rear)
{
  int i;
  for(i = 0; i < rear; i++)
    queue[i] = queue[i + 1];
  rear = rear - 1;
  return rear;
}

// check if the queue is empty
int isEmpty(int rear)
{
  if(rear == -1)
    return 1;
  else  
    return 0;
}

int main(int argc, char* argv[])
{
  int i, new_num;
  char string[4];

  fp_read = fopen(argv[1], "r");
  
  if(fp_read == NULL)
	{
		printf("Error: Could not find the file");
		exit(0);
	}

  fp_write = fopen("sd.txt", "w");
  fclose(fp_write);

  for (i = 0; i < max_Size; i++) 
    adj_list[i] = NULL;

  int count = 0, x, num_V, num_E;

  while(fscanf(fp_read, "%s ", string) != EOF)
  {
    // to store the number of vertices and the number of edges given by the first line of the file
    if(count == 0)
    {
      num_V = atoi(string);
      fscanf(fp_read, "%d", &new_num);
      num_E = new_num;
    }
    else
    {
      x = atoi(string);
      fscanf(fp_read, "%d", &new_num);
      insert_into_adj_list(x, new_num);
    }
    count++;
  }
  fclose(fp_read);

  fp_write = fopen("sd.txt", "a");
  fprintf(fp_write, "%d\n", 0);
  fclose(fp_write);

  BFS_SD(num_V, num_E);

  return 0;
}
