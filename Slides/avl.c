#include <stdio.h>
#include <stdlib.h>

struct node
{
  int key;
  int height;
  struct node* left;
  struct node* right;
};

// A utility function to create a new BST node
struct node* newNode(int key){
  // Allocate memory for new node
  struct node* node = (struct node*)malloc(sizeof(struct node));

  node->key = key;
  node->height = 0; // new node is initially added at leaf
  node->left = NULL;
  node->right = NULL;

  return node;
}

// Helper function to get the height of a node
int getHeight(struct node* node){
  // NIL nodes
  if (node == NULL)
  	return -1;
  // Regular nodes
  return node->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
  return (a>b)?a:b;
}

// Helper function for right rotate
struct node* rightRotate(struct node* prt){
  struct node* chd = prt->left;
  prt->left = chd->right;
  prt->height = 1 + max(getHeight(prt->left),getHeight(prt->right));
  chd->right = prt;
  chd->height = 1 + max(getHeight(chd->left),getHeight(chd->right));
  prt = chd;
  return prt;
}

// Helper function for left rotate
struct node* leftRotate(struct node* prt){
  struct node* chd = prt->right;
  prt->right = chd->left;
  prt->height = 1 + max(getHeight(prt->left),getHeight(prt->right));
  chd->left = prt;
  chd->height = 1 + max(getHeight(chd->left),getHeight(chd->right));
  prt = chd;
  return prt;
}

// The retrace function
struct node* retrace(struct node* node){
  // If NIL node no need to anything
  if(node == NULL)
  	return node;
  // If tree is left-heavy, needs rebalancing
  if((getHeight(node->left) - getHeight(node->right)) > 1){
  	// If left subtree is right-heavy, needs double rotation
  	if(getHeight(node->left->left) < getHeight(node->left->right))
  	  node->left = leftRotate(node->left);
  	node = rightRotate(node);
  }
  // If tree is right-heavy, needs rebalancing
  else if((getHeight(node->right) - getHeight(node->left)) > 1){
  	// If right subtree is left-heavy, needs double rotation
  	if(getHeight(node->right->left) > getHeight(node->right->right))
  	  node->right = rightRotate(node->right);
  	node = leftRotate(node);
  }
  // Adjust node's height
  node->height = 1 + max(getHeight(node->left),getHeight(node->right));
  return node;
}

// function to insert a new node with given key in AVL
struct node* insert(struct node* node, int key){
  // If we reach a NULL pointer, this is the place to insert
  if (node == NULL)
  	return retrace(newNode(key));
  // otherwise, recur down the tree
  if (key < node->key)
  	node->left = insert(node->left, key);
  else if (key > node->key)
  	node->right = insert(node->right, key);
  else
  	printf("Key %d is already present!\n", key);
  // Retrace
  node = retrace(node);
  // Return the (unchanged) node pointer
  return node;
}

void printTree(struct node* node, int level){
  if (node == NULL)
	return;

  printTree(node->left,level+1);
  printf("%d [%d] ", node->key, level);
  printTree(node->right,level+1);
}

int getMax(struct node* node){
  while(node->right != NULL)
	node = node->right;
  return node->key;
}

struct node* getMin(struct node* node){
  if(node->left != NULL)
	return getMin(node->left);
  else
	return node;
}

int contains(struct node* node, int query){
  if (node == NULL)
    return 0;
  if (query < node->key)
  	return contains(node->left, query);
  else if (query > node->key) 
  	return contains(node->right, query);
  else
  	return 1;
}

