#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash_table.h"

#define HASH_TABLE_SIZE 53
#define PRIME_1 7
#define PRIME_2 23

static HashItem DELETED_ITEM = {NULL, NULL};

static HashItem* create_item(const char* key, const char* value) {
	HashItem* new_item;

	new_item = malloc(sizeof(HashItem));
	new_item->key = strdup(key);
	new_item->value = strdup(value);

	return new_item;
}

static void free_item(HashItem* item) {
	free(item->value);
	free(item->key);
	free(item);
}

HashTable* create_table() {
	HashTable* new_table;

	new_table = malloc(sizeof(HashTable));
	new_table->count = 0;
	new_table->size = HASH_TABLE_SIZE;
	new_table->items = calloc(new_table->size, sizeof(HashItem*));

	return new_table;
}

void delete_table(HashTable* table) {
	HashItem* item;

	for (int i = 0; i < table->size; i++) {
		item = table->items[i];
		if (item != NULL) {
			free(item);
		}
	}
	free(table->items);
	free(table);
}

// The prime number needs to be larger than the alphabet
static int generate_hash(const char* key, const int prime, const int table_size) {
	long hash = 0;
	const int key_length = strlen(key);

	for (int i = 0; i < key_length; i++) {
		hash += pow(prime, key_length - (i+1)) * key[i];
	}
	hash = hash % table_size;

	// do i need this casting?
	return (int)hash;
}

static int get_index(const char* key, const int table_size, int attempt) {
	const int hash_1 = generate_hash(key, PRIME_1, table_size);
	const int hash_2 = generate_hash(key, PRIME_2, table_size);
	// hash 2 is incremented to avoid the case where it equals zero, canceling the second term, which would make this function return the same hash over and over in the case of a collision
	return (hash_1 + attempt * (hash_2+1)) % table_size;
}

void insert_item(HashTable* table, const char* key, const char* value) {
	HashItem* new_item;
	int index, attempt;

	new_item = create_item(key, value);

	attempt = 0;
	index = get_index(key, table->size, attempt);
	while (
		table->items[index] != NULL &&
		table->items[index] != &DELETED_ITEM
	) {
		if (strcmp(table->items[index]->key, key) == 0) {
			free_item(table->items[index]);
			table->items[index] = new_item;
			return;
		}
		attempt++;
		index = get_index(key, table->size, attempt);
	}

	table->items[index] = new_item;
	table->count++;
}

char* search_table(HashTable* table, const char* key) {
	int index, attempt;

	attempt = 0;
	index = get_index(key, table->size, attempt);
	while (
		table->items[index] != NULL &&
		table->items[index] != &DELETED_ITEM
	) {
		if (strcmp(table->items[index]->key, key) == 0) {
			return table->items[index]->value;
		}
		attempt++;
		index = get_index(key, table->size, attempt);
	}

	return NULL;
}

void delete_item(HashTable* table, const char* key) {
	int index, attempt;

	attempt = 0;
	index = get_index(key, table->size, attempt);
	while (table->items[index] != NULL) {
		if (
			strcmp(table->items[index]->key, key) == 0 &&
			table->items[index] != &DELETED_ITEM
		) {
			free_item(table->items[index]);
			table->items[index] = &DELETED_ITEM;
		}
		attempt++;
		index = get_index(key, table->size, attempt);
	}
	table->count--;
}
