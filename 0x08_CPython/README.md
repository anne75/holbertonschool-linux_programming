# CPython

Create shared library in C to be used in python code.  
compiled such as:  
```
gcc -Wall -Werror -Wextra -pedantic -std=c99 -shared -Wl,-soname,PyList -o libPyList.so -fPIC -I/usr/include/python3.4 1-python.c
```
