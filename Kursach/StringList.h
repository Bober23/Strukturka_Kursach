//нижний уровень
//предложение
//хранит строки(слова)
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "MyString.h"

struct listElement
{
    char* value;
    listElement* nextElement = NULL;
    listElement* prevElement = NULL;
};
struct listCollection {
    listElement* head;
    listElement* current;
    listElement* tail;
};


void PrintList(listCollection collection) {
    listElement* node = collection.head;
    if (node != NULL) {
        while (1) {
            StringOutput(node->value);
            if (node == collection.current)
                printf("*");
            printf(" ");
            node = node->nextElement;
            if (node == NULL) {
                printf("\n");
                break;
            }
        }
    }
    else printf("\n");
}
void PrintListReversed(listCollection collection) {
    listElement* node = collection.tail;
    if (node != NULL) {
        while (1) {
            StringOutput(node->value);
            if (node == collection.current)
                printf("*");
            printf(" ");
            node = node->prevElement;
            if (node == NULL) {
                printf("\n");
                break;
            }
        }
    }
    else printf("\n");
}
void ListDeleteNext(listCollection* list) {
    if (list->current->nextElement->nextElement != NULL) {
        listElement* badNode = list->current->nextElement;
        list->current->nextElement = list->current->nextElement->nextElement;
        list->current->nextElement->prevElement = list->current;
        free(badNode);
    }
    else {
        list->current->nextElement = NULL;
        list->tail = list->current;
    }
}
void ListDeletePrev(listCollection* list) {
    if (list->current->prevElement->prevElement != NULL) {
        listElement* badNode = list->current->prevElement;
        list->current->prevElement = list->current->prevElement->prevElement;
        list->current->prevElement->nextElement = list->current;
        free(badNode);
    }
    else { 
        list->current->prevElement = NULL;
        list->head = list->current;
    }
}
void ListDeleteAll(listCollection* list) {
    listElement* node = list->head;
    listElement* badElement = node;
    if (node != NULL) {
        while (node->nextElement != NULL)
        {
            badElement = node;
            node = node->nextElement;
            free(badElement);
        }
    }
    list->head = NULL;
    list->current = NULL;
    list->tail = NULL;
}
int ListCheckEmpty(listCollection* list) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return 1;
    }
    else {
        printf("List is not empty\n");
        return 0;
    }
}
void ListCheckPointerOnEnd(listCollection* list) {
    if (list->current->nextElement == NULL) {
        printf("YES\n");
    }
    else printf("NO\n");
}
void ListCheckPointerOnStart(listCollection* list) {
    if (list->current->prevElement == NULL) {
        printf("YES\n");
    }
    else printf("NO\n");
}
void ListMovePointerToStart(listCollection* list) {
    list->current = list->head;
}
void ListMovePointerToEnd(listCollection* list) {
    list->current = list->tail;
}
void ListAddElement(listCollection* collection, char* data, int directionFlag) {
    struct listElement* current;
    current = (struct listElement*)malloc(sizeof(struct listElement));
    if (current == NULL) { printf("Error, NULL\n"); exit(1); }
    current->value = data;
    current->nextElement = NULL;
    current->prevElement = NULL;
    //≈сли выбран Before
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
    //≈сли выбран After
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
void ListMovePointerForvard(listCollection* list) {
    list->current = list->current->nextElement;
}
void ListMovePointerBack(listCollection* list) {
    list->current = list->current->prevElement;
}
void ListCheckNext(listCollection* list) {
    printf("Next element is:\n");
    StringOutput(list->current->nextElement->value);
    printf("\n");
}
void ListCheckPrev(listCollection* list) {
    printf("Prev element is:\n");
    StringOutput(list->current->prevElement->value);
    printf("\n");
}
void ListChangeNext(listCollection* list, char* data) {
    list->current->nextElement->value = data;
}
void ListChangePrev(listCollection* list, char* data) {
    list->current->prevElement->value = data;
}
listCollection ListMenu(listCollection* listPointer) {//add parameter
    int menuPointer = 0;
    int buffer;
    int isExist = 0;
    int directionFlag;
    struct listCollection list;
    if (listPointer != NULL) {
        list = *listPointer;
    }
    else {
        list.current = NULL;
        list.head = NULL;
        list.tail = NULL;
    }
    system("cls");
    while (menuPointer != 19) {
        menuPointer = 0;
        system("cls");
        printf("Sentense Menu\n");
        printf("Select menu item\n");
        printf("1. Clear list\n");
        printf("2. Check empty\n");
        printf("3. Set pointer to head\n");
        printf("4. Check pointer on the end\n");
        printf("5. Move pointer forvard\n");
        printf("6. Check next element\n");
        printf("7. Delete next element\n");
        printf("8. Extract next element\n");
        printf("9. Change next element\n");
        printf("10. Add new element\n");
        printf("11. Print list\n");
        printf("12. Set pointer to tail\n");
        printf("13. Check pointer on the start\n");
        printf("14. Move pointer back\n");
        printf("15. Check prev element\n");
        printf("16. Delete prev element\n");
        printf("17. Extract prev element\n");
        printf("18. Change prev element\n");
        printf("19. Return to queue menu\n");
        printf("20. Print reversed list\n");
        printf("\nList: \n");
        if (list.head != NULL)
            PrintList(list);
        else printf("List is Empty\n");
        scanf_s("%d", &menuPointer);
        buffer = getchar();//мусор
        switch (menuPointer)
        {
        case 1:
            system("cls");
            if (list.head != NULL) {
                ListDeleteAll(&list);
            }
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 2:
            system("cls");
            ListCheckEmpty(&list);
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 3:
            system("cls");
            ListMovePointerToStart(&list);
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 4:
            system("cls");
            if (list.head != NULL) {
                ListCheckPointerOnEnd(&list);
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty list\n");
            buffer = getchar();
            break;
        case 5:
            system("cls");
            if (list.head != NULL) {
                if (list.current->nextElement != NULL) {
                    ListMovePointerForvard(&list);
                    printf("Work done, press enter to return\n");
                }
                else printf("Error, end of list");
            }
            else printf("Error, list empty");
            buffer = getchar();
            break;
        case 6:
            system("cls");
            if (list.head != NULL) {
                if (list.current->nextElement != NULL) {
                    ListCheckNext(&list);
                    printf("Work done, press enter to return\n");
                }
                else printf("Error, end of list");
            }
            else printf("Error, empty list\n");
            buffer = getchar();
            break;
        case 7:
            system("cls");
            if (list.head != NULL) {
                if (list.current->nextElement != NULL) {
                    ListDeleteNext(&list);
                    printf("Work done, press enter to return\n");
                }
                else printf("Error, end of list");
            }
            else printf("Error, empty list\n");
            buffer = getchar();
            break;
        case 8:
            system("cls");
            if (list.head != NULL) {
                if (list.current->nextElement != NULL) {
                    ListCheckNext(&list);
                    ListDeleteNext(&list);
                    printf("Work done, press enter to return\n");
                }
                else printf("Error, end of list");
            }
            else printf("Error, empty list\n");
            buffer = getchar();
            break;
        case 9:
            system("cls");
            if (list.head != NULL) {
                if (list.current->nextElement != NULL) {
                    char* inputChangeElement;
                    inputChangeElement = StringInput();
                    ListChangeNext(&list, inputChangeElement);
                    printf("Work done, press enter to return\n");
                }
                else
                    printf("Error, end of list\n");
            }
            else printf("Error, empty list\n");
            buffer = getchar();
            break;
        case 10:
            system("cls");
            char* inputElement;
            directionFlag = 0;
            while (directionFlag != 1 && directionFlag != 2) {
                printf("Before or after pointer?\n");
                printf("1. Before\n");
                printf("2. After\n");
                scanf_s("%d", &directionFlag);
            }
            buffer = getchar();
            inputElement = StringInput();
            ListAddElement(&list, inputElement, directionFlag);
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 11:
            system("cls");
            if (list.head != NULL) {
                PrintList(list);
                printf("Work done, press enter button to return\n");
            }
            else printf("Error, list is empty\n");
            buffer = getchar();
            break;
        case 12:
            system("cls");
            ListMovePointerToEnd(&list);
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 13:
            system("cls");
            if (list.head != NULL) {
                ListCheckPointerOnStart(&list);
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty list\n");
            buffer = getchar();
            break;
        case 14:
            system("cls");
            if (list.head != NULL) {
                if (list.current->prevElement != NULL) {
                    ListMovePointerBack(&list);
                    printf("Work done, press enter to return\n");
                }
                else printf("Error, start of list");
            }
            else printf("Error, list empty");
            buffer = getchar();
            break;
        case 15:
            system("cls");
            if (list.head != NULL) {
                if (list.current->prevElement != NULL) {
                    ListCheckPrev(&list);
                    printf("Work done, press enter to return\n");
                }
                else printf("Error, start of list");
            }
            else printf("Error, empty list\n");
            buffer = getchar();
            break;
        case 16:
            system("cls");
            if (list.head != NULL) {
                if (list.current->prevElement != NULL) {
                    ListDeletePrev(&list);
                    printf("Work done, press enter to return\n");
                }
                else printf("Error, start of list");
            }
            else printf("Error, empty list\n");
            buffer = getchar();
            break;
        case 17:
            system("cls");
            if (list.head != NULL) {
                if (list.current->prevElement != NULL) {
                    ListCheckPrev(&list);
                    ListDeletePrev(&list);
                    printf("Work done, press enter to return\n");
                }
                else printf("Error, start of list");
            }
            else printf("Error, empty list\n");
            buffer = getchar();
            break;
        case 18:
            system("cls");
            if (list.head != NULL) {
                if (list.current->prevElement != NULL) {
                    char* inputChangeElement;
                    inputChangeElement = StringInput();
                    ListChangePrev(&list, inputChangeElement);
                    printf("Work done, press enter to return\n");
                }
                else
                    printf("Error, start of list\n");
            }
            else printf("Error, empty list\n");
            buffer = getchar();
            break;
        case 20:
            system("cls");
            if (list.head != NULL) {
                PrintListReversed(list);
                printf("Work done, press enter button to return\n");
            }
            else printf("Error, list is empty\n");
            buffer = getchar();
            break;
        default:
            system("cls");
            break;
        }
    }
    return list;
}