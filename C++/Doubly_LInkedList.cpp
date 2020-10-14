#include <iostream>
#include <stdlib.h>
using namespace std;
struct node
{
    int data;
    struct node *next;
    struct node *prev;
};
typedef struct node *nodeptr;
nodeptr getNode(int);
nodeptr insFirst(int, nodeptr);
void insLast(int, nodeptr);
void display(nodeptr);
void insAfter(int, nodeptr);
nodeptr searchFunc(int, nodeptr);
nodeptr insBefore(int, nodeptr, nodeptr);
nodeptr deleteFirst(nodeptr);
nodeptr deleteLast(nodeptr);
void deleteAfter(nodeptr);
nodeptr deleteBefore(nodeptr, nodeptr);
int main()
{
    nodeptr start = NULL;
    nodeptr p;
    nodeptr temp;
    int i, choice, item, tempitem;
    for (i = 1; i; i++)
    {
        cout << "1.INSERT FIRST\n2.INSERT LAST\n3.INSERT BEFORE\n4.INSERT AFTER\n5.DISPLAY\n6.DELETE FIRST\n7.DELETE LAST\n8.DELETE AFTER\n9.DELETE BEFORE\n10.EXIT" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "ENTER ELEMENT TO BE ADDED" << endl;
            cin >> item;
            start = insFirst(item, start);
            break;
        case 2:
            cout << "ENTER ELEMENT TO BE ADDED" << endl;
            cin >> item;
            insLast(item, start);
            break;
        case 3:
            cout << "ENTER ELEMENT TO BE ADDED" << endl;
            cin >> item;
            cout << "ENTER BEFORE WHICH ELEMENT THE NEW WLEMENT SHOULD BE ADDED" << endl;
            cin >> tempitem;
            p = searchFunc(tempitem, start);
            temp = insBefore(item, p, start);
            if (temp != NULL)
                start = temp;
            break;
        case 4:
            cout << "ENTER ELEMENT TO BE ADDED" << endl;
            cin >> item;
            cout << "ENTER AFTER WHICH ELEMENT THE NEW ELEMENT SHOULD BE ADDED" << endl;
            cin >> tempitem;
            p = searchFunc(tempitem, start);
            insAfter(item, p);
            break;
        case 5:
            display(start);
            break;
        case 6:
            start = deleteFirst(start);
            break;
        case 7:
            start = deleteLast(start);

            break;
        case 8:
            cout << "ENTER THE ELEMENT AFTER WHICH THE NEXT ELEMENT HAS TO BE DELETED" << endl;
            cin >> tempitem;
            p = searchFunc(tempitem, start);
            deleteAfter(p);
            break;
        case 9:
            cout << "ENTER THE ELEMENT BEFORE WHICH THE ELEMENT HAS TO BE DELETED" << endl;
            cin >> tempitem;
            p = searchFunc(tempitem, start);
            start = deleteBefore(start, p);
        default:
            cout << "INVALID CHOICE" << endl;
        }
    }
}
nodeptr getNode(int item)
{
    nodeptr p;
    p = (nodeptr)malloc(sizeof(struct node));
    p->data = item;
    p->next = NULL;
    p->prev = NULL;
    return p;
}
nodeptr insFirst(int item, nodeptr start)
{
    nodeptr p;
    p = getNode(item);
    if (p == NULL)
        cout << "VOID INSERTION" << endl;
    else
    {
        p->next = start;
        start = p;
    }
    return start;
}
void insLast(int item, nodeptr start)
{
    nodeptr p = getNode(item);
    nodeptr q = start;
    if (p == NULL)
        cout << "VOID INSERTION" << endl;

    else
    {
        while (q->next != NULL)
            q = q->next;
        q->next = p;
        p->prev = q;
    }
}
void display(nodeptr start)
{
    nodeptr p = start;
    if (start == NULL)
        cout << "LIST IS EMPTY" << endl;
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}
void insAfter(int item, nodeptr p)
{
    if (p == NULL)
        cout << "NO SUCH ELEMENT FOUND" << endl;

    else
    {
        nodeptr q = getNode(item);
        if (q == NULL)
            cout << "VOID INSERTION" << endl;
        else
        {
            q->next = p->next;
            p->next = q;
            q->prev = p;
            //updating the prev pointer of the node after the new inserted node(IF IT EXISTS)
            if (q->next != NULL)
            {
                q = q->next;
                q->prev = p->next;
            }
        }
    }
}
nodeptr insBefore(int item, nodeptr p, nodeptr start)
{
    if (p == NULL)
        cout << "NO SUCH ELEMENT FOUND" << endl;

    else
    {
        nodeptr q = getNode(item);
        nodeptr r;
        if (q == NULL)
            cout << "VOID INSERTION" << endl;

        else
        {
            if (p != start)
            {
                q->prev = p->prev;
                r = q->prev;
                r->next = q;
            }
            else
                start = q;
            q->next = p;
            p->prev = q;
        }
    }
    return start;
}
nodeptr searchFunc(int tempitem, nodeptr start)
{
    nodeptr p = start;
    while (p != NULL && p->data != tempitem)
        p = p->next;
    return p;
}
nodeptr deleteFirst(nodeptr start)
{
    if (start == NULL)
        cout << "UNDERFLOW" << endl;
    else
    {
        nodeptr p = start;
        start->prev = NULL;
        start = start->next;
        cout << p->data << " HAS BEEN DELETED" << endl;
        free(p);
    }
    return start;
}
nodeptr deleteLast(nodeptr start)
{
    int item;
    if (start == NULL)
        cout << "UNDERFLOW" << endl;
    else
    {
        nodeptr p = start;
        while (p->next != NULL)
            p = p->next;
        if (p->prev != NULL)
            (p->prev)->next = NULL;
        else
            start = NULL;
        cout << p->data << " HAS BEEN DELETED" << endl;
        free(p);
    }
    return start;
}
void deleteAfter(nodeptr p)
{
    if (p == NULL)
        cout << "NO SUCH ELEMENT FOUND" << endl;
    else
    {
        nodeptr q = p->next;
        if (q == NULL)
            cout << "THIS IS THE LAST ELEMENT.NO ELEMENT AHEAD" << endl;
        else
        {
            if (q->next == NULL)
            {
                p->next = NULL;
                cout << q->data << " HAS BEEN DELETED" << endl;
                free(q);
            }
            else
            {
                (q->next)->prev = q->prev;
                p->next = q->next;
                cout << q->data << " HAS BEEN DELETED" << endl;
                free(q);
            }
        }
    }
}
nodeptr deleteBefore(nodeptr start, nodeptr p)
{
    if (p == NULL)
        cout << "NO SUCH ELEMENT EXISTS" << endl;
    else
    {
        nodeptr q = p->prev;
        if (q == NULL)
            cout << "NO ELEMENT BEFORE THIS.THIS IS THE FIRST ITEM IN THE LIST" << endl;
        else
        {
            if (q->prev == NULL)
            {
                p->prev = NULL;
                cout << q->data << " HAS BEEN DELETED" << endl;
                free(q);
            }
            else
            {
                (q->prev)->next = p;
                p->prev = q->prev;
                cout << q->data << " HAS BEEN DELETED" << endl;
                free(q);
            }
        }
    }
    return start;
}
