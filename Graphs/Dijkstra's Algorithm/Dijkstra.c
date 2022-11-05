%%writefile dijk.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp_read, *fp_write;

// Adjacency list node
struct node
{
  int data;
  int weight;
  struct node *next;
};

// Adjacency list
struct adj_list
{
	struct node *head;
};

// Graph
struct Graph
{
	int num_V;
	struct adj_list* x;
};

struct node* new_adj_list_node(int dest_vertex, int weight)
{
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node -> data = dest_vertex;
	new_node -> weight = weight;
	new_node -> next = NULL;
	return new_node;
}

struct Graph* create_graph(int num_V)
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph -> num_V = num_V;

	graph -> x = (struct adj_list*)malloc(num_V * sizeof(struct adj_list));

	for (int i = 0; i < num_V; ++i)
		graph -> x[i].head = NULL;

	return graph;
}

// Min heap node
struct min_heap_node
{
	int vertex;
	int dist;
};

// Min heap
struct min_heap
{
	int min_heap_size;	
	int c;
	int *pos;
	struct min_heap_node **x;
};

struct min_heap_node* new_mh_node(int vertex, int dist)
{
	struct min_heap_node* mh_node = (struct min_heap_node*)malloc(sizeof(struct min_heap_node));
	mh_node -> vertex = vertex;
	mh_node -> dist = dist;
	return mh_node;
}

// create a min heap - the root node has the minimum value
struct min_heap* create_mh(int c)
{
	struct min_heap* mh = (struct min_heap*)malloc(sizeof(struct min_heap));
	mh -> pos = (int *)malloc(c * sizeof(int));
	mh -> min_heap_size = 0;
	mh -> c = c;
	mh -> x = (struct min_heap_node**)malloc(c * sizeof(struct min_heap_node*));
	return mh;
}

// declare all functions used

void insert_into_adj_list(struct Graph* graph, int src_vertex, int dest_vertex, int weight);
void swap_mh_node(struct min_heap_node** node_1, struct min_heap_node** node_2);
void convert_to_min_heap(struct min_heap* mini_h, int i);
void decrement_key(struct min_heap* h, int vertex, int dist);
int heap_is_empty(struct min_heap* h);
int is_present(struct min_heap *h, int vertex);
void print_func(int dist[], int n);
void dijkstra(struct Graph* graph, int src_vertex);

struct min_heap_node* get_min(struct min_heap* h)
{
	if (heap_is_empty(h))
		return NULL;

	struct min_heap_node* root = h -> x[0];

	struct min_heap_node* end_node = h -> x[h -> min_heap_size - 1];
	h -> x[0] = end_node;

	h -> pos[root -> vertex] = h -> min_heap_size - 1;
	h -> pos[end_node -> vertex] = 0;

	h -> min_heap_size = h -> min_heap_size - 1;
	convert_to_min_heap(h, 0);

	return root;
}

// to re-arrange the nodes in the heap such that it is a min heap at all times
void swap_mh_node(struct min_heap_node** node_1, struct min_heap_node** node_2)
{
	struct min_heap_node* temp_node = *node_1;
	*node_1 = *node_2;
	*node_2 = temp_node;
}

void convert_to_min_heap(struct min_heap* mini_h, int i)
{
	int least, l, r;
	least = i;
	l = (2 * i) + 1;
	r = l + 1;

	if((l < mini_h -> min_heap_size) && (mini_h -> x[l] -> dist < mini_h -> x[least] -> dist))
	  least = l;

	if((r < mini_h -> min_heap_size) && (mini_h -> x[r] -> dist < mini_h -> x[least] -> dist))
	  least = r;

	if(least != i)
	{
		struct min_heap_node *least_node = mini_h -> x[least];
		struct min_heap_node *idxNode = mini_h -> x[i];

		mini_h -> pos[least_node -> vertex] = i;
		mini_h -> pos[idxNode -> vertex] = least;

		swap_mh_node(&mini_h -> x[least], &mini_h -> x[i]);
		convert_to_min_heap(mini_h, least);
	}
}

