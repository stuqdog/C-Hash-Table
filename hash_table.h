#ifndef hash_table
#define hash_table

typedef struct K_V_Pair {
    char *key;
    char *value;
    struct K_V_Pair *prev;
    struct K_V_Pair *next;
} K_V_Pair;

typedef struct Hash_Table {
    int cur_size;
    int cur_items;
    K_V_Pair** entries;
} Hash_Table;

Hash_Table* new_HT();
Hash_Table* resize(Hash_Table *dict);
void hash_remove(Hash_Table *dict, char *key);
void hash_insert(Hash_Table* dict, char *key, char *value);
int hash_index(char *key, int size);
void assign_index(Hash_Table *dict, K_V_Pair *pair, int index);
char* hash_search(Hash_Table *dict, char *key);
K_V_Pair* find_key_in_hash_table(Hash_Table *dict, char *key, int index);
int table_size(Hash_Table* dict);


// typedef union {
//     int value_int;
//     char *value_char;
//     bool val_bool;
//     char *type;
// } Key;

#endif
