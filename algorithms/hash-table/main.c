#include <stdio.h>

#include "hash_table.h"
#include "prime.h"

int main() {
	HashTable* table = create_table();
	insert_item(table, "1", "a");
	insert_item(table, "2", "b");
	insert_item(table, "3", "c");

	printf("%s\n", search_table(table, "1"));
	printf("%s\n", search_table(table, "2"));
	printf("%s\n", search_table(table, "3"));

	return 0;
}
