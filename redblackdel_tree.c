#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    char color;
    struct node *left, *right, *parent;
};

struct node *root = NULL;

// Create node
struct node* createNode(int value)
{
    struct node *newNode;

    newNode = (struct node*)malloc(sizeof(struct node));

    newNode->data = value;
    newNode->color = 'R'; // New node red
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    return newNode;
}

// Insert node
struct node* insert(struct node *root, int value)
{
    if(root == NULL)
    {
        struct node *temp = createNode(value);
        temp->color = 'B'; // Root always black
        return temp;
    }

    if(value < root->data)
    {
        root->left = insert(root->left, value);
    }
    else if(value > root->data)
    {
        root->right = insert(root->right, value);
    }

    return root;
}

// Find minimum value node
struct node* minNode(struct node *temp)
{
    while(temp->left != NULL)
    {
        temp = temp->left;
    }

    return temp;
}

// Delete node
struct node* deleteNode(struct node *root, int value)
{
    if(root == NULL)
    {
        return root;
    }

    if(value < root->data)
    {
        root->left = deleteNode(root->left, value);
    }

    else if(value > root->data)
    {
        root->right = deleteNode(root->right, value);
    }

    else
    {
        // Node with one child or no child
        if(root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }

        else if(root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        struct node *temp = minNode(root->right);

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// Display tree
void inorder(struct node *root)
{
    if(root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main()
{
    int choice, value;

    while(1)
    {
        printf("\n1. Insert");
        printf("\n2. Delete");
        printf("\n3. Display");
        printf("\n4. Exit");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);

                root = insert(root, value);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);

                root = deleteNode(root, value);
                break;

            case 3:
                printf("Tree: ");
                inorder(root);
                printf("\n");
                break;

            case 4:
                exit(0);

            default:
                printf("Wrong choice");
        }
    }

    return 0;
}


// Steps to Write Code (Short)
// Create node structure (data, color, left, right, parent)
// Write function to create a new node (color = Red)
// Insert node using BST logic
// Apply balancing rule (keep root black, maintain properties)
// Write delete function (BST deletion cases)
// Write inorder traversal for display
// Add menu in main function

// Applications (Short)
// Database indexing
// Linux process scheduling
// C++ STL (map, set)
// Fast searching & sorting
// Memory management systems