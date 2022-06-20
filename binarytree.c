/******************************************************************************************
* PROGRAM: binarytree.c
* DESCRIPTION: Binary Tree Implementation
* AUTHOR: Vijay Natrajan
* MODIFIED: June 20, 2022
* CREATED: June 20, 2022
* VERSION: 0.1.0
*******************************************************************************************/ 

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

// STRUCT node holds integer key and string data
struct node {
    int key;
    char *data;
    struct node *left;
    struct node *right;
};

// POINTERS TO FIRST AND LAST NODES
struct node *root = NULL;

// CREATE A B-TREE NODE
struct node *create_node(int key, char *data) {
    struct node *new = NULL;
    
    new = (struct node *) malloc(sizeof(struct node));
    new->key = key;
    new->data = data;
    new->left = new->right = NULL;

    return new;
}

void append_node(struct node *new, struct node *ptr) {
    if(ptr==NULL) {
        return;
    }

    if(new->key <= ptr->key && ptr->left==NULL) {                                   // B-TREE IS EMPTY - ADD FIRST NODE
        ptr->left=new;
        return;
    } else if(new->key > ptr->key && ptr->right==NULL) {
        ptr->right=new;
        return;
    }

    if(new->key <= ptr->key && ptr->left!=NULL) {
        append_node(new,ptr->left);
    } else if(new->key > ptr->key & ptr->right!=NULL) {
        append_node(new,ptr->right);
    }
}

void add(int key, char *data) {
    struct node *new = (struct node*) malloc(sizeof(struct node));
    new->key = key;
    new->data = data;

    if(root==NULL) {
        root = new;
        return;
    }

    append_node(new,root);
}

// BFS TRAVERSAL FOR B-TREE
void traverse(int level, struct node *ptr) {
    if(ptr==NULL) {
        return;
    }

    printf("\n[Level:%2d]-%3d:%s\n",level,ptr->key,ptr->data);

    traverse(++level,ptr->left);
    traverse(++level,ptr->right);
}

void main(int argc, char *argv) {
    // Create a B-Tree
    add(10,"Vijay");
    add(5,"Ajay");
    add(3,"Ram");
    add(7,"Shyam");
    add(20,"Sundar");
    add(2,"Rahul");
    add(9,"John");
    add(25,"Preeti");

    // Traverse
    traverse(0,root);
}