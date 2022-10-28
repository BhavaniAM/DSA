<h1> BFS implementation to solve the single-source shortest path problem on undirected graphs. </h1>

<b> <h3> Input:- </h3> </b>
The first line has 2 inputs:- the number of vertices and the number of edges

The subsequent lines have 2 numbers representing an undirected edge between 2 vertices.

There are no repeated edges.

<b> <h3> Output:- </h3> </b>
Each line has one integer which represents the distance from the source (in this case, vertex 0) to the (k-1)th vertex where k is the line number.

<b> <h3> Commands to execute the code on Colab:- </h3> </b>

!gcc BFS.c

!./a.out input1.graph

!diff -w sd.txt sd1.txt
