/*
 * Node.c - Has the structure for the Node containing data
 *
 *  Created on: Oct 14, 2017
 *      Author: Sergio David Munoz Sierra
 *      Git: sdmunozsierra
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//typedef int (*Search)(node *, char *, Compare *);

/** Search a node */
node * search_node(node* root, char* key, Compare cmp){
	int result = cmp(key, root->name);

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

/** Remove a node. It is a modified version of search*/
node * remove_node(node* root, char* key, Compare cmp){
	int result;
	result = cmp(key, root->name);

	if(root == NULL ){
    	printf("Deleted: %s\n",root->name);
		return root;
	}

	else if(result<0){
		if(root->left == NULL)
    		printf("Can't Delete, ie was not found: %s\n", key);
		root->left = remove_node(root->left, key, cmp);
	}

	else if(result>0){
		if(root->right == NULL)
    		printf("Can't Delete, ie was not found: %s\n", key);
		root->right = remove_node(root->right, key, cmp);
	}

	//Found!
	else if(result == 0){
		if(root ->left == NULL){
			printf("Deleted: %s\n",root->name);
			node* temp = root->right;
			free(root);
			return temp;
		}
		else if(root ->right == NULL){
			printf("Deleted: %s\n",root->name);
			node* temp = root->left;
			free(root);
			return temp;
		}
	}

	return root;
}

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
	printf("\nWelcome to ACME Solutions\n");
	printf("Press i  1 to insert an element\n");
	printf("Press s  2 to search an element\n");
	printf("Press d  3 to delete an element\n");
	printf("Press p  4 to print tree in order\n");
	printf("Press q  0 to quit\n");
}

/** Main  */
int main(){
	//Create root
	node* root = NULL;
	char a;
	char name[40];
	int start = 0;
//	Compare *cmp = compare_string;
//	Compare *cmp ;

	//TEST Compare without typedef
	root = insert(root, "Henry",(Compare)compare_string);
	root = insert(root, "Max",(Compare)compare_string);
	root = insert(root, "50",(Compare)compare_string);
	root = insert(root, "30",(Compare)compare_string);
	root = insert(root, "HELLO",(Compare)compare_string);
	root = insert(root, "40",(Compare)compare_string);
	root = insert(root, "Sergio",(Compare)compare_string);
	root = insert(root, "COMPA",(Compare)compare_string);

	//SEARCH
	printf("Searching HELLO\n");
	search_node(root, "HELLO", (Compare)compare_string);
	printf("Searching NOT FOUND\n");
	search_node(root, "NOT FOUND", (Compare)compare_string);

	//REMOVE
	root = remove_node(root, "HELLO", (Compare)compare_string);
	root = insert(root, "Some",(Compare)compare_string);
	root = insert(root, "1",(Compare)compare_string);
	root = remove_node(root, "1", (Compare)compare_string);
	root = remove_node(root, "COMPA", (Compare)compare_string);
	root = remove_node(root, "Sergio", (Compare)compare_string);

	//display menu
	menu();
	beggin:

	do { //Grab last char user input
	    printf("Input an option: ");
	    a = getchar();
	} while(a!='q' && a!='i' && a!='s' && a!='p' && a!='d');

	printf("\nEnter a name to work with: \n");
	scanf("%s", name);
	printf("Name: %s\n", name);

	switch(a) {
	    case 'i':
	    	printf("Inserting...\n");
	    	root = insert(root, name, (Compare)compare_string);
	      break;
	    case 'd':
	    	printf("Removing...\n");
	    	root = remove_node(root, name, (Compare)compare_string);
	      break;
	    case 's':
	    	printf("Searching...\n");
	    	search_node(root, name, (Compare)compare_string);
	      break;
	    case 'p':
	    	printf("Display tree:\n");
	    	inorder(root);
	      break;
	    case 'q':
	    	printf("Exiting...\n");
	    	start = 1;
	      break;
	}

	while(start != 1)
		goto beggin;
//	}

	printf("End..:\n");
	//inorder(root);
	return 0;
}
