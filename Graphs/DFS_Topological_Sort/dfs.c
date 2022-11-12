%%writefile dfs.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The isolated vertices and the vertices with out degree are at the end of the output file.
// initialise global variables 
int visited[10000000], j, x[10000000], num_V, iso_v[10000000], k;

// create the structure for the adjacency list that stores the neighboring vertices for each vertex
struct node
{
  int data;
  struct node *next;
};
struct node* adj_list[10000000];

int max_Size = 10000000;

// declare all the functions
void insert_into_adj_list(int src_vertex, int dest_vertex);
void dfs(int u, int num_V);
void topological_order(int num_V);

// define all file pointers
FILE *fp_read, *fp_write;

// insert the vertices into an adjacency list. Create an acyclic directed graph with unweighted edges
void insert_into_adj_list(int src_vertex, int dest_vertex)
{   
  // src -> dest
  struct node *src_to_dest = (struct node*)malloc(sizeof(struct node));

  src_to_dest -> data = dest_vertex;
  src_to_dest -> next = adj_list[src_vertex];
  adj_list[src_vertex] = src_to_dest;
}

// topological ordering function that calls the DFS method 
void topological_order(int num_v) 
{  
    int i;
    //printf("num_v = %d\n", num_V);
    for (i = 0; i < num_V; i++) 
        visited[i] = 0;
    // declared as global variables, no need to re-initialise
    j = 0, k = 0;
    for (i = 0; i < num_V; i++) 
    {
        if (visited[i] == 0) 
            dfs(i, num_V);
    }
    return;
}

// DFS method to recursively visit nodes and add the node whose all neighbors have been visited to the reverse topological sorted array
void dfs(int vis, int num_v) 
{  
    int v, found_v = 0, count = 0;
    visited[vis] = 1;
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    for (v = 0; v < num_v - 1; v++) 
    {
        temp = adj_list[vis];
        //printf("vis = %d -> ", vis);
        while(temp != NULL)
        {
          //printf("%d ", temp -> data);
          count = count + 1;
          if(temp -> data == v)
          {
            found_v = 1;
            break;
          }
          temp = temp -> next;
        }
        //printf("\n");
        if(found_v == 1 && visited[v] == 0) 
        {
          found_v = 0;
          dfs(v, num_v);
        }
        found_v = 0;
    }
    if(count != 0)
    {
      j = j + 1;
      x[j] = vis;
    }
    else
    {
      k = k + 1;
      iso_v[k] = vis;
    }
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

  fp_write = fopen("ts.txt", "w");
  fclose(fp_write);

  for (i = 0; i < max_Size; i++) 
    adj_list[i] = NULL;

  int count = 0, w, num_E;

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
      w = atoi(string);
      fscanf(fp_read, "%d", &new_num);
      insert_into_adj_list(w, new_num);
    }
    count++;
  }
  fclose(fp_read);

  /*for(i = 0; i < num_V; i++)
  {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp = adj_list[i];
    printf("%d -> ", i);
    while(temp != NULL)
    {
      printf("%d ", temp -> data);
      temp = temp -> next;
    }
    printf("\n");
  }*/

  topological_order(num_V);

  fp_write = fopen("ts.txt", "a");
  for(i = j; i >= 1; i--) 
    fprintf(fp_write, "%d\n", x[i]);

  for(i = k; i >= 1; i--) 
    fprintf(fp_write, "%d\n", iso_v[i]);

  fclose(fp_write);

  return 0;
}
