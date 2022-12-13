//нижний уровень
//очередь, реализованна€ на двухсв€зном списке
//хранит строки
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "StringList.h"

struct queueElement
{
    listCollection value;
    queueElement* nextElement = NULL;
    queueElement* prevElement = NULL;
};
struct queueCollection {
    queueElement* head;
    queueElement* tail;
};
queueCollection QueueStartWork() {
    queueCollection queue;
    queue.head = NULL;
    queue.tail = NULL;
    return queue;
}
void QueueDeleteAll(queueCollection* queue) {
    queueElement* node = queue->head;
    queueElement* badElement = node;
    while (node->nextElement != NULL)
    {
        badElement = node;
        node = node->nextElement;
        free(badElement);
    }
    queue->head = NULL;
    queue->tail = NULL;
}
void QueueDeleteTail(queueCollection* queue) {
    queueElement* node = queue->tail;
    if (queue->head != queue->tail) {
        queue->tail = queue->tail->prevElement;
        queue->tail->nextElement = NULL;
    }
    else {
        queue->tail = NULL;
        queue->head = NULL;
    }
    ListDeleteAll(&node->value);
    free(node);
}

void QueueCheckEmpty(queueCollection* queue) {
    if (queue->head == NULL && queue->tail == NULL)
        printf("Queue is empty\n");
    else if (queue->head != NULL && queue->tail != NULL)
        printf("Queue is not empty\n");
    else printf("Error!\n");
}
int QueueSize(queueCollection* queue) {
    queueElement* current = queue->head;
    int counter = 0;
    while (current != NULL) {
        current = current->nextElement;
        counter++;
    }
    
    return counter;
}
void QueueAddElement(queueCollection* queue) {
    if (queue->head == NULL) {
        struct queueElement* newElement;
        newElement = (struct queueElement*)malloc(sizeof(struct queueElement));
        if (newElement == NULL) { printf("Error, NULL\n"); exit(1); }
        newElement->value = ListMenu(NULL);
        newElement->prevElement = NULL;
        newElement->nextElement = NULL;
        queue->head = newElement;
        queue->tail = queue->head;
    }
    else {
        struct queueElement* newElement;
        newElement = (struct queueElement*)malloc(sizeof(struct queueElement));
        if (newElement == NULL) { printf("Error, NULL\n"); exit(1); }
        newElement->value = ListMenu(NULL);
        newElement->nextElement = queue->head;
        newElement->prevElement = NULL;
        queue->head->prevElement = newElement;
        queue->head = newElement;
    }
}

void QueueWatchTail(queueCollection* queue) {
    printf("Element: ");
    PrintList(queue->tail->value);
}
void QueueInsert(queueCollection* queue) {
    QueueWatchTail(queue);
    QueueDeleteTail(queue);
}
void QueueChangeTail(queueCollection* queue) {
    printf("Started work with first element\n");
    queue->tail->value = ListMenu(&queue->tail->value);
}
void QueuePrint(queueCollection* queue) {
    queueElement* current = queue->head;
    int counter = 0;
    while (current != NULL) {
        printf("[%d]: ", counter);
        PrintList(current->value);
        counter++;
        current = current->nextElement;
    }
}
void QueueMenu() {
    int menuPointer = 0;
    int buffer;
    int isExist = 0;
    int flagCreate = 0;
    queueCollection queue = QueueStartWork();
    system("cls");
    while (menuPointer != 9) {
        menuPointer = 0;
        int directionFlag = 0;
        system("cls");
        printf("Queue Menu\n");
        printf("Select menu item\n");
        printf("1. Clear queue\n");
        printf("2. Check empty\n");
        printf("3. Add new element\n");
        printf("4. Insert first element\n");
        printf("5. Watch first element\n");
        printf("6. Delete first element\n");
        printf("7. Change first element\n");
        printf("8. Print queue\n");
        printf("9. Return\n");
        printf("\nQueue contains %d elements\n", QueueSize(&queue));
        if (QueueSize(&queue) != 0) {
            printf("Queue:\n");
            QueuePrint(&queue);
        }
        scanf_s("%d", &menuPointer);
        buffer = getchar();//мусор
        switch (menuPointer)
        {
        case 1:
            system("cls");
            if (queue.head != NULL) {
                QueueDeleteAll(&queue);
            }
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 2:
            system("cls");
            QueueCheckEmpty(&queue);
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 3:
            flagCreate = 0;
            while (flagCreate != 1 && flagCreate != 2) {
                system("cls");
                printf("You want to make new list and start work with it?\n");
                printf("1. Create list and start work\n");
                printf("2. Return to queue menu\n");
                scanf_s("%d", &flagCreate);
                if (flagCreate == 1) {
                    QueueAddElement(&queue);
                    printf("Work done, press enter to return\n");
                    buffer = getchar();
                }
                else if (flagCreate != 2) {
                    printf("Input correct number\n");
                    buffer = getchar();
                    buffer = getchar();
                }

            }
            break;
        case 4:
            system("cls");
            if (queue.tail != NULL) {
                QueueInsert(&queue);
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty queue\n");
            buffer = getchar();
            break;
        case 5:
            system("cls");
            if (queue.head != NULL) {
                QueueWatchTail(&queue);
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty queue\n");
            buffer = getchar();
            break;
        case 6:
            system("cls");
            if (queue.tail != NULL) {
                QueueDeleteTail(&queue);
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty queue\n");
            buffer = getchar();
            break;
        case 7:
            system("cls");
            if (queue.tail != NULL) {
                QueueChangeTail(&queue);
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty queue\n");
            buffer = getchar();
            break;
        case 8:
            system("cls");
            if (queue.tail != NULL) {
                QueuePrint(&queue);
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty queue\n");
            buffer = getchar();
            break;
        default:
            system("cls");
            break;
        }
    }
    if (queue.head != NULL)
        QueueDeleteAll(&queue); //если выход
}