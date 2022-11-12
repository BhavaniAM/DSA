<h1> BFS implementation to topologically sort a graph using Depth First Search. </h1>

<b> <h3> Input:- </h3> </b>
The first line has 2 inputs:- the number of vertices and the number of edges

The subsequent lines have 2 numbers representing a directed edge between 2 vertices.

There are no repeated edges.

<b> <h3> Output:- </h3> </b>
Each line has one integer which represents the vertex.

<b> <h3> Commands to execute the code on Colab:- </h3> </b>

!gcc dfs.c

!./a.out input1.graph

!diff -w ts.txt ts1.txt

Note:- The outputs can vary from the provided output files as there can be different possible correct orders for topological sorting.
