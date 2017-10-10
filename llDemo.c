#include <stdio.h>		/* for printf */
#include <stdlib.h>		/* for free() */
#include <ctype.h>		/* for */
#include <string.h> 	/* for strlen */
#include "llist.h"		/* for list operations */


/* read no more than limit chars into s, return #chars read.  Doesn't include trailing \n */
int gets_n(char *s, int limit)	
{
  char *p = s;			/* for indexing into s */
  char c;
  if (fgets(s, limit, stdin)) {
    while ((c = *p) && c != '\n') /* scan p through s until 0 or \n */
      p++;
    if (c == '\n')		/* erase \n */
      *p = 0;
  }
  return (p - s);		/* #chars read (not including terminator or \n*/
}

int get_one(char *s, int limit){
  char *p = s;
  char c;
  while( (getchar()) != EOF ){
    c = *p;
    p++;
  }
  *p = 0;
  return 0;
    
}


int menu(){
  printf("---MENU---\n");
  printf("0 \tmenu\n");
  printf("1 \tprepend\n");
  printf("11\tprint list\n");
  printf("-1\tquit\n");
  return 0;
}

int main(){

  char buf[100];
  LList *lp = llAlloc();	/* make empty list */

  //Menu Input
  char input[3]; //from 0-9
  int command = 0; //parsed

  menu();
  do{

    int len, i, max;
    printf("Enter Command to use\n");
    fgets(input,3,stdin);

    len = max = strlen(input) -1;
    max = atoi(3);
    if(len>max){
      printf("Two words\n");
      return 1;
    }
    
    //Check the input is a number
    for(i=0; i <len; i++){
      if( input[0] == '-') continue;
      if( !isdigit( input[i]) ){
        printf("La estas cagando\n");
        return 1;
      }
    }

    command = atoi(input);
    printf("You have used: %d\n",command);
    
  }while( command != -1);
  /**do{
    scanf("%d",command);
    switch(command){
    case 0:{
      menu();
      break;
    }
    case 1:{
      printf("Please enter numbers to prepend\n");
      while(gets_n(buf, 100))
        llPut(lp, buf);
      break;
    }
    case 11:{
      llPrint(lp, "List contents, prior to reading input:");
      break;
    }
    case -1:{
      break;
    }
    default:{
      printf("invalud default case\n");
    }
    }//end switch
  }while(command != -1);

  printf("menu has ended\n"); */
  
  while (gets_n(buf, 100))	/* build list */
    llPut(lp, buf);
  llPrint(lp, "List contents, prior to reading input:");


  llPrint(lp, "List contents, after building list:");

  llMakeEmpty(lp);

  printf("After emptying the list...");
  llPrint(lp, 0);		/* default message */

  llFree(lp);

  return 0;
}
