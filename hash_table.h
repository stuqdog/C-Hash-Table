#ifndef hash_table
#define hash_table

Hash_Table* new_hash_table(int size);
Hash_Table* resize(Hash_Table* dict);
void hash_insert(char* key, char* value);
int hash_index(char* key), int size;
void assign_index(Hash_Table* dict, K_V_Pair* pair)

int hash_size = 64;


typedef union {
    int value_int;
    char *value_char;
    bool val_bool;
    char *type;
} Key;

typedef struct {
    char *key;
    char *value;
    K_V_Pair* next;
} K_V_Pair;

typedef struct {
    int cur_size;
    int cur_items;
    K_V_Pair** entries;
} Hash_Table;

#endif
