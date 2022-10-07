%%writefile Hashing_With_Chaining.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define the structure and create a hash_table which is an array of pointers

struct node
{
  char* data;
  struct node* next;
};
struct node* hash_table[25000];

// define all file pointers
FILE *fp_read_word, *fp_write, *fp_read_query;

// declare the functions
int calc_hash(char* word, int hash_size);
void find_ana(char *word, int hash_slot);
void insert_into_table(char* word, int hash_slot);

// main program
int main(int argc, char* argv[])
{
  int i, hash_slot;
  char string[50];

  // read file if it exists
  fp_read_word = fopen(argv[1], "r");
  
  if(fp_read_word == NULL)
	{
		printf("Error: Could not find the file");
		exit(0);
	}

  // take the argument for the hash table size
  int hash_size = atoi(argv[2]);
  
  for (i = 0; i < hash_size; i++) 
    hash_table[i] = NULL;
  
  // read each word from words.txt and store it in the hash table 
  while(fscanf(fp_read_word, "%s ", string) != EOF)
  {
    hash_slot = calc_hash(string, hash_size);
    insert_into_table(string, hash_slot);
  }
  fclose(fp_read_word);

  fp_write = fopen("anagrams.txt", "w");
  fclose(fp_write);

  // read file if it exists
  fp_read_query = fopen(argv[3], "r");
  if(fp_read_query == NULL)
	{
		printf("Error: Could not find the file");
		exit(0);
	}

  // check for the anagrams of the word in the hash table
  while(fscanf(fp_read_word, "%s ", string) != EOF)
  {
    hash_slot = calc_hash(string, hash_size);
    find_ana(string, hash_slot);
  }

  fclose(fp_read_query);
  return 0;
}

void insert_into_table(char* word, int hash_slot)
{   
  struct node *newnode=(struct node *)malloc(sizeof(struct node));

  newnode -> data = (char*)malloc(strlen(word) + 1);
  strcpy(newnode -> data, word);

  newnode->next = hash_table[hash_slot];
  hash_table[hash_slot] = newnode;
}

int calc_hash(char* word, int hash_size)
{ 
  int x, sum = 0, i, l = strlen(word);
  for(i = 0; i < l; i++)
  {
    x = word[i];
    sum = sum + x;
  }
  return (sum % hash_size);
}

void find_ana(char* string1, int hash_slot)
{
  // store the frequency of each character and compare the frequency of each character in both the strings
  struct node* temp = hash_table[hash_slot];
  fp_write = fopen("anagrams.txt", "a");
  char *string2;
  while(temp)
  {
    int x, flag = 0;
    char *string2;
    string2 = temp -> data;
    if(strlen(string1) != strlen(string2))
    {
      temp = temp -> next;
      continue;
    }
    else
    {
      int size = 255;
      int i, freq1[size], freq2[size], l = strlen(string1);
      for(i = 0; i < size; i ++)
      {
        freq1[i] = 0;
        freq2[i] = 0;
      }
      for(i = 0; i < l; i ++)
      {
        x = string1[i];
        freq1[x] ++;

        x = string2[i];
        freq2[x] ++;
      }
      for(i = 0; i < size; i++)
      {
        if(freq1[i] != freq2[i])
        {
          flag = 1;
          break;
        }
      }
    } 
    if(flag == 0)
    {
      fprintf(fp_write, "%s ", string2);
    }
    temp = temp -> next;
  }
  fprintf(fp_write, "\n");
  fclose(fp_write);
}
