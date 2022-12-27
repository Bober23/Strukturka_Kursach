//средний уровень
//очередь, реализованная на двухсвязном списке
//хранит предложения
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "StringList.h"

struct queueElement //структура элемента очереди
{
    listCollection value; //значение элемента очереди
    queueElement* nextElement = NULL;  //указатель на следующий элемент
    queueElement* prevElement = NULL;  //указатель на предыдущий элемент
};
struct queueCollection { //структура очереди
    queueElement* head; //указатель на начало очереди
    queueElement* tail; //указатель на конец очереди
    int size = 0; //размер очереди
};

void QueueDeleteAll(queueCollection* queue) {  //Функция принимает на вход указатель на очередь, очищает очередь
    queueElement* node = queue->head;
    queueElement* badElement = node;
    while (node->nextElement != NULL)
    {
        badElement = node;
        node = node->nextElement;
        ListDeleteAll(&badElement->value);  //удаление элементов предложения внутри очереди
        free(badElement);
    }
    queue->head = NULL;
    queue->tail = NULL;
}
void QueueDeleteTail(queueCollection* queue) {  //Функция принимает на вход указатель на очередь, удаляет первый элемент
    queueElement* node = queue->tail;
    if (queue->head != queue->tail) {
        queue->tail = queue->tail->prevElement;
        queue->tail->nextElement = NULL;
    }
    else {
        queue->tail = NULL;
        queue->head = NULL;
    }
    ListDeleteAll(&node->value);//удаление элементов предложения внутри очереди
    free(node);
}

void QueueCheckEmpty(queueCollection* queue) {  //Функция принимает на вход указатель на очередь, печатает, является ли очередь пустой
    if (queue->head == NULL && queue->tail == NULL)
        printf("Queue is empty\n");
    else if (queue->head != NULL && queue->tail != NULL)
        printf("Queue is not empty\n");
    else printf("Error!\n");
}
int QueueSize(queueCollection* queue) { //Функция принимает на вход указатель на очередь, возвращает количество элементов очереди
    queueElement* current = queue->head;
    int counter = 0;
    while (current != NULL) {
        current = current->nextElement;
        counter++;
    }
    
    return counter;
}
void QueueAddElement(queueCollection* queue) {  //Функция принимает на вход указатель на очередь, вызывает функцию ListMenu и добавляет полученное значение в конец очереди
    if (queue->head == NULL) {  //если очередь пуста
        struct queueElement* newElement;
        newElement = (struct queueElement*)malloc(sizeof(struct queueElement));  //
        if (newElement == NULL) { printf("Error, NULL\n"); exit(1); }
        newElement->value = ListMenu(NULL);  //вызов меню для предложения
        newElement->prevElement = NULL;
        newElement->nextElement = NULL;
        queue->head = newElement;
        queue->tail = queue->head;
    }
    else {  //если очередь не пуста
        struct queueElement* newElement;
        newElement = (struct queueElement*)malloc(sizeof(struct queueElement));
        if (newElement == NULL) { printf("Error, NULL\n"); exit(1); }
        newElement->value = ListMenu(NULL);  //вызов меню для предложения
        newElement->nextElement = queue->head;
        newElement->prevElement = NULL;
        queue->head->prevElement = newElement;
        queue->head = newElement;
    }
}

