#include<stdio.h>
#include<stdlib.h>
#include<limits.h>


typedef struct Node_t {
    int data;
    struct Node_t* next;
    struct Node_t* prev;
} Node_t,* Node;


Node newNode(int data,Node next,Node prev)
{
    Node node = (Node)calloc(1,sizeof(Node_t));
    node->data = data;
    node->next = next;
    node->prev = prev;

    return node;
}

void printList(Node node)
{
    while(node)
    {
        // printf("%d <- |%d| -> %d ",node->prev!=NULL?node->prev->data:-1,node->data,node->next!=NULL?node->next->data:-1);
        printf("%d ",node->data);
        node = node->next;
    }
    printf("NULL\n");
}

void addFirst(Node *pnode,int data)
{
    Node temp = newNode(data,*pnode,NULL);
    if(*pnode==NULL)
    {
        *pnode = temp;
        return ;
    }
    (*pnode)->prev = temp;
    *pnode = temp;
}

void addlast(Node *pnode,int data)
{
    if(*pnode==NULL)
    {
        addFirst(pnode,data);
        return;
    }
    
    Node node = *pnode;
    while(node->next)
    {
        node = node->next;
    }

    node->next=newNode(data,NULL,node);;

}

Node reverse(Node head)
{
    Node node = head;
    Node next = NULL;
    Node prev = node->prev;
    while(node)
    {
        next = node->next;
        node->next=node->prev;
        node->prev=next;
        prev = node;
        node = next;

    }

    return prev;
}

Node reverseK(Node head,int k)
{

    if(head == NULL)
    return NULL;

    Node curr = head;
    Node next = NULL;
    Node previous = NULL;
    int count = 1;
    while(curr && count<=k)
    {
        next = curr->next;
        curr->next =  previous;
        curr->prev = next;
        previous = curr;
        curr = next;
        count++;

    }

    previous->prev = NULL;
    head->next = reverseK(curr,k);
    if(head->next)
    head->next->prev = head;

    return previous;
}

void sort(Node head)
{
    Node curr = head;
    while(curr)
    {
        Node node = curr->next;
        while(node)
        {
            if(curr->data>node->data)
            {
                int temp = curr->data;
                curr->data=node->data;
                node->data=temp;
            }
            node=node->next;
        }
        curr=curr->next;
    }
}

void sortK(Node head,int size)
{

    if(head==NULL)
    return ;

    Node curr = head;
    int k = 1;
    while(curr && k<=size)
    {
        Node node = curr->next;
        int count = size-k;
        while(node && count>0)
        {
            if(curr->data>node->data)
            {
                int temp = curr->data;
                curr->data=node->data;
                node->data=temp;
            }
            node=node->next;
        }
        curr=curr->next;
        k++;
    } 

    sortK(curr,size)  ;

}


int getLen(Node head)
{
    Node node = head;
    int count = 0;
    while(node)
    {
        count++;
        node = node->next;
    }
    return count;
}

Node rotate(Node head,int k)
{
    Node node = head;
    int count = getLen(head)-k;
    int x = 0;
    Node temp = NULL;
    while(node->next)
    {
        x++;
        if(x==count)
        {
            temp=node;
        }
        node = node->next;
    }

    node->next = head;
    head->prev=node;

    Node newHead= temp->next;
    temp->next=NULL;
    newHead->prev=NULL;
    return newHead;
}


int main()
{
    Node head = NULL;
    addlast(&head,60);
    addlast(&head,10);
    addlast(&head,30);
    addlast(&head,30);
    addlast(&head,90);
    addlast(&head,70);

    sort(head);
    printList(head);
    printList(rotate(head,3));

}

//done assignment4