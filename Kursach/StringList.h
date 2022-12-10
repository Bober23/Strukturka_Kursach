//нижний уровень
//строка(предложение), реализованная на двухсвязном списке
//хранит символы(char)
#include "stdio.h"
#include "stdlib.h"
struct stringElement
{
    char value;
    stringElement* nextElement = NULL;
    stringElement* prevElement = NULL;
};
struct stringCollection {
    stringElement* head;
    stringElement* current;
    stringElement* tail;
};
void PrintString(stringCollection collection) {
    stringElement* node = collection.head;
    while (1) {
        printf("%c", node->value);
        if (node == collection.current)
            printf("*");
        node = node->nextElement;
        if (node == NULL) {
            printf("\n");
            break;
        }
    }
}
void ReversePrintString(stringCollection collection) {
    stringElement* node = collection.tail;
    while (1) {
        printf("%c", node->value);
        if (node == collection.current)
            printf("*");
        node = node->prevElement;
        if (node == NULL) {
            printf("\n");
            break;
        }
    }
}
void StringDeleteNext(stringCollection* string) {
    if (string->current->nextElement->nextElement != NULL) {
        stringElement* badNode = string->current->nextElement;
        string->current->nextElement = string->current->nextElement->nextElement;
        string->current->nextElement->prevElement = string->current;
        free(badNode);
    }
    else {
        free(string->current->nextElement);
        string->current->nextElement = NULL;
        string->tail = string->current;
    }
}
void StringDeletePrev(stringCollection* string) {
    if (string->current->prevElement->prevElement != NULL) {
        stringElement* badNode = string->current->prevElement;
        string->current->prevElement = string->current->prevElement->prevElement;
        string->current->prevElement->nextElement = string->current;
        free(badNode);

    }
    else {
        free(string->current->prevElement);
        string->current->prevElement = NULL;
        string->head = string->current;
    }
}
void StringDeleteAll(stringCollection* string) {
    stringElement* node = string->head;
    stringElement* badElement = node;
    while (node->nextElement != NULL)
    {
        badElement = node;
        node = node->nextElement;
        free(badElement);
    }
    string->head = NULL;
    string->current = NULL;
    string->tail = NULL;
}
int StringCheckEmpty(stringCollection* string) {
    if (string->head == NULL) {
        printf("string is empty\n");
        return 1;
    }
    else {
        printf("string is not empty\n");
        return 0;
    }
}
void StringCheckPointerOnEnd(stringCollection* string) {
    if (string->current->nextElement == NULL) {
        printf("YES\n");
    }
    else printf("NO\n");
}
void StringCheckPointerOnStart(stringCollection* string) {
    if (string->current->prevElement == NULL) {
        printf("YES\n");
    }
    else printf("NO\n");
}
void StringMovePointerToStart(stringCollection* string) {
    string->current = string->head;
}
void StringMovePointerToEnd(stringCollection* string) {
    string->current = string->tail;
}
void StringAddElement(stringCollection* collection, char data, int directionFlag) {
    struct stringElement* current;
    current = (struct stringElement*)malloc(sizeof(struct stringElement));
    if (current == NULL) { printf("Error, NULL\n"); exit(1); }
    current->value = data;
    current->nextElement = NULL;
    current->prevElement = NULL;
    //Если выбран Before
    if (directionFlag == 1) {
        if (collection->head == NULL) {
            collection->head = current;
            collection->current = current;
            collection->tail = current;
        }
        else if (collection->current->prevElement == NULL) {
            current->nextElement = collection->current;
            collection->current->prevElement = current;
            collection->head = current;
        }
        else {
            current->prevElement = collection->current->prevElement;
            current->nextElement = collection->current;
            collection->current->prevElement->nextElement = current;
            collection->current->prevElement = current;
        }
    }
    //Если выбран After
    else if (directionFlag == 2) { //если выбран пункт after
        if (collection->head == NULL) {
            collection->head = current;
            collection->current = current;
            collection->tail = current;
        }
        else if (collection->current->nextElement == NULL) {
            current->prevElement = collection->current;
            collection->current->nextElement = current;
            collection->tail = current;
        }
        else {
            current->nextElement = collection->current->nextElement;
            current->prevElement = collection->current;
            collection->current->nextElement->prevElement = current;
            collection->current->nextElement = current;
        }
    }
}
void StringMovePointerForvard(stringCollection* string) {
    string->current = string->current->nextElement;
}
void StringMovePointerBack(stringCollection* string) {
    string->current = string->current->prevElement;
}
void StringCheckNext(stringCollection* string) {
    printf("Next element is %c\n", string->current->nextElement->value);
}
void StringCheckPrev(stringCollection* string) {
    printf("Previous element is %c\n", string->current->prevElement->value);
}
void StringChangeNext(stringCollection* string, char data) {
    string->current->nextElement->value = data;
}
void StringChangePrev(stringCollection* string, char data) {
    string->current->prevElement->value = data;
}
stringCollection StringMenu(stringCollection* stringPointer) {//add parameter
    int menuPointer = 0;
    int buffer;
    int isExist = 0;
    struct stringCollection string;
    if (stringPointer != NULL) {
        string = *stringPointer;
    }
    else {
        string.current = NULL;
        string.head = NULL;
        string.tail = NULL;
    }
    system("cls");
    while (menuPointer != 20) {
        menuPointer = 0;
        int directionFlag = 0;
        system("cls");
        printf("Menu\n");
        printf("Select menu item\n");
        printf("1. Clear string\n");
        printf("2. Check empty\n");
        printf("3. Set pointer to head\n");
        printf("4. Set pointer to tail \n");
        printf("5. Check pointer on the end\n");
        printf("6. Check pointer on the start\n");
        printf("7. Move pointer forvard\n");
        printf("8. Move pointer back\n");
        printf("9. Check next element\n");
        printf("10. Check previous element\n");
        printf("11. Delete next element\n");
        printf("12. Delete previous element\n");
        printf("13. Extract next element\n");
        printf("14. Extract previous element\n");
        printf("15. Change next element\n");
        printf("16. Change previous element\n");
        printf("17. Add new element\n");
        printf("18. Print string\n");
        printf("19. Print reversed string\n");
        printf("20. Return to queue menu\n");
        printf("\nString: \n");
        if (string.head != NULL) {
            PrintString(string);
            printf("Reversed string: \n");
            ReversePrintString(string);
        }
        else printf("string is Empty\n");
        scanf_s("%d", &menuPointer);
        buffer = getchar();//мусор
        switch (menuPointer)
        {
        case 1:
            system("cls");
            if (string.head != NULL) {
                StringDeleteAll(&string);
            }
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 2:
            system("cls");
            StringCheckEmpty(&string);
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 3:
            system("cls");
            StringMovePointerToStart(&string);
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 4:
            system("cls");
            StringMovePointerToEnd(&string);
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 5:
            system("cls");
            if (string.head != NULL) {
                StringCheckPointerOnEnd(&string);
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty string\n");
            buffer = getchar();
            break;
        case 6:
            system("cls");
            if (string.head != NULL) {
                StringCheckPointerOnStart(&string);
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty string\n");
            buffer = getchar();
            break;
        case 7:
            system("cls");
            if (string.head != NULL) {
                if (string.current->nextElement != NULL) {
                    StringMovePointerForvard(&string);
                    printf("Work done, press enter to return\n");
                }
                else printf("Error, end of string");
            }
            else printf("Error, string empty");
            buffer = getchar();
            break;
        case 8:
            system("cls");
            if (string.head != NULL) {
                if (string.current->prevElement != NULL) {
                    StringMovePointerBack(&string);
                    printf("Work done, press enter to return\n");
                }
                else printf("Error, start of string");
            }
            else printf("Error, string empty");
            buffer = getchar();
            break;
        case 9:
            system("cls");
            if (string.head != NULL) {
                if (string.current->nextElement != NULL) {
                    StringCheckNext(&string);
                    printf("Work done, press enter to return\n");
                }
                else printf("Error, end of string");
            }
            else printf("Error, empty string\n");
            buffer = getchar();
            break;
        case 10:
            system("cls");
            if (string.head != NULL) {
                if (string.current->prevElement != NULL) {
                    StringCheckPrev(&string);
                    printf("Work done, press enter to return\n");
                }
                else printf("Error, start of string");
            }
            else printf("Error, empty string\n");
            buffer = getchar();
            break;
        case 11:
            system("cls");
            if (string.head != NULL) {
                if (string.current->nextElement != NULL) {
                    StringDeleteNext(&string);
                    printf("Work done, press enter to return\n");
                }
                else printf("Error, end of string");
            }
            else printf("Error, empty string\n");
            buffer = getchar();
            break;
        case 12:
            system("cls");
            if (string.head != NULL) {
                if (string.current->prevElement != NULL) {
                    StringDeletePrev(&string);
                    printf("Work done, press enter to return\n");
                }
                else printf("Error, start of string");
            }
            else printf("Error, empty string\n");
            buffer = getchar();
            break;
        case 13:
            system("cls");
            if (string.head != NULL) {
                if (string.current->nextElement != NULL) {
                    StringCheckNext(&string);
                    StringDeleteNext(&string);
                    printf("Work done, press enter to return\n");
                }
                else printf("Error, end of string");
            }
            else printf("Error, empty string\n");
            buffer = getchar();
            break;
        case 14:
            system("cls");
            if (string.head != NULL) {
                if (string.current->prevElement != NULL) {
                    StringCheckPrev(&string);
                    StringDeletePrev(&string);
                    printf("Work done, press enter to return\n");
                }
                else printf("Error, start of string");
            }
            else printf("Error, empty string\n");
            buffer = getchar();
            break;
        case 15:
            system("cls");
            if (string.head != NULL) {
                if (string.current->nextElement != NULL) {
                    char inputChangeElement;
                    printf("Input new element\n");
                    buffer = scanf_s("%c", &inputChangeElement);
                    StringChangeNext(&string, inputChangeElement);
                    printf("Work done, press enter to return\n");
                    buffer = getchar();
                }
                else
                    printf("Error, end of string\n");
            }
            else printf("Error, empty string\n");
            buffer = getchar();
            break;
        case 16:
            system("cls");
            if (string.head != NULL) {
                if (string.current->prevElement != NULL) {
                    char inputChangeElement;
                    printf("Input new element\n");
                    buffer = scanf_s("%c", &inputChangeElement);
                    StringChangePrev(&string, inputChangeElement);
                    printf("Work done, press enter to return\n");
                    buffer = getchar();
                }
                else
                    printf("Error, start of string\n");
            }
            else printf("Error, empty string\n");
            buffer = getchar();
            break;
        case 17:
            system("cls");
            char inputElement;
            printf("Before or after pointer?\n");
            printf("1. Before\n");
            printf("2. After\n");
            scanf_s("%d", &directionFlag);
            buffer = getchar();
            if (directionFlag == 1 || directionFlag == 2) {
                printf("Input your element\n");
                buffer = scanf_s("%c", &inputElement);
                StringAddElement(&string, inputElement, directionFlag);
                printf("Work done, press enter to return\n");
                buffer = getchar();
                buffer = getchar();
            }
            else {
                printf("Incorrect input\n");
                buffer = getchar();
            }
            break;
        case 18:
            system("cls");
            if (string.head != NULL) {
                PrintString(string);
                printf("Work done, press enter button to return\n");
            }
            else printf("Error, string is empty\n");
            buffer = getchar();
            break;
        case 19:
            system("cls");
            if (string.head != NULL) {
                ReversePrintString(string);
                printf("Work done, press enter button to return\n");
            }
            else printf("Error, string is empty\n");
            buffer = getchar();
            break;
        default:
            system("cls");
            break;
        }
    }
    return string;
}