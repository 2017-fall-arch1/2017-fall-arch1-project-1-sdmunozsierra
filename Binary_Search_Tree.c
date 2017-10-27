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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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
	printf("Created: %s\n", str); //Print created node
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
	int result = cmp(key, root->name); //get key

    if (root == NULL || result == 0){
    	printf("FOUND: %s\n",root->name);  //FoundQ
    	return root;
    }
    else if(result < 0){ 			//Go to left
    	if(root->left == NULL){
    		printf("NOT FOUND: %s\n", key); //Not found
    		return root;
    	}
    	return search_node(root->left, key, cmp);
    }
    if(root->right == NULL){
    	printf("NOT FOUND: %s\n",key); //Not found
    }
    return search_node(root->right, key, cmp);
}

/** Remove a node. It is a modified version of search*/
node * remove_node(node* root, char* key, Compare cmp){
	int result;
	result = cmp(key, root->name); //get result

	if(root == NULL ){
    	printf("Deleted: %s\n",root->name); //Found and deleted
		return root;
	}

	else if(result<0){
		if(root->left == NULL) //not found can't delete
    		printf("Can't Delete, ie was not found: %s\n", key);
		root->left = remove_node(root->left, key, cmp); //recursion
	}

	else if(result>0){
		if(root->right == NULL) //not found can't delete
    		printf("Can't Delete, ie was not found: %s\n", key);
		root->right = remove_node(root->right, key, cmp); //recursion
	}

	//Found!
	else if(result == 0){
		if(root ->left == NULL){
			printf("Deleted: %s\n",root->name);
			node* temp = root->right;
			free(root); //Free memory
			return temp;
		}
		else if(root ->right == NULL){
			printf("Deleted: %s\n",root->name);
			node* temp = root->left;
			free(root); //Free memory
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

/* File Methods */
/** Check for a valid input file */
int check_file(char *filename){
	struct stat statbuf; //Create a statbuf
	FILE *fb = fopen(filename, "r"); //Open as read

	if(fb==NULL) //There is no file
	    printf("Selected path is NULL\n");
	else
	    printf("Selected path is not NULL\n");

	//Check if the path is either a dir or a file
	stat(filename, &statbuf);
	if(S_ISDIR(statbuf.st_mode))
	    printf("Path is a Directory\n");
	else
	    printf("Path is a File\n");
	return 0; //End
}

/** Read a file and add the contents to the bst */
node * read_file(node* root, char *fn, Compare cmp){

	FILE *fp = fopen(fn, "r"); //open file
	char lb[BUFSIZ]; //Get the buffer size
	int len; //Keep length size

	//While there are lines continue inserting new names
	while (fgets(lb, sizeof(lb), fp)) {
		len = strlen(lb);
		if(lb[len-1] == '\n') //Looks for annoying new lines
		    lb[len-1] = 0;
		root = insert(root, lb, cmp); //Insert
	}

	fclose(fp); //Close file
	return root; //Return root
}
/** Append to open file */
void append(node* root){
	char *fn ="/home/keanue/Data/Git/2017-fall-arch1-project-1-sdmunozsierra/test.txt";
	FILE *f = fopen(fn, "a");

	node* curr = root;
	if (curr != NULL){
		fprintf(f,"%s\n", curr->name);
	}
	fclose(f);
	if (curr != NULL){
		append(curr->left);
		append(curr->right);
	}
}

/** Write to file */
int write_file(node* root, char *filename){
	FILE *f = fopen(filename, "w");

	fclose(f);
	append(root);

	return 0;
}

/** Display the menu (user interface) */
void menu(){
	printf("\nWelcome to ACME Solutions\n");
	printf("------------------------------\n");
	printf("Press i  to insert an element\n");
	printf("Press s  to search an element\n");
	printf("Press d  to delete an element\n");
	printf("------------------------------\n");
	printf("Press r  to read from file\n");
	printf("Press w  to write tree to file\n");
	printf("------------------------------\n");
	printf("Press p  to print tree inorder\n");
	printf("Press q  to quit\n");
	printf("------------------------------\n");
}

/** Main  */
int main(){
	//Create root
	node* root = NULL;
	char a;
	char name[40];
	int start = 0;
	char *filename = "/home/keanue/Data/Git/2017-fall-arch1-project-1-sdmunozsierra/test.txt";
	//check_file(filename); //Check for a valid file

	//display menu
	menu();
	beggin:

	printf("Input an option: ");
	do { //Grab last char user input
	    a = getchar();
	} while(a!='q' && a!='i' && a!='s' && a!='p' && a!='d' && a!='r' && a!='w');

	//These do not need input name
	if(a=='p'|| a=='q'|| a=='r'|| a=='w')
		goto cont;

	//Enter a user input name to work with
	printf("\nEnter a name to work with: \n");
	scanf("%s", name);
	printf("Name: %s\n", name);

	cont:
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
	    case 'r':
	    	printf("Reading from file %s\n",filename);
	    	root = read_file(root, filename, (Compare)compare_string);
	      break;
	    case 'w':
	    	printf("Writting to file %s\n",filename);
	    	write_file(root, filename);
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

	printf("End..:\n");
	return 0;
}
