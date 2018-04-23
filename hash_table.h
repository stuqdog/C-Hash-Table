#ifndef hash_table
#define hash_table

Hash_Table* hash_table(int size);
Hash_Table* resize(Hash_Table* dict);
void remove(Hash_Table* dict, char* key);
void hash_insert(char* key, char* value);
int hash_index(char* key), int size;
void assign_index(Hash_Table* dict, K_V_Pair* pair);
char* hash_search(Hash_Table* dict, char* key);
K_V_Pair* find_key_in_hash_table(Hash_Table* dict, char* key);

int hash_size = 16;


typedef union {
    int value_int;
    char *value_char;
    bool val_bool;
    char *type;
} Key;

typedef struct {
    char *key;
    char *value;
    K_V_Pair* prev;
    K_V_Pair* next;
} K_V_Pair;

typedef struct {
    int cur_size;
    int cur_items;
    K_V_Pair** entries;
} Hash_Table;

#endif
