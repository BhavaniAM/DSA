%%writefile 190020011.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Adjacency list to store all the vertices of the given graph
struct node
{
  int data;
  int weight;
  struct node *next;
};
struct node* adj_list[200000];

// Adjacency list to store the MST
struct adj
{
  int data;
  struct adj *link;
};
struct adj* new_adj_list[200000];

// file pointers to read and write a file
FILE *fp_read, *fp_write;

// function declarations
void quicksort(int weights[], int x[], int y[], int first, int last);
int isCycle(int V);
int checkForCycle(int ele, int parent, int *vis);

void insert_into_adj_list(int src_vertex, int dest_vertex);
void insert_into_new_adj_list(int src_vertex, int dest_vertex);

// check if there is a cycle in the MST on inserting an edge
int checkForCycle(int ele, int parent, int *vis) 
{
  vis[ele] = 1;
  struct adj* temp = new_adj_list[ele];
  while(temp != NULL)
  {
    if (!vis[temp -> data]) 
    {
      if(checkForCycle(temp -> data, ele, vis))
        return 1;
    } 
    else if (temp -> data != parent)
      return 1;
    temp = temp -> link;
  }
  return 0;
}

int isCycle(int V) 
{
  int num_V = V + 1;
  int vis[num_V], i;
  for(i = 0; i < num_V; i++)
    vis[i] = 0;
  for (i = 0; i < V; i++) 
  {
    if(!vis[i]) 
    {
      if(checkForCycle(i, -1, vis)) 
        return 1;
    }
  }
  return 0;
}

// insert the edge into the undirected graph
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

// insert the edge into the MST
void insert_into_new_adj_list(int src_vertex, int dest_vertex)
{
  // src -> dest
  struct adj *src_to_dest = (struct adj*)malloc(sizeof(struct adj));

  src_to_dest -> data = dest_vertex;
  src_to_dest -> link = new_adj_list[src_vertex];
  new_adj_list[src_vertex] = src_to_dest;

  // dest -> src
  struct adj *dest_to_src = (struct adj*)malloc(sizeof(struct adj));

  dest_to_src -> data = src_vertex;
  dest_to_src -> link = new_adj_list[dest_vertex];
  new_adj_list[dest_vertex] = dest_to_src;
}

// delete the edge from the MST if it forms a cycle on insertion
void delete_from_new_adj_list(int x, int y)
{
  struct adj* src_temp = (struct adj*)malloc(sizeof(struct adj));
  
  src_temp = new_adj_list[x];
  if(src_temp -> link== NULL)
  {
    new_adj_list[x] = NULL;
    return;
  }
  new_adj_list[x] = src_temp -> link;

  struct adj* dest_temp = (struct adj*)malloc(sizeof(struct adj));
  
  dest_temp = new_adj_list[y];
  if(dest_temp -> link == NULL)
  {
    new_adj_list[y] = NULL;
    return;
  }
  new_adj_list[y] = dest_temp -> link;
}

// sort all the given edges in ascending order based on the weights
void quicksort(int weights[], int x[], int y[], int first, int last)
{
   int i, j, pivot, temp;
   if(first < last)
   {
      pivot = first;
      i = first;
      j = last;
      while(i < j)
      {
         while((weights[i] <= weights[pivot]) && (i < last))
          i++;
         while(weights[j] > weights[pivot])
          j--;
         if(i < j)
         {
            temp = weights[i];
            weights[i] = weights[j];
            weights[j] = temp;

            temp = x[i];
            x[i] = x[j];
            x[j] = temp;

            temp = y[i];
            y[i] = y[j];
            y[j] = temp;
         }
      }
      temp = weights[pivot];
      weights[pivot] = weights[j];
      weights[j] = temp;

      temp = x[pivot];
      x[pivot] = x[j];
      x[j] = temp;

      temp = y[pivot];
      y[pivot] = y[j];
      y[j] = temp;

      quicksort(weights, x, y, first, j-1);
      quicksort(weights, x, y, j+1, last);
   }
}

int main(int argc, char* argv[])
{
  //printf("hi\n");
  
  // read the file
  fp_read = fopen(argv[1], "r");
  
  if(fp_read == NULL)
	{
		printf("Error: Could not find the file");
		exit(0);
	}

  fp_write = fopen("mst.txt", "w");
  fclose(fp_write);

  int count = 0;
  char string[40];

  // count the number of edges
  while(fscanf(fp_read, "%s", string) != EOF)
  {
    count = count + 1;
  }
  count = count / 3;

  rewind(fp_read);

  int x[count], y[count], w[count], i = 0;

  //printf("Before QS\n");

  // read all the edges and their weights
  while(fscanf(fp_read, "%s ", string) != EOF)
  {
    x[i] = atoi(string);
    fscanf(fp_read, "%d", &y[i]);
    fscanf(fp_read, "%d", &w[i]);
    //printf("%d %d %d\n", x[i], y[i], w[i]);
    i = i + 1;
  }

  fclose(fp_read);

  quicksort(w, x, y, 0, count - 1);

  /*
  fp_write = fopen("new_mst.txt", "a");
  
  printf("After QS\n");

  for(i = 0; i < count; i++)
    fprintf(fp_write, "%d %d %d\n", x[i], y[i], w[i]);

  fclose(fp_write);
  */

  int num_V = 0, max = -1, temp_max;

  for(i = 0; i < count; i++)
    insert_into_adj_list(x[i], y[i]);

  /*
  printf("After insertion\n");

  for(i = 0; i < count; i++)
  {
    struct node* temp = adj_list[i];
    while(temp != NULL)
    {
      printf("%d ", temp -> data);
      temp = temp -> next;
    }
    printf("\n");
  }
  */

  fp_write = fopen("mst.txt", "a");

  // insert into MST
  for(i = 0; i < count; i++)
  {
    insert_into_new_adj_list(x[i], y[i]);

    int k = x[i], l = y[i];
    temp_max = (k > l) ? k : l;
    if(temp_max > max) 
    {
      max = temp_max;
      num_V = max;
    } 

    if(!isCycle(num_V))
      fprintf(fp_write, "%d %d %d\n", x[i], y[i], w[i]);
    else
      delete_from_new_adj_list(x[i], y[i]);
  }
  fclose(fp_write);

  /*printf("New adj list\n");

  // print the MST in increasing order of weights
  for(i = 0; i < count; i++)
  {
    struct adj* temp = new_adj_list[i];
    while(temp != NULL)
    {
      printf("%d ", temp -> data);
      temp = temp -> link;
    }
    printf("\n");
  }*/
  
  return 0;
}
