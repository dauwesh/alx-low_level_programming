#include <stdlib.h>

typedef struct hash_node_s {
    char *key;
    char *value;
    struct hash_node_s *next;
} hash_node_t;

typedef struct hash_table_s {
    unsigned long int size;
    hash_node_t **array;
} hash_table_t;

hash_table_t *hash_table_create(unsigned long int size) {
    if (size == 0) {
        return NULL; // Cannot create a hash table with size 0
    }

    hash_table_t *hash_table = (hash_table_t *)malloc(sizeof(hash_table_t));
    if (hash_table == NULL) {
        return NULL; // Memory allocation failed
    }

    hash_table->size = size;

    hash_table->array = (hash_node_t **)malloc(size * sizeof(hash_node_t *));
    if (hash_table->array == NULL) {
        free(hash_table);
        return NULL; // Memory allocation failed
    }

    // Initialize all pointers to NULL
    for (unsigned long int i = 0; i < size; i++) {
        hash_table->array[i] = NULL;
    }

    return hash_table;
}
