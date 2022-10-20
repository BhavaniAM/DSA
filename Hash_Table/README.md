<h1> Find the anagrams of the given strings using Hashing </h1>


Hash the words present in words.txt using the sum of the ASCII values of the characters in the string as the hash function and open hashing, more specifically, chaining as the technique for collision resolution. Find the anagrams of each query (string) in query.txt from the hash table.

<b> Input:- </b>

words.txt - one word at each line

query.txt - one word at each line

<b> Output:- </b>

anagrams.txt - Each line k has the anagrams associated with the string at line k in the query.txt file.

<b> Commands to execute the code on Google Colab:- </b>

!gcc Hashing_With_Chaining.c

!./a.out words.txt 25000 query1.txt

!diff -w anagrams.txt anagrams1.txt
