#include "utils/utils.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Type {

  String,
  Integer,
  IntegerPointer,
  Empty,

};

struct KeyValuePair {

  char *K;
  void *V;
  enum Type T;
};

struct HashTable {

  struct KeyValuePair *contents;
  bool (*append)(struct HashTable *h, struct KeyValuePair KV);
  void (*remove)(struct HashTable *h, size_t index);

  size_t index;
};

bool append(struct HashTable *table, struct KeyValuePair KV) {

  table->contents = realloc(table->contents,
                            sizeof(struct KeyValuePair) +
                                (sizeof(struct KeyValuePair) * table->index));
  if (is_null_ptr(table->contents)) {
    realloc_failed();
    return false;
  }

  table->contents[table->index] = KV;
  table->index++;
  return true;
}

bool init(struct HashTable *table) {

  struct KeyValuePair origin = {"Root", (void *)&"Genesis", String};
  table->contents = malloc(sizeof(struct KeyValuePair));
  if (is_null_ptr(table->contents)) {
    malloc_failed();
    return false;
  }
  table->index = 0;
  table->contents[table->index] = origin;
  table->index++;
  table->append = append;
  return true;
}

void drop_table(struct HashTable *table) {

  free(table->contents);
  table->index = 0;
}
/* if index is < 0 (like -1) this function pops the last element
 * The function returns the struct removed from the table.
 *
 */

struct KeyValuePair pop_from_table(struct HashTable *table,
                                   signed long int index) {

  size_t tableIndex = index > 0 ? index : table->index - 1;
  struct KeyValuePair KV = table->contents[tableIndex];
  table->contents[tableIndex] = (struct KeyValuePair){NULL, NULL, Empty};
  return KV;
}

void log_key_value(struct KeyValuePair *KV) {

  switch (KV->T) {

  case Empty:
    printf("[(null): (null)]: Empty\n");
    return;
  case String:
    printf("[%s : %s]\n", KV->K, ((char *)KV->V));
    break;
  case Integer:
    printf("[%s : %d]\n", KV->K, (*(int *)KV->V));
    break;
  case IntegerPointer:
    printf("[%s : %d]\n", KV->K, (int)(intptr_t)KV->V);
    break;
  }
}

void log_key_value_by_index(struct HashTable *table, size_t index) {
  // if(index < 0) return; this is impossible since i'm using size_t
  log_key_value(self(table->contents[index]));
}

void log_value(struct HashTable *table, size_t index) {

  struct KeyValuePair KV = table->contents[index];
  switch (KV.T) {

  case Empty:
    printf("(null)\n");
    return;
  case String:
    printf("%s\n", ((char *)KV.V));
    break;
  case Integer:
    printf("%d\n", (*(int *)KV.V));
    break;
  case IntegerPointer:
    printf("%d\n", (int)(intptr_t)KV.V);
    break;
  }
}

void log_table(struct HashTable *table) {

  for (size_t k = 0; k < table->index; k++) {
    struct KeyValuePair pair = table->contents[k];
    if (pair.T == Empty) {
      continue;
    }
    log_key_value(self(pair));
  }
}

void *get_value_by_key(struct HashTable *table, char *key) {
  for (size_t k = 0; k < table->index; k++) {
    struct KeyValuePair KV = table->contents[k];
    if (strcmp(KV.K, key) == 0) {
      return (void *)KV.V;
    }
  }

  return NULL;
}

struct KeyValuePair get_kv_by_key(struct HashTable *table, char *key) {
  for (size_t k = 0; k < table->index; k++) {
    struct KeyValuePair KV = table->contents[k];
    if (strcmp(KV.K, key) == 0) {
      return KV;
    }
  }

  return (struct KeyValuePair){NULL, NULL, Empty};
}

int main(void) {

  struct HashTable table;
  init(self(table));

  int postalCode = 87154632;

  append(self(table),
         (struct KeyValuePair){"Name", (void *)&"Teichmuller", String});
  append(self(table),
         (struct KeyValuePair){"Age", (void *)(intptr_t)10, IntegerPointer});
  append(self(table),
         (struct KeyValuePair){"Company", (void *)&"TeichCO", String});
  append(self(table),
         (struct KeyValuePair){"Address", (void *)&"St. Lucia", String});
  append(self(table),
         (struct KeyValuePair){"CEP", (void *)&postalCode, Integer});

  log_table(self(table)); // this will log all the entries.

  struct KeyValuePair addressInfo = get_kv_by_key(self(table), "Age");
  log_key_value(self(addressInfo)); // this will log the postalCode info.
  void *cityContents = get_value_by_key(self(table), "Address");
  printf("%s\n", (char *)cityContents); // this will log the city name.
  drop_table(self(table));

  return 0;
}
