#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_KEYWORDS 50
#define MAX_OPERATORS 50
#define MAX_SPECIAL 50
#define MAX_LENGTH 100

char keywords[MAX_KEYWORDS][MAX_LENGTH];
char operators[MAX_OPERATORS][MAX_LENGTH];
char specialChars[MAX_SPECIAL][MAX_LENGTH];

int keyword_count = 0, operator_count = 0, special_count = 0;

void loadTokens(const char *filename, char tokens[][MAX_LENGTH], int *count){
  FILE *file = fopen(filename, "r");
  if (file == NULL){
    printf("Error: Unable to open %s\n", filename);
    exit(1);
  }
  while (fgets(tokens[*count], MAX_LENGTH, file)){
    tokens[*count][strlen(tokens[*count]) - 1] = '\0';
    (*count)++;
  }
  fclose(file);
}

int isKeyword(const char *word){
  for (int i = 0; i < keyword_count; i++){
    if (strcmp(word, keywords[i]) == 0){
      return 1;
    }
  }
  return 0;
}

int isOperator(const char *word){
  for (int i = 0; i < operator_count; i++){
    if (strcmp(word, operators[i]) == 0){
      return 1;
    }
  }
  return 0;
}

int isSpecialCharacter(const char ch){
  for (int i = 0; i < special_count; i++){
    if (ch == specialChars[i][0]){
      return 1;
    }
  }
  return 0;
}

int isIdentifier(const char *word){
  if (!isalpha(word[0]) && word[0] != '_'){
    return 0;
  }
  for (int i = 1; word[i] != '\0'; i++){
    if (!isalnum(word[i]) && word[i] != '_'){
      return 0;
    }
  }
  return 1;
}

void processLine(char *line){
  char *token = strtok(line, " \t\n");
  while (token != NULL){
    if (isKeyword(token)){
      printf("Keyword: %s\n", token);
    }
    else if (isOperator(token)){
      printf("Operator: %s\n", token);
    }
    else if (isIdentifier(token)){
      printf("Identifier: %s\n", token);
    }
    else if (strlen(token) == 1 && isSpecialCharacter(token[0])){
      printf("Special Character: %s\n", token);
    }
    else{
      printf("Lexeme: %s\n", token);
    }
    token = strtok(NULL, " \t\n");
  }
}

void processComments(FILE *file){
  char line[MAX_LENGTH];
  while (fgets(line, MAX_LENGTH, file)){
    if (strstr(line, "//")){
      printf("Comment: %s", line);
    }
    else if (strstr(line, "/*")){
      printf("Multiline Comment Start: %s", line);
      while (fgets(line, MAX_LENGTH, file) && !strstr(line, "*/")){
        printf("%s", line);
      }
      printf("Multiline Comment End\n");
    }
  }
}

int main(){
  loadTokens("keywords.txt", keywords, &keyword_count);
  loadTokens("operators.txt", operators, &operator_count);
  loadTokens("special.txt", specialChars, &special_count);
  FILE *file = fopen("samplecode.txt", "r");
  if (file == NULL){
    printf("Error: Unable to open samplecode.txt\n");
    return 1;
  }
  char line[MAX_LENGTH];
  printf("Processing tokens in samplecode.txt:\n");
  while (fgets(line, MAX_LENGTH, file)){
    processLine(line);
  }
  fclose(file);
  file = fopen("samplecode.txt", "r");
  printf("\nProcessing comments in samplecode.txt:\n");
  processComments(file);
  fclose(file);
  return 0;
}