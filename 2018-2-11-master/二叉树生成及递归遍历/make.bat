echo on
gcc -c stack.c -o stack.o
gcc -c btree.c -o btree.o
gcc demo.c stack.o btree.o -o demo
