#include<stdio.h>
#include<stdlib.h>
#include<limits.h>


typedef struct Node_t {
    int data;
    struct Node_t* next;
} Node_t,* Node;

Node newNode(int data,Node next)
{
    Node node = (Node) calloc (1,sizeof(Node_t));
    node->data = data;
    node->next = next;
    return node;
}

void printList(Node node)
{
    while(node)
    {
        printf("%d -> ",node->data);
        node = node->next;
    }
    printf("NULL\n");
}

void addFirst(Node *pnode , int data)
{
    *pnode = newNode(data,*pnode);
}

void addLast(Node *pnode,int data)
{
    if(*pnode==NULL)
    {
        addFirst(pnode,data);
        return;
    }
    Node node = *pnode;
    while(node->next)
        node = node->next;

    node->next = newNode(data,node->next);

}

int addAt(Node *pnode,int data,int index)
{
    if(index == 0)
    {
        addFirst(pnode,data);
        return 1;
    }
    Node node = *pnode;
    index--;
    while(node && index)
    {
        index --;
        node = node->next;
    }
    if(!node)
    {
        return 0;
    }
        node->next = newNode(data,node->next);
        return 1;
    
}

int removeFirst(Node *pnode)
{
    if(*pnode == NULL)
    return INT_MAX;

    Node node = *pnode;
    *pnode = node->next;
    int data = node->data;
    free(node);
    return data;
}

int removeLast(Node *pnode)
{
    if(*pnode==NULL || (*pnode)->next==NULL)
    removeFirst(pnode);

    Node node = *pnode;
    while(node->next->next)
    {
        node = node->next;
    }
    int data = node->next->data;
    free(node->next);
    node->next = NULL;
    return data;
}

int removeFrom (Node *pnode,int index)
{
    if(*pnode==NULL || index==0)
    return removeFirst(pnode);

    Node node = *pnode;
    index--;
    while(node && index)
    {
        node = node->next;
        index--;
    }
    if(node==NULL || node->next == NULL)
    return INT_MAX;

    Node tempNode = node->next;
    node->next = tempNode->next;
    int data = tempNode->data;
    free(tempNode);
    return data;

}

void reverse(Node *pnode)
{
    Node previous = NULL;
    Node curr=*pnode;
    

    while(curr!=NULL)
    {
        Node next = curr->next;
        curr->next=previous;
        previous =  curr;
        curr =  next; 
    }

    *pnode = previous;
}

int main()
{
    Node list = NULL;
    addFirst(&list,10);
    addFirst(&list,20);
    addLast(&list,1);
    addAt(&list,5,0);
    printList(list);
    reverse(&list);
    printList(list);

}