//нижний уровень
//очередь, реализованна€ на двухсв€зном списке
//хранит строки
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "StringList.h"

struct queueElement
{
    stringCollection value;
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
    }
    else {
        queue->tail = NULL;
        queue->head = NULL;
    }
    StringDeleteAll(&node->value);
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
        newElement->value = StringMenu(NULL);
        newElement->prevElement = NULL;
        newElement->nextElement = NULL;
        queue->head = newElement;
        queue->tail = queue->head;
    }
    else {
        struct queueElement* newElement;
        newElement = (struct queueElement*)malloc(sizeof(struct queueElement));
        if (newElement == NULL) { printf("Error, NULL\n"); exit(1); }
        newElement->value = StringMenu(NULL);
        newElement->nextElement = queue->head;
        newElement->prevElement = NULL;
        queue->head->prevElement = newElement;
        queue->head = newElement;
    }
}
void QueueWatchHead(queueCollection* queue) {
    printf("Started work with first element\n");
    queue->head->value=StringMenu(&queue->head->value);
}
void QueueWatchTail(queueCollection* queue) {
    printf("Started work with first element\n");
    queue->tail->value = StringMenu(&queue->tail->value);
}
void QueueInsert(queueCollection* queue) {
    QueueWatchTail(queue);
    QueueDeleteTail(queue);
}
void QueueMenu() {
    int menuPointer = 0;
    int buffer;
    int isExist = 0;
    queueCollection queue = QueueStartWork();
    system("cls");
    while (menuPointer != 7) {
        menuPointer = 0;
        int directionFlag = 0;
        system("cls");
        printf("Queue Menu\n");
        printf("Select menu item\n");
        printf("1. Clear queue\n");
        printf("2. Check empty\n");
        printf("3. Add new element\n");
        printf("4. Insert element\n");
        printf("5. Watch first element\n");
        printf("6. Watch last element\n");
        printf("7. Return\n");
        printf("\nQueue contains %d elements\n", QueueSize(&queue));
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
            system("cls");
            QueueAddElement(&queue);
            printf("Work done, press enter to return\n");
            buffer = getchar();
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
                QueueWatchHead(&queue);
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty queue\n");
            buffer = getchar();
            break;
        case 6:
            system("cls");
            if (queue.tail != NULL) {
                QueueWatchTail(&queue);
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