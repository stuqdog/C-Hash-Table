#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "hash_table.h"
#define MODULO 337


Hash_Table* new_ht() {
    Hash_Table *new;
    new = (Hash_Table*) malloc(sizeof(Hash_Table));

    new->cur_size = 16;
    new->cur_items = 0;
    new->entries = calloc((size_t) 16, sizeof(K_V_Pair*));

    return new;
}


int hash_index(char* key, int size) {
    int k_index = 1;
    int index = 0;

    while (*key) {
        index += (int) *(key)++ * k_index++;
    }
    index = (index % MODULO) % size;
    return index;
}

void resize(Hash_Table* dict) {
    // resizes dict, either doubling it if current items >= 75% of dict size,
    // or halfing it if current items <= 25% of dict size. Reassigns indices
    // based on current size.
    printf("Resize starts\n");
    int old_size = dict->cur_size;
    if (dict->cur_size > 3 * dict->cur_items) {
        dict->cur_size /= 2; // change hash size for resizing purposes.
    } else if (dict->cur_items * 4 >= dict->cur_size * 3){
        dict->cur_size *= 2;
    } else {
        printf("Error. Resize should not have been called.");
        return;
    }
    K_V_Pair** new_table = calloc((size_t) dict->cur_size, sizeof(K_V_Pair*));
    printf("dict cur size: %d\n", dict->cur_size);
    for (int i = 0; i < old_size; ++i) {
        K_V_Pair *current = dict->entries[i];
        while (current) {
            K_V_Pair *next = current->next;
            int new_index = hash_index(current->key, dict->cur_size);
            current->next = NULL;
            current->prev = NULL;
            assign_index(new_table, current, new_index);
            current = next;
        }
    }
    free(dict->entries);
    dict->entries = new_table;
    printf("We're done!\n");
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

void hash_insert(Hash_Table* dict, char* key, char* value) {
    // Checks if we need to resize the dict, and calls resize function if so.
    // Then, it generates a new key-value pair and hashes the key to find an
    // index. Then, calls the assign_index function.
    if (dict->cur_items > ((dict->cur_size * 75) / 100)) {
        resize(dict);
    }
    int idx = hash_index(key, dict->cur_size);
    K_V_Pair *new_pair;
    new_pair = find_key_in_hash_table(dict, key, idx);
    if (new_pair) {
        new_pair->value = value;
        return;
    }
    new_pair = new_dict_entry(key, value);
    dict->cur_items++;
    assign_index(dict->entries, new_pair, idx);
}

void hash_delete(Hash_Table* dict, char* key) {
    // searches for the key in the hash table, and deletes it.
    if (dict->cur_items * 4 <= dict->cur_size) {
        resize(dict);
    }
    int index = hash_index(key, dict->cur_size);
    K_V_Pair* to_remove = find_key_in_hash_table(dict, key, index);
    if (to_remove) {
        dict->cur_items--;
        if (to_remove->prev) {
            to_remove->prev->next = to_remove->next;
            if (to_remove->next) {
                to_remove->next->prev = to_remove->prev;
            }
        } else {
            dict->entries[index] = to_remove->next;
            if (to_remove->next) {
                to_remove->next->prev = NULL;
            }
        }
        free(to_remove);
        return;
    }
    printf("Error. Key not found in hash table.\n");
}



void assign_index(K_V_Pair** dict, K_V_Pair* new_pair, int i) {
    // Assigns a pair to an index. If key is already in the table, then the
    // key's associated value is changed and that's it. If the index is already
    // occupied, then we link that list!
    if (dict[i]) { // i.e., index is already occupied
        K_V_Pair *current = dict[i];
        while (current) {
            if (strcmp(current->key, new_pair->key) == 0) {
                current->key = new_pair->key;
                free(new_pair);
                return;
            }
            if (!(current->next)) {
                current->next = new_pair;
                new_pair->prev = current;
                return;
            }
            current = current->next;
        }
    } else {
        dict[i] = new_pair;
    }
}

char* hash_search(Hash_Table* dict, char* key) {
    int index = hash_index(key, dict->cur_size);
    K_V_Pair* hash_pair = find_key_in_hash_table(dict, key, index);
    if (hash_pair) {
        printf("%s\n", hash_pair->value);
        return hash_pair->value;
    }
    printf("Search failed; key not found in dictionary.\n");
    return NULL;
}


K_V_Pair* find_key_in_hash_table(Hash_Table* dict, char* key, int index) {
    if (dict->entries[index]) {
        K_V_Pair* current = dict->entries[index];
        while (current) {
            if (strcmp(current->key, key) == 0) {
                return current;
            }
            current = current->next;
        }
    }
    return NULL;
}

int hash_size(Hash_Table* dict) {
    printf("Current items: %d\n", dict->cur_items);
    printf("Current size: %d\n", dict->cur_size);
    return dict->cur_items;
}
