# C-Hash-Table
Implementation of a dictionary-style hash table in C.


#### How do I use it?
_Installing_

Download hash_table.c and hash_table.h. Be sure to `#include "hash_table.h"` in your main file, and put hash_table.c and hash_table.h in the same folder as your project so the compiler can find them.

When compiling, be sure to include hash_table.c, e.g. `gcc -Wall -o main main.c hash_table.c`. A simple makefile is included to look at if you are so inclined.

N.b.: Currently, the hash table only accepts character pointers for key and value. Expanding on that functionality is on my to-do list.

_How to hash_

Create a new hash table with `new = new_ht();`. 

To insert a key-value pair into new, or to reassign the value for a key already in your hash table, use `hash_insert(new, key, value);`. 

To search by key, use `hash_search(new, key);`. This will return a pointer to the associated value if the key exists in the hash table. Otherwise, it will printf a notice that the key does not exist and return a NULL pointer.

To delete a key, use `hash_delete(new, key)`. This will delete the key-value pair if it exists in the hash table. Otherwise, it will printf a notice that the key did not exist. 

If you're curious about the current size of the table, `hash_size(new)` will printf the current size of new's array and the number of items currently in that array. Its return value is the number of items in the array. 


#### Technical details
Starting table size is 16 elements. Once a table is 75% full it doubles in size. Once it drops below 25% full it halves in size. Collisions are resolved via linked lists. 

Hashing is done by multiplying the value of each character by its index in the string (+1), summing all these values, modulo by a large prime (337), and then modulo by the table size. 


#### Next steps
Expanding the functionality so the table can take in different variable types as keys and values is high on the list. Beyond that, general refactoring to improve the speed and readability of the code, and adding additional features, e.g. a set which just takes keys, without values.


#### I have suggestions/I have a bug to report/I want to help
Wow, great! Just leave a comment or make a pull request. 
