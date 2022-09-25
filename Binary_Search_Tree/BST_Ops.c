%%writefile 190020011.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// file pointers to read and write
FILE *fp_read, *fp_write;

// structure for a node in the tree
struct BST
{
  int data;
  struct BST *left;
  struct BST *right;
};

// declare the functions used 
struct BST *insert_BST_node(struct BST *root, int val);

void traverse_postorder(struct BST *root);
void traverse_preorder(struct BST *root);
void traverse_inorder(struct BST *root);

void find_min_ele(struct BST *node);
void find_max_ele(struct BST *node);

int search_BST(struct BST *temp, int val);

struct BST* createNode(int val) ;

int main(int argc, char* argv[])
{
  struct BST *root = NULL;
  fp_write = fopen("bst.txt", "w");
  fclose(fp_write);

  int MAX_LEN = 1000000;
  char string[MAX_LEN];
  int count = 0, num_inst = 0;

  // read the file
  fp_read = fopen(argv[1], "r");
  if(fp_read == NULL)
	{
		printf("Error: Could not find the file");
		exit(0);
	}
  while(fgets(string, MAX_LEN, fp_read) != NULL)
  {
    int l = strlen(string), i;
    char count_inst[MAX_LEN];

    // to read the first word in the sentence to know what operation to perform
    for(i = 0; i < l; i++)
    {
      if(string[i] == ' ')
        break;
      else
        count_inst[i] = string[i];
    }

    // check the first 4 letters of each operation (4 are enough as the words are different)
    if(count_inst[0] == 'i' && count_inst[1] == 'n' && count_inst[2] == 's' && count_inst[5] == 't')
    {
      num_inst++;
    }
  }

  int a[num_inst];
  rewind(fp_read);

  while(fgets(string, MAX_LEN, fp_read) != NULL)
  {
    int l = strlen(string), new_num = 0, i, j;
    char word[MAX_LEN];

    // to read the first word in the sentence to know what operation to perform
    for(i = 0; i < l; i++)
    {
      if(string[i] == ' ')
        break;
      else
        word[i] = string[i];
    }

    // check the first 4 letters of each operation (4 are enough as the words are different)
    if(word[0] == 'i' && word[1] == 'n' && word[2] == 's' && word[5] == 't')
    {
      // convert the number from string to int
      for(j = i + 1; j < l - 1; j++)
      {
        new_num = new_num * 10;
        new_num += (string[j] - '0');
      }
      // store all the inserted elements in an array. Not sorted. This is used to find the predecessor and the successor. 
      // Based on the idea of using inorder traversal of BST to find predecessor and successor.
      a[count] = new_num;
      count++;
      root = insert_BST_node(root, new_num);
      fp_write = fopen("bst.txt", "a");
      fprintf(fp_write, "%d inserted\n", new_num);
      fclose(fp_write);
    }

    else if(word[0] == 'p' && word[1] == 'o' && word[2] == 's' && word[3] == 't')
    {
      traverse_postorder(root);
      fp_write = fopen("bst.txt", "a");
      fprintf(fp_write, "\n");
      fclose(fp_write);
    }

    else if(word[0] == 'p' && word[1] == 'r' && word[2] == 'e' && word[3] == 'o')
    {
      traverse_preorder(root);
      fp_write = fopen("bst.txt", "a");
      fprintf(fp_write, "\n");
      fclose(fp_write);
    }

    else if(word[0] == 'm' && word[1] == 'i' && word[2] == 'n' && word[3] == 'i')
    {
      find_min_ele(root);
      fp_write = fopen("bst.txt", "a");
      fprintf(fp_write, "\n");
      fclose(fp_write);
    }

    else if(word[0] == 'm' && word[1] == 'a' && word[2] == 'x' && word[3] == 'i')
    {
      find_max_ele(root);
      fp_write = fopen("bst.txt", "a");
      fprintf(fp_write, "\n");
      fclose(fp_write);
    }

    else if(word[0] == 's' && word[1] == 'e' && word[2] == 'a' && word[3] == 'r')
    {
      for(j = i + 1; j < l - 1; j++)
      {
        new_num = new_num * 10;
        new_num += (string[j] - '0');
      }
      int x = search_BST(root, new_num);
      fp_write = fopen("bst.txt", "a");
      if(x == 1)
        fprintf(fp_write, "%d found", new_num);
      else
        fprintf(fp_write, "%d not found", new_num);
      fprintf(fp_write, "\n");
      fclose(fp_write);
    }

    else if(word[0] == 'p' && word[1] == 'r' && word[2] == 'e' && word[3] == 'd')
    {
      for(j = i + 1; j < l - 1; j++)
      {
        new_num = new_num * 10;
        new_num += (string[j] - '0');
      }
      // checks each element in the array. If it matches the element we are looking for then it finds the next smallest element
      // if our element is the smallest in the array then there is no predecessor
      int min = a[0];
      int check = 0, flag = 0, outer_f = 0;
      for(int m = 0; m < count; m++)
      {
        if(a[m] == new_num)
        {
          outer_f = 1;
          for(int k = 0; k < count; k++)
          {
            if(a[k] < new_num)
            {
              flag = 1;
              if(check == 0)
              {
                check++;
                min = a[k];
              }
              else
              {
                if(a[k] > min)
                min = a[k];
              }
              }
            }
            if(!flag)
            {
              fp_write = fopen("bst.txt", "a");
              fprintf(fp_write, "predecessor of %d does not exist\n", new_num);
              fclose(fp_write);
            }
            else
            {
              fp_write = fopen("bst.txt", "a");
              fprintf(fp_write, "%d\n", min);
              fclose(fp_write);
            }
          }
        }
        if(!outer_f)
        {
          fp_write = fopen("bst.txt", "a");
          fprintf(fp_write, "%d does not exist\n", new_num);
          fclose(fp_write);
        }
      //find_predecessor(root, new_num);
    }

    else if(word[0] == 'i' && word[1] == 'n' && word[2] == 'o' && word[3] == 'r')
    {
      traverse_inorder(root);
      fp_write = fopen("bst.txt", "a");
      fprintf(fp_write, "\n");
      fclose(fp_write);
    }

    else if(word[0] == 's' && word[1] == 'u' && word[2] == 'c' && word[3] == 'c')
    {
      for(j = i + 1; j < l - 1; j++)
      {
        new_num = new_num * 10;
        new_num += (string[j] - '0');
      }
      // checks each element in the array. If it matches the element we are looking for then it finds the next largest element
      // if our element is the largest in the array then there is no successor
      int max = a[0];
      int check = 0, flag = 0, outer_f = 0;
      for(int m = 0; m < count; m++)
      {
        if(a[m] == new_num)
        {
          outer_f = 1;
          for(int k = 0; k < count; k++)
          {
            if(a[k] > new_num)
            {
              flag = 1;
              if(check == 0)
              {
                check++;
                max = a[k];
              }
              else
              {
                if(a[k] < max)
                max = a[k];
              }
              }
            }
            if(!flag)
            {
              fp_write = fopen("bst.txt", "a");
              fprintf(fp_write, "successor of %d does not exist\n", new_num);
              fclose(fp_write);
            }
            else
            {
              fp_write = fopen("bst.txt", "a");
              fprintf(fp_write, "%d\n", max);
              fclose(fp_write);
            }
          }
        }
        if(!outer_f)
        {
          fp_write = fopen("bst.txt", "a");
          fprintf(fp_write, "%d does not exist\n", new_num);
          fclose(fp_write);
        }
    }
  }
  fclose(fp_read);
  return 0;
}

