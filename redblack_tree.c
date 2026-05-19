#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    char color;
    struct Node *left, *right, *parent;
};

struct Node *root = NULL;

// Create node
struct Node* createNode(int data) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->color = 'R'; // New node is Red
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Left Rotate
void leftRotate(struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Right Rotate
void rightRotate(struct Node *x) {
    struct Node *y = x->left;
    x->left = y->right;

    if (y->right != NULL)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

// Fix tree after insertion
void fixInsert(struct Node *node) {

    while (node != root &&
           node->parent->color == 'R') {

        struct Node *parent = node->parent;
        struct Node *grandparent = parent->parent;

        // Parent is left child
        if (parent == grandparent->left) {

            struct Node *uncle = grandparent->right;

            // Recoloring
            if (uncle != NULL &&
                uncle->color == 'R') {

                parent->color = 'B';
                uncle->color = 'B';
                grandparent->color = 'R';
                node = grandparent;
            }
            else {
                // Rotation
                if (node == parent->right) {
                    leftRotate(parent);
                    node = parent;
                    parent = node->parent;
                }

                rightRotate(grandparent);
                parent->color = 'B';
                grandparent->color = 'R';
            }
        }

        // Parent is right child
        else {

            struct Node *uncle = grandparent->left;

            // Recoloring
            if (uncle != NULL &&
                uncle->color == 'R') {

                parent->color = 'B';
                uncle->color = 'B';
                grandparent->color = 'R';
                node = grandparent;
            }
            else {

                // Rotation
                if (node == parent->left) {
                    rightRotate(parent);
                    node = parent;
                    parent = node->parent;
                }

                leftRotate(grandparent);
                parent->color = 'B';
                grandparent->color = 'R';
            }
        }
    }

    root->color = 'B';
}

// Insert
void insert(int data) {

    struct Node *newNode = createNode(data);
    struct Node *temp = root;
    struct Node *parent = NULL;

    // BST insert
    while (temp != NULL) {
        parent = temp;

        if (data < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }

    newNode->parent = parent;

    if (parent == NULL)
        root = newNode;
    else if (data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    fixInsert(newNode);
}

// Search
void search(struct Node *root, int key) {

    if (root == NULL) {
        printf("Not Found\n");
        return;
    }

    if (root->data == key) {
        printf("Found\n");
        return;
    }

    if (key < root->data)
        search(root->left, key);
    else
        search(root->right, key);
}

// Inorder display
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d(%c) ", root->data, root->color);
        inorder(root->right);
    }
}

int main() {

    int choice, value;

    while (1) {

        printf("\n1.Insert");
        printf("\n2.Search");
        printf("\n3.Display");
        printf("\n4.Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter value: ");
            scanf("%d", &value);
            insert(value);
            break;

        case 2:
            printf("Enter key: ");
            scanf("%d", &value);
            search(root, value);
            break;

        case 3:
            printf("Tree: ");
            inorder(root);
            printf("\n");
            break;

        case 4:
            exit(0);

        default:
            printf("Invalid Choice");
        }
    }

    return 0;
}

// Steps to Write Red-Black Tree Code (Short)
// Create Node Structure → data, color, left, right, parent
// Create Node Function → make new node (Red color)
// Write Rotations → Left Rotate & Right Rotate
// BST Insertion → insert node like normal BST
// Fix Tree → use recoloring & rotations if imbalance occurs
// Search Function → find key in tree
// Display Function → inorder traversal
// Main Function → menu for insert, search, display

// Applications (Short)
// Database indexing
// Linux scheduler
// C++ map & set
// Fast searching and sorting
// Memory management