struct node* delete(struct node* node, int key){
	// key not found
  	if (node == NULL){return NULL;}
  	// otherwise, recur down the tree, if smaller then go left, otherwise right
  	if (key < node->key)
  		node->left = delete(node->left, key);
  	else if (key > node->key)
  		node->right = delete(node->right, key);
  	// if key is same as root->key, then this is the node to be deleted
  	else {
  		// if leaf node, remove it
  		if((node->left == NULL) && (node->right == NULL)){free(node); return NULL;}
  		// if node with left child only
  		else if((node->left != NULL) && (node->right == NULL)){struct node* temp = node->left; free(node); return temp;}
  		// if node with right child only
  		else if((node->left == NULL) && (node->right != NULL)){struct node* temp = node->right; free(node); return temp;}
  		// if two children: replace with min node in right subtree
  		if((node->left != NULL) && (node->right != NULL)){
  			struct node* temp = getMin(node->right);
  			node->key = temp->key;
  			// delete the min node in the right subtree
  			node->right = delete(node->right, temp->key);
  		}
  	}
  	// Retrace
  	node = retrace(node);
  	return node;
}

void changeValues (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffleRandon (int arr1[], int n)
{
    //srand ( time(NULL) );
    for (int i = n-1; i > 0; i--)
    {
        int j = rand() % (i+1);
        changeValues(&arr1[i], &arr1[j]);
    }
}

// Main code
int main()
{
  struct node* root = NULL;
  int a[] = {2, 18, 42, 43, 51, 54, 74, 93, 99};
  for(int i=0;i<9;i++){
  	root = insert(root, a[i]);
  	printTree(root, 0);
  	printf("\n");
  }

  // Delete node (54)
  root = delete(root, 54);
  printTree(root, 0);
  printf("\n");
  // Delete node (42)
  root = delete(root, 42);
  printTree(root, 0);
  printf("\n");
  // Delete node (2)
  root = delete(root, 2);
  printTree(root, 0);
  printf("\n");

  //==== The next part does a total of 100 insertions and deletions
  // and show that still the tree remains balanced. The code is written
  // hastily, so there can be pitfalls - especially the
  // 'while (!contains(root, keyDel))' - code can be a candidate for
  // infinite loop for different random number of insertions and deletions.
  // To run it, comment out the above and uncomment the parts
  // following this comment.
 //  //
 //  // Store integers from 0 to 149 in random order
 //  // This is done by reading from a txt file which
 //  // itself was generated by using python
 //  int original[150];
 //  int i = 0;
 //  FILE *file;
 //  file = fopen("randperm.txt", "r");
 //  for (int i=0; i<150; i++)
 //  {
 //    fscanf(file, "%d\n", &original[i]);
 //  }
 //  fclose(file);

 //  // First create a 9 node avl tree with the first 10 random numbers
 //  struct node* root = NULL;
 //  for(int i=0;i<9;i++){
 //  	root = insert(root, original[i]);
 //  }
 //  printTree(root, 0);
 //  printf("\n");

 //  // Initialize counter that will count total number of insertions
 //  // + total number of deletions
 //  int iInsDel = 0;
 //  // Initialize total number of keys inserted till now
 //  int numInsTotal = 8; // Actually 9 - last index of original that was inserted
 //  while (iInsDel<100){
	// // Perform 3 random deletions
	// int numDel = 3; //rand() % 4 + 1;
	// for(int i=0;i<numDel;i++){
	//   // Choose key to be deleted randomly
	//   int keyDel = original[rand() % (numInsTotal) + 0];
	//   // Check if it exists in the tree. If not then choose another one
	//   while (!contains(root, keyDel))
	//   	keyDel = original[rand() % (numInsTotal) + 0];
	//   root = delete(root, keyDel);
	// }
 //    // Increase number of insert/deletion counter
 //    iInsDel += numDel;

 //    // Perform 3 random insertions
 //    int numIns = 3;
 //    for(int i=numInsTotal+1;i<numInsTotal+1+numIns;i++){
 //  	  // Insert element from the original array which is random
 //  	  root = insert(root, original[i]);
 //    }
 //    // Update numInsTotal
 //    numInsTotal += numIns;

 //    // Increase number of insert/deletion counter
 //    iInsDel += numIns;
 //  }
 //  printf("iInsDel: %d\n", iInsDel);
 //  printTree(root, 0);
 //  printf("\n");

  return 0;
}