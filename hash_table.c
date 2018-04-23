#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "hash_table.h"
#define MODULO 337

// int main() {
//     return 0;
// }

/* Things to add:
1) find_key_in_hash_table() function. We're searching for a key in the hash table
in the insert, delete, and search functions. All three of those functions could
just call a single function which returns a pointer to the K_V_Pair if the key
does exist, and NULL otherwise. -- DONE --
2) Freeing! We gotta free more than just a K_V_Pair. We should also free
the key and value themselves. Make a free_all() function, call that instead of
free.
*/

Hash_Table* hash_table() {
    Hash_Table *new;
    new = (Hash_Table*) malloc(sizeof(Hash_Table));

    new->cur_size = hash_size;
    new->cur_items = 0;
    new->entries = calloc((size_t) hash_size, sizeof(K_V_Pair*));

    return new;
}


int hash_index(char* key, int size) {
    int hash = 0;
    int k_index = 1;
    int index = 0;

    while (*key) {
        index += (int) *(key)++ * k_index++;
    }
    int index = (index % MODULO) % size;
    return index;
}

void resize(Hash_Table* dict) {
    // resizes dict, either doubling it if current items >= 75% of dict size,
    // or halfing it if current items <= 25% of dict size. Reassigns indices
    // based on current size.
    if (dict->cur_size > 3 * dict->cur_items) {
        hash_size = dict->cur_size / 2; // change hash size for resizing purposes.
    } else if (dict->cur_items * 4 >= dict->cur_size * 3){
        hash_size = dict->cur_size * 2;
    } else {
        printf("Error. Resize should not have been called.");
        return;
    }
    Hash_Table* new_dict = hash_table();
    for (int i = 0; i < dict->cur_size; ++i) {
        K_V_Pair *current = dict[i];
        while (current) {
            K_V_Pair *next = current->next;
            int new_index = hash_index(current->key, new_dict->size);
            current->next = NULL;
            current->prev = NULL;
            assign_index(new_dict, current, new_index);
            current = next;
        }
    }
    free(dict);
    hash_size = 16; // reset hash size to default for a new hash.
    return new;
}

K_V_Pair* new_dict_entry(char *key, char *value) {
    // creates a new key-value pair.
    K_V_Pair* new;
    new = (K_V_Pair*) malloc(sizeof(K_V_Pair));
    new->key = key;
    new->value = value;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

void insert(Hash_Table* dict, char* key, char* value) {
    // Checks if we need to resize the dict, and calls resize function if so.
    // Then, it generates a new key-value pair and hashes the key to find an
    // index. Then, calls the assign_index function.
    if (++dict->cur_items > ((dict->cur_size * 75) / 100)) {
        dict = resize(dict);
    }
    int i = hash_index(key, dict->cur_size);
    K_V_Pair *new_pair;
    new_pair = find_key_in_hash_table(dict, key, i);
    if (new_pair) {
        free(new_pair->value);
        new_pair->value = value;
        return;
    }
    new_pair = new_dict_entry(key, value);
    if (!dict[i]) {
        dict[i] = new_pair;
        return;
    }
    K_V_Pair* current = dict[i];
    while (current) {
        if (!current->next) {
            current->next = new_pair;
            new_pair->prev = current;
            return;
        }
        current = current->next;
    }
    printf("Error. You should never reach here!\n");
}

void remove(Hash_Table* dict, char* key) {
    // searches for the key in the hash table, and deletes it.
    if (--dict->cur_items * 4 <= dict->cur_size) {
        dict = resize(dict);
    }
    int index = hash_index(key, dict->size);
    K_V_Pair* to_remove = find_key_in_hash_table(dict, key, index);
    if (to_remove) {
        if (!to_remove->prev) {
            dict[index] = to_remove->next;
            to_remove->next->prev = NULL;
        } else {
            to_remove->prev->next = to_remove->next;
            if (to_remove->next) {
                to_remove->next->prev = to_remove->prev;
            }
        }
        free(to_remove->key);
        free(to_remove->value);
        free(to_remove);
        return;
    }
    printf("Error. Key not found in hash table.\n");
}



void assign_index(Hash_Table* dict, K_V_Pair* new_pair, int i) {
    // Assigns a pair to an index. If key is already in the table, then the
    // key's associated value is changed and that's it. If the index is already
    // occupied, then we link that list!
    if (dict[i]) { // index is already occupied
        K_V_Pair *current = dict[i];
        while (current) {
            if (strcmp(current->key, new_pair->key) == 0) {
                current->key = new_pair->key;
                free(new_pair);
                return;
            }
            if (!current->next) {
                current->next = new_pair;
                new_pair->prev = current;
                return;
            }
            current = current->next;
        }
    } else {
        dict->values[i] = new_pair;
    }
}

char* hash_search(Hash_Table* dict, char* key) {
    int index = hash_index(key, dict->size);
    K_V_Pair* hash_pair = find_key_in_hash_table(dict, key, index);
    if (hash_pair) {
        return hash_pair->value;
    }
    printf("Key not found in dictionary.");
    return NULL;
}


K_V_Pair* find_key_in_hash_table(Hash_Table* dict, char* key, int index) {
    if (dict[index]) {
        K_V_Pair* current = dict[index];
        while (current) {
            if (strcmp(current->key, key) == 0) {
                return current;
            }
            current = current->next;
        }
    }
    return NULL;
}
