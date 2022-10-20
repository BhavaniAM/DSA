<h1> Implementation of BST operations </h1>

Operations:-

Insert, inorder, preorder, postorder, search, minimum, maximum, successor, predecessor

At any point of time the BST only has distinct numbers.

<b> Input:- </b>

Each line in the input file has one of the following lines which specify the operation to be performed.

insert <b> number </b>
  
search <b> number </b>
  
inorder
  
preorder
  
postorder
  
minimum
  
maximum
  
successor <b> number </b>
  
predecessor <b> number </b>
  
<b> Output:- </b>
  
The output file bst.txt has the result of the corresponding operation performed.

<b> number </b> inserted
  
<number> found/ <b> number </b> not found
  
inorder sequence of numbers / blank line for empty BST
  
preorder sequence of numbers / blank line for empty BST
  
postorder sequence of numbers / blank line for empty BST
  
<minimum number> / blank line for empty BST
  
<maximum number> / blank line for empty BST
  
<b> successor </b> / <b> number </b> does not exist / <b> successor </b> of number does not exist (if the number is the maximum element)
  
<b> predecessor </b> / <b> number </b> does not exist / <b> predecessor </b> of number does not exist (if the number is the minimum element)


<b> Commands to execute the code on Google Colab </b>

!gcc BST.c

!./a.out input1.txt

!diff -w bst.txt bst1.txt
