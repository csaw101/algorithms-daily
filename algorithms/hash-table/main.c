#include "hash_table.h"

int main() {
	HashTable* table = table_create();
	table_delete(table);

	return 0;
}