struct BST* createNode(int val) 
{
  struct BST*  new_Node = (struct BST*)malloc(sizeof(struct BST));;
  new_Node -> data = val;
  new_Node -> left = NULL;
  new_Node -> right = NULL;

  return new_Node;
}

struct BST *insert_BST_node(struct BST *root, int val)
{
  if(root == NULL)
  {
    root = createNode(val);
    return root;
  }
  if (val < root -> data)
    root -> left = insert_BST_node(root ->left, val);
  else if (val > root -> data)
    root -> right = insert_BST_node(root -> right, val);
  return root;
}

void traverse_preorder(struct BST *root)
{
  if(root!= NULL)
  {
    fp_write = fopen("bst.txt", "a");
    fprintf(fp_write, "%d ", root -> data);
    fclose(fp_write);
    traverse_preorder(root -> left);
    traverse_preorder(root -> right);
    fclose(fp_write);
  }
}

void traverse_inorder(struct BST *root)
{
  if(root != NULL)
  {
    traverse_inorder(root -> left);
    fp_write = fopen("bst.txt", "a");
    fprintf(fp_write, "%d ", root -> data);
    fclose(fp_write);
    traverse_inorder(root -> right);
    fclose(fp_write);
  }
}

void traverse_postorder(struct BST *root)
{
  if(root != NULL) 
  {
    traverse_postorder(root -> left);
    traverse_postorder(root -> right);
    fp_write = fopen("bst.txt", "a");
    fprintf(fp_write, "%d ", root -> data);
    fclose(fp_write);
  }
}

void find_min_ele(struct BST *node)
{
  if(node != NULL)
  {
    while(node -> left != NULL)
      node = node -> left;
    fp_write = fopen("bst.txt", "a");
    fprintf(fp_write, "%d", node -> data);  
    fclose(fp_write);
  }
}

void find_max_ele(struct BST *node)
{
  if(node != NULL)
  {
    while(node -> right != NULL)
      node = node -> right;
    fp_write = fopen("bst.txt", "a");
    fprintf(fp_write, "%d", node -> data);  
    fclose(fp_write);
  }
}

int search_BST(struct BST *temp, int val)
{
  while(temp != NULL)
  {
    if(val == temp -> data)
      return 1;
    else if(val < temp -> data)
      temp = temp -> left;
    else
      temp = temp -> right;
  }
  return 0;
}
