/*
 * Node.c - Has the structure for the Node containing data
 *
 *  Created on: Oct 14, 2017
 *      Author: Sergio David Munoz Sierra
 *      Git: sdmunozsierra
 */

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <string.h>

#define MAXLEN 10 //Max number of chars

/** Node structure
 * TODO Move to other file */
typedef struct node{
	char *name;  //Data to be stored
	struct node *left, *right;	//Pointer to left and right nodes
}node; //return struct node

/** Compare as a typedef */
typedef int (*Compare)(const char *, const char *);

/** Compares the value of two strings
 * TODO This can be a one liner */
int compare_string(const char *a, const char *b){
	return (strcmp (a,b));
}

/** Return the bottom left node (min value) */
node * get_min_node(node* root){
	node* curr = root; //curr point to root
	while(curr!=NULL) //Go to left most node
		curr = curr->left;
	return curr; //return that node
}

/** Create a Node
 * @parameter key Key to be inserted on the bst */
node * create_node(char* str){
	node* new_node = (node*)malloc(sizeof(node)); //alloc memory for node
	new_node->name = malloc( strlen (str) +1) ;   //memory for str (name)

	//Cannot create new node
	if(new_node == NULL){
		printf("Error Creating new Node ERR01. \n"); //ERR01
		exit(0); //0 used for error;
	}

	//Assign name value. Pointers to NULL
	strcpy (new_node->name, str); //Insert the str to name
	//new_node->name = str;
	new_node->left =  NULL;
	new_node->right = NULL;
	printf("Created: %s\n", str);
	return new_node; //return node
}

/** Insert a node */
node * insert(node* node, char* key, Compare cmp){
	int result; //Comparison result

	//Create a new root (node).
	if(node == NULL)
		return create_node(key);

	//Get the comparison
	result = cmp(key, node->name);
	//Insert recursive to the left
	if(result < 0)
		node->left = insert(node->left, key, cmp);
	//Insert recursive to the rigth
	else if(result > 0)
		node->right = insert(node->right, key, cmp);

	return node; //return the node
}

typedef int (*Search)(node *, char *, Compare *);

/** Search a node */
node * search_node(node* root, char* key, Compare cmp){
//	printf("Searching: %s\n", key);
	int result = cmp(key, root->name);

//	printf("RESULT: %d\n",result);

    if (root == NULL || result == 0){
    	printf("FOUND: %s\n",root->name);
    	return root;
    }
    else if(result < 0){
    	if(root->left == NULL){
    		printf("NOT FOUND: %s\n", key);
    		return root;
    	}
    	return search_node(root->left, key, cmp);
    }
    if(root->right == NULL){
    	printf("NOT FOUND: %s\n",key);
    }
    return search_node(root->right, key, cmp);
}
// C function to search a given key in a given BST
//struct node* search(struct node* root, int key)
//{
//    // Base Cases: root is null or key is present at root
//    if (root == NULL || root->key == key)
//       return root;
//
//    // Key is greater than root's key
//    if (root->key < key)
//       return search(root->right, key);
//
//    // Key is smaller than root's key
//    return search(root->left, key);
//}

///** Remove a node */
//node * remove(node* root, char* key, Compare cmp){
//	int result; //Comparison result
//
//	//Base case
//	if(root == NULL)
//		return root;
//
//	result = cmp(key, root->name);
//	//Remove recursive to the left
//	if(result < 0)
//		root->left = remove(root->left, key, cmp);
//
//	//Remove recursive to the right
//	else if(result > 0)
//		root->right = remove(root->right, key, cmp);
//
//	//The root is the node I am looking for
//	//3 cases
//	else{
//
//		//Case 1: node with at most one child
//		if(root->left == NULL){
//			node* temp = root->right;
//			free(root);
//			return temp;
//		}
//		else if (root->right == NULL){
//			node* temp = root->left;
//			free(root);
//			return temp;
//		}
//
//		//Case 2: node with 2 children
//		node* temp = get_min_node(root->left);
//
//		root->name = temp->name;
//
//		root->right = remove(root->right, temp->name, cmp);
//
//	}
//	return root;
//}

/* Traversals */
/** In order traversal recursive */
void inorder(node* root){
	node* curr = root;
	if (curr != NULL){
		inorder(curr->left);
		printf("   %s\n", curr->name);
		inorder(curr->right);
	}
}

/** Display the menu (user interface) */
void menu(){
	printf("\nMenu\n");
	printf("Press i to insert an element\n");
	printf("Press p to print tree in order\n");
	printf("Press q to quit\n");
}

int main(){
	//Create root
	node* root = NULL;
	Compare* cmp = (Compare)compare_string;
	//char *name;

	//TEST
	root = insert(root, "Henry",(Compare)compare_string);
	root = insert(root, "Max",(Compare)compare_string);
	root = insert(root, "50",(Compare)compare_string);
	root = insert(root, "30",(Compare)compare_string);
	root = insert(root, "HELLO",(Compare)compare_string);
	root = insert(root, "40",(Compare)compare_string);
	root = insert(root, "Sergio",(Compare)compare_string);
	printf("TREE:\n");
	inorder(root);
	root = insert(root, "COMPA",(Compare)compare_string);

	//SEARCH
	printf("Searching HELLO\n");
	search_node(root, "HELLO", cmp);
	printf("Searching NOT FOUND\n");
	search_node(root, "NOT FOUND", (Compare)compare_string);
	printf("TREE:\n");
	inorder(root);
	(Search)search_node;
	//(Search)(root, "HELLO", (Compare)compare_string);


//	search(root, "NOT FOUND", (Compare)compare_string);
//	search(root, "HELLO", (Compare)compare_string);
//	search(root, "30", (Compare)compare_string);
//
//	printf("TREE:\n");
//	inorder(root);
	menu();

	return 0;
}
