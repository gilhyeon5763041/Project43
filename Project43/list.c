#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

void init(ListNode** head) {
    *head = NULL;
}

ListNode* insert_first(ListNode* head, int value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}

ListNode* insert(ListNode* head, ListNode* pre, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

ListNode* delete_first(ListNode* head) {
    ListNode* removed;
    if (head == NULL) {
        printf("Error: The list is empty.\n");
        return NULL;
    }
    removed = head;
    head = removed->link;
    free(removed);
    return head;
}

ListNode* delete(ListNode* head, ListNode* pre) {
    ListNode* removed;
    if (pre == NULL) {
        printf("Error: The list is empty.\n");
        return head;
    }
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}

void print_list(ListNode* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL\n");
}

int main() {
    ListNode* list = NULL;
    init(&list);

    int menu = -1;
    while (menu != 0) {
        printf("\nmenu\n");
        printf("(1) insert\n");
        printf("(2) delete\n");
        printf("(3) print\n");
        printf("(0) Exit\n");
        printf("enter the menu : ");
        scanf("%d", &menu);

        switch (menu) {
        case 1: {
            element item;
            int pos;
            printf("enter the number and position : ");
            scanf("%d %d", &item, &pos);

            int count = 0;
            ListNode* prev = NULL;
            ListNode* current = list;

            while (current != NULL && count < pos) {
                prev = current;
                current = current->link;
                count++;
            }

            if (count != pos) {
                if (prev == NULL)
                    printf("Invalid position. The list is empty.\n");
                else
                    printf("Invalid position. The last index is %d. Insert at the end of the last index.\n", count - 1);
                break;
            }

            if (prev == NULL)
                list = insert_first(list, item);
            else
                list = insert(list, prev, item);
            printf("Moved along the link: %d\n", count);
            break;
        }
        case 2: {
            int pos;
            printf("enter the position to delete: ");
            scanf("%d", &pos);

            int count = 0;
            ListNode* prev = NULL;
            ListNode* current = list;

            while (current != NULL && count < pos) {
                prev = current;
                current = current->link;
                count++;
            }

            if (current == NULL) {
                printf("Invalid position. The list is empty.\n");
                break;
            }
            if (count != pos) {
                printf("Invalid position. The last index is %d.\n", count - 1);
                break;
            }

            if (prev == NULL)
                list = delete_first(list);
            else
                list = delete(list, prev);
            printf("Moved along the link: %d\n", count);
            break;
        }
        case 3:
            print_list(list);
            break;
        case 0:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid menu. Please select again.\n");
            break;
        }
    }

    return 0;
}