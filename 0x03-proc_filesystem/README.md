# Intro to the */proc* filesystem

**Tasks**:  
0- Overwrite a string in a heap of a running process.  
To try it:  
- in a first terminal, run tests/infinite_loop   
From the source code infinite_loop.c  
`gcc -g -o infinite_loop infinite_loop.c` (-g if you want to use gdb)  
- in a second one, run read_write_heap.py as sudo.  
This script has 2 main functions, dev_main will do everything for you,
main is more versatile.  

1- Medium [post](https://medium.com/@anne75/journey-into-the-machine-proc-9388546befc6) companion to above script.  

