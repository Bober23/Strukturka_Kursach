#include "stdio.h"
#include "stdlib.h"
#include "string.h"
char* StringInput() { //������� ����� ���������� ������ (�����)
	char buffer;
	int counter = 0;
	printf("Input your word\n");
	buffer = getchar(); //���� ������� ��������
	char* string = NULL;
	string = (char*)malloc(sizeof(char)); //�������� ������ ��� ������ � ���������
	if (string == NULL) { printf("Error, NULL\n"); exit(1); }
	while (buffer != '\n' && buffer != '\0' && buffer != ' ') {
		string[counter] = buffer;
		counter++;
		buffer = getchar();
		string = (char*)realloc(string,sizeof(char)*counter+1); //�������� ������ ��� ������ � ���������
		if (string == NULL) { printf("Error, NULL\n"); exit(1); }
	}
	string[counter] = '\0';
	while ('\n' != getchar());  //������ �� ������
	return string;
}
void StringOutput(char* string) {//������� ������ ���������� ������ (�����)
	for (int i = 0; i < strlen(string); i++) {
		printf("%c", string[i]);
	}
}