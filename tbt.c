#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left, *right;
    int lthread, rthread;
};

struct node *root = NULL;

// Create node
struct node* create(int value)
{
    struct node *newnode;

    newnode = (struct node*)malloc(sizeof(struct node));

    newnode->data = value;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->lthread = 1;
    newnode->rthread = 1;

    return newnode;
}

// Insert node
void insert(int value)
{
    struct node *ptr = root;
    struct node *parent = NULL;

    while (ptr != NULL)
    {
        parent = ptr;

        if (value < ptr->data)
        {
            if (ptr->lthread == 0)
                ptr = ptr->left;
            else
                break;
        }
        else
        {
            if (ptr->rthread == 0)
                ptr = ptr->right;
            else
                break;
        }
    }

    struct node *newnode = create(value);

    // First node
    if (parent == NULL)
    {
        root = newnode;
    }

    // Insert left
    else if (value < parent->data)
    {
        newnode->left = parent->left;
        newnode->right = parent;

        parent->lthread = 0;
        parent->left = newnode;
    }

    // Insert right
    else
    {
        newnode->left = parent;
        newnode->right = parent->right;

        parent->rthread = 0;
        parent->right = newnode;
    }
}

// Inorder traversal
void inorder()
{
    struct node *ptr = root;

    if (root == NULL)
    {
        printf("Tree is empty");
        return;
    }

    while (ptr->lthread == 0)
        ptr = ptr->left;

    printf("\nInorder Traversal: ");

    while (ptr != NULL)
    {
        printf("%d ", ptr->data);

        if (ptr->rthread == 1)
            ptr = ptr->right;
        else
        {
            ptr = ptr->right;
            while (ptr != NULL && ptr->lthread == 0)
                ptr = ptr->left;
        }
    }
}

// Preorder traversal
void preorder()
{
    struct node *ptr = root;

    printf("\nPreorder Traversal: ");

    while (ptr != NULL)
    {
        printf("%d ", ptr->data);

        if (ptr->lthread == 0)
            ptr = ptr->left;
        else if (ptr->rthread == 0)
            ptr = ptr->right;
        else
        {
            while (ptr != NULL && ptr->rthread == 1)
                ptr = ptr->right;

            if (ptr != NULL)
                ptr = ptr->right;
        }
    }
}

// Main function
int main()
{
    int n, value, i;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Enter value: ");
        scanf("%d", &value);

        insert(value);
    }

    inorder();
    preorder();

    return 0;
}


// THREADDED BINARY TREE (TBT)

// Definition:
// A Threaded Binary Tree is a binary tree where NULL pointers
// are replaced by threads to store inorder predecessor or successor.
// It allows traversal without recursion and stack.

// Purpose:
// To perform inorder and preorder traversal without stack or recursion.

// Thread Meaning:
// lthread = 1 -> left pointer is thread
// lthread = 0 -> left pointer is child

// rthread = 1 -> right pointer is thread
// rthread = 0 -> right pointer is child

// Traversals:
// 1. Inorder  -> Left -> Root -> Right
// 2. Preorder -> Root -> Left -> Right

// Steps of Program:
// 1. Create node structure
// 2. Create new node
// 3. Insert node into TBT
// 4. Perform inorder traversal
// 5. Perform preorder traversal

// Time Complexity:
// Insertion         = O(n)
// Inorder Traversal = O(n)
// Preorder Traversal = O(n)
// Space Complexity  = O(n)

// Advantages:
// 1. No recursion required
// 2. No stack needed
// 3. Faster traversal
// 4. Better use of NULL pointers

// Disadvantages:
// 1. Insertion is complex
// 2. Deletion is difficult
// 3. More pointer handling

// Applications:
// 1. Fast tree traversal
// 2. Database indexing
// 3. Expression trees
// 4. Memory efficient traversal
// // 