#include <stdio.h>
#include <malloc.h>

struct node {
	int key;
	char *data;
	struct node *prev;
	struct node *next;
};

struct node *first = NULL;
struct node *last = NULL;

struct node *create_node(int key, char *d) {
	struct node *new = (struct node *) malloc(sizeof(struct node));

	new->key = key;
	new->data = d;
	new->next = new->prev = NULL;
}

void append(int key, char *data) {
	if(first==NULL) {
		first = last = create_node(key,data);
	} else {
		last->next = create_node(key,data);
		last->next->prev = last;
		last = last->next;
	}
}

void traverse() {
	struct node *ptr = first;

	if(first==NULL) {
		printf("\nList is empty!");
		return;
	}

	printf("\nMain Node addresses: first:%0x , last: %0x",first,last);
	printf("\nID	DATA	CURRENT		PREV	NEXT");
	printf("\n---------------------------------------------");
	while(ptr!=NULL) {
		printf("\n%d\t%s\t%0x\t\t%0x\t%0x",ptr->key,ptr->data,ptr,ptr->prev,ptr->next);
		ptr=ptr->next;
	}
	printf("\n");
}

void prepend(int key, char *data) {
	struct node *new = create_node(key,data);

	if(first==NULL) {
		first = last = create_node(key,data);
	} else {
		new->next = first;
		first->prev = new;
		first = new;
	}
}

void clear() {
	struct node *ptr = first;

	while(ptr!=NULL) {
		struct node *next = ptr->next;

		free(ptr);

		ptr = next;
	}

	first = last = NULL;
}

// TEST RUN
void main(int argc, char *argv) {
	printf("\nCreating Double Linked List...");
	append(1,"Red");
	append(3,"Green");
	append(4,"Yellow");
	append(5,"Black");
	append(6,"White");	

	printf("\nTraversing....");
	traverse();

	printf("\nPrepending 2 nodes...");
	prepend(9,"Orange");
	prepend(10,"Violet");
	printf("\nTraversing....");
	traverse();

	printf("\nClearing entire list...");
	clear();
	traverse();

	return;
}
