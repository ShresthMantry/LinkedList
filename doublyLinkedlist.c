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
        printf("%d == ",node->data);
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

void addAt(Node *pnode,int data,int index)
{
    if(index==0)
    {
        addFirst(pnode,data);
        return ;
    }

    Node node = *pnode;
    index--;
    while(node && index)
    {
        node=node->next;
        index--;
    }
    if(!node)
    {
        return ;
    }
    if(node->next==NULL)
    {
        addlast(pnode,data);
        return ;
    }

    Node temp = newNode(data,node->next,node);
    node->next->prev = temp;
    node->next =  temp;

}

void removeFirst(Node *pnode)
{
    if(*pnode==NULL)
    {
        return ;
    }

    Node node =  *pnode;
    if(node->next==NULL)
    {
        *pnode=NULL;
        free(node);
        return ;
    }

    node->next->prev=NULL;
    *pnode = node->next;
    free(node);
}

void removeLast(Node *pnode)
{
    Node node = *pnode;
    if(node == NULL || node->next==NULL)
    {
        removeFirst(pnode);
        return ;
    }

    while(node->next->next)
    {
        node=node->next;
    }

    Node temp = node->next;
    node->next = NULL;
    free(temp);


}

void removeIndex(Node *pnode,int index)
{
    if(index==0)
    {
        removeFirst(pnode);
        return ;
    }

    Node node = *pnode;
    index--;

    while(node && index)
    {
        node = node->next;
        index--;
    }

    if(node==NULL || node->next==NULL)
    {
        return ;
    }

    if(node->next->next==NULL)
    {
        removeLast(pnode);
        return ;
    }

    Node temp = node->next;
    temp->next->prev = node;
    node->next = temp->next;
    free(temp);

}

int main()
{
    Node head = NULL;
    addlast(&head,40);
    addFirst(&head,10);
    addFirst(&head,20);
    addFirst(&head,30);
    printList(head);
    removeIndex(&head,0);

    printList(head);
}