void QueueWatchTail(queueCollection* queue) {  //Функция принимает на вход указатель на очередь, печатает первый элемент очереди
    printf("Element: ");
    PrintList(queue->tail->value);  //вызов функции печати предложения
}
void QueueInsert(queueCollection* queue) {  //Функция принимает на вход указатель на очередь, печатает значение первого элемента очереди и удаляет его
    QueueWatchTail(queue);
    QueueDeleteTail(queue);
}
void QueueChangeTail(queueCollection* queue) {  //Функция принимает на вход указатель на очередь, вызывает ListMenu для первого элемента очереди , полученным значением заменяет его
    printf("Started work with first element\n");
    queue->tail->value = ListMenu(&queue->tail->value);
}
void QueuePrint(queueCollection* queue) {  //Функция принимает на вход указатель на очередь, печатает ее
    queueElement* current = queue->head;
    int counter = 0;
    printf("/*| End |*\\ \n");
    while (current != NULL) {
        printf("    ");
        PrintList(current->value);  //вызов функции печати предложения
        counter++;
        current = current->nextElement;
    }
    
    printf("/*| Start |*\\\n");
}
queueCollection QueueMenu(queueCollection* queuePointer) { //Меню работы с очередью, принимает на вход указатель на очередь, если работает с уже созданной очередью и NULL, если очередь была только что создана. После завершения работы возвращает очередь
    int menuPointer = 0;
    int buffer;
    int isExist = 0;
    int flagCreate = 0;
    int queueSize = 0;
    struct queueCollection queue;
    if (queuePointer != NULL) {  //если очередь уже существует
        queue = *queuePointer;
        queueSize = QueueSize(&queue);
    }
    else {  //если очередь не была создана
        queue.head = NULL;
        queue.tail = NULL;
        system("cls");
        printf("Input queue size\n");
        scanf_s("%d", &queue.size);
        queueSize = 0;
    }
    system("cls");
    while (menuPointer != 9) {
        menuPointer = 0;
        int directionFlag = 0;
        system("cls");  //графический интерфейс
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
        printf("9. Return to sequence menu\n");
        printf("\nQueue size = %d\n",queue.size);
        printf("\nQueue contains %d elements\n", QueueSize(&queue));
        if (QueueSize(&queue) != 0) { //печать очереди после меню
            printf("Queue:\n");
            QueuePrint(&queue); 
        }
        scanf_s("%d", &menuPointer);
        buffer = getchar();//мусор
        switch (menuPointer)
        {
        case 1:  //если выбран пункт очистить очередь
            system("cls");
            if (queue.head != NULL) {
                QueueDeleteAll(&queue);
                queueSize = 0;
            }
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 2:  //если выбран пункт проверить пустоту очереди
            system("cls");
            QueueCheckEmpty(&queue);
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 3:  //если выбран пункт добавить элемент
            flagCreate = 0;
            if(queueSize<queue.size){
                while (flagCreate != 1 && flagCreate != 2) {  //подменю создания предложения
                    system("cls");
                    printf("You want to make new list and start work with it?\n");
                    printf("1. Create list and start work\n");
                    printf("2. Return to queue menu\n");
                    scanf_s("%d", &flagCreate);
                    if (flagCreate == 1) {
                        queueSize++;
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
            }
            else {
                printf("Error, queue overflow");
                buffer = getchar();
            }
            break;
        case 4: //если выбран пункт извлечь первый элемент
            system("cls");
            if (queue.tail != NULL) {
                QueueInsert(&queue);
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty queue\n");
            buffer = getchar();
            break;  //если выбран пункт посмотреть первый элемент
        case 5:
            system("cls");
            if (queue.head != NULL) {
                QueueWatchTail(&queue);
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty queue\n");
            buffer = getchar();
            break;
        case 6:  //если выбран пункт удалить первый элемент
            system("cls");
            if (queue.tail != NULL) {
                QueueDeleteTail(&queue);
                queueSize--;
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty queue\n");
            buffer = getchar();
            break; 
        case 7:  //если выбран пункт изменить первый элемент
            system("cls");
            if (queue.tail != NULL) {
                QueueChangeTail(&queue);
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty queue\n");
            buffer = getchar();
            break;
        case 8:  //если выбран пункт напечатать очередь
            system("cls");
            if (queue.tail != NULL) {
                QueuePrint(&queue);
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty queue\n");
            buffer = getchar();
            break;
        default:  //если неправильно введен номер пункта
            system("cls");
            break;
        }
    }
    return queue;
}