<h1> Implementation of BST operations </h1>

Operations:-

Insert, inorder, preorder, postorder, search, minimum, maximum, successor, predecessor

At any point of time the BST only has distinct numbers.

<b> Input:- </b>

Each line in the input file has one of the following lines which specify the operation to be performed.

insert <number>
  
search <number>
  
inorder
  
preorder
  
postorder
  
minimum
  
maximum
  
successor <number>
  
predecessor <number>
  
<b> Output:- </b>
  
The output file bst.txt has the result of the corresponding operation performed.

<number> inserted
  
<number> found/ <number> not found
  
inorder sequence of numbers / blank line for empty BST
  
preorder sequence of numbers / blank line for empty BST
  
postorder sequence of numbers / blank line for empty BST
  
<minimum number> / blank line for empty BST
  
<maximum number> / blank line for empty BST
  
<successor> / <number> does not exist / <successor> of number does not exist (if the number is the maximum element)
  
<predecessor> / <number> does not exist / <predecessor> of number does not exist (if the number is the minimum element)


<b> Commands to execute the code on Google Colab </b>

!gcc BST.c

!./a.out input1.txt

!diff -w bst.txt bst1.txt
