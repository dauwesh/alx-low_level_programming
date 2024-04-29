#include <string.h>

int hash_table_set(hash_table_t *ht, const char *key, const char *value) {
    if (ht == NULL || key == NULL || *key == '\0') {
        return 0; // Invalid input
    }

    unsigned long int index = key_index((const unsigned char *)key, ht->size);

    // Create a new node
    hash_node_t *new_node = (hash_node_t *)malloc(sizeof(hash_node_t));
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

    // Handle collision by adding the new node at the beginning of the list
    new_node->next = ht->array[index];
    ht->array[index] = new_node;

    return 1; // Successfully added the element
}
