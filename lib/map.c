/* map.h
 * C implementation of a key/value pair data structure with strictly strings
 * Iterative hashmap, not good for Big Data
 * Implementing "dynamic" typing in C is difficult and unnecessary
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct map {
  char *key, *value;
  int ref;
  struct map *next;
} Map;

Map *createmap(char *key, char *value);
Map *addMap(Map *map, char *key, char *value);
char *findMap(Map *map, char *input);
int existsMap(Map *map, char *input);
void printMap(Map *map);

// Checks if either value or key exists in the map
int existsMap(Map *map, char *input) {
  while (map != NULL) {
    if ((strcmp(input, map->key) == 0 || strcmp(input, map->value) == 0)) {
      map->ref++;
      return 1;
    }
    map = map->next;
  }
  return 0;
}

// Finds either the key or value based on either the key or value
char *findMap(Map *map, char *input) {
  while (map != NULL)
  {
    if (strcmp(input, map->key) == 0)
      return map->value;
    if (strcmp(input, map->value) == 0)
      return map->key;
    map = map->next;
  }
}

// Initialize an instance of a map
Map *createMap(char *key, char *value) {
  return addMap(NULL, key, value);
}

// Adds key/value pair to the map
Map *addMap(Map *map, char *key, char *value) {
  if (existsMap(map, key) == 1) return map; // key/value pair already exists
  Map *node = (struct Map *)malloc(sizeof(Map));
  node->key = key;
  node->value = value;
  node->ref = 1;
  if (map == NULL) {
    node->next = NULL;
    return node;
  }
  node->next = map;
  return node;
}

// Prints map and the number of references
void printMap(Map *map) {
  while (map != NULL) {
    printf("%s: %s [ref: %d]\n", map->key, map->value, map->ref);
    map = map->next;
  }
}

// int main() {
//   char *test[6] = {"yes", "no", "maybe", "cat", "dog", "bear"};
//   Map *my_map = createMap(test[0], test[1]);
//   my_map = addMap(my_map, "maybe", test[3]);
//   my_map = addMap(my_map, test[2], test[3]);
//   my_map = addMap(my_map, test[4], test[5]);
//   printMap(my_map);
//   printf("%s\n", findMap(my_map, "yes"));
//   return 0;
// }