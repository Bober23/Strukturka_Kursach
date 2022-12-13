
#include "Sequence.h"


void main() {
    int menuPointer = 0;
    while (menuPointer != 12) {
        menuPointer = 0;
        printf("Menu\n");
        printf("Select menu item\n");
        printf("1. Create sequence and start work\n");
        printf("2. Exit\n");
        scanf_s("%d", &menuPointer);
        if (menuPointer == 1) {
            sequenceCollection sequence = StartWork();
            SequenceMenu(sequence);
            exit(0);
        }
        else if (menuPointer == 2)
            exit(0);
        else printf("Incorrect input\n");
        getchar();
        getchar();
        system("cls");
    }
}