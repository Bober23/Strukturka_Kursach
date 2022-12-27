#include "stdio.h"
#include "stdlib.h"
#include "string.h"
char* StringInput() { //функция ввода символьной строки (слова)
	char buffer;
	int counter = 0;
	printf("Input your word\n");
	buffer = getchar(); //ввод первого элемента
	char* string = NULL;
	string = (char*)malloc(sizeof(char)); //выделяем память под строку и проверяем
	if (string == NULL) { printf("Error, NULL\n"); exit(1); }
	while (buffer != '\n' && buffer != '\0' && buffer != ' ') {
		string[counter] = buffer;
		counter++;
		buffer = getchar();
		string = (char*)realloc(string,sizeof(char)*counter+1); //выделяем память под строку и проверяем
		if (string == NULL) { printf("Error, NULL\n"); exit(1); }
	}
	string[counter] = '\0';
	while ('\n' != getchar());  //защита от дурака
	return string;
}
void StringOutput(char* string) {//функция вывода символьной строки (слова)
	for (int i = 0; i < strlen(string); i++) {
		printf("%c", string[i]);
	}
}