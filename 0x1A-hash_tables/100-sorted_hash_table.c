#include <stdlib.h>

typedef struct shash_node_s {
    char *key;
    char *value;
    struct shash_node_s *next;
    struct shash_node_s *sprev;
    struct shash_node_s *snext;
} shash_node_t;

typedef struct shash_table_s {
    unsigned long int size;
    shash_node_t **array;
    shash_node_t *shead;
    shash_node_t *stail;
} shash_table_t;

shash_table_t *shash_table_create(unsigned long int size) {
    if (size == 0) {
        return NULL; // Cannot create a hash table with size 0
    }

    shash_table_t *shash_table = (shash_table_t *)malloc(sizeof(shash_table_t));
    if (shash_table == NULL) {
        return NULL; // Memory allocation failed
    }

    shash_table->size = size;
    shash_table->array = (shash_node_t **)malloc(size * sizeof(shash_node_t *));
    if (shash_table->array == NULL) {
        free(shash_table);
        return NULL; // Memory allocation failed
    }

    // Initialize all pointers to NULL
    for (unsigned long int i = 0; i < size; i++) {
        shash_table->array[i] = NULL;
    }

    shash_table->shead = NULL;
    shash_table->stail = NULL;

    return shash_table;
}
#include <stdlib.h>
#include <string.h>

typedef struct shash_node_s {
    char *key;
    char *value;
    struct shash_node_s *next;
    struct shash_node_s *sprev;
    struct shash_node_s *snext;
} shash_node_t;

typedef struct shash_table_s {
    unsigned long int size;
    shash_node_t **array;
    shash_node_t *shead;
    shash_node_t *stail;
} shash_table_t;

shash_table_t *shash_table_create(unsigned long int size) {
    if (size == 0) {
        return NULL; // Cannot create a hash table with size 0
    }

    shash_table_t *shash_table = (shash_table_t *)malloc(sizeof(shash_table_t));
    if (shash_table == NULL) {
        return NULL; // Memory allocation failed
    }

    shash_table->size = size;
    shash_table->array = (shash_node_t **)malloc(size * sizeof(shash_node_t *));
    if (shash_table->array == NULL) {
        free(shash_table);
        return NULL; // Memory allocation failed
    }

    // Initialize all pointers to NULL
    for (unsigned long int i = 0; i < size; i++) {
        shash_table->array[i] = NULL;
    }

    shash_table->shead = NULL;
    shash_table->stail = NULL;

    return shash_table;
}

int shash_table_set(shash_table_t *ht, const char *key, const char *value) {
    if (ht == NULL || key == NULL || *key == '\0') {
        return 0; // Invalid input
    }

    unsigned long int index = hash_djb2((const unsigned char *)key) % ht->size;

    // Create a new node
    shash_node_t *new_node = (shash_node_t *)malloc(sizeof(shash_node_t));
    if (new_node == NULL) {
        return 0; // Memory allocation failed
    }

    new_node->key = strdup(key);
    if (new_node->key == NULL) {
        free(new_node);
        return 0; // Memory allocation failed
    }

    new_node->value = strdup(value);
    if (new_node->value == NULL) {
        free(new_node->key);
        free(new_node);
        return 0; // Memory allocation failed
    }

    // Find the position to insert the new node in the sorted list
    shash_node_t *current = ht->shead;
    shash_node_t *prev = NULL;
    while (current != NULL && strcmp(key, current->key) > 0) {
        prev = current;
        current = current->snext;
    }

    // Insert the new node into the sorted list
    if (prev == NULL) {
        new_node->snext = ht->shead;
        if (ht->shead != NULL) {
            ht->shead->sprev = new_node;
        }
        ht->shead = new_node;
    } else {
        new_node->snext = prev->snext;
        new_node->sprev = prev;
        if (prev->snext != NULL) {
            prev->snext->sprev = new_node;
        }
        prev->snext = new_node;
    }

    // Add the new node to the hash table array
    new_node->next = ht->array[index];
    ht->array[index] = new_node;

    return 1; // Successfully added the element
}
