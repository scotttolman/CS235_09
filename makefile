###############################################################
# Program:
#     Assignment 09, Binary Search Tree
#     Brother XXXXX, CS265
# Author:
#     <your name here>
# Summary:
#     <put a description here>
# Time:
#     <how long did it take to complete this program>?
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment09.o
	g++ -o a.out assignment09.o -g
	tar -cf assignment09.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment09.o     : the driver program
##############################################################
assignment09.o: bnode.h bst.h stack.h assignment09.cpp sortBinary.h
	g++ -c assignment09.cpp -g

