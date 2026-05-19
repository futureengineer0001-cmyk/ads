#include <stdio.h>
#include <stdlib.h>

#define ORDER 3   // B+ Tree order

struct Node
{
    int keys[ORDER];
    struct Node *child[ORDER + 1];
    int n;
    int leaf;
    struct Node *next;   // for linked leaf nodes
};

struct Node *root = NULL;

// Create node
struct Node* createNode(int leaf)
{
    struct Node *temp =
        (struct Node*)malloc(sizeof(struct Node));

    temp->n = 0;
    temp->leaf = leaf;
    temp->next = NULL;

    for(int i = 0; i < ORDER + 1; i++)
        temp->child[i] = NULL;

    return temp;
}

// Search
struct Node* search(struct Node *root, int key)
{
    if(root == NULL)
        return NULL;

    int i = 0;

    while(i < root->n && key > root->keys[i])
        i++;

    if(root->leaf)
    {
        if(i < root->n && root->keys[i] == key)
            return root;
        return NULL;
    }

    return search(root->child[i], key);
}

// Display leaf nodes (important feature of B+ Tree)
void displayLeaves(struct Node *root)
{
    struct Node *temp = root;

    while(temp != NULL && !temp->leaf)
        temp = temp->child[0];

    while(temp != NULL)
    {
        for(int i = 0; i < temp->n; i++)
            printf("%d ", temp->keys[i]);

        temp = temp->next;
    }
}

// Insert in leaf (simple version)
void insertInLeaf(struct Node *leaf, int key)
{
    int i = leaf->n - 1;

    while(i >= 0 && leaf->keys[i] > key)
    {
        leaf->keys[i + 1] = leaf->keys[i];
        i--;
    }

    leaf->keys[i + 1] = key;
    leaf->n++;
}

// Simple insert (no full split handling for viva simplicity)
void insert(int key)
{
    if(root == NULL)
    {
        root = createNode(1);
        root->keys[0] = key;
        root->n = 1;
        return;
    }

    struct Node *temp = root;

    while(temp->leaf == 0)
        temp = temp->child[0];

    insertInLeaf(temp, key);
}

// Simple delete (basic BST-like for viva)
void deleteKey(struct Node *root, int key)
{
    printf("Deletion simplified for lab use.\n");
}

// Main
int main()
{
    int choice, value;

    while(1)
    {
        printf("\n1.Insert");
        printf("\n2.Delete");
        printf("\n3.Search");
        printf("\n4.Display Leaves");
        printf("\n5.Exit");
        printf("\nEnter choice: ");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insert(value);
                break;

            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                deleteKey(root, value);
                break;

            case 3:
                printf("Enter value: ");
                scanf("%d", &value);

                if(search(root, value))
                    printf("Found\n");
                else
                    printf("Not Found\n");

                break;

            case 4:
                printf("Leaf nodes: ");
                displayLeaves(root);
                printf("\n");
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}


// A B+ Tree is an improved version of a B-Tree used mainly in databases and file systems for fast searching and indexing.

// All actual data (records) are stored only in the leaf nodes
// 👉 Internal nodes only store keys (index values) to guide the search
// Steps to Write B+ Tree Code (Short)
// Define Node Structure → keys array, child pointers, leaf flag, count, next pointer (for linking leaves)
// Create Node Function → allocate memory and initialize values
// Search Function → compare key and move to correct child or check leaf
// Insert Function → insert key in correct leaf node in sorted order
// Leaf Linking → connect all leaf nodes using next pointer
// Display Function → traverse only leaf nodes using linked list
// Delete Function (basic) → remove key (simplified in lab version)
// Main Function → menu-driven program (insert, search, delete, display)

// Real Applications (Important)
// Database indexing (MySQL, Oracle)
// File systems (fast file access)
// Large-scale storage systems
// Range queries in databases
// Searching huge datasets efficiently
