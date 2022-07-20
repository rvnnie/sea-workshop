# sea-env
A C program to grab all environment variables from a .env file. Memory is dynamically allocated. Program does not account for any syntax-ing, so make sure you have your variables defined as:
```
VARIABLE=value
```
or something similar. Casing does not matter as long as you reference it exactly how it is.

## Usage
Simply call the read function of env.c and store it in a Map * like so:
```
Map *my_env_variables = read()
```
This will fetch the environment variables in the current directory.

Some TODOS: Update the read method to have a file path include and then just call the file open function from within.
