/******************************************************************************************
* PROGRAM: linkedlist.c
* DESCRIPTION: Single Linked List Functions
* AUTHOR: Vijay Natrajan
* MODIFIED: June 20, 2022
* CREATED: June 20, 2022
* VERSION: 0.1.0
*******************************************************************************************/ 

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

// STRUCT node holds string data
struct node {
    char *data;
    struct node *next;
};

// POINTERS TO FIRST AND LAST NODES
struct node *first = NULL;
struct node *last = NULL;

// CREATE A NEW NODE
struct node *create_node(char *d) {
    struct node *new = NULL;
    
    new = (struct node *) malloc(sizeof(struct node));
    new->data = d;
    new->next = NULL;

    return new;
}

// ADD A NODE TO THE END OF THE LIST
void append_node(char *data) {
    struct node *new = create_node(data);

    if(first==NULL) {               // LIST IS EMPTY - ADD FIRST NODE
        first = last = new;
    } else if(first == last) {      // LIST HAS 1 ELEMENT - ADD AFTER LAST
        first->next = new;
        last = new;
    } else                          // LIST HAS 2 OR MORE - ADD AFTER LAST
        last->next = new;
}

// ADD A NODE BEFORE THE FIRST NODE
void prepend_node(char *data) {
    struct node *new = create_node(data);

    if(first==NULL) {               // LIST IS EMPTY - ADD FIRST NODE
        first = last = new;
    } else {
        new->next = first;          // LIST HAS 1 OR MORE - ADD BEFORE FIRST
        first = new;
    }
}

// FIND NODE
struct node *find_node(char *data) {
    struct node *ptr = first;

    while(ptr!=NULL) {                      // TRAVERSE LIST FROM first to last
        if(strcmp(data,ptr->data)==0) {     // DATA MATCHES
            return ptr;
        }

        ptr = ptr->next;
    }

    return ptr;
}

// FIND SECOND-LAST NODE
struct node *find_second_last() {
    struct node *ptr = first;

    while(ptr->next->next!=NULL) {         // TRAVERSE AND FIND 2nd LAST
        ptr = ptr->next;
    }

    return ptr;
}

// FIND PREVIOUS NODE OF CURRENT NODE
struct node *find_prev(struct node *current) {
    struct node *ptr = first; 

    while(ptr->next!=current) {             // TRAVERSE AND FIND PREV OF CURRENT
        ptr = ptr->next;
    }

    return ptr;
}

// DELETE A NODE BASED ON MATCHING DATA
bool delete_node(char *data) {
    struct node *match = find_node(data);                               // FIND NODE BASED ON data

    if(match==NULL) {                                                   // NO MATCH
        printf("\nNo such string: %s - Cannot delete!",data);
        return false;
    } else {
        if(first==last && first==match) {                               // SINGLE ITEM IN LIST
            free(match);
            first = last = NULL;
            return true;
        } else if(first!=last) {                                        // 2 OR MORE ITEMS IN LIST
            if(match==first) {  
                first = first->next;                                    // DELETE FIRST ITEM
                free(match);
                return true;
            } else if(match==last) {
                struct node *newlast = find_second_last();              // DELETE LAST ITEM
                last = newlast;
                free(last->next);
                last->next=NULL;
                return true;
            } else if(match!=first && match!=last) {                    // IN BETWEEN                          
                struct node *prev = find_prev(match);
                prev->next = match->next;
                free(match);
                return true;
            }
        }
    }
}

void print() {
    struct node *ptr = first;

    if(ptr==NULL) {
        printf("\nCannot print-list is empty");
        return;
    }

    do {
        printf("\n%s",ptr->data);
        ptr = ptr->next;
    } while(ptr!=NULL);
}

void main(int arc, char *arv) {
    printf("\nCreating nodes....");

    append_node("Vijay");
    append_node("Ajay");
    append_node("Rajesh");
    prepend_node("Vikas");
    prepend_node("Neha");

    printf("\nPrinting Nodes....");
    print();

    printf("\nDeleting 'Vijay'...");
    delete_node("Vijay");
    printf("\nAfter deleting....");
    print();
    printf("\nDeleting 'Ajay'...");
    delete_node("Ajay");
    print();
    delete_node("Rahul");
    delete_node("Vikas");
    delete_node("Neha");
    delete_node("Ajay");
    print();
}