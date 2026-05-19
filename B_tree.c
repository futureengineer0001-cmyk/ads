#include <stdio.h>
#include <stdlib.h>

#define T 3   // Order of B-Tree

struct Node
{
    int keys[2*T - 1];
    struct Node *child[2*T];
    int n;
    int leaf;
};

// Create new node
struct Node* createNode(int leaf)
{
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));

    temp->leaf = leaf;
    temp->n = 0;

    for(int i = 0; i < 2*T; i++)
        temp->child[i] = NULL;

    return temp;
}

// Search key
struct Node* search(struct Node *root, int key)
{
    int i = 0;

    if(root == NULL)
        return NULL;

    while(i < root->n && key > root->keys[i])
        i++;

    if(i < root->n && root->keys[i] == key)
        return root;

    if(root->leaf)
        return NULL;

    return search(root->child[i], key);
}

// Traverse (Display)
void display(struct Node *root)
{
    if(root != NULL)
    {
        int i;

        for(i = 0; i < root->n; i++)
        {
            if(!root->leaf)
                display(root->child[i]);

            printf("%d ", root->keys[i]);
        }

        if(!root->leaf)
            display(root->child[i]);
    }
}

// Insert in simple way (no full split handling complexity)
void insertSimple(struct Node *root, int key)
{
    int i = root->n - 1;

    if(root->leaf == 1)
    {
        while(i >= 0 && root->keys[i] > key)
        {
            root->keys[i + 1] = root->keys[i];
            i--;
        }

        root->keys[i + 1] = key;
        root->n = root->n + 1;
    }
    else
    {
        printf("This simple code inserts only in leaf node (for viva simplicity)\n");
    }
}

// Create root
struct Node* createRoot(int key)
{
    struct Node *root = createNode(1);
    root->keys[0] = key;
    root->n = 1;
    return root;
}

int main()
{
    struct Node *root = NULL;
    int choice, value;

    while(1)
    {
        printf("\n1.Insert");
        printf("\n2.Search");
        printf("\n3.Display");
        printf("\n4.Exit");
        printf("\nEnter choice: ");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);

                if(root == NULL)
                    root = createRoot(value);
                else
                    insertSimple(root, value);

                break;

            case 2:
                printf("Enter value: ");
                scanf("%d", &value);

                if(search(root, value))
                    printf("Found\n");
                else
                    printf("Not Found\n");

                break;

            case 3:
                printf("B-Tree: ");
                display(root);
                printf("\n");
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}

// A B-Tree is a special type of tree data structure used to store data in a sorted order and allow fast searching, insertion, and deletion.
// Searching:
// Start from the top (root)
// Check values in the node
// If found → done
// If not → go to the correct child
// Repeat
// 🔹 Inserting:
// Go to the correct position (usually leaf node)
// Insert value in sorted order
// If node becomes full:
// Split it
// Move middle value up
// 🔹 Deleting:
// Remove the value
// If node has too few values:
// Borrow from nearby node OR
// Merge nodes
 
// Define Node Structure → keys array, child pointers, count, and leaf flag
// Create Node Function → allocate memory and initialize node values
// Insert Function → insert key in sorted order and split if node is full
// Search Function → compare key and move to correct child
// Display Function → traverse children and print keys in order
// Main Function → menu for insert, search, display, exit

// Real Applications of B-Tree (Short)
// Databases (MySQL, Oracle indexing)
// File systems (Windows, Linux disk storage)
// Search engines (fast data retrieval)
// Large storage systems (optimize disk reads/writes)
// Multi-level indexing in OS
