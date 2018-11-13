typedef struct hash *Hash;

/* create a new empty Hashionary */
Hash HashCreate(void);

/* destroy a Hashionary */
void HashDestroy(Hash);

/* insert a new key-value pair into an existing Hashionary */
void HashInsert(Hash, const char *key);

/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
const int HashSearch(Hash, const char *key);

/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
void HashDelete(Hash, const char *key);