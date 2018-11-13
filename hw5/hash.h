typedef struct hash *Hash;

/* create a new empty dictionary */
Hash HashCreate(void);

/* destroy a dictionary */
void HashDestroy(Hash);

/* insert a new key-value pair into an existing dictionary */
void HashInsert(Hash, const int x, const int y, const int z, const char value);

/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
int HashSearch(Hash, const int x, const int y, const int z);

char HashGet(Hash, const int x, const int y, const int z);