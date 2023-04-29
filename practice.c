#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node_t
{
    int data;
    struct Node_t *next;
} Node_t, *Node;

Node newNode(int data, Node next)
{
    Node node = (Node)calloc(1, sizeof(Node_t));
    node->data = data;
    node->next = next;
    return node;
}

void printList(Node node)
{
    while (node)
    {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

void addFirst(Node *pnode, int data)
{
    *pnode = newNode(data, *pnode);
}

void addLast(Node *pnode, int data)
{
    if (*pnode == NULL)
    {
        addFirst(pnode, data);
        return;
    }
    Node node = *pnode;
    while (node->next)
        node = node->next;

    node->next = newNode(data, node->next);
}

void removeDuplicates(Node *pnode)
{
    Node node = *pnode;
    while (node)
    {
        Node temp = node->next;
        Node prev = node;
        while (temp)
        {
            if (temp->data == node->data)
            {
                Node temp2 = temp;
                prev->next = temp->next;
                temp = temp->next;
                free(temp2);
                continue;
            }

            prev = prev->next;
            temp = temp->next;
        }
        node = node->next;
    }
}

Node mergeSort(Node l1, Node l2)
{
    if (l1->data > l2->data)
    {
        Node l3 = l1;
        l1 = l2;
        l2 = l3;
    }

    Node res = l1;

    while (l1 != NULL && l2 != NULL)
    {
        Node temp = NULL;
        while (l1 != NULL && l1->data <= l2->data)
        {
            temp = l1;
            l1 = l1->next;
        }

        temp->next = l2;
        Node l3 = l2;
        l2 = l1;
        l1 = l3;
    }

    return res;
}

Node middle(Node head)
{
    Node fast = head;
    Node slow = head;

    while (fast && fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

Node rev(Node head)
{
    Node prev = NULL;
    Node curr = head;
    Node next = NULL;

    while (curr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

Node crissCross(Node head1, Node head2)
{
    Node ans = head1;

    while (head1)
    {
        Node next = head1->next;
        head1->next = head2;
        head1 = head2;
        head2 = next;
    }

    return ans;
}

void oddEven(Node *pnode)
{
    Node node = *pnode;
    Node evenhead = NULL;
    Node prev = NULL;

    if (node->data % 2 == 0)
    {
        evenhead = node;
        prev = node;
        node = node->next;
    }
    else
    {
        prev = node;
        node = node->next;
    }

    while (node)
    {
        if (node->data % 2 == 0)
        {
            if (evenhead == NULL)
            {
                prev->next = node->next;
                evenhead = node;
                node->next = *pnode;
                *pnode = evenhead;
                node = prev->next;
                continue;
            }

            else
            {
                prev->next = node->next;
                Node temp = evenhead->next;
                evenhead->next = node;
                node->next = temp;
                node = prev->next;
                evenhead = evenhead->next;
                continue;
            }
        }

        prev = node;
        node = node->next;
    }
}

int main()
{
    Node l1 = NULL;
    addLast(&l1, 2);
    addLast(&l1, 3);
    addLast(&l1, 5);
    addLast(&l1, 7);
    addLast(&l1, 8);
    addLast(&l1, 10);

    oddEven(&l1);
    printList(l1);
}