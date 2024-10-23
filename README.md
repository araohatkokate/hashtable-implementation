# Hash Table Implementation with Chaining

## Description
This project implements a hash table in C++ using the multiplication and division method for the hash function. The hash table supports dynamic resizing (growing and shrinking) based on load factors, and resolves collisions using chaining with a custom doubly linked list. For simplicity, the keys and values are integers, and the hash table is implemented using C-style arrays.

## Features
- Multiplication and division hash function
- Collision resolution using chaining (doubly linked list)
- Dynamic resizing: 
  - Doubles the size when the load factor exceeds 0.75
  - Shrinks when the load factor goes below 0.25
- Written using C++ with C-style arrays (no STL containers used)
  
## Requirements
- A C++ compiler (g++ recommended)
- Basic knowledge of compiling and running C++ programs

## Compilation Instructions
To compile the code, you can use any C++ compiler. Here's how to compile it using `g++`:

```bash
g++ -o hashtable hashtable_implementation.cpp
```
After compiling, run with command 
```bash
./hashtable
```
