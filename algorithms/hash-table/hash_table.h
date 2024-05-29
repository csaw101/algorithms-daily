typedef struct {
	char* key;
	char* value;
} HashItem;

typedef struct {
	int size;
	int base_size;
	int count;
	HashItem** items;
} HashTable;

HashTable* create_table();
void delete_table(HashTable* table);
void insert_item(HashTable* table, const char* key, const char* value);
char* search_table(HashTable* table, const char* key);
void delete_item(HashTable* table, const char* key);
