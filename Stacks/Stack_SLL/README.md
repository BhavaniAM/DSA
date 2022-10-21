<h1> Implement a stack using a singly linked list </h1>

Operations performed:- push, pop, search and display


<b> <h3> Input:- </h3> </b>
Each line in the input file has one of the 4 symbols:- '+', '-', '?', '!'
  - '+' stands for PUSH
  - '-' stands for POP
  - '?' stands for SEARCH
  - '!' stands for DISPLAY
  
'+' and '?' are always followed by a number.

<b> <h3> Output:- </h3> </b>

Each line in the output file has the operation performed corresponding to that line in the input file.


<b> <h3> Commands to execute the code on Google Colab:- </h3> </b>

!gcc Stack_using_SLL.c

!./a.out input.txt <b> stack_size </b>

!diff -w output.txt stack.txt
