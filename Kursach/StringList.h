#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "MyString.h"

struct listElement
{
    char* value;
    listElement* nextElement = NULL;
};
struct listCollection {
    listElement* head;
    listElement* current;
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
void ListDeleteNext(listCollection* list) {
    if (list->current->nextElement->nextElement != 0) {
        listElement* badNode = list->current->nextElement;
        list->current->nextElement = list->current->nextElement->nextElement;
        free(badNode);
    }
    else list->current->nextElement = NULL;
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
void ListMovePointerToStart(listCollection* list) {
    list->current = list->head;
}
void ListAddElement(listCollection* collection, char* data) {
    struct listElement* current;
    current = (struct listElement*)malloc(sizeof(struct listElement));
    if (current == NULL) { printf("Error, NULL\n"); exit(1); }
    current->value = data;
    current->nextElement = NULL;
    if (collection->head == NULL) {
        collection->head = current;
        collection->current = current;
    }
    else if (collection->current->nextElement == NULL) {
        collection->current->nextElement = current;
    }
    else {
        current->nextElement = collection->current->nextElement;
        collection->current->nextElement = current;
    }
}
void ListMovePointerForvard(listCollection* list) {
    list->current = list->current->nextElement;
}
void ListCheckNext(listCollection* list) {
    printf("Next element is:\n");
    StringOutput(list->current->nextElement->value);
    printf("\n");
}
void ListChangeNext(listCollection* list, char* data) {
    list->current->nextElement->value = data;
}
listCollection ListMenu(listCollection* listPointer) {//add parameter
    int menuPointer = 0;
    int buffer;
    int isExist = 0;
    struct listCollection list;
    if (listPointer != NULL) {
        list = *listPointer;
    }
    else {
        list.current = NULL;
        list.head = NULL;
    }
    system("cls");
    while (menuPointer != 12) {
        menuPointer = 0;
        system("cls");
        printf("Menu\n");
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
        printf("12. Return to queue menu\n");
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
            inputElement = StringInput();
            ListAddElement(&list, inputElement);
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
        default:
            system("cls");
            break;
        }
    }
    return list;
}