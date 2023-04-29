#include<stdio.h>
#include<stdlib.h>
#include<limits.h>


typedef struct Node_t {
    int data;
    struct Node_t* next;
} Node_t,* Node;

Node newNode(int data,Node next)
{
    Node node = (Node)calloc(1,sizeof(Node_t));
    node->data = data;
    node->next = next;
    return node;

}

void printList(Node node)
{
    Node temp = node->next;
    while(temp != node)
    {
        printf("%d == ",temp->data);
        temp = temp->next;
    }
    printf("%d \n",node->data);
}

void addFirst(Node *ptail,int data)
{
    if(*ptail==NULL)
    {
        Node temp = newNode(data,NULL);
        temp->next = temp;
        *ptail = temp;
        return ;
    }
    

    (*ptail)->next = newNode(data,(*ptail)->next);

}

void addLast(Node *ptail,int data)
{
    if(*ptail==NULL)
    {
        addFirst(ptail,data);
        return ;
    }
    
    Node temp = newNode(data,(*ptail)->next);
    (*ptail)->next = temp;
    *ptail=temp;

}

void addAt(Node *ptail,int data,int indexData)
{
    Node node = *ptail;
    if(indexData==node->data)
    {
        addLast(ptail,data);
        return ;
    }
    while(node->data!=indexData)
    {
        node = node->next;
    }

    node->next = newNode(data,node->next);

}

void removeFirst(Node *ptail)
{
    Node node = *ptail;
    if(node==NULL)
    {
        return ;
    }
    
    Node temp = node->next;
    node->next=temp->next;
    free(temp);

}

void removeLast(Node *ptail)
{
    Node node = *ptail;
    if(node==NULL || node->next==node)
    {
        removeFirst(ptail);
        return;
    }

    Node head=node->next;
    while(head->next!=node)
    {
        head=head->next;
    }

    head->next=node->next;
    *ptail = head;
    free(node);

}

void removeFrom(Node *ptail,int indexData)
{
    Node node = *ptail;
    Node head = node;
    while(head->data!=indexData)
    {
        head = head->next;
    }
    if(head->next==node)
    {
        removeLast(ptail);
        return ;
    }

    Node temp = head->next;
    head->next = temp->next;
    free(temp);

}


int main()
{
    Node tail = NULL;
    addFirst(&tail,10);
    addFirst(&tail,20);
    addFirst(&tail,50);
    addLast(&tail,30);
    addAt(&tail,15,10);
    printList(tail);
    removeFrom(&tail,50);
    printf("%d \n",tail->data);
    printList(tail);

}