int heap_is_empty(struct min_heap* h)
{
	if(h -> min_heap_size == 0)
    return 1;
  else  
    return 0;
}

void decrement_key(struct min_heap* h, int vertex, int dist)
{
	int i = h -> pos[vertex];
	h -> x[i] -> dist = dist;

	while(i && h -> x[i] -> dist < h -> x[(i - 1) / 2] -> dist)
	{
		h -> pos[h -> x[i] -> vertex] = (i-1)/2;
		h -> pos[h -> x[(i-1)/2] -> vertex] = i;
		swap_mh_node(&h -> x[i], &h -> x[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

// if the node is present in the minimum heap
int is_present(struct min_heap *h, int vertex)
{
  if (h -> pos[vertex] < h -> min_heap_size)
	  return 1;
  return 0;
}

void print_func(int dist[], int n)
{
  fp_write = fopen("dijkstra.txt", "w");
	for (int i = 0; i < n; ++i)
	{
    if(dist[i] == 1e8)
      dist[i] = -1;
    fprintf(fp_write, "%d %d\n", i, dist[i]);
  }
  fclose(fp_write);
}

void dijkstra(struct Graph* graph, int src_vertex)
{
	int num_V = graph -> num_V;
	int dist[num_V];	

	struct min_heap* h = create_mh(num_V);
	for (int v = 0; v < num_V; v++)
	{
		dist[v] = 1e8;
		h -> x[v] = new_mh_node(v, dist[v]);
		h -> pos[v] = v;
	}

	h -> x[src_vertex] = new_mh_node(src_vertex, dist[src_vertex]);
	h -> pos[src_vertex] = src_vertex;
	dist[src_vertex] = 0;
	decrement_key(h, src_vertex, dist[src_vertex]);

	h -> min_heap_size = num_V;

	while (!heap_is_empty(h))
	{
		struct min_heap_node* temp = get_min(h);
	  int u = temp -> vertex;

		struct node* temp_2 = graph -> x[u].head;
		while(temp_2 != NULL)
		{
			int v = temp_2 -> data;

			if((is_present(h, v)) && (dist[u] != 1e8) && (temp_2->weight + dist[u] < dist[v]))
			{
				dist[v] = dist[u] + temp_2 -> weight;
				decrement_key(h, v, dist[v]);
			}
			temp_2 = temp_2->next;
		}
	}
	print_func(dist, num_V);
}

// Insert each edge into the adjacency list
void insert_into_adj_list(struct Graph* graph, int src_vertex, int dest_vertex, int weight)
{
  // src -> dest
	struct node* src_to_dest = new_adj_list_node(dest_vertex, weight);
	src_to_dest -> next = graph -> x[src_vertex].head;
	graph -> x[src_vertex].head = src_to_dest;
}

int main(int argc, char* argv[])
{
	// read the file
  fp_read = fopen(argv[1], "r");
  
  if(fp_read == NULL)
	{
		printf("Error: Could not find the file");
		exit(0);
	}

  int source_vertex = atoi(argv[2]);

  fp_write = fopen("dijkstra.txt", "w");
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

  while(fscanf(fp_read, "%s ", string) != EOF)
  {
    x[i] = atoi(string);
    fscanf(fp_read, "%d", &y[i]);
    fscanf(fp_read, "%d", &w[i]);
    i = i + 1;
  }

  fclose(fp_read);

  int num_V = 0, max = -1, temp_max;

  for(i = 0; i < count; i++)
  {
    int k = x[i], l = y[i];
    temp_max = (k > l) ? k : l;
    if(temp_max > max) 
    {
      max = temp_max;
      num_V = max;
    } 
  }
  
  struct Graph* graph = create_graph(num_V);

  for(i = 0; i < count; i++)
    insert_into_adj_list(graph, x[i], y[i], w[i]);

  dijkstra(graph, source_vertex);

  return 0;
}
