/* env.c
 * Reads values from a .env file to later be used a program
 * Utilizes a string mapping structure, that can also be used 
 * for JSON interpreting
*/

// TODO parse and check for syntax errors
// TODO have a check for multiple references and throw an error
// TODO Incorporate a JSON interpreter

#include "map.c"

// Gets the line length of a file
size_t linelen(FILE *file) {
  size_t len = 0, c;
  while ((c = fgetc(file)) != EOF) {
    if (c == '\n') return len;
    len++;
  }
  return len;
}

// Gets the line length of each side of the equal sign, basically the actual parser
int parselen(char *line, int iter) {
  int len = 0;
  while (line[iter] != '\n' && line[iter] != '\0' && line[iter] != '=') {
    len++;
    iter++;
  }
  return len;
}

// Allocates space for char array and grabs characters to parse from line
char *storeitem(char *line, int len, int start) {
  int i;
  char *returnitem = (char *)malloc(sizeof(char) * (len + 1));
  returnitem[len] = '\0';
  for (i = 0; i < len; i++) returnitem[i] = line[start + i];
  return returnitem;
}

// Starts the parsing of the given line and returns the new head of the Map stack
Map *parse(char *line, Map *env) {
  int len1 = parselen(line, 0), len2 = parselen(line, len1 + 1);
  char *key = storeitem(line, len1, 0), *value = storeitem(line, len2, len1 + 1);
  env = env == NULL ? createMap(key, value) : addMap(env, key, value);
  return env;
}

// Just handles opening files
FILE *open() {
  FILE *file;
  if ((file = fopen("./.env","r")) == NULL){
    printf("Error! opening file");
    exit(1);
  }
  return file;
}

// Reads in each of the lines in the .env file and stores it in a struct
// with key/value pairs
Map *read(FILE *file, FILE *fptr) {
  size_t len = linelen(fptr);
  char *line = (char *) malloc(len * sizeof(char));
  Map *env = NULL;
  while (getline(&line, &len, file) > 0) {
    env = parse(line, env);
    len = linelen(fptr);
    line = realloc(line, len * sizeof(char));
  }
  free(line);
  return env;
}

int main() {
  FILE *file = open(), *fptr = open();
  Map *env = read(file, fptr);
  printMap(env);
  printf("Found: %s\n", findMap(env, "NODE_VERSION"));
  free(env);
  return 0;
}