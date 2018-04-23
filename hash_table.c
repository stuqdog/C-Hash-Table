#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "hash_table.h"
#define MODULO 337

int main() {
    return 0;
}

Hash_Table* new_hash_table() {
    Hash_Table *new;
    new = (Hash_Table*) malloc(sizeof(Hash_Table));

    new->cur_size = hash_size;
    new->cur_items = 0;
    new->entries = calloc((size_t) hash_size, sizeof(K_V_Pair*));

    return new;
}


int hash_index(char* key) {
    int hash = 0;
    int k_index = 1;
    int index = 0;

    while (*key) {
        index += (int) *(key)++ * k_index++;
    }
    int index = (index % MODULO) % hash_size;
    return index;
}

void resize(Hash_Table* dict) {
    if (dict->cur_size > 3 * dict->cur_items) {
        hash_size = dict->cur_size / 2;
    } else {
        hash_size = dict->cur_size * 2;
    }
    Hash_Table* new = new_hash_table();
    for (int i = 0; i < dict->cur_size; ++i) {
        // Okay we can make this better. No need to recreate keys, but also if we're
        // doing this linked list style then we need to potentially reassign more than
        // once per index. So figure out how to do that.
        K_V_Pair *current = dict[i];
        while (current) {
            K_V_Pair *next = current->next;
            int new_index = hash_index(current->key);
            current->next = NULL;
            if (!new[new_index]) {
                new[new_index] = current;
            }
            current = next;
        }
    }
    free(dict);
    hash_size = 64;
    return new;
}

K_V_Pair* new_dict_entry(char *key, char *value) {
    K_V_Pair* new;
    new = (K_V_Pair*) malloc(sizeof(K_V_Pair));
    new->key = key;
    new->value = value;
    new->next = NULL;
    return new;
}

void insert(Hash_Table* dict, char* key, char* value) {
    if (++dict->cur_items > (dict->(cur_size) * 75) / 100) {
        dict = resize(dict);
    }
    int i = hash_index(key, dict->size);
    K_V_Pair *new_pair;
    new_pair = new_dict_entry(key, value);
    if (dict[i]) {
        K_V_Pair *current = dict[i];
        while (current) {
            if (strcmp(current->key, key) == 0) {
                current->key = key;
                free(new_pair);
                return;
            }
            if (!current->next) {
                break;
            }
            current = current->next;
        }
        current->next = new_pair;
    } else {
        dict->values[i] = new_pair;
    }
}

void assign_index(Hash_Table* dict, K_V_Pair* pair) {

}
