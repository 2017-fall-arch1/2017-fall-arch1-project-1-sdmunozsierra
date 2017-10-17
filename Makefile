#CC=GCC
#CFLAGS=-g
#EXECS=Binary_Sarch_Tree.c

	
#clean:
#	rm -f *.o $(EXECS)

Binary_Search_Tree.o : Binary_Search_Tree.c 
	gcc Binary_Search_Tree.c -o bst

clean :
	rm -f *.o 
