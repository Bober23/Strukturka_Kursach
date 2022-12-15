//верхний уровень
//последовательность на двусвязном списке
//хранит очереди
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "QueueList.h"

struct sequenceElement //объявляем структуру элементов последовательности
{
    queueCollection value;
    sequenceElement* nextElement = NULL;
};
struct sequenceCollection { //объявляем структуру последовательности
    sequenceElement* head;
    sequenceElement* current;
};


void PrintSequence(sequenceCollection* sequence) { //функция принимает на вход указатель на последовательность, печатает последовательность
    sequenceElement* current = sequence->head;
    int counter = 0;
    while (current != NULL) {
        printf("[%d]:", counter + 1);
        if (current == sequence->current)
            printf("<--");
        printf("\n");
        QueuePrint(&current->value); //вызов функции печати очереди
        counter++;
        current = current->nextElement;
    }
    
}
void DeleteAll(sequenceCollection* sequence) {  //принимает на вход указатель на последовательность, удаляет ее
    sequenceElement* node = sequence->head;
    sequenceElement* badElement = node;
    while (node->nextElement != NULL)
    {
        badElement = node;
        node = node->nextElement;
        QueueDeleteAll(&badElement->value);
        free(badElement);
    }
    sequence->head = NULL;
    sequence->current = NULL;
}
sequenceCollection StartWork() {  //создает последовательность, возвращает ее
    sequenceCollection sequence;
    sequence.current = NULL;
    sequence.head = NULL;
    return sequence;

} 
int CheckEmpty(sequenceCollection* sequence) { //принимает на вход указатель на последовательность, проверяет пустоту
    if (sequence->head == NULL) {              //возвращает 1 если пусто, 0 если не пусто
        printf("Sequence is empty\n");
        return 1;
    }
    else {
        printf("Sequence is not empty\n");
        return 0;
    }
}
void CheckWatched(sequenceCollection* sequence,int flag) { //принимает на вход последовательность, проверяет, прочитана ли последовательность полностью
    if (sequence->current->nextElement == NULL&&flag==1) {
        printf("No unwatched elements\n");
    }
    else printf("Sequence has unwatched elements\n");
}
void MovePointerToStart(sequenceCollection* sequence) { //принимает на вход указатель на последовательность, двигает указатель в начало
    sequence->current = sequence->head;
}
void AddElement(sequenceCollection* collection) { //принимает на вход указатель на последовательность, создает очередь и добавляет ее в конец последовательности
    struct sequenceElement* current;
    current = (struct sequenceElement*)malloc(sizeof(struct sequenceElement));
    if (current == NULL) { printf("Error, NULL\n"); exit(1); }
    current->value = QueueMenu(NULL);
    current->nextElement = NULL;
    if (collection->head == NULL) { //если последовательность пустая
        collection->head = current;
        collection->current = current;
    }
    else { //если не пустая
        sequenceElement* node = collection->head;
        while (node->nextElement != NULL) {
            node = node->nextElement;
        }
        node->nextElement = current;
    }
}
void MovePointerForvard(sequenceCollection* sequence) { //принимает на вход указатель на последовательность, двигает ее рабочий указатель вперед
    sequence->current = sequence->current->nextElement;
}
void CheckCurrent(sequenceCollection* sequence) { //принимает на вход указатель на последовательность, печатает значение элемента, на который указывает рабочий указатель
    QueuePrint(&sequence->current->value);
}
void ChangeCurrent(sequenceCollection* sequence) { //принимает на вход указатель на последовательность, изменяет значение элемента, на который указывает рабочий указатель
    sequence->current->value= QueueMenu(&sequence->current->value);
}
int SequenceSize(sequenceCollection* sequence) { //принимает на вход указатель на последовательность, возвращает количество элементов последовательности
    sequenceElement* current = sequence->head;
    int counter = 0;
    while (current != NULL) {
        current = current->nextElement;
        counter++;
    }

    return counter;
}
void SequenceMenu(sequenceCollection sequence) { //меню последовательности
    int menuPointer = 0;
    int buffer;
    int watchFlag=0;
    int isExist = 0;
    system("cls");
    while (menuPointer != 11) {
        menuPointer = 0;
        int flagCreate = 0;
        system("cls");
        printf("Sequence Menu\n");
        printf("Select menu item\n");
        printf("1. Clear sequence\n");
        printf("2. Check empty\n");
        printf("3. Set pointer to head\n");
        printf("4. Check no unwatched elements\n");
        printf("5. Skip element\n");
        printf("6. Check element\n");
        printf("7. Change element\n");
        printf("8. Add new element\n");
        printf("9. Print sequence\n");
        printf("10. Read element\n");
        printf("11. Delete sequence and exit\n");
        printf("\nSequence contains %d elements\n", SequenceSize(&sequence));
        if (sequence.head != NULL) { //если последовательность не пустая, то печатаем ее
            printf("Sequence: \n");
            PrintSequence(&sequence);
        }
        scanf_s("%d", &menuPointer);
        buffer = getchar();//мусор
        switch (menuPointer)
        {
        case 1: //если выбрано действие "Очистить последовательность"
            system("cls");
            if (sequence.head != NULL) {
                DeleteAll(&sequence);
            }
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 2: //если выбрано действие "Проверить пустоту последовательности"
            system("cls");
            CheckEmpty(&sequence);
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 3: //если выбрано действие "Установить указатель в начало"
            system("cls");
            MovePointerToStart(&sequence);
            watchFlag = 0;
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 4: //если выбрано действие "Проверить наличие непросмотренных элементов"
            system("cls");
            if (sequence.head != NULL) {
                CheckWatched(&sequence,watchFlag);
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty sequence\n");
            buffer = getchar();
            break;
        case 5: //если выбрано действие "Пропустить элемент"
            system("cls");
            if (sequence.head != NULL) {
                if (sequence.current->nextElement != NULL) {
                    MovePointerForvard(&sequence);
                    printf("Work done, press enter to return\n");
                }
                else printf("Error, end of sequence");
            }
            else printf("Error, sequence empty");
            buffer = getchar();
            break;
        case 6: //если выбрано действие "Посмотреть элемент"
            system("cls");
            if (sequence.head != NULL) {
                CheckCurrent(&sequence);
                if (sequence.current->nextElement == NULL)
                    watchFlag = 1;
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty sequence\n");
            buffer = getchar();
            break;
        case 7: //если выбрано действие "Изменить элемент"
            system("cls");
            if (sequence.head != NULL) {
                ChangeCurrent(&sequence);
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty sequence\n");
            buffer = getchar();
            break;
        case 8: //если выбрано действие "Добавить элемент"
            flagCreate = 0;
            while (flagCreate != 1 && flagCreate != 2) {
                system("cls");
                printf("You want to make new queue and start work with it?\n");
                printf("1. Create queue and start work\n");
                printf("2. Return to queue menu\n");
                scanf_s("%d", &flagCreate);
                if (flagCreate == 1) {
                    AddElement(&sequence);
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
        case 9: //если выбрано действие "Напечатать последовательность"
            system("cls");
            if (sequence.head != NULL) {
                PrintSequence(&sequence);
                printf("Work done, press enter button to return\n");
            }
            else printf("Error, sequence is empty\n");
            buffer = getchar();
            break;
        case 10: //если выбрано действие "Прочитать элемент"
            system("cls");
            if (sequence.head != NULL) {
                if (sequence.current->nextElement != NULL) {
                    QueuePrint(&sequence.current->value);
                    MovePointerForvard(&sequence);
                    printf("Work done, press enter button to return\n");
                }
                else printf("Error, end of sequence");
            }
            else printf("Error, sequence is empty\n");
            buffer = getchar();
            break;
        default:
            system("cls");
            break;
        }
    }
    if (sequence.head != NULL)
        DeleteAll(&sequence); //если выход
}
