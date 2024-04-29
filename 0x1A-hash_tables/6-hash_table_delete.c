#include <stdlib.h>

void hash_table_delete(hash_table_t *ht) {
    if (ht == NULL) {
        return; // Invalid input
    }

    // Iterate over each index of the hash table array
    for (unsigned long int i = 0; i < ht->size; i++) {
        hash_node_t *current = ht->array[i];
        // Traverse the linked list at each index and free memory
        while (current != NULL) {
            hash_node_t *next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            current = next;
        }
    }

    // Free the array of pointers and the hash table itself
    free(ht->array);
    free(ht);
}
