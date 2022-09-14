#include <stdio.h>
#include <stdlib.h>

struct node
{
  int key;
  struct node* left;
  struct node* right;
};

// A utility function to create a new BST node
struct node* newNode(int key){
  // Allocate memory for new node
  struct node* node = (struct node*)malloc(sizeof(struct node));

  node->key = key;
  node->left = NULL;
  node->right = NULL;

  return node;
}

// function to insert a new node with given key in BST
struct node* insert(struct node* node, int key){
  // If we reach a NULL pointer, this is the place to insert
  if (node == NULL)
  	return newNode(key);
  // otherwise, recur down the tree
  if (key < node->key)
  	node->left = insert(node->left, key);
  else if (key > node->key)
  	node->right = insert(node->right, key);
  else
  	printf("Key %d is already present!\n", key);
  // Return the (unchanged) node pointer
  return node;
}

void inorder(struct node* root)
{
	if (root == NULL)
	  return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
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

// int getMin(struct node* node){
//   if(node->left != NULL)
//     return getMin(node->left);
//   else
//     return node->key;
// }

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
  	return node;
}

// Main code
int main()
{
	struct node* root = NULL;
  root = insert(root, 51);
  insert(root, 43);
  insert(root, 93);
  insert(root, 18);
  insert(root, 42);
  insert(root, 99);
  insert(root, 54);
  insert(root, 2);
  insert(root, 74);
  insert(root, 74);

  // print inoder traversal of the BST
  inorder(root);
  printf("\n");
  // print inorder traversal of the BST with level information
  printTree(root, 0);
  printf("\n");
  // print max element of the tree
  printf("Max: %d\n", getMax(root));
  // print min element of the tree
  printf("Min: %d\n", getMin(root)->key);
  // Delete node (2)
  root = delete(root, 2);
  // print inorder traversal of the BST with level information
  printTree(root, 0);
  printf("\n");
  // Delete node (18)
  root = delete(root, 18);
  // print inorder traversal of the BST with level information
  printTree(root, 0);
  printf("\n");
  // Delete node (51)
  root = delete(root, 51);
  // print inorder traversal of the BST with level information
  printTree(root, 0);
  printf("\n");

	return 0;
}