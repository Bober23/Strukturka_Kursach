
#include "Sequence.h"


void main() {
    int menuPointer = 0;
    while (menuPointer != 12) {  //цикл работает пока не выбран один из пунктов
        menuPointer = 0;
        printf("Menu\n");
        printf("Select menu item\n");
        printf("1. Create sequence and start work\n");
        printf("2. Exit\n");
        scanf_s("%d", &menuPointer);
        if (menuPointer == 1) { 
            sequenceCollection sequence = StartWork();  //созадем последовательность
            SequenceMenu(sequence); //вызваем меню последовательности для только что созданной последовательности
            exit(0);
        }
        else if (menuPointer == 2) //выход
            exit(0);
        else printf("Incorrect input\n");
        getchar();
        getchar();
        system("cls");
    }
}