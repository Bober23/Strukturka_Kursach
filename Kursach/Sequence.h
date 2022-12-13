#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "QueueList.h"

struct sequenceElement
{
    queueCollection value;
    sequenceElement* nextElement = NULL;
    sequenceElement* prevElement = NULL;
};
struct sequenceCollection {
    sequenceElement* head;
    sequenceElement* current;
    sequenceElement* tail;
};


void PrintSequence(sequenceCollection* sequence) {
    sequenceElement* current = sequence->head;
    int counter = 0;
    while (current != NULL) {
        printf("[%d]:", counter + 1);
        if (current == sequence->current)
            printf("<--");
        printf("\n");
        QueuePrint(&current->value);
        counter++;
        current = current->nextElement;
    }
    
}
void DeleteAll(sequenceCollection* sequence) {
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
    sequence->tail = NULL;
}
sequenceCollection StartWork() {
    sequenceCollection sequence;
    sequence.current = NULL;
    sequence.head = NULL;
    sequence.tail = NULL;
    return sequence;

}
int CheckEmpty(sequenceCollection* sequence) {
    if (sequence->head == NULL) {
        printf("Sequence is empty\n");
        return 1;
    }
    else {
        printf("Sequence is not empty\n");
        return 0;
    }
}
void CheckWatched(sequenceCollection* sequence) {
    if (sequence->current->nextElement == NULL) {
        printf("YES\n");
    }
    else printf("NO\n");
}
void MovePointerToStart(sequenceCollection* sequence) {
    sequence->current = sequence->head;
}
void AddElement(sequenceCollection* collection) {
    struct sequenceElement* current;
    current = (struct sequenceElement*)malloc(sizeof(struct sequenceElement));
    if (current == NULL) { printf("Error, NULL\n"); exit(1); }
    current->value = QueueMenu(NULL);
    current->nextElement = NULL;
    current->prevElement = NULL;
    if (collection->head == NULL) {
        collection->head = current;
        collection->current = current;
        collection->tail = current;
    }
    else {
        collection->tail->nextElement = current;
        current->prevElement = collection->tail;
        collection->tail = current;
    }
}
void MovePointerForvard(sequenceCollection* sequence) {
    sequence->current = sequence->current->nextElement;
}
void CheckCurrent(sequenceCollection* sequence) {
    QueuePrint(&sequence->current->value);
}
void ChangeCurrent(sequenceCollection* sequence) {
    sequence->current->value= QueueMenu(&sequence->current->value);
}
int SequenceSize(sequenceCollection* sequence) {
    sequenceElement* current = sequence->head;
    int counter = 0;
    while (current != NULL) {
        current = current->nextElement;
        counter++;
    }

    return counter;
}
void SequenceMenu(sequenceCollection sequence) {
    int menuPointer = 0;
    int buffer;
    int isExist = 0;
    system("cls");
    while (menuPointer != 11) {
        menuPointer = 0;
        int flagCreate = 0;
        system("cls");
        printf("Menu\n");
        printf("Select menu item\n");
        printf("1. Clear sequence\n"); //!
        printf("2. Check empty\n"); //!
        printf("3. Set pointer to head\n");
        printf("4. Check no unwatched elements\n");
        printf("5. Skip element\n");
        printf("6. Check element\n");
        printf("7. Change element\n");
        printf("8. Add new element\n");    //!
        printf("9. Print sequence\n");
        printf("10. Read element\n");
        printf("11. Delete sequence and exit\n");
        printf("\nSequence contains %d elements\n", SequenceSize(&sequence));
        if (sequence.head != NULL) {
            printf("Sequence: \n");
            PrintSequence(&sequence);
        }
        scanf_s("%d", &menuPointer);
        buffer = getchar();//мусор
        switch (menuPointer)
        {
        case 1:
            system("cls");
            if (sequence.head != NULL) {
                DeleteAll(&sequence);
            }
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 2:
            system("cls");
            CheckEmpty(&sequence);
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 3:
            system("cls");
            MovePointerToStart(&sequence);
            printf("Work done, press enter to return\n");
            buffer = getchar();
            break;
        case 4:
            system("cls");
            if (sequence.head != NULL) {
                CheckWatched(&sequence);
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty sequence\n");
            buffer = getchar();
            break;
        case 5:
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
        case 6:
            system("cls");
            if (sequence.head != NULL) {
                CheckCurrent(&sequence);
                printf("Work done, press enter to return\n");
            }
            else printf("Error, empty sequence\n");
            buffer = getchar();
            break;
        case 7:
            system("cls");
            if (sequence.head != NULL) {
                ChangeCurrent(&sequence);
                printf("Work done, press enter to return\n");
                buffer = getchar();
            }
            else printf("Error, empty sequence\n");
            buffer = getchar();
            break;
        case 8:
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
        case 9:
            system("cls");
            if (sequence.head != NULL) {
                PrintSequence(&sequence);
                printf("Work done, press enter button to return\n");
            }
            else printf("Error, sequence is empty\n");
            buffer = getchar();
            break;
        case 10:
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
