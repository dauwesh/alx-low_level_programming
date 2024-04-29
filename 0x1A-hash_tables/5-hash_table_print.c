#include <stdio.h>

void hash_table_print(const hash_table_t *ht) {
    if (ht == NULL) {
        return; // Invalid input
    }

    printf("{\n");
    for (unsigned long int i = 0; i < ht->size; i++) {
        hash_node_t *current = ht->array[i];
        while (current != NULL) {
            printf("'%s': '%s'", current->key, current->value);
            if (current->next != NULL) {
                printf(", ");
            }
            current = current->next;
        }
        if (ht->array[i] != NULL) {
            printf("\n");
        }
    }
    printf("}\n");
}
